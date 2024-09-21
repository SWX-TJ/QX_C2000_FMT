#include <board_config.h>
#include "qx_hw_serial.h"
#include "interrupt.h"
#include "sysctl.h"
#include <qx_hw_drivers/include/serial_config.h>
#include "qx_hw_dma.h"
/*
 * low level hardware operations
 */
static rt_err_t qx_enable_serial_clock_gate(volatile struct SCI_REGS *ins)
{
    rt_err_t rst = RT_EOK;

    if(ins == &SciaRegs){
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
    }else if(ins == &ScibRegs){
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIB);
    }else{
        rst = RT_ERROR;
    }

    return rst;
}

#include "gpio.h"

static rt_err_t qx_serial_gpio_config(struct qx_serial_board_config* cfg)
{
    GPIO_PinMux rx_pin_mux,tx_pin_mux;
    rt_err_t rst = RT_EOK;
    /*
     * support list of SCIA Rx
     * GPIO3 GPIO9 GPIO17 GPIO25 GPIO28 GPIO35
     * support list of SCIA Tx
     * GPIO2 GPIO8 GPIO16 GPIO24 GPIO29 GPIO37
     */
    if(cfg->instance == &SciaRegs)
    {
        switch(cfg->rx_pin_num){
            case 3: rx_pin_mux = GPIO_3_SCIA_RX; break;
            case 9: rx_pin_mux = GPIO_9_SCIA_RX; break;
            case 17: rx_pin_mux = GPIO_17_SCIA_RX; break;
            case 25: rx_pin_mux = GPIO_25_SCIA_RX; break;
            case 28: rx_pin_mux = GPIO_28_SCIA_RX; break;
            case 35: rx_pin_mux = GPIO_35_SCIA_RX; break;
            default: rx_pin_mux = 0xffUL; break;
        }

        switch(cfg->tx_pin_num){
            case 2: tx_pin_mux = GPIO_2_SCIA_TX; break;
            case 8: tx_pin_mux = GPIO_8_SCIA_TX; break;
            case 16: tx_pin_mux = GPIO_16_SCIA_TX; break;
            case 24: tx_pin_mux = GPIO_24_SCIA_TX; break;
            case 29: tx_pin_mux = GPIO_29_SCIA_TX; break;
            case 37: tx_pin_mux = GPIO_37_SCIA_TX; break;
            default: tx_pin_mux = 0xffUL; break;
        }

    }else if(cfg->instance == &ScibRegs){
        /*
         * support list of SCIB Rx
         * GPIO11 GPIO13 GPIO15 GPIO57
         * support list of SCIB Tx
         * GPIO9 GPIO10 GPIO12 GPIO14 GPIO40 GPIO41 GPIO56
         */
        switch(cfg->rx_pin_num){
            case 11: rx_pin_mux = GPIO_11_SCIB_RX; break;
            case 13: rx_pin_mux = GPIO_13_SCIB_RX; break;
            case 15: rx_pin_mux = GPIO_15_SCIB_RX; break;
            case 57: rx_pin_mux = GPIO_57_SCIB_RX; break;
            default: rx_pin_mux = 0xffUL; break;
        }

        switch(cfg->tx_pin_num){
            case 9: tx_pin_mux = GPIO_9_SCIB_TX; break;
            case 10: tx_pin_mux = GPIO_10_SCIB_TX; break;
            case 12: tx_pin_mux = GPIO_12_SCIB_TX; break;
            case 14: tx_pin_mux = GPIO_14_SCIB_TX; break;
            case 40: tx_pin_mux = GPIO_40_SCIB_TX; break;
            case 41: tx_pin_mux = GPIO_41_SCIB_TX; break;
            case 56: tx_pin_mux = GPIO_56_SCIB_TX; break;
            default: tx_pin_mux = 0xffUL; break;
        }

    }

    if(rx_pin_mux != 0xffUL){
        GPIO_Config(cfg->rx_pin_num, rx_pin_mux, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    }else{
        rst = -RT_ERROR;
    }

    if(tx_pin_mux != 0xffUL){
        GPIO_Config(cfg->tx_pin_num, tx_pin_mux, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    }else{
        rst = -RT_ERROR;
    }

    return rst;
}

#include "cpu_port.h"
static rt_err_t qx_serial_parameter_config(struct qx_serial_t* ins)
{
    rt_err_t rst = RT_EOK;

    rt_uint32_t baudRate = ins->serial_arch.config.baud_rate;

    rt_uint32_t baudRate_config_int = (SystemCoreClock/(baudRate*16U));

    rt_uint32_t baudRate_config_fri = ((SystemCoreClock - (baudRate_config_int*baudRate*16U))/baudRate);

    SCI_DataWidthType data_bit;

    switch(ins->serial_arch.config.data_bits){
        case DATA_BITS_5: data_bit = SCI_DATA_5BITS; break;
        case DATA_BITS_6: data_bit = SCI_DATA_6BITS; break;
        case DATA_BITS_7: data_bit = SCI_DATA_7BITS; break;
        case DATA_BITS_8: data_bit = SCI_DATA_8BITS; break;
        default: rst = -RT_ERROR; break;
    }

    SCI_StopBitType stop_bit;

    switch(ins->serial_arch.config.stop_bits){
        case STOP_BITS_1: stop_bit = SCI_STOP_BIT_1; break;
        case STOP_BITS_2: stop_bit = SCI_STOP_BIT_2; break;
        default: rst = -RT_ERROR; break;
    }

    SCI_ParityType parity_mode;

    switch(ins->serial_arch.config.parity){
        case PARITY_NONE:parity_mode = SCI_PARITY_NONE; break;
        case PARITY_ODD: parity_mode = SCI_PARITY_ODD; break;
        case PARITY_EVEN:parity_mode = SCI_PARITY_EVEN; break;
        default: rst = -RT_ERROR; break;
    }

    if(rst == RT_EOK){
        SCI_setConfig(ins->board_config->instance,
                      (uint32_t)baudRate_config_int,
                      (uint8_t)baudRate_config_fri,
                      data_bit,
                      stop_bit,
                      parity_mode);
    }

    return rst;
}

/**************************************************************************************************************/
/*
 * serial operations field
 */
static rt_err_t qx_serial_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct qx_serial_t* current_serial;
    rt_err_t result;

    current_serial = rt_container_of(serial, struct qx_serial_t,serial_arch);

    /* 1.enable module clock gate */
    result = qx_enable_serial_clock_gate(current_serial->board_config->instance);

    /* 2.serial tx rx gpio config */
    result = qx_serial_gpio_config(current_serial->board_config);

    result = qx_serial_parameter_config(current_serial);

    return result;
}

static rt_uint32_t could_receive_block = 0;
static rt_uint32_t could_receive_index = 0;

#if defined(RT_SERIAL_USING_DMA)
static rt_err_t qx_serial_dma_config(struct rt_serial_device *serial, rt_ubase_t flag)
{
    struct qx_serial_t* current_serial;
    uint32_t reg_base = 0;
    DMA_ConfigParams* dma_parameter = NULL;
    uint8_t channel = 0;
    INTERRUPT_Type intr = 0;
    rt_err_t rst = RT_EOK;

    current_serial = rt_container_of(serial, struct qx_serial_t,serial_arch);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);
//    SCI_enableFIFO(current_serial->board_config->instance);

    if(RT_DEVICE_FLAG_DMA_RX == flag){
        dma_parameter = current_serial->board_config->serial_rx_dma;
        if(current_serial->board_config->instance == &SciaRegs){
            dma_parameter->srcAddr = (u32)&(SciaRegs.RBR);
        }else if(current_serial->board_config->instance == &ScibRegs){
            dma_parameter->srcAddr = (u32)&(ScibRegs.RBR);
        }
        dma_parameter->destAddr = (u32)(((struct rt_serial_rx_fifo*)(serial->serial_rx))->buffer);
        channel = current_serial->board_config->rx_channel;
        could_receive_block = (serial->config.bufsz) / (dma_parameter->blockSize+1);
        could_receive_index = could_receive_block;
//        SCI_resetRxFIFO(current_serial->board_config->instance);
//        SCI_setRxFIFOInterruptLevel(current_serial->board_config->instance,SCI_RX_FIFO_TRIGGER_1_2_FULL);
    }
    else if(RT_DEVICE_FLAG_DMA_TX == flag){
        dma_parameter = current_serial->board_config->serial_tx_dma;
        if(current_serial->board_config->instance == &SciaRegs){
            dma_parameter->destAddr = (u32)&(SciaRegs.THR);
        }else if(current_serial->board_config->instance == &ScibRegs){
            dma_parameter->destAddr = (u32)&(ScibRegs.THR);
        }
        channel = current_serial->board_config->tx_channel;
        SCI_setTxFIFOInterruptLevel(current_serial->board_config->instance,SCI_TX_FIFO_TRIGGER_EMPTY);
    }


    switch(channel){
        case 1: reg_base = DMA_CH1_BASE; intr = INT_DMA_CH1; break;
        case 2: reg_base = DMA_CH2_BASE; intr = INT_DMA_CH2; break;
        case 3: reg_base = DMA_CH3_BASE; intr = INT_DMA_CH3; break;
        case 4: reg_base = DMA_CH4_BASE; intr = INT_DMA_CH4; break;
        case 5: reg_base = DMA_CH5_BASE; intr = INT_DMA_CH5; break;
        case 6: reg_base = DMA_CH6_BASE; intr = INT_DMA_CH6; break;
        default: reg_base = 0xffUL; intr = 0xffUL; break;
    }

    if((reg_base != 0xffUL) && (intr != 0xffUL) && (dma_parameter!=NULL)){
        DMA_configChannel(reg_base,dma_parameter);
        DMA_disableAllInterrupt(reg_base);
        DMA_disableAllInterruptStatus(reg_base);
        DMA_enableInterrupt(reg_base,DMA_TRANSFORM_DONE_INTR);
        DMA_enableInterruptStatus(reg_base,DMA_TRANSFORM_DONE_INTR);
        DMA_initController();
        Interrupt_enable(intr);
    }else{
        rst = -RT_ERROR;
        return rst;
    }

    if(RT_DEVICE_FLAG_DMA_RX == flag){
        DMA_startChannel(channel);
    }

    return rst;
}
#endif

static rt_err_t qx_serial_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    rt_err_t rst = RT_EOK;

    struct qx_serial_t* current_serial;

    current_serial = rt_container_of(serial, struct qx_serial_t,serial_arch);

#ifdef RT_SERIAL_USING_DMA
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif

    switch(cmd){
        case RT_DEVICE_CTRL_CLR_INT: SCI_disableInterrupt(current_serial->board_config->instance,SCI_INT_SET_RXRDY);
                                     Interrupt_disable(current_serial->board_config->intr_type);
                                     break;

        case RT_DEVICE_CTRL_SET_INT: SCI_enableInterrupt(current_serial->board_config->instance,SCI_INT_SET_RXRDY);
                                     Interrupt_enable(current_serial->board_config->intr_type);
                                     break;

        case RT_DEVICE_CTRL_CLOSE:  if(current_serial->board_config->instance == &SciaRegs){
                                        SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
                                    }else if(current_serial->board_config->instance == &ScibRegs){
                                        SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_SCIB);
                                    }else{
                                        rst = RT_ERROR;
                                    }
                                    break;
        #ifdef RT_SERIAL_USING_DMA
        case RT_DEVICE_CTRL_CONFIG: rst = qx_serial_dma_config(serial,ctrl_arg); break;
        #endif

        default: break;
    }

    return rst;
}

static int qx_serial_putc(struct rt_serial_device *serial, char c)
{
    struct qx_serial_t* current_serial;

    current_serial = rt_container_of(serial, struct qx_serial_t,serial_arch);

    SCI_writeCharBlocking(current_serial->board_config->instance,c);

    return 1;
}

static int qx_serial_getc(struct rt_serial_device *serial)
{
    int ret = -1;

    struct qx_serial_t* current_serial;

    current_serial = rt_container_of(serial, struct qx_serial_t,serial_arch);

    SCI_IntStatusType int_flag = 0;

    int_flag = SCI_getInterruptStatus(current_serial->board_config->instance);

    if(int_flag == SCI_INT_SATUS_RXRDY)
        ret = SCI_readCharNonBlocking(current_serial->board_config->instance);

    return ret;
}
#if defined(RT_SERIAL_USING_DMA)
static rt_ssize_t hw_serial_dma_transmit(struct rt_serial_device *serial,rt_uint8_t *buf, rt_size_t size)
{
    struct qx_serial_t* current_serial;

    current_serial = rt_container_of(serial, struct qx_serial_t,serial_arch);

    rt_uint32_t reg_base = 0;

    rt_uint8_t channel = current_serial->board_config->tx_channel;

    DMA_ConfigParams* dma_parameter = current_serial->board_config->serial_tx_dma;
    dma_parameter->srcAddr = (rt_uint32_t)buf;
    dma_parameter->blockSize = size - 1;

    switch(channel){
        case 1: reg_base = DMA_CH1_BASE; break;
        case 2: reg_base = DMA_CH2_BASE; break;
        case 3: reg_base = DMA_CH3_BASE; break;
        case 4: reg_base = DMA_CH4_BASE; break;
        case 5: reg_base = DMA_CH5_BASE; break;
        case 6: reg_base = DMA_CH6_BASE; break;
        default: reg_base = 0xffUL; break;
    }

    if(!DMA_getRunStatusFlag(reg_base)){
        DMA_configChannel(reg_base,dma_parameter);
        DMA_startChannel(channel);
        return size;
    }else{
        return 0;
    }
}

static rt_ssize_t qx_serial_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    rt_ssize_t rst = 0;

    if(!size){
        return 0;
    }

    if (RT_SERIAL_DMA_TX == direction){
        rst = hw_serial_dma_transmit(serial,buf,size);
    }

    return 1;
}
#endif
static const struct rt_uart_ops qx_serial_ops =
{
    .configure = qx_serial_configure,
    .control = qx_serial_control,
    .putc = qx_serial_putc,
    .getc = qx_serial_getc,
#if defined(RT_SERIAL_USING_DMA)
    .dma_transmit = qx_serial_dma_transmit,
#endif
};

/**************************************************************************************************************/
enum {
#if defined(BOARD_CFG_SCIA)
        SCIA_INDEX,
#endif

#if defined(BOARD_CFG_SCIB)
        SCIB_INDEX,
#endif
};

/* list of board serial devices */
static struct qx_serial_board_config serial_board_config[] =
{

#if defined(BOARD_CFG_SCIA)
        SCIA_CONFIG,
#endif

#if defined(BOARD_CFG_SCIB)
        SCIB_CONFIG,
#endif

};

/* list of serial objects */
static struct qx_serial_t serial_obj[sizeof(serial_board_config)/sizeof(serial_board_config[0])] = {0};

static void qx_serial_dma_mode_config(void)
{
#if defined(BOARD_CFG_SCIA)
    serial_obj[SCIA_INDEX].serial_dma_flag = 0;
#if defined(BOARD_SERIALA_RX_USING_DMA)
    serial_obj[SCIA_INDEX].serial_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static DMA_ConfigParams serial_a_dma_rx = SERIAL_A_RX_DMA_PARAM_CFG;
    serial_board_config[SCIA_INDEX].serial_rx_dma->dma_param = &serial_a_dma_rx;
    serial_board_config[SCIA_INDEX].serial_rx_dma->channel = SERIAL_A_RX_DMA_CHANNEL_CFG;
#endif

#if defined(BOARD_SERIALA_TX_USING_DMA)
    serial_obj[SCIA_INDEX].serial_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static DMA_ConfigParams serial_a_dma_tx = SERIAL_A_TX_DMA_PARAM_CFG;
    serial_board_config[SCIA_INDEX].serial_tx_dma->dma_param = &serial_a_dma_tx;
    serial_board_config[SCIA_INDEX].serial_tx_dma->channel = SERIAL_A_TX_DMA_CHANNEL_CFG;
#endif
#endif

#if defined(BOARD_CFG_SCIB)
    serial_obj[SCIB_INDEX].serial_dma_flag = 0;
#if defined(BOARD_SERIALB_RX_USING_DMA)
    serial_obj[SCIB_INDEX].serial_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static DMA_ConfigParams serial_b_dma_rx = SERIAL_B_RX_DMA_PARAM_CFG;
    serial_board_config[SCIB_INDEX].serial_rx_dma = &serial_b_dma_rx;
    serial_board_config[SCIB_INDEX].rx_channel = SERIAL_B_RX_DMA_CHANNEL_CFG;
#endif

#if defined(BOARD_SERIALB_TX_USING_DMA)
    serial_obj[SCIB_INDEX].serial_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static DMA_ConfigParams serial_b_dma_tx = SERIAL_B_TX_DMA_PARAM_CFG;
    serial_board_config[SCIB_INDEX].serial_tx_dma = &serial_b_dma_tx;
    serial_board_config[SCIB_INDEX].tx_channel = SERIAL_B_TX_DMA_CHANNEL_CFG;
#endif

#endif

}

rt_err_t rt_hw_serial_init(void)
{
    rt_size_t obj_num = sizeof(serial_obj)/sizeof(struct qx_serial_t);

    struct serial_configure cfg = RT_SERIAL_CONFIG_DEFAULT;

    qx_serial_dma_mode_config();

    rt_err_t rst = 0;

    for(uint32_t i = 0; i < obj_num;i++){
        serial_obj[i].board_config = &(serial_board_config[i]);
        serial_obj[i].serial_arch.config = cfg;
        serial_obj[i].serial_arch.ops = &qx_serial_ops;

        rst = rt_hw_serial_register(&serial_obj[i].serial_arch, serial_obj[i].board_config->name,
                                               RT_DEVICE_FLAG_RDWR
                                               | RT_DEVICE_FLAG_INT_RX
                                               | RT_DEVICE_FLAG_INT_TX
                                               | serial_obj[i].serial_dma_flag
                                               , NULL);
    }

    return rst;
}

static void serial_isr(struct rt_serial_device *serial)
{
    struct qx_serial_t* current_serial;

    current_serial = rt_container_of(serial, struct qx_serial_t,serial_arch);

    SCI_IntStatusType int_flag = 0;

    int_flag = SCI_getInterruptStatus(current_serial->board_config->instance);

    if(int_flag == SCI_INT_SATUS_RXRDY){
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    /*
    else if(int_flag == SCI_INT_SATUS_TXRDY){
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
    }
    */
}
#if defined(RT_SERIAL_USING_DMA)
static void rx_dma_callback(struct rt_serial_device *serial)
{
    could_receive_index--;

    struct qx_serial_t* current_serial;

    rt_uint32_t reg_base = 0;

    rt_uint32_t intr_type = 0;

    current_serial = rt_container_of(serial, struct qx_serial_t,serial_arch);

    rt_uint32_t rec_size = current_serial->board_config->serial_rx_dma->blockSize + 1;

    switch(current_serial->board_config->rx_channel){
        case 1: reg_base = DMA_CH1_BASE; break;
        case 2: reg_base = DMA_CH2_BASE; break;
        case 3: reg_base = DMA_CH3_BASE; break;
        case 4: reg_base = DMA_CH4_BASE; break;
        case 5: reg_base = DMA_CH5_BASE; break;
        case 6: reg_base = DMA_CH6_BASE; break;
        default: reg_base = 0xffUL; break;
    }

    if(reg_base != 0xffUl){
        intr_type = DMA_getInterruptStatus(reg_base);
    }
    else {
        return;
    }

    if(intr_type & DMA_TRANSFORM_DONE_INTR){
        rt_hw_serial_isr(serial,(RT_SERIAL_EVENT_RX_DMADONE | (rec_size<<8)));
    }

    DMA_clearErrorFlag(reg_base,intr_type);


    if(could_receive_index == 0){
        DMA_configDestAddress(reg_base,&(((struct rt_serial_rx_fifo*)(serial->serial_rx))->buffer));
//        struct rt_serial_rx_fifo* rx_fifo = (struct rt_serial_rx_fifo*)serial->serial_rx;
//        rx_fifo->put_index = 0;
//        rx_fifo->get_index = 0;
//        rx_fifo->is_full = RT_FALSE;
        could_receive_index = could_receive_block;
    }

    DMA_startChannel(current_serial->board_config->rx_channel);

}


static void tx_dma_callback(struct rt_serial_device *serial)
{
    struct qx_serial_t* current_serial;

    rt_uint32_t reg_base = 0;

    rt_uint32_t intr_type = 0;

    current_serial = rt_container_of(serial, struct qx_serial_t,serial_arch);

    switch(current_serial->board_config->tx_channel){
        case 1: reg_base = DMA_CH1_BASE; break;
        case 2: reg_base = DMA_CH2_BASE; break;
        case 3: reg_base = DMA_CH3_BASE; break;
        case 4: reg_base = DMA_CH4_BASE; break;
        case 5: reg_base = DMA_CH5_BASE; break;
        case 6: reg_base = DMA_CH6_BASE; break;
        default: reg_base = 0xffUL; break;
    }

    if(reg_base != 0xffUl){
        intr_type = DMA_getInterruptStatus(reg_base);
    }
    else {
        return;
    }

    if(intr_type & DMA_TRANSFORM_DONE_INTR){
        rt_hw_serial_isr(serial,RT_SERIAL_EVENT_TX_DMADONE);
    }

    DMA_clearErrorFlag(reg_base,intr_type);

}
#endif
/**************************************************************************************************************/
/*
 * interrupt routine
 */
__interrupt void scia_isr(void)
{
#if defined(BOARD_CFG_SCIA)
    rt_interrupt_enter();

    serial_isr(&(serial_obj[SCIA_INDEX].serial_arch));

    rt_interrupt_leave();
#endif
}
/**************************************************************************************************************/
__interrupt void scib_isr(void)
{
#if defined(BOARD_CFG_SCIB)
    rt_interrupt_enter();

    serial_isr(&(serial_obj[SCIB_INDEX].serial_arch));

    rt_interrupt_leave();
#endif
}
/**************************************************************************************************************/

#if defined(RT_SERIAL_USING_DMA)
#if (SERIAL_B_RX_DMA_CHANNEL_CFG == 1)
__interrupt void dma_ch1_isr(void)
#elif (SERIAL_B_RX_DMA_CHANNEL_CFG == 2)
__interrupt void dma_ch2_isr(void)
#elif (SERIAL_B_RX_DMA_CHANNEL_CFG == 3)
__interrupt void dma_ch3_isr(void)
#elif (SERIAL_B_RX_DMA_CHANNEL_CFG == 4)
__interrupt void dma_ch4_isr(void)
#elif (SERIAL_B_RX_DMA_CHANNEL_CFG == 5)
__interrupt void dma_ch5_isr(void)
#elif (SERIAL_B_RX_DMA_CHANNEL_CFG == 6)
__interrupt void dma_ch6_isr(void)
#else
void dma_rx_foo_channel_isr(void)
#endif
{
    rt_interrupt_enter();

#if defined(SERIAL_A_RX_DMA_CHANNEL_CFG)
    rx_dma_callback(&(serial_obj[SCIA_INDEX].serial_arch));
#endif

#if defined(SERIAL_B_RX_DMA_CHANNEL_CFG)
    rx_dma_callback(&(serial_obj[SCIB_INDEX].serial_arch));
#endif
    rt_interrupt_leave();
}
#endif

#if defined(RT_SERIAL_USING_DMA)
#if (SERIAL_B_TX_DMA_CHANNEL_CFG == 1)
__interrupt void dma_ch1_isr(void)
#elif (SERIAL_B_TX_DMA_CHANNEL_CFG == 2)
__interrupt void dma_ch2_isr(void)
#elif (SERIAL_B_TX_DMA_CHANNEL_CFG == 3)
__interrupt void dma_ch3_isr(void)
#elif (SERIAL_B_TX_DMA_CHANNEL_CFG == 4)
__interrupt void dma_ch4_isr(void)
#elif (SERIAL_B_TX_DMA_CHANNEL_CFG == 5)
__interrupt void dma_ch5_isr(void)
#elif (SERIAL_B_TX_DMA_CHANNEL_CFG == 6)
__interrupt void dma_ch6_isr(void)
#else
void dma_tx_foo_channel_isr(void)
#endif
{
    rt_interrupt_enter();

#if defined(SERIAL_A_TX_DMA_CHANNEL_CFG)
    tx_dma_callback(&(serial_obj[SCIA_INDEX].serial_arch));
#endif

#if defined(SERIAL_B_TX_DMA_CHANNEL_CFG)
    tx_dma_callback(&(serial_obj[SCIB_INDEX].serial_arch));
#endif

    rt_interrupt_leave();
}
#endif
