#ifndef QX_DMA_H
#define QX_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_dma.h"
#include "inc/hw_dma.h"
#include "define.h"

typedef enum
{
    DMA_M2M_DMA = 0x0,
    DMA_M2P_DMA = 0x1,
    DMA_P2M_DMA = 0x2,
    DMA_P2P_DMA = 0x3,
    DMA_M2P_SRC = 0x4,
    DMA_P2P_SRC = 0x5,
    DMA_P2M_DST = 0x6,
    DMA_P2P_DST = 0x7
} DMA_TtFc;

typedef enum
{
    DMA_MSIZE_1    = 0x0,
    DMA_MSIZE_4    = 0x1,
    DMA_MSIZE_8    = 0x2,
    DMA_MSIZE_16   = 0x3,
    DMA_MSIZE_32   = 0x4,
    DMA_MSIZE_64   = 0x5,
    DMA_MSIZE_128  = 0x6,
    DMA_MSIZE_256  = 0x7,
    DMA_MSIZE_512  = 0x8,
    DMA_MSIZE_1024 = 0x9
} DMA_BurstLength;

typedef enum
{
    DMA_MBLK_TYPE_CONTIGUOUS = 0,
    DMA_MBLK_TYPE_RELOAD,
    DMA_MBLK_TYPE_SHADOW_REG,
    DMA_MBLK_TYPE_LL
} DMA_MultBlockType;

typedef enum
{
    DMA_IRQ_CH1_ACTIVE    = BIT(0),
    DMA_IRQ_CH2_ACTIVE    = BIT(1),
    DMA_IRQ_CH3_ACTIVE    = BIT(2),
    DMA_IRQ_CH4_ACTIVE    = BIT(3),
    DMA_IRQ_CH5_ACTIVE    = BIT(4),
    DMA_IRQ_CH6_ACTIVE    = BIT(5),
    DMA_IRQ_COMMON_ACTIVE = BIT(16)
} DMA_IrqStatus;

typedef enum
{
    DMA_COMM_IRQ_NONE      = 0,
    DMA_SLVIF_DEC_ERR      = BIT(0),
    DMA_SLVIF_WR2RO_ERR    = BIT(1),
    DMA_SLVIF_RD2WO_ERR    = BIT(2),
    DMA_SLVIF_DRONHOLD_ERR = BIT(3),
    DMA_SLVIF_WRPARITY_ERR = BIT(7),
    DMA_SLVIF_OF_DEC_ERR   = BIT(8)
} DMA_CommIrq;

typedef enum
{
    DMA_IRQ_NONE             = 0,
    DMA_IRQ_BLOCK_TRF        = BIT(0),
    DMA_IRQ_DMA_TRF          = BIT(1),
    DMA_IRQ_SRC_TRAN         = BIT(3),
    DMA_IRQ_DST_TRAN         = BIT(4),
    DMA_IRQ_SRC_DEC_ERR      = BIT(5),
    DMA_IRQ_DST_DEC_ERR      = BIT(6),
    DMA_IRQ_SRC_SLV_ERR      = BIT(7),
    DMA_IRQ_DST_SLV_ERR      = BIT(8),
    DMA_IRQ_LLI_RD_DEC_ERR   = BIT(9),
    DMA_IRQ_LLI_WR_DEC_ERR   = BIT(10),
    DMA_IRQ_LLI_RD_SLV_ERR   = BIT(11),
    DMA_IRQ_LLI_WR_SLV_ERR   = BIT(12),
    DMA_IRQ_INVALID_ERR      = BIT(13),
    DMA_IRQ_MULTIBLKTYPE_ERR = BIT(14),
    DMA_IRQ_DEC_ERR          = BIT(16),
    DMA_IRQ_WR2RO_ERR        = BIT(17),
    DMA_IRQ_RD2RWO_ERR       = BIT(18),
    DMA_IRQ_WRONCHEN_ERR     = BIT(19),
    DMA_IRQ_SHADOWREG_ERR    = BIT(20),
    DMA_IRQ_WRONHOLD_ERR     = BIT(21),
    DMA_IRQ_LOCK_CLEARED     = BIT(27),
    DMA_IRQ_SRC_SUSPENDED    = BIT(28),
    DMA_IRQ_SUSPENDED        = BIT(29),
    DMA_IRQ_DISABLED         = BIT(30),
    DMA_IRQ_ABORTED          = BIT(31),
    DMA_IRQ_ALL_ERR          = ((unsigned long)(0x2F << 15 | 0x2FF << 4)),
    DMA_IRQ_ALL              = 0xFFFFFFFFUL
} DMA_ChIrq;

typedef enum
{
    DMA_HS_HARDWARE = 0,
    DMA_HS_SOFTWARE = 1
} DMA_HandShakeType;

typedef enum
{
    DMA_TRANS_WIDTH_8   = 0x0,
    DMA_TRANS_WIDTH_16  = 0x1,
    DMA_TRANS_WIDTH_32  = 0x2,
    DMA_TRANS_WIDTH_64  = 0x3,
    DMA_TRANS_WIDTH_128 = 0x4,
    DMA_TRANS_WIDTH_256 = 0x5,
    DMA_TRANS_WIDTH_512 = 0x6,
    DMA_TRANS_WIDTH_MAX = DMA_TRANS_WIDTH_512
} DMA_TransferWidth;

typedef enum
{
    DMA_TRIGGER_NONE       = 0,
    DMA_TRIGGER_MEM        = 0,
    DMA_TRIGGER_ADCA1      = 1,
    DMA_TRIGGER_HRADCA1    = 1,
    DMA_TRIGGER_ADCA2      = 2,
    DMA_TRIGGER_HRADCA2    = 2,
    DMA_TRIGGER_ADCA3      = 3,
    DMA_TRIGGER_HRADCA3    = 3,
    DMA_TRIGGER_ADCA4      = 4,
    DMA_TRIGGER_HRADCA4    = 4,
    DMA_TRIGGER_ADCAEVT    = 5,
    DMA_TRIGGER_HRADCAEVT  = 5,
    DMA_TRIGGER_ADCB1      = 6,
    DMA_TRIGGER_HRADCB1    = 6,
    DMA_TRIGGER_ADCB2      = 7,
    DMA_TRIGGER_HRADCB2    = 7,
    DMA_TRIGGER_ADCB3      = 8,
    DMA_TRIGGER_HRADCB3    = 8,
    DMA_TRIGGER_ADCB4      = 9,
    DMA_TRIGGER_HRADCB4    = 9,
    DMA_TRIGGER_ADCBEVT    = 10,
    DMA_TRIGGER_HRADCBEVT  = 10,
    DMA_TRIGGER_ADCC1      = 11,
    DMA_TRIGGER_HRADCC1    = 11,
    DMA_TRIGGER_ADCC2      = 12,
    DMA_TRIGGER_HRADCC2    = 12,
    DMA_TRIGGER_ADCC3      = 13,
    DMA_TRIGGER_HRADCC3    = 13,
    DMA_TRIGGER_ADCC4      = 14,
    DMA_TRIGGER_HRADCC4    = 14,
    DMA_TRIGGER_ADCCEVT    = 15,
    DMA_TRIGGER_HRADCCEVT  = 15,
    DMA_TRIGGER_XINT1      = 16,
    DMA_TRIGGER_XINT2      = 17,
    DMA_TRIGGER_XINT3      = 18,
    DMA_TRIGGER_XINT4      = 19,
    DMA_TRIGGER_XINT5      = 20,
    DMA_TRIGGER_EPWM1SOCA  = 21,
    DMA_TRIGGER_EPWM1SOCB  = 22,
    DMA_TRIGGER_EPWM2SOCA  = 23,
    DMA_TRIGGER_EPWM2SOCB  = 24,
    DMA_TRIGGER_EPWM3SOCA  = 25,
    DMA_TRIGGER_EPWM3SOCB  = 26,
    DMA_TRIGGER_EPWM4SOCA  = 27,
    DMA_TRIGGER_EPWM4SOCB  = 28,
    DMA_TRIGGER_EPWM5SOCA  = 29,
    DMA_TRIGGER_EPWM5SOCB  = 30,
    DMA_TRIGGER_EPWM6SOCA  = 31,
    DMA_TRIGGER_EPWM6SOCB  = 32,
    DMA_TRIGGER_EPWM7SOCA  = 33,
    DMA_TRIGGER_EPWM7SOCB  = 34,
    DMA_TRIGGER_EPWM8SOCA  = 35,
    DMA_TRIGGER_EPWM8SOCB  = 36,
    DMA_TRIGGER_TINT0      = 37,
    DMA_TRIGGER_TINT1      = 38,
    DMA_TRIGGER_TINT2      = 39,
    DMA_TRIGGER_ECAP1      = 40,
    DMA_TRIGGER_ECAP2      = 41,
    DMA_TRIGGER_ECAP3      = 42,
    DMA_TRIGGER_ECAP4      = 43,
    DMA_TRIGGER_ECAP5      = 44,
    DMA_TRIGGER_ECAP6      = 45,
    DMA_TRIGGER_ECAP7      = 46,
    DMA_TRIGGER_SDFM1FLT1  = 47,
    DMA_TRIGGER_SDFM1FLT2  = 48,
    DMA_TRIGGER_SDFM1FLT3  = 49,
    DMA_TRIGGER_SDFM1FLT4  = 50,
    DMA_TRIGGER_SPIA_M_TX  = 51,
    DMA_TRIGGER_SPIA_S_TX  = 51,
    DMA_TRIGGER_SPIA_M_RX  = 52,
    DMA_TRIGGER_SPIA_S_RX  = 52,
    DMA_TRIGGER_SPIB_M_TX  = 53,
    DMA_TRIGGER_SPIB_S_TX  = 53,
    DMA_TRIGGER_SPIB_M_RX  = 54,
    DMA_TRIGGER_SPIB_S_RX  = 54,
    DMA_TRIGGER_EPWM9SOCA  = 55,
    DMA_TRIGGER_EPWM9SOCB  = 56,
    DMA_TRIGGER_EPWM10SOCA = 57,
    DMA_TRIGGER_EPWM10SOCB = 58,
    DMA_TRIGGER_EPWM11SOCA = 59,
    DMA_TRIGGER_EPWM11SOCB = 60,
    DMA_TRIGGER_EPWM12SOCA = 61,
    DMA_TRIGGER_SCIATX     = 61,
    DMA_TRIGGER_SCIBTX     = 61,
    DMA_TRIGGER_EPWM12SOCB = 62,
    DMA_TRIGGER_SCIARX     = 62,
    DMA_TRIGGER_SCIBRX     = 62,
    DMA_TRIGGER_FSITXA     = 63,
    DMA_TRIGGER_FSIRXA     = 63
} DMA_Trigger;

typedef enum
{
    DMA_EMULATION_STOP,
    DMA_EMULATION_FREE_RUN
} DMA_EmulationMode;

typedef enum
{
    DMA_INT_AT_BEGINNING,
    DMA_INT_AT_END
} DMA_InterruptMode;

typedef struct
{
    u32 srcAddr;
    u32 destAddr;
    u32 blockSize;
    DMA_TransferWidth srcWidth;
    DMA_TransferWidth destWidth;
    DMA_BurstLength srcMsize;
    DMA_BurstLength destMsize;
    DMA_TtFc TT_FC;
    DMA_Trigger srcHSInterface;
    DMA_Trigger destHSInterface;
    DMA_HandShakeType srcHSType;
    DMA_HandShakeType destHSType;
} DMA_ConfigParams;

#ifdef DEBUG
static inline DMA_isBaseValid(uint32_t base)
{
    return ((base == DMA_CH1_BASE) || (base == DMA_CH2_BASE) || (base == DMA_CH3_BASE)
            || (base == DMA_CH4_BASE) || (base == DMA_CH5_BASE) || (base == DMA_CH6_BASE));
}
#endif

static inline void DMA_initController(void)
{
    DmaRegs.CFG.bit.DMAC_EN = 1;
    DmaRegs.CFG.bit.INT_EN  = 1;
}

static inline void DMA_triggerSoftReset(void)
{
    DmaRegs.RESET = 0x1;
}

static inline void DMA_setEmulationMode(DMA_EmulationMode mode)
{ }

static inline void DMA_enableTrigger(uint32_t base)
{
    ASSERT(DMA_isBaseValid(base));
    ((volatile struct DMA_CH_REGS *)base)->CFG2_H.bit.HS_SEL_SRC = 0;
    ((volatile struct DMA_CH_REGS *)base)->CFG2_H.bit.HS_SEL_DST = 0;
}

static inline void DMA_disableTrigger(uint32_t base)
{
    ASSERT(DMA_isBaseValid(base));
    ((volatile struct DMA_CH_REGS *)base)->CFG2_H.bit.HS_SEL_SRC = 1;
    ((volatile struct DMA_CH_REGS *)base)->CFG2_H.bit.HS_SEL_DST = 1;
}

static inline void DMA_forceTrigger(uint32_t base)
{ }

static inline void DMA_clearTriggerFlag(uint32_t base)
{ }

static inline bool DMA_getTransferStatusFlag(uint32_t base)
{
    ASSERT(DMA_isBaseValid(base));
    return ((volatile struct DMA_CH_REGS *)base)->INTSTATUS & 0x2U;
}

static inline bool DMA_getBurstStatusFlag(uint32_t base)
{
    ASSERT(DMA_isBaseValid(base));
    return ((volatile struct DMA_CH_REGS *)base)->INTSTATUS & 0x1U;
}

static inline bool DMA_getRunStatusFlag(uint32_t base)
{
    ASSERT(DMA_isBaseValid(base));
    return DmaRegs.CHEN & (1 << ((base - DMA_CH1_BASE) / 0x100));
}

static inline bool DMA_getOverflowFlag(uint32_t base)
{
    return 0;
}

static inline bool DMA_getTriggerFlagStatus(uint32_t base)
{
    return 0;
}

static inline void DMA_startChannel(u8 channel)
{
    DmaRegs.CHEN |= (0x101 << (channel - 1));
}

static inline void DMA_stopChannel(u8 channel)
{
    DmaRegs.CHEN &= ~(0x101 << (channel - 1));
}

static inline u32 DMA_getInterruptStatus(uint32_t base)
{
    return ((volatile struct DMA_CH_REGS *)(base))->INTSTATUS;
}

static inline void DMA_disableAllInterrupt(uint32_t base)
{
    ((volatile struct DMA_CH_REGS *)(base))->INTSIGNAL_EN = 0;
}

static inline void DMA_disableAllInterruptStatus(uint32_t base)
{
    ((volatile struct DMA_CH_REGS *)(base))->INTSTATUS_EN = 0;
}

static inline void DMA_enableInterrupt(uint32_t base, u32 flag)
{
    ((volatile struct DMA_CH_REGS *)(base))->INTSIGNAL_EN |= flag;
}

static inline void DMA_enableInterruptStatus(uint32_t base, u32 flag)
{
    ((volatile struct DMA_CH_REGS *)(base))->INTSTATUS_EN |= flag;
}

static inline void DMA_disableInterrupt(uint32_t base, u32 flag)
{
    ((volatile struct DMA_CH_REGS *)(base))->INTSIGNAL_EN &= (~flag);
}

static inline void DMA_disableInterruptStatus(uint32_t base, u32 flag)
{
    ((volatile struct DMA_CH_REGS *)(base))->INTSTATUS_EN &= (~flag);
}

static inline void DMA_enableOverrunInterrupt(uint32_t base)
{ }

static inline void DMA_disableOverrunInterrupt(uint32_t base)
{ }

static inline void DMA_clearErrorFlag(uint32_t base, u32 flag)
{
    ((volatile struct DMA_CH_REGS *)(base))->INTCLEAR = flag;
}

static inline void DMA_setInterruptMode(uint32_t base, DMA_InterruptMode mode)
{ }

static inline void DMA_setPriorityMode(bool ch1IsHighPri)
{
    if (ch1IsHighPri)
        ((volatile struct DMA_CH_REGS *)(DMA_CH1_BASE))->CFG2_H.bit.CH_PRIOR = 5;
    else
        ((volatile struct DMA_CH_REGS *)(DMA_CH1_BASE))->CFG2_H.bit.CH_PRIOR = 0;
}

static inline void DMA_configSourceAddress(uint32_t base, const void *srcAddr)
{
    ASSERT(DMA_isBaseValid(base));
    ((volatile struct DMA_CH_REGS *)base)->SAR = *(u32 *)srcAddr;
}

static inline void DMA_configDestAddress(uint32_t base, const void *destAddr)
{
    ASSERT(DMA_isBaseValid(base));
    ((volatile struct DMA_CH_REGS *)base)->DAR = *(u32 *)destAddr;
}

extern void DMA_configChannel(uint32_t base, const DMA_ConfigParams *config);

extern void DMA_configAddress(uint32_t base, const void *destAddr, const void *srcAddr);

extern void DMA_configSrcAddress(uint32_t base, const void *srcAddr);

extern void DMA_configBurst(uint32_t base, uint16_t size, int16_t srcStep, int16_t destStep);

extern void DMA_configTransfer(
    uint32_t base, uint32_t transferSize, int16_t srcStep, int16_t destStep);

extern void DMA_configTransferSize(uint32_t base, uint32_t transferSize);

extern void DMA_configMode(uint32_t base, DMA_Trigger trigger, uint32_t config);

#ifdef __cplusplus
}
#endif

#endif
