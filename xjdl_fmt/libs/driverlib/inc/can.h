#ifndef QX_CAN_H
#define QX_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_can.h"
#include "define.h"

typedef enum
{
    CAN_MODE_RESET         = 0x01U,
    CAN_MODE_LISSTEN_ONLY  = 0x02U,
    CAN_MODE_SELF_TEST     = 0x04U,
    CAN_MODE_SINGLE_FILTER = 0x08U,
    CAN_MODE_DOUBLE_FILTER = 0x00U,
    CAN_MODE_SLEEP         = 0x10U,
} CAN_ModeType;

typedef enum
{
    CAN_FRAME_STANDARD = 0x00U,
    CAN_FRAME_EXTEND   = 0x01U,
} CAN_FrameType;

typedef enum
{
    CAN_FRAME_DATA   = 0x00U,
    CAN_FRAME_REMOTE = 0x01U,
} CAN_FrameDataType;

typedef enum
{
    CAN_CMD_TRANS_REQUEST       = 0x01U,
    CAN_CMD_ABOART_TARNS        = 0x02U,
    CAN_CMD_RELEASE_RECV_BUFF   = 0x04U,
    CAN_CMD_CLEAR_DATA_OVERRUN  = 0x08U,
    CAN_CMD_SELF_RECEPT_REQUEST = 0x10U,
} CAN_CmdType;

typedef enum
{
    CAN_STATUS_RECV_BUFFER    = 0x01U,
    CAN_STATUS_DATA_OVERRUN   = 0x02U,
    CAN_STATUS_TRANS_BUFFER   = 0x04U,
    CAN_STATUS_TRANS_COMPIETE = 0x08U,
    CAN_STATUS_RECV_PROCESS   = 0x10U,
    CAN_STATUS_TRANS_PROCESS  = 0x20U,
    CAN_STATUS_ERROR          = 0x40U,
    CAN_STATUS_BUS_OFF        = 0x80U,
} CAN_StatusType;

typedef enum
{
    CAN_INT_NONE             = 0x00U,
    CAN_INT_RECV             = 0x01U,
    CAN_INT_TRANS            = 0x02U,
    CAN_INT_ERROR_WARNNING   = 0x04U,
    CAN_INT_OVERRUN          = 0x08U,
    CAN_INT_WAKEUP           = 0x10U,
    CAN_INT_ERROR_PASSIVE    = 0x20U,
    CAN_INT_ARBITRATION_LOST = 0x40U, // normal no need enable
    CAN_INT_BUS_ERROR        = 0x80U, // normal no need enable
    CAN_INT_ALL              = 0xFFU,
} CAN_IntType;

typedef enum
{
    CAN_OUTPUT_MODE_NORMAL   = 0x02U,
    CAN_OUTPUT_MODE_CLOCKOUT = 0x03U,
} CAN_OutputModeType;

typedef enum
{
    CAN_LOST_ID28_BIT = 0x00U,
    CAN_LOST_ID27_BIT = 0x01U,
    CAN_LOST_ID26_BIT = 0x02U,
    CAN_LOST_ID25_BIT = 0x03U,
    CAN_LOST_ID24_BIT = 0x04U,
    CAN_LOST_ID23_BIT = 0x05U,
    CAN_LOST_ID22_BIT = 0x06U,
    CAN_LOST_ID21_BIT = 0x07U,
    CAN_LOST_ID20_BIT = 0x08U,
    CAN_LOST_ID19_BIT = 0x09U,
    CAN_LOST_ID18_BIT = 0x0AU,
    CAN_LOST_SRTR_BIT = 0x0BU,
    CAN_LOST_IDE_BIT  = 0x0CU,
    CAN_LOST_ID17_BIT = 0x0DU,
    CAN_LOST_ID16_BIT = 0x0EU,
    CAN_LOST_ID15_BIT = 0x0FU,
    CAN_LOST_ID14_BIT = 0x10U,
    CAN_LOST_ID13_BIT = 0x11U,
    CAN_LOST_ID12_BIT = 0x12U,
    CAN_LOST_ID11_BIT = 0x13U,
    CAN_LOST_ID10_BIT = 0x14U,
    CAN_LOST_ID9_BIT  = 0x15U,
    CAN_LOST_ID8_BIT  = 0x16U,
    CAN_LOST_ID7_BIT  = 0x17U,
    CAN_LOST_ID6_BIT  = 0x18U,
    CAN_LOST_ID5_BIT  = 0x19U,
    CAN_LOST_ID4_BIT  = 0x1AU,
    CAN_LOST_ID3_BIT  = 0x1BU,
    CAN_LOST_ID2_BIT  = 0x1CU,
    CAN_LOST_ID1_BIT  = 0x1DU,
    CAN_LOST_ID0_BIT  = 0x1EU,
    CAN_LOST_RTR_BIT  = 0x1FU,
} CAN_ArbitrationLostType;

typedef enum
{
    CAN_BIT_ERROR   = 0x00U,
    CAN_FORM_ERROR  = 0x01U,
    CAN_STUFF_ERROR = 0x02U,
    CAN_OTHER_ERROR = 0x03U,
} CAN_ErrorType;

typedef enum
{
    CAN_SEG_START_OF_FRAME        = 0x03U,
    CAN_SEG_ID28_TO_ID21          = 0x02U,
    CAN_SEG_ID20_TO_ID18          = 0x06U,
    CAN_SEG_SRTR_BIT              = 0x04U,
    CAN_SEG_IDE_BIT               = 0x05U,
    CAN_SEG_ID17_TO_ID13          = 0x07U,
    CAN_SEG_ID12_TO_ID5           = 0x0FU,
    CAN_SEG_ID4_TO_ID0            = 0x0EU,
    CAN_SEG_RTR_BIT               = 0x0CU,
    CAN_SEG_RESERVE_BIT_1         = 0x0DU,
    CAN_SEG_RESERVE_BIT_0         = 0x09U,
    CAN_SEG_DATA_LEN_CODE         = 0x0BU,
    CAN_SEG_DATA_FIELD            = 0x0AU,
    CAN_SEG_CRC_SEQUENCE          = 0x08U,
    CAN_SEG_CRC_DELIMITER         = 0x24U,
    CAN_SEG_ACKNOWLEDGE           = 0x19U,
    CAN_SEG_ACKNOWLEDGE_DELIMITER = 0x1BU,
    CAN_SEG_END_OF_FRAME          = 0x1AU,
    CAN_SEG_INTERMISSION          = 0x18U,
    CAN_SEG_ACTIVE_ERROR_FLAG     = 0x17U,
    CAN_SEG_PASSIVE_ERROR_FLAG    = 0x20U,
    CAN_SEG_TOLERATE_DOMAIN_BIT   = 0x19U,
    CAN_SEG_ERROR_DELIMITER       = 0x23U,
    CAN_SEG_OVERLOAD_FLAG         = 0x28U,
} CAN_SegmentCodeType;

typedef enum
{
    CAN_CLKOUT_DIV_2  = 0x00U,
    CAN_CLKOUT_DIV_4  = 0x01U,
    CAN_CLKOUT_DIV_6  = 0x02U,
    CAN_CLKOUT_DIV_8  = 0x03U,
    CAN_CLKOUT_DIV_10 = 0x04U,
    CAN_CLKOUT_DIV_12 = 0x05U,
    CAN_CLKOUT_DIV_14 = 0x06U,
    CAN_CLKOUT_DIV_1  = 0x07U,
} CAN_ClkOutDivType;

/* clang-format off */
#define STA_FRAME_SINGLE_FITER(ID, FRMAE_DATA_TYPE, DATA1, DATA2) \
(((ID) << 21) | ((FRMAE_DATA_TYPE) << 20) | ((DATA1) << 8) | (DATA2))

#define STA_FRAME_DOUBLE_FITER(ID1, FRAME_DATA_TYPE1, ID2, FRAME_DATA_TYPE2, DATA1, DATA2) \
(((ID1) << 21) | ((FRAME_DATA_TYPE1) << 20) | (((DATA1) >> 4) << 19)| \
((ID2) <<   5) | ((FRAME_DATA_TYPE2) <<  4) | ((DATA2)  >> 4))

#define EXT_FRAME_SINGLE_FITER(ID, FRMAE_DATA_TYPE) \
(((ID) << 3) | ((FRMAE_DATA_TYPE) << 2))

#define EXT_FRAME_DOUBLE_FITER(ID1, ID2) \
((((ID1) >> 13) << 16) | ((ID2) >> 13))
/* clang-format on */

STATIC_INLINE void CAN_setMode(uint32_t base, CAN_ModeType modes)
{
    ((volatile struct CAN_REGS *)base)->MODE.all = modes;
}

STATIC_INLINE void CAN_setClkDiv(uint32_t base, uint32_t div)
{
    if (base == CANA_BASE)
        DevCfgRegs.CANACLKDIV.bit.CLK_CANA_DIV_NUM = div;
    else if (base == CANB_BASE)
        DevCfgRegs.CANBCLKDIV.bit.CLK_CANB_DIV_NUM = div;
}

STATIC_INLINE void CAN_setCmd(uint32_t base, CAN_CmdType cmds)
{
    ((volatile struct CAN_REGS *)base)->CMD.all = cmds;
}

STATIC_INLINE u32 CAN_getStatus(uint32_t base)
{
    return ((volatile struct CAN_REGS *)base)->SR.all;
}

STATIC_INLINE void CAN_setInterrupt(uint32_t base, CAN_IntType ints)
{
    ((volatile struct CAN_REGS *)base)->IER.all = ints;
}

STATIC_INLINE u32 CAN_getAndAutoClearInterrupt(uint32_t base)
{
    return ((volatile struct CAN_REGS *)base)->IR.all;
}

/* can baudrate = pclk/(2 * (bpr+1) * (1 + (tseg1+1) + (tseg2+1)) */
/* sample  rate = (1 + (tseg1 + 1))/((1 + (tseg1+1) + (tseg2+1)), suggest at 75% ~ 85% */
STATIC_INLINE void CAN_setBusTiming(uint32_t base, u32 brp, u32 sjw, u32 tseg1, u32 tseg2, u32 sam)
{
    ((volatile struct CAN_REGS *)base)->BTR0.bit.BRP   = brp;
    ((volatile struct CAN_REGS *)base)->BTR0.bit.SJW   = sjw;
    ((volatile struct CAN_REGS *)base)->BTR1.bit.TSEG1 = tseg1;
    ((volatile struct CAN_REGS *)base)->BTR1.bit.TSEG2 = tseg2;
    ((volatile struct CAN_REGS *)base)->BTR1.bit.SAM   = sam;
}

STATIC_INLINE void CAN_setOutputMode(uint32_t base, CAN_OutputModeType modes)
{
    ((volatile struct CAN_REGS *)base)->OCR = modes;
}

STATIC_INLINE CAN_ArbitrationLostType CAN_getArbirationLost(uint32_t base)
{
    return ((volatile struct CAN_REGS *)base)->ALC.all;
}

STATIC_INLINE CAN_ErrorType CAN_getErrorCode(uint32_t base)
{
    return ((volatile struct CAN_REGS *)base)->ECC.bit.ERROR_CODE;
}

STATIC_INLINE CAN_SegmentCodeType CAN_getSegmentCode(uint32_t base)
{
    return ((volatile struct CAN_REGS *)base)->ECC.bit.SEGMENT_CODE;
}

STATIC_INLINE void CAN_setErrorWaningLimit(uint32_t base, u8 error_num)
{
    ((volatile struct CAN_REGS *)base)->EWLR = error_num;
}

STATIC_INLINE u8 CAN_getRecvErrorCount(uint32_t base)
{
    return ((volatile struct CAN_REGS *)base)->RXERR;
}

STATIC_INLINE u8 CAN_getTransErrorCount(uint32_t base)
{
    return ((volatile struct CAN_REGS *)base)->TXERR;
}

STATIC_INLINE void CAN_setAcceptFilter(uint32_t base, uint32_t acr, uint32_t amr)
{
    ((volatile struct CAN_REGS *)base)->BUFF.bit.ACR0 = (acr >> 24) & 0xFFU;
    ((volatile struct CAN_REGS *)base)->BUFF.bit.ACR1 = (acr >> 16) & 0xFFU;
    ((volatile struct CAN_REGS *)base)->BUFF.bit.ACR2 = (acr >> 8) & 0xFFU;
    ((volatile struct CAN_REGS *)base)->BUFF.bit.ACR3 = (acr & 0xFFU);

    ((volatile struct CAN_REGS *)base)->BUFF.bit.AMR0 = (amr >> 24) & 0xFFU;
    ((volatile struct CAN_REGS *)base)->BUFF.bit.AMR1 = (amr >> 16) & 0xFFU;
    ((volatile struct CAN_REGS *)base)->BUFF.bit.AMR2 = (amr >> 8) & 0xFFU;
    ((volatile struct CAN_REGS *)base)->BUFF.bit.AMR3 = (amr & 0xFFU);
}

STATIC_INLINE void CAN_setClockOutDivider(uint32_t base, CAN_ClkOutDivType clkout_div)
{
    ((volatile struct CAN_REGS *)base)->CDR.bit.CDR = clkout_div;
}

STATIC_INLINE void CAN_enableClockOutput(uint32_t base)
{
    ((volatile struct CAN_REGS *)base)->CDR.bit.CLOCK_OFF = 0;
}

STATIC_INLINE void CAN_disableClockOutput(uint32_t base)
{
    ((volatile struct CAN_REGS *)base)->CDR.bit.CLOCK_OFF = 1;
}

STATIC_INLINE void CAN_setRecvBuffStartOffset(uint32_t base, int offset)
{
    ((volatile struct CAN_REGS *)base)->RBSA.all = offset;
}

STATIC_INLINE void CAN_enableDMA(uint32_t base)
{ }

STATIC_INLINE void CAN_disableDMA(uint32_t base)
{ }

STATIC_INLINE u32 CAN_isTransmitterBusy(uint32_t base)
{
    return !((volatile struct CAN_REGS *)base)->SR.bit.TBS;
}

void CAN_sendStandardFrame(uint32_t base, u32 frame_id, CAN_FrameDataType rtr, const void *msg, u8 msglen);
void CAN_sendExtendFrame(uint32_t base, u32 frame_id, CAN_FrameDataType rtr, const void *msg, u8 msglen);
void CAN_recvFrameBlocking(uint32_t base, void *msg);
void CAN_recvFrameNonBlocking(uint32_t base, void *msg);

#ifdef __cplusplus
}
#endif

#endif // __QX_DSP_CAN_H
