#include "sysctl.h"
#include "dma.h"

// #define EN_UART_UPDATA // boot 串口烧录支持

#ifdef EN_UART_UPDATA

#include "sci.h"
#include "gpio.h"
#include "flash.h"

static void putchar(char c)
{
    while (!SciaRegs.LSR.bit.THRE) // wait send empty
        ;
    SciaRegs.THR = c;
    while (!SciaRegs.LSR.bit.TEMT) // wait send finish
        ;
}

void SCI_readCharArray(volatile struct SCI_REGS *sci, void *array, u32 len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        while (!sci->LSR.bit.DR)
            ;
        *((u8 *)array + i) = (u8)(sci->RBR);
    }
}

/*======================= Xmodem start ================================*/

/* Xmodem (128 bytes) packet format
 * Byte  0:       Header
 * Byte  1:       Packet number
 * Byte  2:       Packet number complement
 * Bytes 3-130:   Data
 * Bytes 131-132: CRC
 */

/* Xmodem (1024 bytes) packet format
 * Byte  0:         Header
 * Byte  1:         Packet number
 * Byte  2:         Packet number complement
 * Bytes 3-1026:    Data
 * Bytes 1027-1028: CRC
 */

#define X_MAX_ERRORS ((u8)3u)

/* Bytes defined by the protocol. */
#define X_SOH ((u8)0x01u) /**< Start Of Header (128 bytes). */
#define X_STX ((u8)0x02u) /**< Start Of Header (1024 bytes). */
#define X_EOT ((u8)0x04u) /**< End Of Transmission. */
#define X_ACK ((u8)0x06u) /**< Acknowledge. */
#define X_NAK ((u8)0x15u) /**< Not Acknowledge. */
#define X_CAN ((u8)0x18u) /**< Cancel. */
#define X_C   ((u8)0x43u) /**< ASCII "C" to notify the host we want to use CRC16. */

/* Status report for the functions. */
typedef enum
{
    X_OK           = 0x00u, /**< The action was successful. */
    X_ERROR_CRC    = 0x01u, /**< CRC calculation error. */
    X_ERROR_NUMBER = 0x02u, /**< Packet number mismatch error. */
    X_ERROR_UART   = 0x04u, /**< UART communication error. */
    X_ERROR_FLASH  = 0x08u, /**< Flash related error. */
    X_ERROR        = 0xFFu  /**< Generic error. */
} xmodem_status;

static u16 xmodem_calc_crc(u8 *data, u16 length)
{
    u16 crc = 0u;
    while (length)
    {
        length--;
        crc = crc ^ ((u16)*data++ << 8u);
        for (u8 i = 0u; i < 8u; i++)
        {
            if (crc & 0x8000u)
                crc = (crc << 1u) ^ 0x1021u;
            else
                crc = crc << 1u;
        }
    }
    return crc;
}

static xmodem_status xmodem_error_handler(u8 *error_number, u8 max_error_number)
{
    xmodem_status status = X_OK;
    (*error_number)++;
    if ((*error_number) >= max_error_number)
    { /* Graceful abort. */
        putchar(X_CAN);
        putchar(X_CAN);
        status = X_ERROR;
    }
    else
    { /* Otherwise send a NAK for a repeat. */
        putchar(X_NAK);
        status = X_OK;
    }
    return status;
}

static void xmodem_recv_and_program(void)
{
    int i                     = 0;
    xmodem_status status      = X_OK;
    u32 flash_program_addr    = 0x3000000u;
    u8 error_number           = 0;
    u8 first_packet_recv_flag = 0;
    u32 xmodem_packet_number  = 1;
    u8 header                 = 0;
    u16 size                  = 0;
    u16 crc_received          = 0;
    u16 crc_calculated        = 0;

    u8 packet_number[2];
    u8 packet_data[1024];
    u8 packet_crc[2];

    while (1)
    {
        if (first_packet_recv_flag == 0 || status != X_OK)
        {
            status               = X_OK;
            flash_program_addr   = 0x3000000u;
            error_number         = 0;
            xmodem_packet_number = 1;

            while (!SciaRegs.LSR.bit.DR)
            {
                // if (i++ == 100000)
                //{
                putchar(X_C);
                putchar('\n');
                putchar('\r');
                i = 0;
                //};
            }

            header = (u8)(SciaRegs.THR);
        }
        else
        {
            while (!SciaRegs.LSR.bit.DR)
                ;
            header = (u8)(SciaRegs.THR);
        }

        switch (header) /* The header can be: SOH, STX, EOT and CAN. */
        {
            case X_SOH:
            case X_STX:
            {
                if (X_SOH == header)
                    size = 128;
                else if (X_STX == header)
                    size = 1024;

                SCI_readCharArray(&SciaRegs, packet_number, 2);
                SCI_readCharArray(&SciaRegs, packet_data, size);
                SCI_readCharArray(&SciaRegs, packet_crc, 2);

                crc_received   = ((u16)packet_crc[0] << 8u) | ((u16)packet_crc[1]);
                crc_calculated = xmodem_calc_crc(packet_data, size);

                if (xmodem_packet_number != packet_number[0]
                    || 255u != (packet_number[0] + packet_number[1]))
                    status |= X_ERROR_NUMBER;
                if (crc_calculated != crc_received)
                    status |= X_ERROR_CRC;

                if (X_OK == status)
                {
                    if (first_packet_recv_flag == 0)
                    {
                        // Flash chip erase
                        while (Flash0CtrlRegs.STATUS.bit.WIP)
                            ;
                        while (Flash0CtrlRegs.ERASE & 0x20000000) // wait NO BUSY
                            ;
                        /* ERASE register need write with 32 bit by once */
                        Flash0CtrlRegs.ERASE = 0x90000000 | FLASH_ERASE_CHIP << 25;
                        while (Flash0CtrlRegs.ERASE & 0x80000000) // wait ERASE Finish
                            ;
                        first_packet_recv_flag = 1;
                    }

                    for (i = 0; i < size / 4; i++)
                        HWREG(flash_program_addr + i * 4) = *((u32 *)(packet_data + i * 4));

                    xmodem_packet_number++;
                    flash_program_addr += size;
                    putchar(X_ACK);
                }
                else
                    status = xmodem_error_handler(&error_number, X_MAX_ERRORS);
                break;
            }
            case X_EOT: /* End of Transmission. */
                /* ACK, feedback to user (as a text), then jump to user application. */
                putchar(X_ACK);
                return;
            case X_CAN: /* Abort from host. */
                first_packet_recv_flag = 0;
                status                 = X_ERROR;
                break;
            default: /* Wrong header. */
                status = xmodem_error_handler(&error_number, X_MAX_ERRORS);
                break;
        }
    }
}
/*======================= Xmodem END ================================*/
#endif

static inline void copy_trim()
{
    HWREG(REGFILE_BASE + 0x24) = 0x55AA55AA; // unlock trim

    // copy trim data
    HWREG(REGFILE_BASE + 0) = *((uint32_t *)(FLASH0OTP1_BASE + 0));
    HWREG(REGFILE_BASE + 4) = *((uint32_t *)(FLASH0OTP1_BASE + 4));
    HWREG(REGFILE_BASE + 8) = *((uint32_t *)(FLASH0OTP1_BASE + 8));

    HWREG(REGFILE_BASE + 0x20) = 1;          // enable efuse
    HWREG(REGFILE_BASE + 0x24) = 0xAA55AA55; // lock trim
}

/* start addresses for DSP text/data image and their length information
 * Their values are from flash image generation script of file 'gen_flash_image.py'
 */
#define DSP_IMAGE_START_ADDR      (0x30002400U)
#define DSP_IMAGE_INFO_START_ADDR (0x30002000U)

#define DMA_LENGTH (256)

static void dma_read(int src_addr, int dst_addr, int len)
{
    int tempSrc = src_addr;
    int tempDst = dst_addr;

    do
    {
        // 每次用DMA传输256字节
        DmaCh1Regs.SAR = tempSrc;
        DmaCh1Regs.DAR = tempDst;
        DmaRegs.CHEN   = 0x0101; // DMA CH1 启动

        while (!(DmaCh1Regs.INTSTATUS & 0x02)) // 等待结束中断标志位
            ;
        DmaCh1Regs.INTCLEAR = 0x02; // 清除结束中断标志位

        tempSrc = tempSrc + DMA_LENGTH;
        tempDst = tempDst + DMA_LENGTH;
        len     = len - DMA_LENGTH;

    } while (len > 0);
}

extern u32 _CORE0_CODE_ENTRY;
extern u32 _CORE0_IRAM_START;
extern u32 _CORE0_DRAM_START;
extern u32 _CORE1_IRAM_START;
extern u32 _CORE1_DRAM_START;

extern void _dsp_boot_jmp_to_core0(int);

// bit[17:15] of _CORE<n>_IRAM_START
#define CPU_EXP_START_MASK (0x7)
#define CPU_EXP_START_OFST (15)

_Noreturn void qx_bootloader_main(void)
{
    // copy trim data from flash OTP area to regfile
    //copy_trim();

    // set CPU interrupt vector table IRAM bank, [0,7]
    CpuSysRegs.CPU0EXPSTART.bit.EXPSTART
        = ((int)(&_CORE0_IRAM_START) >> CPU_EXP_START_OFST) & CPU_EXP_START_MASK;
    CpuSysRegs.CPU1EXPSTART.bit.EXPSTART
        = ((int)(&_CORE1_IRAM_START) >> CPU_EXP_START_OFST) & CPU_EXP_START_MASK;

    NmiIntruptRegs.NMICFG.bit.NMIE = 1; // 使能全局NMI中断

    // 注意:
    // 1. ECC DMEM 校验和检错功能必须在boot启动最初阶段就完成配置
    // 2. ECC IMEM 校验功能必须主程序里开启, boot中启动会导致启动卡死
    // 3. ECC DMEM 纠错功能开启后将只支持全域32位内存操作, 需要在软件保证没有对DMEM的8/16位操作
    // EccRegs.ECC_IMEM_MODE.bit.ECC_FLASH_EN = 1; // 使能FLASH ECC检错功能
    // EccRegs.ECC_DMEM_MODE.bit.CHECK_MODE = 1; // 1: DATA MEM检错, 2: DATA MEM纠错

#ifdef EN_UART_UPDATA
    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0; // 设置CPU时钟为10Mhz
    ClkCfgRegs.LOSPCP.bit.LSPCLKDIV          = 0; // 设置LSP时钟为10Mhz

    CpuSysRegs.PCLKCR5.bit.SCIA = 1;              // 使能SCIA时钟
    SciaRegs.LCR.bit.DLAB       = 1;              // 波特率配置解锁
    SciaRegs.DLH                = 0;              // 波特率整数部分高16位
    SciaRegs.DLL                = 5;              // 波特率整数部分低16位
    SciaRegs.DLF                = 7;              // 小数部分,波特率=115200@10Mhz
    SciaRegs.LCR.bit.DLAB       = 0;              // 波特率配置上锁
    SciaRegs.LCR.bit.PEN        = 0;              // 检验位 = NONE
    SciaRegs.LCR.bit.DLS        = SCI_DATA_8BITS; // 数据位宽 = 8
    SciaRegs.LCR.bit.STOP       = SCI_STOP_BIT_1; // 停止位 = 1

    GpioCtrlRegs.GPAMUX2.bit.GPIO29  = 1; // set GPIO29 复用为SCIA_TX
    GpioCtrlRegs.GPADIR.bit.GPIO29   = 1; // set GPIO29 设为输出
    GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3; // set GPIO29 设为异步模式
    GpioCtrlRegs.GPAMUX2.bit.GPIO28  = 1; // set GPIO28 复用为SCIA_RX
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3; // set GPIO28 设为异步模式

    xmodem_recv_and_program();
#endif

    CpuSysRegs.PCLKCR0.bit.DMA = 1; // 使能DMA时钟
    // 配置DMA固定参数
    DmaRegs.CFG.all                = 0x03; // DMA 使能, 中断使能
    DmaCh1Regs.BLOCK_TS            = 0x3f; // DMA block为256字节
    DmaCh1Regs.CFG_H.all           = 0x00; // DMA MEM to MEM
    DmaCh1Regs.CTL_L.bit.SRC_WIDTH = 2;    // SRC 位宽为32Bits
    DmaCh1Regs.CTL_L.bit.DST_WIDTH = 2;    // DST 位宽为32 Bits
    DmaCh1Regs.INTSIGNAL_EN        = 0x02; // DMA中断只保留DMA传输结束中断

    int *p = (int *)(DSP_IMAGE_INFO_START_ADDR);

    int core0_text_len = *(p);
    int core0_data_len = *(p + 1);
    int core1_text_len = *(p + 2);
    int core1_data_len = *(p + 3);

    int flashCore0Text = DSP_IMAGE_START_ADDR;
    int flashCore0Data = DSP_IMAGE_START_ADDR + core0_text_len;
    int flashCore1Text = DSP_IMAGE_START_ADDR + core0_text_len + core0_data_len;
    int flashCore1Data = DSP_IMAGE_START_ADDR + core0_text_len + core0_data_len + core1_text_len;

    // 从FLASH搬运数据到SARM
    // 先搬运DATA_RAM以避免flash ecc出错时nmi_isr函数中无法访问数据段数据
    if (core0_data_len != 0)
        dma_read(flashCore0Data, (int)(&_CORE0_DRAM_START), core0_data_len);

    if (core0_text_len != 0)
        dma_read(flashCore0Text, (int)(&_CORE0_IRAM_START), core0_text_len);

    if (core1_data_len != 0)
        dma_read(flashCore1Data, (int)(&_CORE1_DRAM_START), core1_data_len);

    if (core1_text_len != 0)
        dma_read(flashCore1Text, (int)(&_CORE1_IRAM_START), core1_text_len);

    DmaRegs.RESET = 1;    // 复位DMA
    while (DmaRegs.RESET) // 等待复位
        ;
    CpuSysRegs.PCLKCR0.bit.DMA = 0; // 关闭DMA时钟

#ifdef EN_UART_UPDATA
    DevCfgRegs.SOFTPRES5.bit.SCIA = 1; // 复位SCIA
    for (int i = 0; i < 10; i++)       // 等待复位
        ;
    CpuSysRegs.PCLKCR5.bit.SCIA = 0; // 关闭SCIA时钟

    // 恢复GPIO
    GpioCtrlRegs.GPAMUX2.bit.GPIO28  = 0;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO29  = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO29   = 0;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 0;

    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 2; // 恢复CPU时钟到默认的2.5Mhz
    ClkCfgRegs.LOSPCP.bit.LSPCLKDIV          = 2; // 恢复LSP时钟到默认的2.5Mhz
#endif

    // jump to DSP core 0 and execute its first instruction @_CORE0_CODE_ENTRY
    // @_CORE0_CODE_ENTRY is defined in link scripts and is configurable
    _dsp_boot_jmp_to_core0((int)(&_CORE0_CODE_ENTRY));

    // add infinite loop to make compiler happy on _Noreturn
    while (1)
        ;
}
