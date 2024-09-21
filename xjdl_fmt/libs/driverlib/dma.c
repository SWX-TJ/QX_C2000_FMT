#include "driverlib.h"
//__attribute__((optnone))
void DMA_configChannel(uint32_t base, const DMA_ConfigParams *config)
{
    DMA_configAddress(base, &config->destAddr, &config->srcAddr);
    DMA_configTransfer(base, config->blockSize, config->srcWidth, config->destWidth);
    DMA_configBurst(base, 0, config->srcMsize, config->destMsize);
    DMA_configMode(base, config->srcHSInterface, config->destHSInterface);
}

void DMA_configAddress(uint32_t base, const void *destAddr, const void *srcAddr)
{
    volatile struct DMA_CH_REGS *ch_reg = (volatile struct DMA_CH_REGS *)base;

    ch_reg->SAR = *(u32 *)srcAddr;
    ch_reg->DAR = *(u32 *)destAddr;
}

void DMA_configSrcAddress(uint32_t base, const void *srcAddr)
{
    volatile struct DMA_CH_REGS *ch_reg = (volatile struct DMA_CH_REGS *)base;

    ch_reg->SAR = *(u32 *)srcAddr;
}

void DMA_configBurst(uint32_t base, uint16_t size, int16_t srcStep, int16_t destStep)
{
    volatile struct DMA_CH_REGS *ch_reg = (volatile struct DMA_CH_REGS *)base;

    ch_reg->CTL_L.bit.SRC_MSIZE = srcStep;
    ch_reg->CTL_L.bit.DST_MSIZE = destStep;
}

void DMA_configTransfer(uint32_t base, uint32_t transferSize, int16_t srcStep, int16_t destStep)
{
    volatile struct DMA_CH_REGS *ch_reg = (volatile struct DMA_CH_REGS *)base;

    if (transferSize > DMA_MAX_BLOCK_TS)
        transferSize = DMA_MAX_BLOCK_TS;

    ch_reg->BLOCK_TS            = transferSize;
    ch_reg->CTL_L.bit.SRC_WIDTH = srcStep;
    ch_reg->CTL_L.bit.DST_WIDTH = destStep;
}

void DMA_configTransferSize(uint32_t base, uint32_t transferSize)
{
    volatile struct DMA_CH_REGS *ch_reg = (volatile struct DMA_CH_REGS *)base;

    if (transferSize > DMA_MAX_BLOCK_TS)
        transferSize = DMA_MAX_BLOCK_TS;

    ch_reg->BLOCK_TS            = transferSize;
}

void DMA_configMode(uint32_t base, DMA_Trigger srcTrigger, DMA_Trigger destTrigger)
{
    volatile struct DMA_CH_REGS *ch_reg = (volatile struct DMA_CH_REGS *)base;

    ch_reg->CFG2_H.bit.HS_SEL_SRC = 0;
    ch_reg->CFG2_L.bit.SRC_PER    = srcTrigger;
    ch_reg->CFG2_H.bit.HS_SEL_DST = 0;
    ch_reg->CFG2_L.bit.DST_PER    = destTrigger;

    if ((srcTrigger == 0) && (destTrigger == 0))
    {
        ch_reg->CFG2_H.bit.TT_FC = DMA_M2M_DMA;
        ch_reg->CTL_L.bit.SINC   = 0;
        ch_reg->CTL_L.bit.DINC   = 0;
    }
    else if ((srcTrigger == 0) && (destTrigger != 0))
    {
        ch_reg->CFG2_H.bit.TT_FC = DMA_M2P_DMA;
        ch_reg->CTL_L.bit.SINC   = 0;
        ch_reg->CTL_L.bit.DINC   = 1;
    }
    else if ((srcTrigger != 0) && (destTrigger == 0))
    {
        ch_reg->CFG2_H.bit.TT_FC = DMA_P2M_DMA;
        ch_reg->CTL_L.bit.SINC   = 1;
        ch_reg->CTL_L.bit.DINC   = 0;
    }
    else
    {
        ch_reg->CFG2_H.bit.TT_FC = DMA_P2P_DMA;
        ch_reg->CTL_L.bit.SINC   = 1;
        ch_reg->CTL_L.bit.DINC   = 1;
    }
}
