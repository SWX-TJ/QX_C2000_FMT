#include "inc/i2c.h"

void I2C_initController(volatile struct I2C_REGS *i2c, uint32_t sysclkHz, uint32_t bitRate)
{ }

void I2C_enableInterrupt(volatile struct I2C_REGS *i2c, I2C_InterruptFlag flag)
{
    switch (flag)
    {
        case I2C_INT_NONE:
            i2c->IC_INTR_MASK.all = 0x0000U;
            break;
        case I2C_INT_RX_UNDERFLOW:
            i2c->IC_INTR_MASK.bit.M_RX_UNDER = 1;
            break;
        case I2C_INT_RX_OVERFLOW:
            i2c->IC_INTR_MASK.bit.M_RX_OVER = 1;
            break;
        case I2C_INT_RX_FULL:
            i2c->IC_INTR_MASK.bit.M_RX_FULL = 1;
            break;
        case I2C_INT_TX_OVERFLOW:
            i2c->IC_INTR_MASK.bit.M_TX_OVER = 1;
            break;
        case I2C_INT_TX_EMPTY:
            i2c->IC_INTR_MASK.bit.M_TX_EMPTY = 1;
            break;
        case I2C_INT_RD_REQUEST:
            i2c->IC_INTR_MASK.bit.M_RD_REQ = 1;
            break;
        case I2C_INT_TX_ABORT:
            i2c->IC_INTR_MASK.bit.M_TX_ABRT = 1;
            break;
        case I2C_INT_RX_DONE:
            i2c->IC_INTR_MASK.bit.M_RX_DONE = 1;
            break;
        case I2C_INT_ACTIVITY:
            i2c->IC_INTR_MASK.bit.M_ACTIVITY = 1;
            break;
        case I2C_INT_STOP_DET:
            i2c->IC_INTR_MASK.bit.M_STOP_DET = 1;
            break;
        case I2C_INT_START_DET:
            i2c->IC_INTR_MASK.bit.M_START_DET = 1;
            break;
        case I2C_INT_GEN_CALL:
            i2c->IC_INTR_MASK.bit.M_GEN_CALL = 1;
            break;
        case I2C_INT_RESTART_DET:
            i2c->IC_INTR_MASK.bit.M_RESTART_DET = 1;
            break;
        case I2C_INT_ALL:
            i2c->IC_INTR_MASK.all = I2C_INT_ALL;
            break;
    }
}

void I2C_disableInterrupt(volatile struct I2C_REGS *i2c, I2C_InterruptFlag flag)
{
    switch (flag)
    {
        case I2C_INT_NONE:
            break;
        case I2C_INT_RX_UNDERFLOW:
            i2c->IC_INTR_MASK.bit.M_RX_UNDER = 0;
            break;
        case I2C_INT_RX_OVERFLOW:
            i2c->IC_INTR_MASK.bit.M_RX_OVER = 0;
            break;
        case I2C_INT_RX_FULL:
            i2c->IC_INTR_MASK.bit.M_RX_FULL = 0;
            break;
        case I2C_INT_TX_OVERFLOW:
            i2c->IC_INTR_MASK.bit.M_TX_OVER = 0;
            break;
        case I2C_INT_TX_EMPTY:
            i2c->IC_INTR_MASK.bit.M_TX_EMPTY = 0;
            break;
        case I2C_INT_RD_REQUEST:
            i2c->IC_INTR_MASK.bit.M_RD_REQ = 0;
            break;
        case I2C_INT_TX_ABORT:
            i2c->IC_INTR_MASK.bit.M_TX_ABRT = 0;
            break;
        case I2C_INT_RX_DONE:
            i2c->IC_INTR_MASK.bit.M_RX_DONE = 0;
            break;
        case I2C_INT_ACTIVITY:
            i2c->IC_INTR_MASK.bit.M_ACTIVITY = 0;
            break;
        case I2C_INT_STOP_DET:
            i2c->IC_INTR_MASK.bit.M_STOP_DET = 0;
            break;
        case I2C_INT_START_DET:
            i2c->IC_INTR_MASK.bit.M_START_DET = 0;
            break;
        case I2C_INT_GEN_CALL:
            i2c->IC_INTR_MASK.bit.M_GEN_CALL = 0;
            break;
        case I2C_INT_RESTART_DET:
            i2c->IC_INTR_MASK.bit.M_RESTART_DET = 0;
            break;
        case I2C_INT_ALL:
            i2c->IC_INTR_MASK.all = 0U;
            break;
    }
}

void I2C_clearInterruptStatus(volatile struct I2C_REGS *i2c, I2C_InterruptFlag flag)
{
    uint32_t tmp;

    switch (flag)
    {
        case I2C_INT_NONE:
            break;
        case I2C_INT_RX_UNDERFLOW:
            tmp = i2c->IC_CLR_RX_UNDER;
            break;
        case I2C_INT_RX_OVERFLOW:
            tmp = i2c->IC_CLR_RX_OVER;
            break;
        case I2C_INT_RX_FULL:
            break;
        case I2C_INT_TX_OVERFLOW:
            tmp = i2c->IC_CLR_TX_OVER;
            break;
        case I2C_INT_TX_EMPTY:
            break;
        case I2C_INT_RD_REQUEST:
            tmp = i2c->IC_CLR_RD_REQ;
            break;
        case I2C_INT_TX_ABORT:
            tmp = i2c->IC_CLR_TX_ABRT;
            break;
        case I2C_INT_RX_DONE:
            tmp = i2c->IC_CLR_RX_DONE;
            break;
        case I2C_INT_ACTIVITY:
            tmp = i2c->IC_CLR_ACTIVITY;
            break;
        case I2C_INT_STOP_DET:
            tmp = i2c->IC_CLR_STOP_DET;
            break;
        case I2C_INT_START_DET:
            tmp = i2c->IC_CLR_START_DET;
            break;
        case I2C_INT_GEN_CALL:
            tmp = i2c->IC_CLR_GEN_CALL;
            break;
        case I2C_INT_RESTART_DET:
            tmp = i2c->IC_CLR_RESTART_DET;
            break;
        case I2C_INT_ALL:
            tmp = i2c->IC_CLR_INTR;
            break;
    }
}

void I2C_configModuleFrequency(volatile struct I2C_REGS *i2c, uint32_t sysclkHz)
{ }

/***************************************************************************************************/
/* temp code of i2c lib */
void I2cPeripheralEnable(volatile struct I2C_REGS * address, enum i2cEnable_e enable)
{
    if(enable == I2CENABLE)
    {
        address->IC_ENABLE.all = address->IC_ENABLE.all | (1 << 0);
    }
    else if(enable == I2CDISABLE)
    {
        address->IC_ENABLE.all = address->IC_ENABLE.all & ~(uint32_t)(1 << 0);
    }
}

void I2cSetRole(volatile struct I2C_REGS * address, enum i2cRole_e role)
{
    if(role == I2CROLE_MASTER)
    {
        address->IC_CON.all = address->IC_CON.all | ((1 << 0) | (1 << 6));
    }
    else if(role == I2CROLE_SLAVE)
    {
        address->IC_CON.all = address->IC_CON.all & ~(uint32_t)((1 << 0) | (1 << 6));
    }
}

void I2cSetAddrBitWide(volatile struct I2C_REGS * address, enum i2cBitWide_e bitWide)
{
    address->IC_CON.all = address->IC_CON.all & ~(uint32_t)((1 << 3) | (1 << 4)) | ((bitWide << 3) | (bitWide << 4));
    address->IC_TAR.all = address->IC_TAR.all & ~(uint32_t)(1 << 12) | (bitWide << 12);
}

void I2cEnableRestart(volatile struct I2C_REGS * address, enum i2cEnable_e enable)
{
    address->IC_CON.all = address->IC_CON.all & ~(uint32_t)(1 << 5) | (enable << 5);
}

void I2CSetSelfId(volatile struct I2C_REGS * address, uint16_t id)
{
    address->IC_SAR.all = address->IC_SAR.all & ~((uint32_t)0x3FF) | (id);
}

void I2CSetDestId(volatile struct I2C_REGS * address, uint16_t id)
{
    address->IC_TAR.all = address->IC_TAR.all & ~((uint32_t)0x3FF) | (id);
}

void I2cInterruptInitial(volatile struct I2C_REGS * address)
{
    address->IC_INTR_MASK.all = 0x00;
}

void I2CEnableInterrupt(volatile struct I2C_REGS * address, enum i2cInterrupt_e interrupt, enum i2cEnable_e enable)
{
    if(enable == I2CENABLE)
    {
        address->IC_INTR_MASK.all = address->IC_INTR_MASK.all | interrupt;
    }
    else if(enable == I2CDISABLE)
    {
        address->IC_INTR_MASK.all = address->IC_INTR_MASK.all & ~(uint32_t)(interrupt);
    }
}

void I2cSendData(struct I2C_REGS * address, uint8_t data)
{
    while((address->IC_STATUS.all & (1 << 1)) == 0) {};
    address->IC_DATA_CMD.all = (address->IC_DATA_CMD.all & ~((uint32_t)0x1FF)) | data;
}

void I2cReadCmd(struct I2C_REGS * address)
{
    address->IC_DATA_CMD.all = address->IC_DATA_CMD.all | (uint32_t)(0x100);
}

uint8_t I2cReadData(struct I2C_REGS * address)
{
    return (uint8_t)(address->IC_DATA_CMD.all & 0xFF);
}

void I2cClearIsrAllStatus(struct I2C_REGS * address)
{
    uint32_t regValue = 0x00;

    regValue = address->IC_CLR_INTR;
}

uint32_t I2cGetIsrStatus(struct I2C_REGS * address)
{
    return address->IC_RAW_INTR_STAT.all;
}
/***************************************************************************************************/

