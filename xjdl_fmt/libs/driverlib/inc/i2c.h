#ifndef QX_I2C_H
#define QX_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_i2c.h"
#include "define.h"

typedef enum
{
    I2C_STANDARD_MODE  = 0x1U,
    I2C_FAST_MODE      = 0x2U,
    I2C_HIGHSPEED_MODE = 0x3U
} I2C_SpeedMode;

typedef enum
{
    I2C_CONTROLLER_MASTER_ONLY  = 1,
    I2C_CONTROLLER_SLAVE_ONLY   = 2,
    I2C_CONTROLLER_MASTER_SLAVE = 3
} I2C_ControllerType;

typedef enum
{
    I2C_INT_NONE         = 0x0U,
    I2C_INT_RX_UNDERFLOW = 0x1U,
    I2C_INT_RX_OVERFLOW  = 0x2U,
    I2C_INT_RX_FULL      = 0x4U,
    I2C_INT_TX_OVERFLOW  = 0x8U,
    I2C_INT_TX_EMPTY     = 0x10U,
    I2C_INT_RD_REQUEST   = 0x20U,
    I2C_INT_TX_ABORT     = 0x40U,
    I2C_INT_RX_DONE      = 0x80U,
    I2C_INT_ACTIVITY     = 0x100U,
    I2C_INT_STOP_DET     = 0x200U,
    I2C_INT_START_DET    = 0x400U,
    I2C_INT_GEN_CALL     = 0x800U,
    I2C_INT_RESTART_DET  = 0x1000U,
    I2C_INT_ALL          = 0x1FFFU
} I2C_InterruptFlag;

typedef enum
{
    I2C_ACTIVITY     = 0x1U,
    I2C_TXFIFO_NF    = 0x2U,
    I2C_TXFIFO_EMPTY = 0x4U,
    I2C_RXFIFO_NE    = 0x8U,
    I2C_RXFIFO_FULL  = 0x10U,
    I2C_MST_ACTIVITY = 0x20U,
    I2C_SLV_ACTIVITY = 0x40U,
} I2C_Status;

typedef enum
{
    I2C_ADDR_MODE_7BITS  = 0,
    I2C_ADDR_MODE_10BITS = 1
} I2C_AddressMode;

typedef enum
{
    I2C_FIFO_TXE_0 = 0x0U,
    I2C_FIFO_TXE_1 = 0x1U,
    I2C_FIFO_TXE_2 = 0x2U,
    I2C_FIFO_TXE_3 = 0x3U,
    I2C_FIFO_TXE_4 = 0x4U,
    I2C_FIFO_TXE_5 = 0x5U,
    I2C_FIFO_TXE_6 = 0x6U,
    I2C_FIFO_TXE_7 = 0x7U
} I2C_TxFIFOLevel;

typedef enum
{
    I2C_FIFO_RXF_1 = 0x0U,
    I2C_FIFO_RXF_2 = 0x1U,
    I2C_FIFO_RXF_3 = 0x2U,
    I2C_FIFO_RXF_4 = 0x3U,
    I2C_FIFO_RXF_5 = 0x4U,
    I2C_FIFO_RXF_6 = 0x5U,
    I2C_FIFO_RXF_7 = 0x6U,
    I2C_FIFO_RXF_8 = 0x7U,
} I2C_RxFIFOLevel;

typedef enum
{
    I2C_FIFO_TX0 = 0x0U,
    I2C_FIFO_TX1 = 0x1U,
    I2C_FIFO_TX2 = 0x2U,
    I2C_FIFO_TX3 = 0x3U,
    I2C_FIFO_TX4 = 0x4U,
    I2C_FIFO_TX5 = 0x5U,
    I2C_FIFO_TX6 = 0x6U,
    I2C_FIFO_TX7 = 0x7U
} I2C_TxDMATriggerLevel;

typedef enum
{
    I2C_FIFO_RX1 = 0x0U,
    I2C_FIFO_RX2 = 0x1U,
    I2C_FIFO_RX3 = 0x2U,
    I2C_FIFO_RX4 = 0x3U,
    I2C_FIFO_RX5 = 0x4U,
    I2C_FIFO_RX6 = 0x5U,
    I2C_FIFO_RX7 = 0x6U,
    I2C_FIFO_RX8 = 0x7U
} I2C_RxDMATriggerLevel;

STATIC_INLINE void I2C_enableModule(volatile struct I2C_REGS *i2c)
{
    i2c->IC_ENABLE.bit.ENABLE = 1;
    while (i2c->IC_ENABLE_STATUS.bit.IC_EN != 1)
        ;
}

STATIC_INLINE void I2C_disableModule(volatile struct I2C_REGS *i2c)
{
    i2c->IC_ENABLE.bit.ENABLE = 0;
    while (i2c->IC_ENABLE_STATUS.bit.IC_EN != 0)
        ;
}

STATIC_INLINE void I2C_enableMasterMode(volatile struct I2C_REGS *i2c)
{
    i2c->IC_CON.bit.MASTER_MODE = 1;
}

STATIC_INLINE void I2C_disableMasterMode(volatile struct I2C_REGS *i2c)
{
    i2c->IC_CON.bit.MASTER_MODE = 0;
}

STATIC_INLINE void I2C_enableSlaveMode(volatile struct I2C_REGS *i2c)
{
    i2c->IC_CON.bit.IC_SLAVE_DISABLE = 0;
}

STATIC_INLINE void I2C_disableSlaveMode(volatile struct I2C_REGS *i2c)
{
    i2c->IC_CON.bit.IC_SLAVE_DISABLE = 1;
}

STATIC_INLINE void I2C_setSpeedMode(volatile struct I2C_REGS *i2c, I2C_SpeedMode mode)
{
    i2c->IC_CON.bit.SPEED = mode;
}

STATIC_INLINE void I2C_setAddressMode(volatile struct I2C_REGS *i2c, I2C_AddressMode mode)
{
    i2c->IC_CON.bit.IC_10BITADDR_SLAVE = mode;
    //    i2c->IC_CON.bit.IC_10BITADDR_MASTER = mode;
}

STATIC_INLINE void I2C_enableRestart(volatile struct I2C_REGS *i2c)
{
    i2c->IC_CON.bit.IC_RESTART_EN = 1;
}

STATIC_INLINE void I2C_disableRestart(volatile struct I2C_REGS *i2c)
{
    i2c->IC_CON.bit.IC_RESTART_EN = 0;
}

STATIC_INLINE void I2C_enableStopDetIfAddress(volatile struct I2C_REGS *i2c)
{
    i2c->IC_CON.bit.STOP_DET_IFADDRESSED = 1;
}

STATIC_INLINE void I2C_disableStopDetIfAddress(volatile struct I2C_REGS *i2c)
{
    i2c->IC_CON.bit.STOP_DET_IFADDRESSED = 0;
}

STATIC_INLINE void I2C_setFIFOInterruptLevel(
    volatile struct I2C_REGS *i2c, I2C_TxFIFOLevel txLevel, I2C_RxFIFOLevel rxLevel)
{
    i2c->IC_TX_TL = txLevel;
    i2c->IC_RX_TL = rxLevel;
}

STATIC_INLINE void I2C_getFIFOInterruptLevel(
    volatile struct I2C_REGS *i2c, I2C_TxFIFOLevel *txLevel, I2C_RxFIFOLevel *rxLevel)
{
    *txLevel = (I2C_TxFIFOLevel)i2c->IC_TX_TL;
    *rxLevel = (I2C_RxFIFOLevel)i2c->IC_RX_TL;
}

STATIC_INLINE uint8_t I2C_getTxFIFOStatus(volatile struct I2C_REGS *i2c)
{
    return (u8)i2c->IC_TXFLR;
}

STATIC_INLINE uint8_t I2C_getRxFIFOStatus(volatile struct I2C_REGS *i2c)
{
    return (u8)i2c->IC_RXFLR;
}

STATIC_INLINE void I2C_setTargetAddress(volatile struct I2C_REGS *i2c, uint16_t targetAddr)
{
    // I2C_disableModule(i2c);

    i2c->IC_TAR.bit.TAR = targetAddr;

    // I2C_enableModule(i2c);
}

STATIC_INLINE void I2C_setOwnAddress(volatile struct I2C_REGS *i2c, uint16_t ownAddr)
{
    // I2C_disableModule(i2c);

    i2c->IC_SAR.bit.SAR = ownAddr;

    // I2C_enableModule(i2c);
}

STATIC_INLINE void I2C_setSCLLowCount(volatile struct I2C_REGS *i2c, uint16_t count)
{
    // I2C_disableModule(i2c);

    if (i2c->IC_CON.bit.SPEED == 1)
        i2c->IC_SS_SCL_LCNT.bit.SS_SCL_LCNT = count;
    else if (i2c->IC_CON.bit.SPEED == 2)
        i2c->IC_FS_SCL_LCNT.bit.FS_SCL_LCNT = count;

    // I2C_enableModule(i2c);
}

STATIC_INLINE void I2C_setSCLHighCount(volatile struct I2C_REGS *i2c, uint16_t count)
{
    // I2C_disableModule(i2c);

    if (i2c->IC_CON.bit.SPEED == 1)
        i2c->IC_SS_SCL_HCNT.bit.SS_SCL_HCNT = count;
    else if (i2c->IC_CON.bit.SPEED == 2)
        i2c->IC_FS_SCL_HCNT.bit.FS_SCL_HCNT = count;

    // I2C_enableModule(i2c);
}

STATIC_INLINE void I2C_setSDAHold(volatile struct I2C_REGS *i2c, uint16_t rxHold, uint16_t txHold)
{
    // I2C_disableModule(i2c);

    i2c->IC_SDA_HOLD.bit.IC_SDA_RX_HOLD = rxHold;
    i2c->IC_SDA_HOLD.bit.IC_SDA_TX_HOLD = txHold;

    // I2C_enableModule(i2c);
}

STATIC_INLINE void I2C_setSpikeSuppression(volatile struct I2C_REGS *i2c, uint8_t count)
{
    // I2C_disableModule(i2c);

    i2c->IC_FS_SPKLEN = count;

    // I2C_enableModule(i2c);
}

STATIC_INLINE bool I2C_isBusy(volatile struct I2C_REGS *i2c)
{
    return i2c->IC_STATUS.bit.ACTIVITY;
}

STATIC_INLINE uint32_t I2C_getStatus(volatile struct I2C_REGS *i2c)
{
    return i2c->IC_STATUS.all;
}

STATIC_INLINE uint32_t I2C_getInterruptStatus(volatile struct I2C_REGS *i2c)
{
    return i2c->IC_INTR_STAT.all;
}

STATIC_INLINE uint32_t I2C_getPendingInterrupt(volatile struct I2C_REGS *i2c)
{
    return (i2c->IC_INTR_STAT.all ^ i2c->IC_RAW_INTR_STAT.all);
}

STATIC_INLINE void I2C_enableDMA(volatile struct I2C_REGS *i2c)
{
    i2c->IC_DMA_CR.bit.TDMAE = 1;
    i2c->IC_DMA_CR.bit.RDMAE = 1;
}

STATIC_INLINE void I2C_disableDMA(volatile struct I2C_REGS *i2c)
{
    i2c->IC_DMA_CR.bit.TDMAE = 0;
    i2c->IC_DMA_CR.bit.RDMAE = 0;
}

STATIC_INLINE void I2C_sendStopCondition(volatile struct I2C_REGS *i2c)
{
    i2c->IC_DATA_CMD.bit.STOP = 1;
}

STATIC_INLINE void I2C_sendNACK(volatile struct I2C_REGS *i2c)
{
    // I2C_disableModule(i2c);

    i2c->IC_SLV_DATA_NACK_ONLY = 1U;

    // I2C_enableModule(i2c);
}

STATIC_INLINE void I2C_sendStartWrite(volatile struct I2C_REGS *i2c)
{
    i2c->IC_DATA_CMD.bit.CMD = 0;
}

STATIC_INLINE void I2C_sendStartRead(volatile struct I2C_REGS *i2c)
{
    i2c->IC_DATA_CMD.bit.CMD = 1;
}

STATIC_INLINE uint8_t I2C_getData(volatile struct I2C_REGS *i2c)
{
    return (u8)i2c->IC_DATA_CMD.bit.DATA;
}

STATIC_INLINE void I2C_putData(volatile struct I2C_REGS *i2c, uint8_t data)
{
    i2c->IC_DATA_CMD.bit.DATA = data;
}

STATIC_INLINE void I2C_setDMATriggerLevel(
    volatile struct I2C_REGS *i2c, I2C_RxDMATriggerLevel rxLevel, I2C_TxDMATriggerLevel txLevel)
{
    i2c->IC_DMA_RDLR = rxLevel;
    i2c->IC_DMA_TDLR = txLevel;
}

void I2C_initController(volatile struct I2C_REGS *i2c, uint32_t sysclkHz, uint32_t bitRate);
void I2C_enableInterrupt(volatile struct I2C_REGS *i2c, I2C_InterruptFlag flag);
void I2C_disableInterrupt(volatile struct I2C_REGS *i2c, I2C_InterruptFlag flag);
void I2C_clearInterruptStatus(volatile struct I2C_REGS *i2c, I2C_InterruptFlag flag);
void I2C_configModuleFrequency(volatile struct I2C_REGS *i2c, uint32_t sysclkHz);

/********************************************************************************/
/* temp define of i2c lib */
#define     I2CFREQ_NORMAL      100000
#define     I2CFREQ_RAPID       1000000
#define     I2CFREQ_HIGHSPEED   3400000

enum i2cRole_e
{
    I2CROLE_SLAVE = 0,
    I2CROLE_MASTER,
};

enum i2cBitWide_e
{
    I2CBITWIDE_7 = 0,
    I2CBITWIDE_10,
};

enum i2cEnable_e
{
    I2CENABLE = 1,
    I2CDISABLE = 0,
};

enum i2cInterrupt_e
{
    I2CINTERRUPT_RXFULL = (uint32_t)(1 << 2),
    I2CINTERRUPT_RDREQ = (uint32_t)(1 << 5),
    I2CINTERRUPT_STOP = (uint32_t)(1 << 9),
};

void I2cInitial(void);
uint16_t GetI2cbRxData(uint8_t **data);
uint16_t GetI2caRxData(uint8_t **data);

void I2cPeripheralEnable(volatile struct I2C_REGS * address, enum i2cEnable_e enable);
//void I2cSetFrequency(volatile struct I2C_REGS * address, uint32_t frequency);
void I2cSetRole(volatile struct I2C_REGS * address, enum i2cRole_e role);
void I2cSetAddrBitWide(volatile struct I2C_REGS * address, enum i2cBitWide_e bitWide);
void I2cEnableRestart(volatile struct I2C_REGS * address, enum i2cEnable_e enable);
void I2CSetSelfId(volatile struct I2C_REGS * address, uint16_t id);
void I2CSetDestId(volatile struct I2C_REGS * address, uint16_t id);
void I2cInterruptInitial(volatile struct I2C_REGS * address);
void I2CEnableInterrupt(volatile struct I2C_REGS * address, enum i2cInterrupt_e interrupt, enum i2cEnable_e enable);
void I2cSendData(struct I2C_REGS * address, uint8_t data);
void I2cReadCmd(struct I2C_REGS * address);
uint8_t I2cReadData(struct I2C_REGS * address);
void I2cClearIsrAllStatus(struct I2C_REGS * address);
uint32_t I2cGetIsrStatus(struct I2C_REGS * address);
/********************************************************************************/

#if 0
#endif

#ifdef __cplusplus
}
#endif

#endif
