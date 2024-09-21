#ifndef QX_LIN_H
#define QX_LIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_lin.h"
#include "define.h"

typedef enum
{
    DELAY_DISABLED     = 0x00,
    DELAY_HALF_BIT     = 0x01,
    DELAY_3QARTERS_BIT = 0x10,
    DELAY_ONE_BIT      = 0x11
} LIN_CmdDelay;

//*****************************************************************************
//
//! \brief Interrupt enable register
//
//*****************************************************************************
typedef enum
{
    LIDE   = 0x01,
    RDYE   = 0x02,
    ERRE   = 0x04,
    ABORTE = 0x08,
    SLEEPE = 0x10,
    WAKEE  = 0x20
} LIN_Lie;

//*****************************************************************************
//
//! \brief Error register
//
//*****************************************************************************
typedef enum
{
    FER    = 0x1,
    BITER  = 0x2,
    PER    = 0x4,
    CHKSER = 0x8,
    TOVER  = 0x10,
    SYNCER = 0x20,
    OVER   = 0x40,
    WAKEER = 0x80
} LIN_Ler;

//*****************************************************************************
//
//! \brief List of LIN commands executed by LIN device.
//
//*****************************************************************************
typedef enum
{
    CMD_ABORT,
    CMD_SEND_HEADER,
    CMD_RESPONSE_TX,
    CMD_RESPONSE_RX,
    CMD_WAKEUP
} LIN_Cmd;

//*****************************************************************************
//
//! \brief List of LIN size parameters
//
//*****************************************************************************
typedef enum
{
    SIZE_0_BYTES       = 0x0,
    SIZE_1_BYTES       = 0x1,
    SIZE_2_BYTES       = 0x2,
    SIZE_3_BYTES       = 0x3,
    SIZE_4_BYTES       = 0x4,
    SIZE_5_BYTES       = 0x5,
    SIZE_6_BYTES       = 0x6,
    SIZE_7_BYTES       = 0x7,
    SIZE_8_BYTES       = 0x8,
    SIZE_AUTO_BITRATE  = 0xC,
    SIZE_WAKE_UP       = 0xD,
    SIZE_LOG_MODE      = 0xE,
    SIZE_LENGTH_IN_LID = 0xF
} LIN_Size;

//*****************************************************************************
//
//! \brief LIN bus status register
//
//*****************************************************************************

typedef enum
{
    LBS_NONE   = 0x00,
    LBS_SLEEPM = 0x01,
    LBS_WAKEUP = 0x02,
    LBS_SLEEP  = 0x04,
} LIN_Lbs;

//*****************************************************************************
//
//! \brief List of LIN mode parameters
//
//*****************************************************************************
typedef enum
{
    CRC_ENHANCED = 0x0,
    CRC_CLASSIC  = 0x1
} LIN_Crc;

//*****************************************************************************
//
//! \brief List of LIN mode parameters
//
//*****************************************************************************
typedef enum
{
    MODE_SLAVE  = 0x0,
    MODE_MASTER = 0x1
} LIN_Mode;

//*****************************************************************************
//
//! \brief List of LIN AINC parameters
//
//*****************************************************************************
typedef enum
{
    AINC_DIS = 0x0,
    AINC_EN  = 0x1
} LIN_AINC;

/**
 * @brief Enable automatic increment buffer.
 * @param *lin Pointer to LIN device
 * After this function has been performed, the internal buffer index is automatically incremented
 * each time the LBUF register is accessed.
 */
static inline void LIN_enableAutoIncBuffer(uint32_t base)
{
    ((volatile struct LIN_REGS *)base)->LSEL.bit.AINC = 1; // Auto increment FIFO index after access
}

/**
 * @brief Disable automatic increment buffer.
 * @param *lin Pointer to LIN device
 * After executing this function, the internal buffer index must be addressed in order to read/write
 * consecutive bytes.
 *
 */
static inline void LIN_disableAutoIncBuffer(uint32_t base)
{
    ((volatile struct LIN_REGS *)base)->LSEL.bit.AINC
        = 0; // Do not auto increment FIFO index after access
}

/**
 * @brief Set buffer index
 * @param *lin Pointer to LIN device
 * @param buff_index Buffer index
 */
static inline void LIN_setBufferIndex(uint32_t base, u8 buff_index)
{
    ((volatile struct LIN_REGS *)base)->LSEL.bit.INDEX = buff_index;
}

/**
 * @brief Set delay between writing to LCR register and executing the command in LIN
 * @param *lin Pointer to LIN device
 * @param delay Delay type to be set
 */
static inline void LIN_setCommandDelay(uint32_t base, LIN_CmdDelay delay)
{
    ((volatile struct LIN_REGS *)base)->LSEL.bit.DLY = delay;
}

/**
 * @brief Enable auto synchronization. This option is used only when LIN is working as a SLAVE.
 * @param *lin Pointer to LIN device
 * Allow the slave synchronize baud rate to the master baud rate.
 * Auto synchronization can only take place when the baud rate deviation between master and slave is
 * less than 14%.
 */
static inline void LIN_enableAutoSync(uint32_t base)
{
    ((volatile struct LIN_REGS *)base)->DLH.bit.SYNC = 1; // Set SYNC bit
}

/**
 * @brief Disable auto synchronization.
 * @param *lin Pointer to LIN device
 */
static inline void LIN_disableAutoSync(uint32_t base)
{
    ((volatile struct LIN_REGS *)base)->DLH.bit.SYNC = 0; // Reset SYNC bit
}

/**
 * @brief Set header delay send value. The value set by this function defines the delay between
 * triggering the Send Header command and its execution.
 * @param *lin Pointer to LIN device
 * @param x count value
 */
static inline void LIN_setHeaderDelay(uint32_t base, u16 x)
{
    ((volatile struct LIN_REGS *)base)->HDRL.all = (x & 0x00FF);
    ((volatile struct LIN_REGS *)base)->HDRH.all = (x >> 8);
}

/**
 * @brief Set header delay prescaler.
 * @param *lin Pointer to LIN device
 * @param x Prescaler value
 */

static inline void LIN_setHeaderDelayPrescaler(uint32_t base, u8 x)
{
    ((volatile struct LIN_REGS *)base)->HDP.all = x;
}

/** @name Wake up and Sleep group description */
///@{
/**
 * @brief Set wake up response timer. When LIN is in slave mode and send wake-up signal master node
 * of LIN bus should response in 150 - 250 ms.
 * @param *lin Pointer to LIN device
 * If master node not response in this time the WAKEERR bit is set in LER register and interrupt in
 * generated. This function allow to configure timeout value and is related to bit time duration on
 * LIN bus. This option is used in slave mode only.
 *
 */
static inline void LIN_setWakeUpResponseTimer(uint32_t base, u8 x)
{
    ((volatile struct LIN_REGS *)base)->WURT = x;
}

/**
 * @brief Enable idle detection timer. Enabling the idle state detection causes LIN to trace
 * @param *lin Pointer to LIN device
 * the state of LIN bus until recessive to dominant transition or timer overflow occur.
 * When transition occurs the internal counter is reset, and then timer overflow the SLEEP bit in
 * LBS register is set.
 */
static inline void LIN_enableIdleDetectionTimer(uint32_t base)
{
    ((volatile struct LIN_REGS *)base)->IDTH.bit.IDTRUN = 1; // Set IDTRUN bit
}

/**
 * @brief Disable idle detection timer
 * @param *lin Pointer to LIN device
 */
static inline void LIN_disableIdleDetectionTimer(uint32_t base)
{
    ((volatile struct LIN_REGS *)base)->IDTH.bit.IDTRUN = 0; // Reset IDTRUN bit
}

/**
 * @brief Set idle detection timer overflow value. This function allows specify time after which the
 * idle state on the LIN bus is detected.
 * @param *lin Pointer to LIN device
 * @param x Overflow value
 */
static inline void LIN_setIdleDetectionTimer(uint32_t base, u16 x)
{
    ((volatile struct LIN_REGS *)base)->IDTL     = (x & 0xFF);
    ((volatile struct LIN_REGS *)base)->IDTH.all = (x >> 8) & 0x1F;
}

/** @name Interrupt group description */
///@{
/**
 * @brief Disable selected interrupt
 * @param *lin Pointer to LIN device
 * @param interrupt Name of interrupt
 */
static inline void LIN_interruptDisable(uint32_t base, LIN_Lie interrupt)
{
    ((volatile struct LIN_REGS *)base)->LIE.all
        = ((((volatile struct LIN_REGS *)base)->LIE.all) & ~interrupt);
}

/**
 * @brief Disable all interrupts
 * @param *lin Pointer to LIN device
 */
static inline void LIN_interruptDisableAll(uint32_t base)
{
    ((volatile struct LIN_REGS *)base)->LIE.all = 0x00;
}

/**
 * @brief Enable selected interrupt
 * @param *lin Pointer to LIN device
 * @param interrupt Name of interrupt
 */
static inline void LIN_interruptEnable(uint32_t base, LIN_Lie interrupt)
{
    ((volatile struct LIN_REGS *)base)->LIE.all
        = ((((volatile struct LIN_REGS *)base)->LIE.all) | interrupt);
}

/** @name Register getters/setters group description */
///@{

/**
 * @brief Get LBUF register state
 * @param *lin Pointer to LIN device
 * @return Current FIFO output
 */
static inline u8 LIN_getLBUF(uint32_t base)
{
    return ((volatile struct LIN_REGS *)base)->LBUF;
}

/**
 * @brief Get LSEL register state
 * @param *lin Pointer to LIN device
 * @return Current state
 */
static inline u8 LIN_getLSEL(uint32_t base)
{
    return ((volatile struct LIN_REGS *)base)->LSEL.all;
}

/**
 * @brief Set LID register state
 * @param *lin Pointer to LIN device
 * @param state Value to be set
 */
static inline void LIN_setLID(uint32_t base, u8 state)
{
    ((volatile struct LIN_REGS *)base)->LID.all = state;
}

/**
 * @brief Get LID register state
 * @param *lin Pointer to LIN device
 * @return Current state
 */
static inline u8 LIN_getLID(uint32_t base)
{
    return ((volatile struct LIN_REGS *)base)->LID.bit.LID;
}

/**
 * @brief Get LER register state
 * @param *lin Pointer to LIN device
 * @return Current state
 */
static inline u8 LIN_getLER(uint32_t base)
{
    return ((volatile struct LIN_REGS *)base)->LER.all;
}

/**
 * @brief Set LIE register state
 * @param *lin Pointer to LIN device
 * @param state Value to be set
 */
static inline void LIN_setLIE(uint32_t base, u8 state)
{
    ((volatile struct LIN_REGS *)base)->LIE.all = state;
}

/**
 * @brief Get LIE register state
 * @param *lin Pointer to LIN device
 * @return Current state
 */
static inline u8 LIN_getLIE(uint32_t base)
{
    return ((volatile struct LIN_REGS *)base)->LIE.all;
}

/**
 * @brief Get LSR register state
 * @param *lin Pointer to LIN device
 * @return Current state
 */
static inline u8 LIN_getLSR(uint32_t base)
{
    return ((volatile struct LIN_REGS *)base)->LSR_LCR.all;
}

/**
 * @brief Get DL register state
 * @param *lin Pointer to LIN device
 * @return Current state
 */
static inline u16 LIN_getDL(uint32_t base)
{
    u16 state;
    state = ((((volatile struct LIN_REGS *)base)->DLH.all) << 8)
            | (((volatile struct LIN_REGS *)base)->DLL.all);
    return state;
}

/**
 * @brief Get HDR delay register state
 * @param *lin Pointer to LIN device
 * @return Current state
 */
static inline u16 LIN_getHDR(uint32_t base)
{
    u16 state;
    state = (((volatile struct LIN_REGS *)base)->HDRL.all)
            | ((((volatile struct LIN_REGS *)base)->HDRH.all) << 8);
    return state;
}

/**
 * @brief Get HDP register state
 * @param *lin Pointer to LIN device
 * @return Current state
 */
static inline u8 LIN_getHDP(uint32_t base)
{
    return ((volatile struct LIN_REGS *)base)->HDP.all;
}

/**
 * @brief Set LBR register state
 * @param *lin Pointer to LIN device
 * @param state Value to be set
 */
static inline void LIN_setLBS(uint32_t base, u8 state)
{
    ((volatile struct LIN_REGS *)base)->LBS.all = state;
}

/**
 * @brief Get LBR register state
 * @param *lin Pointer to LIN device
 * @param state Value to be set
 */
static inline u8 LIN_getLBS(uint32_t base)
{
    return ((volatile struct LIN_REGS *)base)->LBS.all;
}

/**
 * @brief Get WURT register state
 * @param *lin Pointer to LIN device
 * @param state Value to be set
 */
static inline u8 LIN_getWURT(uint32_t base)
{
    return ((volatile struct LIN_REGS *)base)->WURT;
}

/**
 * @brief Get IDT register state
 * @param *lin Pointer to LIN device
 * @return Current state
 */
static inline u16 LIN_getIDT(uint32_t base)
{
    u16 state;
    state = (((volatile struct LIN_REGS *)base)->IDTL)
            | ((((volatile struct LIN_REGS *)base)->IDTH.all) << 8);
    return state;
}

/**
 * @brief Function calculate and set value to baud rate divider.
 * @param *lin Pointer to LIN device
 * @param clock System clock value
 * @param bud Baudrate value in range 1-20 kB
 */
static inline void LIN_setBaudrate(uint32_t base, u32 clock, u32 baud)
{
    u32 tmp                                     = (clock / (16 * baud));
    ((volatile struct LIN_REGS *)base)->DLL.all = ((u8)(tmp & 0x00FF));
    ((volatile struct LIN_REGS *)base)->DLH.all = ((u8)((tmp & 0x7FFF) >> 8));
}

static inline void LIN_clearPendingFlags(uint32_t base)
{
    u8 tmp1 = LIN_getLER(base);
    u8 tmp2 = LIN_getLBS(base);
    u8 tmp3 = LIN_getLID(base);
    u8 tmp4 = LIN_getLSR(base);
}

///@}

/** @name General usage functions */
///@{
/**
 * @brief Execute LIN command. After executes this function LIN device start executing specified
 * command, the RDY bit in LSR register is clear until command is in the progress. After proper
 * execution the RDY bit is set and interrupt is generated.
 * @param cmd Command to be send
 * @param ms Master/Slave mode select
 * @param lin13 Checksum selector
 * @param len Lenght of message, this option is valid only when LIN2.1 is selected (lin13=0) in
 * other case the size of message is taken form LID reggister
 */
void LIN_sendCommand(uint32_t base, LIN_Cmd cmd, u8 ms, u8 lin13, u8 len);

/** @name General usage functions */
///@{
/**
 * @brief Execute LIN command. After executes this function LIN device start executing specified
 * command, the RDY bit in LSR register is clear until command is in the progress. After proper
 * execution the RDY bit is set and interrupt is generated.
 * @param *lin Pointer to LIN device
 * @param cmd_delay Delay between LCR write and command execution to be set
 * @param ainc Auto increment FIFO index after access enable
 * @param index FIFO index to be set
 */
void LIN_writeLSEL(uint32_t base, LIN_CmdDelay cmd_delay, u8 ainc, u8 index);

/**
 * @brief Function copies data from the *dat parameter to the internal data buffer of LIN device.
 * @param *dat Pointer to data to be written
 * @param len Length of data in bytes
 */
void LIN_writeBuffer(uint32_t base, u8 *dat, u8 len);

/**
 * @brief Function copies data from the internal data buffer of LIN device to the *dat parameter.
 * @param *lin Pointer to LIN device
 * @param *dat Pointer to data storage buffer
 * @param len Length of data in bytes
 */
void LIN_readBuffer(uint32_t base, u8 *dat, u8 len);

/**
 * @brief Function wait until new header has not been received.
 */
struct LIN_LSR_BITS LIN_waitForHeader(uint32_t base);

/**
 * @brief Function wait until current command is in the progress.
 * @param *lin Pointer to LIN device
 */
struct LIN_LSR_BITS LIN_waitForReady(uint32_t base);

#ifdef __cplusplus
}
#endif

#endif
