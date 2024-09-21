#include "driverlib.h"

void SCI_setConfig(volatile struct SCI_REGS *sci, uint32_t baud_int, uint8_t baud_fra,
    SCI_DataWidthType data_bit, SCI_StopBitType stop_bit, SCI_ParityType parity)
{
    SCI_setBaud(sci, baud_int, baud_fra);
    SCI_setParityMode(sci, parity);
    sci->LCR.bit.DLS  = data_bit;
    sci->LCR.bit.STOP = stop_bit;
}

void SCI_setParityMode(volatile struct SCI_REGS *sci, SCI_ParityType parity)
{
    while (sci->USR.bit.BUSY) /* wait no busy */
        ;
    if (parity == SCI_PARITY_NONE)
    {
        sci->LCR.bit.PEN = 0;
    }
    else if (parity == SCI_PARITY_EVEN)
    {
        sci->LCR.bit.PEN = 1;
        sci->LCR.bit.EPS = 1;
    }
    else if (parity == SCI_PARITY_ODD)
    {
        sci->LCR.bit.PEN = 1;
        sci->LCR.bit.EPS = 0;
    }
}

void SCI_setBaud(volatile struct SCI_REGS *sci, uint32_t baud_int, uint8_t baud_fra)
{
    while (sci->USR.bit.BUSY) /* wait no busy */
        ;
    sci->LCR.bit.DLAB = 1; /* unlock band rate set */
    sci->DLL          = (baud_int & 0x00ff);
    sci->DLH          = (baud_int & 0xff00) >> 8;
    sci->DLF          = baud_fra; /* bandrate Fractional part */
    sci->LCR.bit.DLAB = 0;        /* lock the band rate set */
}

void SCI_writeCharArray(volatile struct SCI_REGS *sci, void *array, uint32_t len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        while (!sci->LSR.bit.THRE)
            ;
        sci->THR = *((uint8_t *)array + i);
    }
}

void SCI_readCharArray(volatile struct SCI_REGS *sci, void *array, uint32_t len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        while (!sci->LSR.bit.DR)
            ;
        *((uint8_t *)array + i) = (u8)(sci->RBR);
    }
}
