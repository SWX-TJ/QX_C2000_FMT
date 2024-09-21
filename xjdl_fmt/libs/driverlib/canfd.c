#include "driverlib.h"

void CANFD_sendFrame(uint32_t base, uint32_t sta_id, CANFD_TTSEN ttsen, CANFD_BRS brs,
    CANFD_FDF fdf, CANFD_RTR rtr, CANFD_IDE ide, const void *msg, u8 DLC)
{
    volatile struct CANFD_REGS *can = (volatile struct CANFD_REGS *)base;
    u8 payload                      = CANFD_Payload(fdf, DLC);
    u8 msglen                       = (payload < 8) ? ((payload >> 2) + 1) : (payload >> 2);
    while (CANFD_isTransmitterBusy(base))
        ;
    can->TBUF[0] = (ttsen << 31) | (sta_id & 0x7FFU);
    can->TBUF[1] = (ide << 7) | (rtr << 6) | (fdf << 5) | (brs << 4) | (DLC & 0x0f);
    for (uint32_t i = 0; i < msglen; i++)
        can->TBUF[2 + i] = *((u32 *)msg + i);
    CANFD_setCmd(base, CANFD_CMD_TPE);
}

void CANFD_recvFrameBlocking(uint32_t base, void *msg)
{
    volatile struct CANFD_REGS *can = (volatile struct CANFD_REGS *)base;
    for (uint32_t i = 0; i < 20; i++)
        *((u32 *)msg + i) = can->RBUF[i];
    /* release the recv buffer for wait recv next frame */
    can->RCTRL.bit.RREL = 1;
}
