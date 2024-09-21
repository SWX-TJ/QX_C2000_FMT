#ifndef QX_CANFD_H
#define QX_CANFD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_canfd.h"
#include "define.h"

typedef enum
{
    CANFD_MODE_BUSOFF  = 0x01U,
    CANFD_MODE_TSSS    = 0x08U,
    CANFD_MODE_TPSS    = 0x10U,
    CANFD_MODE_LBMI    = 0x20U,
    CANFD_MODE_LBME    = 0x40U,
    CANFD_MODE_RESET   = 0x80U,
    CANFD_MODE_NORESET = 0x00U,
} CANFD_ModeType;

typedef enum
{
    CANFD_CMD_TSA   = 0x01U,
    CANFD_CMD_TSALL = 0x02U,
    CANFD_CMD_TSONE = 0x04U,
    CANFD_CMD_TPA   = 0x08U,
    CANFD_CMD_TPE   = 0x10U,
    CANFD_CMD_STBY  = 0x20U,
    CANFD_CMD_LOM   = 0x40U,
    CANFD_CMD_TBSEL = 0x80U,
    CANFD_CMD_NO    = 0x00U,
} CANFD_CmdType;

typedef enum
{
    CANFD_TTSEN_DISABLE = 0x0U,
    CANFD_TTSEN_ENABLE  = 0x1U,
} CANFD_TTSEN;

typedef enum
{
    CANFD_IDE_STANDARD = 0x0U,
    CANFD_IDE_EXTEND   = 0x1U,
} CANFD_IDE;

typedef enum
{
    CANFD_RTR_DATA   = 0x0U,
    CANFD_RTR_REMOTE = 0x1U,
} CANFD_RTR;

typedef enum
{
    CANFD_FDF_CAN20 = 0x0U,
    CANFD_FDF_CANFD = 0x1U,
} CANFD_FDF;

typedef enum
{
    CANFD_BRS_SLOW = 0x0U,
    CANFD_BRS_FAST = 0x1U,
} CANFD_BRS;

typedef enum
{
    CANFD_INT_NONE  = 0x00U,
    CANFD_INT_EIE   = 0x02U,
    CANFD_INT_TSIE  = 0x04U,
    CANFD_INT_TPIE  = 0x08U,
    CANFD_INT_RAFIE = 0x10U,
    CANFD_INT_RFIE  = 0x20U,
    CANFD_INT_ROIE  = 0x40U,
    CANFD_INT_RIE   = 0x80U,
    CANFD_INT_ALL   = 0xFFU,
} CANFD_IntType;

STATIC_INLINE void CANFD_setMode(uint32_t base, CANFD_ModeType modes)
{
    ((volatile struct CANFD_REGS *)base)->CFGSTAT.all = modes;
}

STATIC_INLINE void CANFD_setCmd(uint32_t base, CANFD_CmdType cmds)
{
    ((volatile struct CANFD_REGS *)base)->TCMD.all = cmds;
}

STATIC_INLINE void CANFD_setInterrupt(uint32_t base, CANFD_IntType ints)
{
    ((volatile struct CANFD_REGS *)base)->RTIE.all = ints;
}

STATIC_INLINE void CANFD_setAcceptFilter(uint32_t base, uint32_t acr, uint32_t amr)
{
    ((volatile struct CANFD_REGS *)base)->ACF_EN_0.all = 0xff;
    ((volatile struct CANFD_REGS *)base)->ACF_EN_1.all = 0x07;

    ((volatile struct CANFD_REGS *)base)->ACFCTRL.bit.SELMASK = 0;
    ((volatile struct CANFD_REGS *)base)->CFGSTAT.all         = 0xa0;
    ((volatile struct CANFD_REGS *)base)->ACF.all             = acr;

    ((volatile struct CANFD_REGS *)base)->ACFCTRL.bit.SELMASK = 1;
    ((volatile struct CANFD_REGS *)base)->ACF.all             = amr;
    ((volatile struct CANFD_REGS *)base)->CFGSTAT.bit.RESET   = 0;
}

STATIC_INLINE u32 CANFD_Payload(CANFD_FDF fdf, u8 DLC)
{
    u8 msglen;
    if (fdf == CANFD_FDF_CAN20)
    {
        if (DLC < 8)
            msglen = DLC;
        else
            msglen = 8;
    }
    else
    {
        switch (DLC)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                msglen = DLC;
                break;
            case 9:
                msglen = 12;
                break;
            case 10:
                msglen = 16;
                break;
            case 11:
                msglen = 20;
                break;
            case 12:
                msglen = 24;
                break;
            case 13:
                msglen = 32;
                break;
            case 14:
                msglen = 48;
                break;
            case 15:
                msglen = 64;
                break;
            default:
                msglen = 0;
                break; // Invalid DLC
        }
    }

    return msglen;
}

STATIC_INLINE u32 CANFD_isTransmitterBusy(uint32_t base)
{
    return ((volatile struct CANFD_REGS *)base)->CFGSTAT.bit.TACTIVE;
}

STATIC_INLINE u32 CANFD_isReceiveBusy(uint32_t base)
{
    return ((volatile struct CANFD_REGS *)base)->CFGSTAT.bit.RACTIVE;
}

void CANFD_sendFrame(uint32_t base, uint32_t sta_id, CANFD_TTSEN ttsen, CANFD_BRS brs,
    CANFD_FDF fdf, CANFD_RTR rtr, CANFD_IDE ide, const void *msg, u8 DLC);
void CANFD_recvFrameBlocking(uint32_t base, void *msg);

#ifdef __cplusplus
}
#endif

#endif
