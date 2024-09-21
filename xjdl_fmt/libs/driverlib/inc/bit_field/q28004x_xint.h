#ifndef Q28004X_XINT_H
#define Q28004X_XINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_types.h"

//---------------------------------------------------------------------------
// XINT Individual Register Bit Definitions:

struct XINTCR_BITS
{                         // bits description
    Uint32 ENABLE   : 1;  // 0 XINTx Enable
    Uint32 rsvd1    : 1;  // 1 Reserved
    Uint32 POLARITY : 2;  // 3:2 XINTx Polarity
    Uint32 rsvd2    : 12; // 15:4 Reserved
};

union XINTCR_REG
{
    Uint32 all;
    struct XINTCR_BITS bit;
};

struct XTINT_DMAEN_BITS
{
	Uint32 XINT1_DMAEN : 1; //XINT1 DMA enable
	Uint32 XINT2_DMAEN : 1; //XINT2 DMA enable
	Uint32 XINT3_DMAEN : 1; //XINT3 DMA enable
	Uint32 XINT4_DMAEN : 1; //XINT4 DMA enable
	Uint32 XINT5_DMAEN : 1; //XINT5 DMA enable
	Uint32 rsvd        : 3;
	Uint32 TINT0_DMAEN : 1; //TINT0 DMA enable
	Uint32 TINT1_DMAEN : 1; //TINT1 DMA enable
	Uint32 TINT2_DMAEN : 1; //TINT2 DMA enable
};

union XTINT_DMAEN_REG
{
	Uint32 all;
	struct XTINT_DMAEN_BITS bit;
};

struct XTINT_OVERFCLR_BITS
{
	Uint32 XINT1_OVERFCLR : 1; //XINT1 DMA enable
	Uint32 XINT2_OVERFCLR : 1; //XINT2 DMA enable
	Uint32 XINT3_OVERFCLR : 1; //XINT2 DMA enable
	Uint32 XINT4_OVERFCLR : 1; //XINT2 DMA enable
	Uint32 XINT5_OVERFCLR : 1; //XINT2 DMA enable
	Uint32 rsvd           : 3;
	Uint32 TINT0_OVERFCLR : 1; //TINT0 DMA enable
	Uint32 TINT1_OVERFCLR : 1; //TINT1 DMA enable
	Uint32 TINT2_OVERFCLR : 1; //TINT2 DMA enable
};

union XTINT_OVERFCLR_REG
{
	Uint32 all;
	struct XTINT_OVERFCLR_BITS bit;
};

struct XTINT_OVERF_BITS
{
	Uint32 XINT1_OVERF : 1; //XINT1 DMA enable
	Uint32 XINT2_OVERF : 1; //XINT2 DMA enable
	Uint32 rsvd        : 6;
	Uint32 TINT0_OVERF : 1; //TINT0 DMA enable
	Uint32 TINT1_OVERF : 1; //TINT1 DMA enable
	Uint32 TINT2_OVERF : 1; //TINT2 DMA enable
};

union XTINT_OVERF_REG
{
	Uint32 all;
	struct XTINT_OVERF_BITS bit;
};

struct XINT_REGS
{
    union XINTCR_REG XINT1CR; // 0x00 XINT1 configuration register
    union XINTCR_REG XINT2CR; // 0x04 XINT2 configuration register
    union XINTCR_REG XINT3CR; // 0x08 XINT3 configuration register
    union XINTCR_REG XINT4CR; // 0x0C XINT4 configuration register
    union XINTCR_REG XINT5CR; // 0x10 XINT5 configuration register
    Uint32 XINT1CTR;           // 0x14 XINT1 counter register
    Uint32 XINT2CTR;           // 0x18 XINT2 counter register
    Uint32 XINT3CTR;           // 0x1C XINT3 counter register
    union XTINT_DMAEN_REG XTINT_DMAEN; // 0x20 XINT TINT DMA enable
    union XTINT_OVERFCLR_REG XTINT_OVERFCLR; // 0x24 XINT TINT DMA overflow flag clear
    union XTINT_OVERF_REG XTINT_OVERF; // 0x2C XINT TINT DMA overflow flag

};

//---------------------------------------------------------------------------
// XINT External References & Function Declarations:
//

extern volatile struct XINT_REGS XintRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
