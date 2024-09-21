#ifndef QX_IPC_H
#define QX_IPC_H

#include "q28004x_ipc.h"
#include "define.h"

typedef enum
{
    IPC_EVENT0  = 0x1,
    IPC_EVENT1  = 0x2,
    IPC_EVENT2  = 0x4,
    IPC_EVENT3  = 0x8,
    IPC_EVENT4  = 0x10,
    IPC_EVENT5  = 0x20,
    IPC_EVENT6  = 0x40,
    IPC_EVENT7  = 0x80,
    IPC_EVENT8  = 0x100,
    IPC_EVENT9  = 0x200,
    IPC_EVENT10 = 0x400,
    IPC_EVENT11 = 0x800,
    IPC_EVENT12 = 0x1000,
    IPC_EVENT13 = 0x2000,
    IPC_EVENT14 = 0x4000,
    IPC_EVENT15 = 0x8000,
    IPC_EVENT16 = 0x10000,
    IPC_EVENT17 = 0x20000,
    IPC_EVENT18 = 0x40000,
    IPC_EVENT19 = 0x80000,
    IPC_EVENT20 = 0x100000,
    IPC_EVENT21 = 0x200000,
    IPC_EVENT22 = 0x400000,
    IPC_EVENT23 = 0x800000,
    IPC_EVENT24 = 0x1000000,
    IPC_EVENT25 = 0x2000000,
    IPC_EVENT26 = 0x4000000,
    IPC_EVENT27 = 0x8000000,
    IPC_EVENT28 = 0x10000000,
    IPC_EVENT29 = 0x20000000,
    IPC_EVENT30 = 0x40000000,
    IPC_EVENT31 = 0x80000000,
} IPC_EVENT_INDEX;

// post event
STATIC_INLINE void IPC_post(IPC_EVENT_INDEX event)
{
    IpcEventRegs.IPC_SET.all = event;
}

// clear self post
STATIC_INLINE void IPC_postClear(IPC_EVENT_INDEX event)
{
    IpcEventRegs.IPC_CLR.all = event;
}

// wait post
STATIC_INLINE void IPC_wait(IPC_EVENT_INDEX event)
{
    while (!(IpcEventRegs.IPC_STS.all & event))
        ;
}

// ack post
STATIC_INLINE void IPC_ack(IPC_EVENT_INDEX event)
{
    IpcEventRegs.IPC_ACK.all = event;
}

// wait post ack
STATIC_INLINE void IPC_waitAck(IPC_EVENT_INDEX event)
{
    while (IpcEventRegs.IPC_FLG.all & event)
        ;
}

// get current post status, clear by remote ack
STATIC_INLINE int IPC_getPostStatus(IPC_EVENT_INDEX event)
{
    return IpcEventRegs.IPC_FLG.all & event;
}

// block post and wait remote ack
STATIC_INLINE void IPC_postAndWaitAck(IPC_EVENT_INDEX event)
{
    IpcEventRegs.IPC_SET.all = event;        // send post
    while (IpcEventRegs.IPC_FLG.all & event) // wait post ack
        ;
}

// block wait remote post and ack
STATIC_INLINE void IPC_waitAndAck(IPC_EVENT_INDEX event)
{
    while (!(IpcEventRegs.IPC_STS.all & event)) // wait post
        ;
    IpcEventRegs.IPC_ACK.all = event; // send ack post
}

#endif
