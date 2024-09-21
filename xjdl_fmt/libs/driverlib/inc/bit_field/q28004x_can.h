#ifndef Q28004X_CAN_H
#define Q28004X_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_types.h"

//---------------------------------------------------------------------------
// CAN Register Bit Definitions:

struct CAN_MODE_BIT
{
    Uint32 RM  : 1; /* [0] */
    Uint32 LOM : 1; /* [1] */
    Uint32 STM : 1; /* [2] */
    Uint32 AFM : 1; /* [3] */
    Uint32 SM  : 1; /* [4] */
};

union CAN_MODE_REG
{
    Uint32 all;
    struct CAN_MODE_BIT bit;
};

struct CAN_CMD_BIT
{
    Uint32 TR  : 1; /* [0] */
    Uint32 AT  : 1; /* [1] */
    Uint32 RRB : 1; /* [2] */
    Uint32 CDO : 1; /* [3] */
    Uint32 SRR : 1; /* [4] */
};

union CAN_CMD_REG
{
    Uint32 all;
    struct CAN_CMD_BIT bit;
};

struct CAN_SR_BIT
{
    Uint32 RBS : 1; /* [0] */
    Uint32 DOS : 1; /* [1] */
    Uint32 TBS : 1; /* [2] */
    Uint32 TCS : 1; /* [3] */
    Uint32 RS  : 1; /* [4] */
    Uint32 TS  : 1; /* [5] */
    Uint32 ES  : 1; /* [6] */
    Uint32 BS  : 1; /* [7] */
};

union CAN_SR_REG
{
    Uint32 all;
    struct CAN_SR_BIT bit;
};

struct CAN_IR_BIT
{
    Uint32 RI  : 1; /* [0] */
    Uint32 TI  : 1; /* [1] */
    Uint32 EI  : 1; /* [2] */
    Uint32 DOI : 1; /* [3] */
    Uint32 WUI : 1; /* [4] */
    Uint32 EPI : 1; /* [5] */
    Uint32 ALI : 1; /* [6] */
    Uint32 BEI : 1; /* [7] */
};

union CAN_IR_REG
{
    Uint32 all;
    struct CAN_IR_BIT bit;
};

struct CAN_IER_BIT
{
    Uint32 RIE  : 1; /* [0] */
    Uint32 TIE  : 1; /* [1] */
    Uint32 EIE  : 1; /* [2] */
    Uint32 DOIE : 1; /* [3] */
    Uint32 WUIE : 1; /* [4] */
    Uint32 EPIE : 1; /* [5] */
    Uint32 ALIE : 1; /* [6] */
    Uint32 BEIE : 1; /* [7] */
};

union CAN_IER_REG
{
    Uint32 all;
    struct CAN_IER_BIT bit;
};

struct CAN_BTR0_BIT
{
    Uint32 BRP : 6; /* [5:0] */
    Uint32 SJW : 2; /* [7:6] */
};

union CAN_BTR0_REG
{
    Uint32 all;
    struct CAN_BTR0_BIT bit;
};

struct CAN_BTR1_BIT
{
    Uint32 TSEG1 : 4; /* [3:0] */
    Uint32 TSEG2 : 3; /* [6:4] */
    Uint32 SAM   : 1; /* [7] */
};

union CAN_BTR1_REG
{
    Uint32 all;
    struct CAN_BTR1_BIT bit;
};

struct CAN_ALC_BIT
{
    Uint32 ALC : 5; /* [4:0] */
};

union CAN_ALC_REG
{
    Uint32 all;
    struct CAN_ALC_BIT bit;
};

struct CAN_ECC_BIT
{
    Uint32 SEGMENT_CODE : 5; /* [4:0] */
    Uint32 DIRECTION    : 1; /* [5] */
    Uint32 ERROR_CODE   : 2; /* [7:6] */
};

union CAN_ECC_REG
{
    Uint32 all;
    struct CAN_ECC_BIT bit;
};

struct CAN_BUFF_BIT
{
    Uint32 ACR0;
    Uint32 ACR1;
    Uint32 ACR2;
    Uint32 ACR3;
    Uint32 AMR0;
    Uint32 AMR1;
    Uint32 AMR2;
    Uint32 AMR3;
};

union CAN_BUFF_REG
{
    Uint32 BUFF[13];
    struct CAN_BUFF_BIT bit;
};

struct CAN_RMC_BIT
{
    Uint32 RMC : 5; /* [4:0] */
};

union CAN_RMC_REG
{
    Uint32 all;
    struct CAN_RMC_BIT bit;
};

struct CAN_RBSA_BIT
{
    Uint32 RBSA  : 6; /* [5:0] */
    Uint32 RSVD4 : 2; /* [7:6] */
};

union CAN_RBSA_REG
{
    Uint32 all;
    struct CAN_RBSA_BIT bit;
};

struct CAN_CDR_BIT
{
    Uint32 CDR       : 3; /* [2:0] */
    Uint32 CLOCK_OFF : 1; /* [3] */
};

union CAN_CDR_REG
{
    Uint32 all;
    struct CAN_CDR_BIT bit;
};

struct CAN_REGS
{

    union CAN_MODE_REG MODE; /* offset: 0x00 */
    union CAN_CMD_REG CMD;   /* offset: 0x04 */
    union CAN_SR_REG SR;     /* offset: 0x08 */
    union CAN_IR_REG IR;     /* offset: 0x0C */
    union CAN_IER_REG IER;   /* offset: 0x10 */
    Uint32 rcvd0;            /* offset: 0x14 */
    union CAN_BTR0_REG BTR0; /* offset: 0x18 */
    union CAN_BTR1_REG BTR1; /* offset: 0x1C */
    Uint32 OCR;              /* offset: 0x20 */
    Uint32 rsvd1;            /* offset: 0x24 */
    Uint32 rsvd2;            /* offset: 0x28 */
    union CAN_ALC_REG ALC;   /* offset: 0x2C */
    union CAN_ECC_REG ECC;   /* offset: 0x2C */
    Uint32 EWLR;             /* offset: 0x34 */
    Uint32 RXERR;            /* offset: 0x38 */
    Uint32 TXERR;            /* offset: 0x3C */
    union CAN_BUFF_REG BUFF; /* offset: offset: 0x40-0x70 */
    union CAN_RMC_REG RMC;   /* offset: 0x74 */
    union CAN_RBSA_REG RBSA; /* offset: 0x78 */
    union CAN_CDR_REG CDR;   /* offset: 0x7C */
    Uint32 RECV_FIFO[63];    /* offset: 0x80-0x17C */
    Uint32 TRANS_BUFF[13];   /* offset: 0x180-0x1B0 */
};

extern volatile struct CAN_REGS CanARegs;
extern volatile struct CAN_REGS CanBRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
