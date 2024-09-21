#ifndef QX_FLASH_H
#define QX_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "define.h"
#include "q28004x_flash.h"
#include "q28004x_sysctl.h"

//*****************************************************************************
//
//! Values that can be passed to Flash_setBankPowerMode() as the bank parameter
//
//*****************************************************************************
typedef enum
{
    FLASH_ERASE_SECTOR = 0,
    FLASH_ERASE_BLOCK  = 1,
    FLASH_ERASE_CHIP   = 2,
} Flash_EraseType;

//*****************************************************************************
//
// Delay instruction that allows for register configuration to complete.
//
//*****************************************************************************
#define FLASH_DELAY_CONFIG __asm(" RPT #7 || NOP")

#ifdef DEBUG
static inline bool Flash_isCtrlBaseValid(uint32_t ctrlBase)
{
    return ((ctrlBase == FLASH0CTRL_BASE));
}
#endif

static inline void Flash_setClkDiv(u32 div)
{
    DevCfgRegs.FLASHCLKDIV.bit.CLK_FLASH_DIV_NUM = div;
}

static inline void Flash_enableQspiMode()
{
    Flash0CtrlRegs.CONFIG.bit.QE = 1;
    while (Flash0CtrlRegs.STATUS.bit.WIP)
        ;
}

static inline void Flash_disableQspiMode()
{
    Flash0CtrlRegs.CONFIG.bit.QE = 0;
    while (Flash0CtrlRegs.STATUS.bit.WIP)
        ;
}

static inline vu32 Flash_readWord(u32 addr)
{
    return HWREG(addr);
}

static inline void Flash_writeWord(u32 addr, vu32 val)
{
    HWREG(addr) = val;
}

extern void Flash_initModule(u32 div, u32 qspi_en);
extern void Flash_eraseChip(void);
extern void Flash_eraseBlock(vu32 addr);
extern void Flash_eraseSector(vu32 addr);

#ifdef __cplusplus
}
#endif

#endif
