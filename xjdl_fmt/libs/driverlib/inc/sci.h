#ifndef QX_SCI_H
#define QX_SCI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_sci.h"
#include "define.h"

typedef enum
{
    SCI_DATA_5BITS = 0x00U,
    SCI_DATA_6BITS = 0x01U,
    SCI_DATA_7BITS = 0x02U,
    SCI_DATA_8BITS = 0x03U,
} SCI_DataWidthType;

typedef enum
{
    SCI_STOP_BIT_1 = 0x00U,
    SCI_STOP_BIT_2 = 0x01U, /* 1.5 stop bit when DLS = 0, else 2 stop bit */
} SCI_StopBitType;

typedef enum
{
    SCI_PARITY_NONE = 0x00U,
    SCI_PARITY_EVEN = 0x01U,
    SCI_PARITY_ODD  = 0x02U,
} SCI_ParityType;

typedef enum
{
    SCI_INT_SET_NONE  = 0x00U, /* no interrupt */
    SCI_INT_SET_RXRDY = 0x01U, /* Recv Data Available interrupt */
    SCI_INT_SET_TXRDY = 0x02U, /* Transmit Empty interrupt */
    SCI_INT_SET_RLS   = 0x04U, /* Recv Line Status interrupt */
    SCI_INT_SET_MSI   = 0x08U, /* Modem Status interrupt */
    SCI_INT_SET_THER  = 0x10U, /* RX FIFO level interrupt */
    SCI_INT_SET_ALL   = 0x1FU
} SCI_IntSetType;

typedef enum
{
    SCI_INT_SATUS_MODEM_STATUS = 0x00U, /* modem status interrupt */
    SCI_INT_SATUS_NONE         = 0x01U, /* no interrupt pending */
    SCI_INT_SATUS_TXRDY        = 0x02U, /* tx ready interrupt */
    SCI_INT_SATUS_RXRDY        = 0x04U, /* rx ready interrupt */
    SCI_INT_SATUS_LINE_STATUS  = 0x06U, /* recieiver line interrupt */
    SCI_INT_SATUS_BUSY         = 0x07U, /* busy dectect interrupt */
    SCI_INT_SATUS_RXTIMEROUT   = 0x0CU, /* character timerout interrupt */
} SCI_IntStatusType;

typedef enum
{
    SCI_RX_FIFO_TRIGGER_1_CHAR      = 0x00, /* trgger when 1 char in rx FIFO */
    SCI_RX_FIFO_TRIGGER_1_4_FULL    = 0x01, /* trgger when 1/4 full in rx FIFO */
    SCI_RX_FIFO_TRIGGER_1_2_FULL    = 0x02, /* trgger when 1/2 full in rx FIFO */
    SCI_RX_FIFO_TRIGGER_2_LESS_FULL = 0x03, /* trgger when 2 less than full in rx FIFO */
} SCI_RxFIFOLevel;

typedef enum
{
    SCI_TX_FIFO_TRIGGER_EMPTY    = 0x00, /* trgger when tx FIFO empty */
    SCI_TX_FIFO_TRIGGER_2_CHAR   = 0x01, /* trgger when tx FIFO has 2 char */
    SCI_TX_FIFO_TRIGGER_1_4_FULL = 0x02, /* trgger when tx FIFO 1/4 full */
    SCI_TX_FIFO_TRIGGER_1_2_FULL = 0x03, /* trgger when tx FIFO 1/2 full */
} SCI_TxFIFOLevel;

typedef enum
{
    SCI_DMA_MODE_SINGLE = 0,
    SCI_DMA_MODE_MULTI  = 1
} SCI_DMAMode;

typedef enum
{
    SCI_RX_STATUS_NONE = 0x00,
    SCI_RX_STATUS_DR   = 0x01,
    SCI_RX_STATUS_OE   = 0x02,
    SCI_RX_STATUS_PE   = 0x04,
    SCI_RX_STATUS_FE   = 0x08,
    SCI_RX_STATUS_BI   = 0x10,
    SCI_RX_STATUS_THRE = 0x20,
    SCI_RX_STATUS_TEMT = 0x40,
    SCI_RX_STATUS_RFE  = 0x80,
    SCI_RX_STATUS_ADDR = 0x100
} SCI_RxStatus;

STATIC_INLINE void SCI_enableFIFO(volatile struct SCI_REGS *sci)
{
    sci->FCR.bit.FIFOE = 1;
    sci->FCR.bit.DMAM = 1;
}

STATIC_INLINE void SCI_disableFIFO(volatile struct SCI_REGS *sci)
{
    sci->FCR.bit.FIFOE = 0;
}

STATIC_INLINE bool SCI_isFIFOEnabled(volatile struct SCI_REGS *sci)
{
    return sci->IIR.bit.FIFO_EN;
}

STATIC_INLINE void SCI_resetRxFIFO(volatile struct SCI_REGS *sci)
{
    sci->FCR.bit.RFIFOR = 1;
}

STATIC_INLINE void SCI_resetTxFIFO(volatile struct SCI_REGS *sci)
{
    sci->FCR.bit.XFIFOR = 1;
}

STATIC_INLINE void SCI_setRxFIFOInterruptLevel(
    volatile struct SCI_REGS *sci, SCI_RxFIFOLevel rxlevel)
{
    sci->FCR.bit.RCVR = rxlevel;
}

STATIC_INLINE void SCI_setTxFIFOInterruptLevel(
    volatile struct SCI_REGS *sci, SCI_TxFIFOLevel txlevel)
{
    sci->FCR.bit.TET = txlevel;
}

STATIC_INLINE bool SCI_isTxFIFOFull(volatile struct SCI_REGS *sci)
{
    return !sci->USR.bit.TFNF;
}

STATIC_INLINE bool SCI_isRxFIFOEmpty(volatile struct SCI_REGS *sci)
{
    return !sci->USR.bit.RFNE;
}

STATIC_INLINE u32 SCI_getTxFIFOStatus(volatile struct SCI_REGS *sci)
{
    return sci->TFL.bit.TFL;
}

STATIC_INLINE u32 SCI_getRxFIFOStatus(volatile struct SCI_REGS *sci)
{
    return sci->RFL.bit.RFL;
}

STATIC_INLINE u32 SCI_getRxStatus(volatile struct SCI_REGS *sci)
{
    return sci->LSR.all;
}

STATIC_INLINE bool SCI_isTransmitterBusy(volatile struct SCI_REGS *sci)
{
    return !sci->LSR.bit.TEMT;
}

STATIC_INLINE bool SCI_hasErrorInFIFO(volatile struct SCI_REGS *sci)
{
    return sci->LSR.bit.RFE;
}

STATIC_INLINE void SCI_setDmaMode(volatile struct SCI_REGS *sci, SCI_DMAMode mode)
{
    if (mode == SCI_DMA_MODE_SINGLE)
        sci->FCR.bit.DMAM = 0;
    else if (mode == SCI_DMA_MODE_MULTI)
        sci->FCR.bit.DMAM = 1;
}

STATIC_INLINE void SCI_writeCharBlocking(volatile struct SCI_REGS *sci, u32 data)
{
    while (!sci->LSR.bit.THRE)
        ;
    sci->THR = data;
    /* wait send finish */
    while (!sci->LSR.bit.TEMT)
        ;
}

STATIC_INLINE void SCI_writeCharNonBlocking(volatile struct SCI_REGS *sci, u32 data)
{
    sci->THR = data;
}

STATIC_INLINE u32 SCI_readCharBlocking(volatile struct SCI_REGS *sci)
{
    while (!sci->LSR.bit.DR)
        ;
    return (sci->RBR);
}

STATIC_INLINE u32 SCI_readCharNonBlocking(volatile struct SCI_REGS *sci)
{
    return (sci->RBR);
}

STATIC_INLINE void SCI_enableLoopback(volatile struct SCI_REGS *sci)
{
    sci->LCR.bit.BC = 1;
}

STATIC_INLINE void SCI_disableLoopback(volatile struct SCI_REGS *sci)
{
    sci->LCR.bit.BC = 0;
}

STATIC_INLINE void SCI_enableInterrupt(volatile struct SCI_REGS *sci, SCI_IntSetType interrupts)
{
    sci->IER.all = interrupts;
}

STATIC_INLINE void SCI_disableInterrupt(volatile struct SCI_REGS *sci, SCI_IntSetType interrupts)
{
    sci->IER.all |= ~interrupts;
}

STATIC_INLINE SCI_IntStatusType SCI_getInterruptStatus(volatile struct SCI_REGS *sci)
{
    return (SCI_IntStatusType)sci->IIR.bit.INTID;
}

STATIC_INLINE SCI_ParityType SCI_getParityMode(volatile struct SCI_REGS *sci)
{
    return (SCI_ParityType)sci->LCR.bit.EPS;
}

void SCI_setConfig(volatile struct SCI_REGS *sci, uint32_t baud_int, uint8_t baud_fra,
    SCI_DataWidthType data_bit, SCI_StopBitType stop_bit, SCI_ParityType parity);
void SCI_setParityMode(volatile struct SCI_REGS *sci, SCI_ParityType parity);
void SCI_setBaud(volatile struct SCI_REGS *sci, uint32_t baud_int, uint8_t baud_fra);
void SCI_writeCharArray(volatile struct SCI_REGS *sci, void *array, uint32_t len);
void SCI_readCharArray(volatile struct SCI_REGS *sci, void *array, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif
