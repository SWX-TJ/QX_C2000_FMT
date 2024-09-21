#ifndef Q28004X_INTERRUPT_H
#define Q28004X_INTERRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_types.h"

//---------------------------------------------------------------------------
// Except Register Bit Definitions:
//---------------------------------------------------------------------------

struct EXP_REGS
{
    Uint32 rsvd;  // Reserved,      offset:0x00
    Uint32 RD;    // RD Register,   offset:0x04
    Uint32 RS;    // RS Register,   offset:0x08
    Uint32 RT;    // RT Register,   offset:0x0C
    Uint32 RX;    // RX Register,   offset:0x10
    Uint32 IMM;   // IMM Register,  offset:0x14
    Uint32 EPCR;  // EPCR Register, offset:0x18
    Uint32 rsvd1; // Reserved,      offset:0x1C
    Uint32 INTM;  // INTM Register, offset:0x20
};

//---------------------------------------------------------------------------
// PIC_CTRL Register Bit Definitions:
//---------------------------------------------------------------------------

struct PIC_BITS
{ // bits description
    Uint32 GROUP1  : 1;
    Uint32 GROUP2  : 1;
    Uint32 GROUP3  : 1;
    Uint32 GROUP4  : 1;
    Uint32 GROUP5  : 1;
    Uint32 GROUP6  : 1;
    Uint32 GROUP7  : 1;
    Uint32 GROUP8  : 1;
    Uint32 GROUP9  : 1;
    Uint32 GROUP10 : 1;
    Uint32 GROUP11 : 1;
    Uint32 GROUP12 : 1;
    Uint32 TIMER1  : 1;
    Uint32 TIMER2  : 1;
    Uint32 NMI     : 1;
};

union PIC_REG
{
    Uint32 all;
    struct PIC_BITS bit;
};

struct PIE_BITS
{                      // bits description
    Uint32 INTx1  : 1; // 0 Enable for Interrupt 1.1
    Uint32 INTx2  : 1; // 1 Enable for Interrupt 1.2
    Uint32 INTx3  : 1; // 2 Enable for Interrupt 1.3
    Uint32 INTx4  : 1; // 3 Enable for Interrupt 1.4
    Uint32 INTx5  : 1; // 4 Enable for Interrupt 1.5
    Uint32 INTx6  : 1; // 5 Enable for Interrupt 1.6
    Uint32 INTx7  : 1; // 6 Enable for Interrupt 1.7
    Uint32 INTx8  : 1; // 7 Enable for Interrupt 1.8
    Uint32 INTx9  : 1; // 8 Enable for Interrupt 1.9
    Uint32 INTx10 : 1; // 9 Enable for Interrupt 1.10
    Uint32 INTx11 : 1; // 10 Enable for Interrupt 1.11
    Uint32 INTx12 : 1; // 11 Enable for Interrupt 1.12
    Uint32 INTx13 : 1; // 12 Enable for Interrupt 1.13
    Uint32 INTx14 : 1; // 13 Enable for Interrupt 1.14
    Uint32 INTx15 : 1; // 14 Enable for Interrupt 1.15
    Uint32 INTx16 : 1; // 15 Enable for Interrupt 1.16
};

union PIE_REG
{
    Uint32 all;
    struct PIE_BITS bit;
};

struct PIE_CTRL_REGS
{
    Uint32 rsvd0;           // offset:0x00
    union PIC_REG IER;      // Interrupt Enable Register, offset:0x04
    Uint32 rsvd1;           // offset: 0x08
    union PIE_REG PIEIER1;  // Interrupt Group 1 Enable Register, offset:0x0C
    union PIE_REG PIEIER2;  // Interrupt Group 2 Enable Register, offset:0x10
    union PIE_REG PIEIER3;  // Interrupt Group 3 Enable Register, offset:0x14
    union PIE_REG PIEIER4;  // Interrupt Group 4 Enable Register, offset:0x18
    union PIE_REG PIEIER5;  // Interrupt Group 5 Enable Register offset:0x1C
    union PIE_REG PIEIER6;  // Interrupt Group 6 Enable Register, offset:0x20
    union PIE_REG PIEIER7;  // Interrupt Group 7 Enable Register, offset:0x24
    union PIE_REG PIEIER8;  // Interrupt Group 8 Enable Register, offset:0x28
    union PIE_REG PIEIER9;  // Interrupt Group 9 Enable Register, offset:0x2C
    union PIE_REG PIEIER10; // Interrupt Group 10 Enable Register, offset:0x30
    union PIE_REG PIEIER11; // Interrupt Group 11 Enable Register, offset:0x34
    union PIE_REG PIEIER12; // Interrupt Group 12 Enable Register, offset:0x38
    union PIC_REG IER_RET;  // Interrupt Enable Return Register, offset:0x3C
};

extern volatile struct EXP_REGS ExpRegs;
extern volatile struct PIE_CTRL_REGS PieCtrlRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
