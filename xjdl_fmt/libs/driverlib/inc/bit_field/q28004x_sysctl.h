#ifndef Q28004X_SYSCTL_H
#define Q28004X_SYSCTL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_types.h"

//---------------------------------------------------------------------------
// Watchdog Register Bit Definitions:
//---------------------------------------------------------------------------

struct WD_CR_BIT
{
    Uint32 WD_EN : 1;  // 0 watchdog counter enable
    Uint32 RMOD  : 1;  // 1 output mode, 0=reset 1=gen interrupt
    Uint32 rsvd1 : 30; // 31:2
};

union WD_CR_REG
{
    Uint32 all;
    struct WD_CR_BIT bit;
};

struct WD_CRR_BIT
{
    Uint32 WD_CRR : 8;  // 7:0 Counter Restart Register, write to 0x76 to feed dog
    Uint32 rsvd   : 24; // 31:9
};

union WD_CRR_REG
{
    Uint32 all;
    struct WD_CRR_BIT bit;
};

struct WD_STAT_BIT
{
    Uint32 WD_STAT : 1;  // 0 Interrupt status register
    Uint32 rsvd    : 31; // 31:1
};

union WD_STAT_REG
{
    Uint32 all;
    struct WD_STAT_BIT bit;
};

struct WD_EOI_BIT
{
    Uint32 WD_EOI : 1;  // 0 Interrupt Clear Register
    Uint32 rsvd   : 31; // 31:1
};

union WD_EOI_REG
{
    Uint32 all;
    struct WD_EOI_BIT bit;
};

struct WD_REGS
{
    union WD_CR_REG WD_CR;
    Uint32 WD_TORR;
    Uint32 WD_CCVR;
    union WD_CRR_REG WD_CRR;
    union WD_STAT_REG WD_STAT;
    union WD_EOI_REG WD_EOI;
    Uint32 rsvd1[51]; // rsvd1[1] is WDT_PORT_LEVEL
    Uint32 rsvd2[7];  // WDG_PARAM resreve
};

//---------------------------------------------------------------------------
// DEV_CFG Register Bit Definitions:
//---------------------------------------------------------------------------

struct SOFTPRES0_BITS
{
    Uint32 CPU1 : 1; // [0]
};

union SOFTPRES0_REG
{
    Uint32 all;
    struct SOFTPRES0_BITS bit;
};

struct SOFTPRES1_BITS
{
    Uint32 EPWM1  : 1; // [0]
    Uint32 EPWM2  : 1; // [1]
    Uint32 EPWM3  : 1; // [2]
    Uint32 EPWM4  : 1; // [3]
    Uint32 EPWM5  : 1; // [4]
    Uint32 EPWM6  : 1; // [5]
    Uint32 EPWM7  : 1; // [6]
    Uint32 EPWM8  : 1; // [7]
    Uint32 EPWM9  : 1; // [8]
    Uint32 EPWM10 : 1; // [9]
    Uint32 EPWM11 : 1; // [10]
    Uint32 EPWM12 : 1; // [11]
};

union SOFTPRES1_REG
{
    Uint32 all;
    struct SOFTPRES1_BITS bit;
};

struct SOFTPRES2_BITS
{
    Uint32 ECAP1 : 1; // [0]
    Uint32 ECAP2 : 1; // [1]
    Uint32 ECAP3 : 1; // [2]
    Uint32 ECAP4 : 1; // [3]
    Uint32 ECAP5 : 1; // [4]
    Uint32 ECAP6 : 1; // [5]
    Uint32 ECAP7 : 1; // [6]
};

union SOFTPRES2_REG
{
    Uint32 all;
    struct SOFTPRES2_BITS bit;
};

struct SOFTPRES3_BITS
{
    Uint32 EQEP1 : 1; // [0]
    Uint32 EQEP2 : 1; // [1]
};

union SOFTPRES3_REG
{
    Uint32 all;
    struct SOFTPRES3_BITS bit;
};

struct SOFTPRES4_BITS
{
    Uint32 SD1 : 1; // [0]
};

union SOFTPRES4_REG
{
    Uint32 all;
    struct SOFTPRES4_BITS bit;
};

struct SOFTPRES5_BITS
{
    Uint32 SCIA : 1; // [0]
    Uint32 SCIB : 1; // [1]
};

union SOFTPRES5_REG
{
    Uint32 all;
    struct SOFTPRES5_BITS bit;
};

struct SOFTPRES6_BITS
{
    Uint32 SPIA : 1; // [0]
    Uint32 SPIB : 1; // [1]
};

union SOFTPRES6_REG
{
    Uint32 all;
    struct SOFTPRES6_BITS bit;
};

struct SOFTPRES7_BITS
{
    Uint32 I2CA  : 1; // [0]
    Uint32 PMUBS : 1; // [1]
};

union SOFTPRES7_REG
{
    Uint32 all;
    struct SOFTPRES7_BITS bit;
};

struct SOFTPRES8_BITS
{
    Uint32 CANA : 1; // [0]
    Uint32 CANB : 1; // [1]
};

union SOFTPRES8_REG
{
    Uint32 all;
    struct SOFTPRES8_BITS bit;
};

struct SOFTPRES9_BITS
{
    Uint32 ADCA    : 1; // [0]
    Uint32 ADCB    : 1; // [1]
    Uint32 ADCC    : 1; // [2]
    Uint32 rsvd    : 3; // [5:3]
    Uint32 ADCA_HR : 1; // [6]
    Uint32 ADCB_HR : 1; // [7]
    Uint32 ADCC_HR : 1; // [8]
};

union SOFTPRES9_REG
{
    Uint32 all;
    struct SOFTPRES9_BITS bit;
};

struct SOFTPRES10_BITS
{
    Uint32 CMPSS1 : 1; // [0]
    Uint32 CMPSS2 : 1; // [1]
    Uint32 CMPSS3 : 1; // [2]
    Uint32 CMPSS4 : 1; // [3]
    Uint32 CMPSS5 : 1; // [4]
    Uint32 CMPSS6 : 1; // [5]
    Uint32 CMPSS7 : 1; // [6]
};

union SOFTPRES10_REG
{
    Uint32 all;
    struct SOFTPRES10_BITS bit;
};

struct SOFTPRES11_BITS
{
    Uint32 PGA1 : 1; // [0]
    Uint32 PGA2 : 1; // [1]
    Uint32 PGA3 : 1; // [2]
    Uint32 PGA4 : 1; // [3]
    Uint32 PGA5 : 1; // [4]
    Uint32 PGA6 : 1; // [5]
    Uint32 PGA7 : 1; // [6]
};

union SOFTPRES11_REG
{
    Uint32 all;
    struct SOFTPRES11_BITS bit;
};

struct SOFTPRES12_BITS
{
    Uint32 DACA : 1; // [0]
    Uint32 DACB : 1; // [1]
};

union SOFTPRES12_REG
{
    Uint32 all;
    struct SOFTPRES12_BITS bit;
};

struct SOFTPRES13_BITS
{
    Uint32 LINEA : 1; // [0]
    Uint32 XINTF : 1; // [1]
};

union SOFTPRES13_REG
{
    Uint32 all;
    struct SOFTPRES13_BITS bit;
};

struct HARDWARERES0_BITS
{
    Uint32 reserve1 : 32; // [0]
};

union HARDWARERES0_REG
{
    Uint32 all;
    struct HARDWARERES0_BITS bit;
};

struct HARDWARERES1_BITS
{
    Uint32 EPWM1  : 1; // [0]
    Uint32 EPWM2  : 1; // [1]
    Uint32 EPWM3  : 1; // [2]
    Uint32 EPWM4  : 1; // [3]
    Uint32 EPWM5  : 1; // [4]
    Uint32 EPWM6  : 1; // [5]
    Uint32 EPWM7  : 1; // [6]
    Uint32 EPWM8  : 1; // [7]
    Uint32 EPWM9  : 1; // [8]
    Uint32 EPWM10 : 1; // [9]
    Uint32 EPWM11 : 1; // [10]
    Uint32 EPWM12 : 1; // [11]
};

union HARDWARERES1_REG
{
    Uint32 all;
    struct HARDWARERES1_BITS bit;
};

struct HARDWARERES2_BITS
{
    Uint32 ECAP1 : 1; // [0]
    Uint32 ECAP2 : 1; // [1]
    Uint32 ECAP3 : 1; // [2]
    Uint32 ECAP4 : 1; // [3]
    Uint32 ECAP5 : 1; // [4]
    Uint32 ECAP6 : 1; // [5]
    Uint32 ECAP7 : 1; // [6]
};

union HARDWARERES2_REG
{
    Uint32 all;
    struct HARDWARERES2_BITS bit;
};

struct HARDWARERES3_BITS
{
    Uint32 EQEP1 : 1; // [0]
    Uint32 EQEP2 : 1; // [1]
};

union HARDWARERES3_REG
{
    Uint32 all;
    struct HARDWARERES3_BITS bit;
};

struct HARDWARERES4_BITS
{
    Uint32 SD1 : 1; // [0]
};

union HARDWARERES4_REG
{
    Uint32 all;
    struct HARDWARERES4_BITS bit;
};

struct HARDWARERES5_BITS
{
    Uint32 SCIA : 1; // [0]
    Uint32 SCIB : 1; // [1]
};

union HARDWARERES5_REG
{
    Uint32 all;
    struct HARDWARERES5_BITS bit;
};

struct HARDWARERES6_BITS
{
    Uint32 SPIA : 1; // [0]
    Uint32 SPIB : 1; // [1]
};

union HARDWARERES6_REG
{
    Uint32 all;
    struct HARDWARERES6_BITS bit;
};

struct HARDWARERES7_BITS
{
    Uint32 I2CA   : 1; // [0]
    Uint32 PMBUSA : 1; // [1]
};

union HARDWARERES7_REG
{
    Uint32 all;
    struct HARDWARERES7_BITS bit;
};

struct HARDWARERES8_BITS
{
    Uint32 CANA : 1; // [0]
    Uint32 CANB : 1; // [1]
};

union HARDWARERES8_REG
{
    Uint32 all;
    struct HARDWARERES8_BITS bit;
};

struct HARDWARERES9_BITS
{
    Uint32 ADCA    : 1; // [0]
    Uint32 ADCB    : 1; // [1]
    Uint32 ADCC    : 1; // [2]
    Uint32 rsvd    : 3; // [5:3]
    Uint32 ADCA_HR : 1; // [6]
    Uint32 ADCB_HR : 1; // [7]
    Uint32 ADCC_HR : 1; // [8]
};

union HARDWARERES9_REG
{
    Uint32 all;
    struct HARDWARERES9_BITS bit;
};

struct HARDWARERES10_BITS
{
    Uint32 CMPSS1 : 1; // [0]
    Uint32 CMPSS2 : 1; // [1]
    Uint32 CMPSS3 : 1; // [2]
    Uint32 CMPSS4 : 1; // [3]
    Uint32 CMPSS5 : 1; // [4]
    Uint32 CMPSS6 : 1; // [5]
    Uint32 CMPSS7 : 1; // [6]
};

union HARDWARERES10_REG
{
    Uint32 all;
    struct HARDWARERES10_BITS bit;
};

struct HARDWARERES11_BITS
{
    Uint32 PGA1 : 1; // [0]
    Uint32 PGA2 : 1; // [1]
    Uint32 PGA3 : 1; // [2]
    Uint32 PGA4 : 1; // [3]
    Uint32 PGA5 : 1; // [4]
    Uint32 PGA6 : 1; // [5]
    Uint32 PGA7 : 1; // [6]
};

union HARDWARERES11_REG
{
    Uint32 all;
    struct HARDWARERES11_BITS bit;
};

struct HARDWARERES12_BITS
{
    Uint32 DACA : 1; // [0]
    Uint32 DACB : 1; // [1]
};

union HARDWARERES12_REG
{
    Uint32 all;
    struct HARDWARERES12_BITS bit;
};

struct HARDWARERES13_BITS
{
    Uint32 LINEA : 1; // [0]
    Uint32 XINTF : 1; // [1]
};

union HARDWARERES13_REG
{
    Uint32 all;
    struct HARDWARERES13_BITS bit;
};

struct CANFD_BITS
{
    Uint32 CANFD1 : 1; // [0]
    Uint32 CANFD2 : 1; // [1]
};

union CANFD_REG
{
    Uint32 all;
    struct CANFD_BITS bit;
};

struct FLASHREADY_BITS
{
    Uint32 FLASH_WR_READY : 1; // [0]
    Uint32 FLASH_RD_READY : 1; // [1]
};

union FLASHREADY_REG
{
    Uint32 all;
    struct FLASHREADY_BITS bit;
};

struct FLASHCLKDIV_BITS
{
    Uint32 CLK_FLASH_DIV_NUM : 16; // [0]
};

union FLASHCLKDIV_REG
{
    Uint32 all;
    struct FLASHCLKDIV_BITS bit;
};

struct CANACLKDIV_BITS
{
    Uint32 CLK_CANA_DIV_NUM : 16; // [0]
};

union CANACLKDIV_REG
{
    Uint32 all;
    struct CANACLKDIV_BITS bit;
};
struct CANBCLKDIV_BITS
{
    Uint32 CLK_CANB_DIV_NUM : 16; // [0]
};

union CANBCLKDIV_REG
{
    Uint32 all;
    struct CANBCLKDIV_BITS bit;
};

struct EMU_SUSPEND_BITS
{
    Uint32 ADCA_HS_EMU_SUSPEND : 1; // [0]
    Uint32 ADCB_HS_EMU_SUSPEND : 1; // [1]
    Uint32 ADCC_HS_EMU_SUSPEND : 1; // [2]
    Uint32 EPWM1_EMU_SUPEND    : 1; // [3]
    Uint32 EPWM2_EMU_SUPEND    : 1; // [4]
    Uint32 EPWM3_EMU_SUPEND    : 1; // [5]
    Uint32 EPWM4_EMU_SUPEND    : 1; // [6]
    Uint32 EPWM5_EMU_SUPEND    : 1; // [7]
    Uint32 EPWM6_EMU_SUPEND    : 1; // [7]
    Uint32 EPWM7_EMU_SUPEND    : 1; // [9]
    Uint32 EPWM8_EMU_SUPEND    : 1; // [10]
    Uint32 EPWM9_EMU_SUPEND    : 1; // [11]
    Uint32 EPWM10_EMU_SUPEND   : 1; // [12]
    Uint32 EPWM11_EMU_SUPEND   : 1; // [13]
    Uint32 EPWM12_EMU_SUPEND   : 1; // [14]
    Uint32 ECAP1_EMU_SUPEND    : 1; // [15]
    Uint32 ECAP2_EMU_SUPEND    : 1; // [16]
    Uint32 ECAP3_EMU_SUPEND    : 1; // [17]
    Uint32 ECAP4_EMU_SUPEND    : 1; // [18]
    Uint32 ECAP5_EMU_SUPEND    : 1; // [19]
    Uint32 ECAP6_EMU_SUPEND    : 1; // [20]
    Uint32 ECAP7_EMU_SUPEND    : 1; // [21]
    Uint32 EQEP0_EMU_SUPEND    : 1; // [22]
    Uint32 EQEP1_EMU_SUPEND    : 1; // [23]
};

union EMU_SUSPEND_REG
{
    Uint32 all;
    struct EMU_SUSPEND_BITS bit;
};

struct DEV_CFG_REGS
{
    Uint32 rsvd0[16];                      // offset:0x0 ~ 0x40
    union SOFTPRES0_REG SOFTPRES0;         // offset:0x40
    union SOFTPRES1_REG SOFTPRES1;         // offset:0x44
    union SOFTPRES2_REG SOFTPRES2;         // offset:0x48
    union SOFTPRES3_REG SOFTPRES3;         // offset:0x4C
    union SOFTPRES4_REG SOFTPRES4;         // offset:0x50
    union SOFTPRES5_REG SOFTPRES5;         // offset:0x54
    union SOFTPRES6_REG SOFTPRES6;         // offset:0x58
    union SOFTPRES7_REG SOFTPRES7;         // offset:0x5C
    union SOFTPRES8_REG SOFTPRES8;         // offset:0x60
    union SOFTPRES9_REG SOFTPRES9;         // offset:0x64
    union SOFTPRES10_REG SOFTPRES10;       // offset:0x68
    union SOFTPRES11_REG SOFTPRES11;       // offset:0x6C
    union SOFTPRES12_REG SOFTPRES12;       // offset:0x70
    union SOFTPRES13_REG SOFTPRES13;       // offset:0x74
    Uint32 rsvd1[50];                      // offset:0x13C~0x78
    union HARDWARERES0_REG HARDWARERES0;   // offset:0x140
    union HARDWARERES1_REG HARDWARERES1;   // offset:0x144
    union HARDWARERES2_REG HARDWARERES2;   // offset:0x148
    union HARDWARERES3_REG HARDWARERES3;   // offset:0x14C
    union HARDWARERES4_REG HARDWARERES4;   // offset:0x150
    union HARDWARERES5_REG HARDWARERES5;   // offset:0x154
    union HARDWARERES6_REG HARDWARERES6;   // offset:0x158
    union HARDWARERES7_REG HARDWARERES7;   // offset:0x15C
    union HARDWARERES8_REG HARDWARERES8;   // offset:0x160
    union HARDWARERES9_REG HARDWARERES9;   // offset:0x164
    union HARDWARERES10_REG HARDWARERES10; // offset:0x168
    union HARDWARERES11_REG HARDWARERES11; // offset:0x16C
    union HARDWARERES12_REG HARDWARERES12; // offset:0x170
    union HARDWARERES13_REG HARDWARERES13; // offset:0x174
    Uint32 rsvd2[6];                       // offset:0x178~0x18C
    union CANFD_REG CANFD;                 // offset:0x190
    Uint32 rsvd3[3];                       // offset:0x194~0x19C
    union FLASHCLKDIV_REG FLASHCLKDIV;     // offset:0x1A0
    union CANACLKDIV_REG CANACLKDIV;       // offset:0x1A4
    union CANBCLKDIV_REG CANBCLKDIV;       // offset:0x1A8
    union EMU_SUSPEND_REG EMU_SUSPEND;     // offset:0x1AC
    Uint32 rsvd4[44];                      // offset:0x1B0~0x25C
    Uint32 CPU0TIMER0_DIV;                 // offset:0x260
    Uint32 CPU0TIMER1_DIV;                 // offset:0x264
    Uint32 CPU0TIMER2_DIV;                 // offset:0x268
    Uint32 CPU1TIMER0_DIV;                 // offset:0x26C
    Uint32 CPU1TIMER1_DIV;                 // offset:0x270
    Uint32 CPU1TIMER2_DIV;                 // offset:0x274
};

//---------------------------------------------------------------------------
// CLK_CFG Register Bit Definitions:
//---------------------------------------------------------------------------

struct CLKSRCCTL1_BITS
{                            // bits description
    Uint32 OSCCLKSRCSEL : 2; // 1:0 OSCCLK Source Select Bit
    Uint32 rsvd1        : 1; // 2 Reserved
    Uint32 INTOSC2OFF   : 1; // 3 Internal Oscillator 2 Off Bit
    Uint32 rsvd2        : 1; // 4 Reserved
    Uint32 WDHALTI      : 1; // 5 Watchdog HALT Mode Ignore Bit
};

union CLKSRCCTL1_REG
{
    Uint32 all;
    struct CLKSRCCTL1_BITS bit;
};

struct CLKSRCCTL2_BITS
{                          // bits description
    Uint32 rsvd1      : 2; // 1:0 Reserved
    Uint32 CANACLKSEL : 2; // 3:2 CANA Bit Clock Source Select Bit
    Uint32 CANBCLKSEL : 2; // 5:4 CANB Bit Clock Source Select Bit
};

union CLKSRCCTL2_REG
{
    Uint32 all;
    struct CLKSRCCTL2_BITS bit;
};

struct CLKSRCCTL3_BITS
{                          // bits description
    Uint32 XCLKOUTSEL : 3; // 2:0 XCLKOUT Source Select Bit
};

union CLKSRCCTL3_REG
{
    Uint32 all;
    struct CLKSRCCTL3_BITS bit;
};

struct SYSPLLCTL1_BITS
{                        // bits description
    Uint32 PLLEN    : 1; // 0 SYSPLL enable/disable bit
    Uint32 PLLCLKEN : 1; // 1 SYSPLL bypassed or included in the PLLSYSCLK path
};

union SYSPLLCTL1_REG
{
    Uint32 all;
    struct SYSPLLCTL1_BITS bit;
};

struct SYSPLLMULT_BITS
{                      // bits description
    Uint32 IDIV  : 4;  // 3:0 PLL Input Divider Paramenter
    Uint32 rsvd0 : 23; // 26:4 reserve
    Uint32 RST   : 1;  // 27 enable Reset Mode
};

union SYSPLLMULT_REG
{
    Uint32 all;
    struct SYSPLLMULT_BITS bit;
};

struct SYSPLLSTS_BITS
{                     // bits description
    Uint32 LOCKS : 1; // 0 SYSPLL Lock Status Bit
    Uint32 SLIPS : 1; // 1 SYSPLL Slip Status Bit
};

union SYSPLLSTS_REG
{
    Uint32 all;
    struct SYSPLLSTS_BITS bit;
};

struct SYSCLKDIVSEL_BITS
{                            // bits description
    Uint32 PLLSYSCLKDIV : 6; // 5:0 PLLSYSCLK Divide Select
};

union SYSCLKDIVSEL_REG
{
    Uint32 all;
    struct SYSCLKDIVSEL_BITS bit;
};

struct XCLKOUTDIVSEL_BITS
{                          // bits description
    Uint32 XCLKOUTDIV : 2; // 1:0 XCLKOUT Divide Select
};

union XCLKOUTDIVSEL_REG
{
    Uint32 all;
    struct XCLKOUTDIVSEL_BITS bit;
};

struct LOSPCP_BITS
{                         // bits description
    Uint32 LSPCLKDIV : 3; // 2:0 LSPCLK Divide Select
};

union LOSPCP_REG
{
    Uint32 all;
    struct LOSPCP_BITS bit;
};

struct MCDCR_BITS
{                       // bits description
    Uint32 MCLKSTS : 1; // 0 Missing Clock Status Bit
    Uint32 MCLKCLR : 1; // 1 Missing Clock Clear Bit
    Uint32 MCLKOFF : 1; // 2 Missing Clock Detect Off Bit
    Uint32 OSCOFF  : 1; // 3 MCD Oscillator Clock Off Bit
};

union MCDCR_REG
{
    Uint32 all;
    struct MCDCR_BITS bit;
};

struct X1CNT_BITS
{                      // bits description
    Uint32 X1CNT : 10; // 9:0 X1 Counter
    Uint32 rsvd1 : 6;  // 15:10 Reserved
    Uint32 CLR   : 1;  // 16 X1 Counter Clear
};

union X1CNT_REG
{
    Uint32 all;
    struct X1CNT_BITS bit;
};

struct XTALCR_BITS
{                      // bits description
    Uint32 OSCOFF : 1; // 0 XTAL Oscillator powered-down
    Uint32 SE     : 1; // 1 XTAL Oscilator in Single-Ended mode
};

union XTALCR_REG
{
    Uint32 all;
    struct XTALCR_BITS bit;
};

struct CLKSTATUS_REG_BITS
{
    Uint32 OSC1READLY : 1;
    Uint32 OSC2READLY : 1;
    Uint32 X1READLY   : 1;
};

union CLKSTATUS_REG
{
    Uint32 all;
    struct CLKSTATUS_REG_BITS bit;
};

struct CLK_CFG_REGS
{
    union CLKSRCCTL1_REG CLKSRCCTL1; // offset:0x00 Clock Source Control register-1
    union CLKSRCCTL2_REG CLKSRCCTL2; // offset:0x04 Clock Source Control register-2
    union CLKSRCCTL3_REG CLKSRCCTL3; // offset:0x08 Clock Source Control register-3
    union SYSPLLCTL1_REG SYSPLLCTL1; // offset:0x0C SYSPLL Control register-1
    union SYSPLLMULT_REG SYSPLLMULT; // offset:0x10 SYSPLL Multiplier register
    Uint32 SYSPLL_IMULT_L;           // offset:0x14 PLL Mult Paramenter, LOW 32 bit(bit set style)
    Uint32 SYSPLL_IMULT_H;           // offset:0x18 PLL Mult Paramenter, HIGH 32 bit(bit set style)
    Uint32 SYSPLL_ODIV;              // offset:0x1C PLL Output Divider Paramenter (bit set style)
    union SYSPLLSTS_REG SYSPLLSTS;   // offest:0x20 SYSPLL Status register
    union SYSCLKDIVSEL_REG SYSCLKDIVSEL;   // offset:0x24 System Clock Divider Select register
    union XCLKOUTDIVSEL_REG XCLKOUTDIVSEL; // offset:0x28 XCLKOUT Divider Select register
    union LOSPCP_REG LOSPCP;               // offset:0x2C Low Speed Clock Source Prescalar
    union MCDCR_REG MCDCR;                 // offset:0x30 Missing Clock Detect Control Register
    union X1CNT_REG X1CNT;                 // offset:0x34 10-bit Counter on X1 Clock
    union XTALCR_REG XTALCR;               // offset:0x38 XTAL Control Register
    union CLKSTATUS_REG CLKSTATUS;         // offset:0x3C CLK Status Register
    Uint32 IMULT;                          // offset:0x40 PLL Mult Paramenter (num set style)
    Uint32 ODIV; // offset:0x44 PLL Output Divider Paramenter(num set style)
};

//---------------------------------------------------------------------------
// CPU_SYS Register Bit Definitions:
//---------------------------------------------------------------------------

struct PCLKCR0_BITS
{
    Uint32 CPU1        : 1; // [0]
    Uint32 rsvd1       : 1; // [1]
    Uint32 DMA         : 1; // [2]
    Uint32 rsvd2       : 2; // [3]
    Uint32 CPU0_TIMER0 : 1; // [5]
    Uint32 CPU0_TIMER1 : 1; // [6]
    Uint32 CPU0_TIMER2 : 1; // [7]
    Uint32 CPU1_TIMER0 : 1; // [8]
    Uint32 CPU1_TIMER1 : 1; // [9]
    Uint32 CPU1_TIMER2 : 1; // [10]
    Uint32 rsvd3       : 7; // [17:11]
    Uint32 TBCLKSYNC   : 1; // [18]
};

union PCLKCR0_REG
{
    Uint32 all;
    struct PCLKCR0_BITS bit;
};

struct PCLKCR1_BITS
{
    Uint32 EPWM1  : 1; // [0]
    Uint32 EPWM2  : 1; // [1]
    Uint32 EPWM3  : 1; // [2]
    Uint32 EPWM4  : 1; // [3]
    Uint32 EPWM5  : 1; // [4]
    Uint32 EPWM6  : 1; // [5]
    Uint32 EPWM7  : 1; // [6]
    Uint32 EPWM8  : 1; // [7]
    Uint32 EPWM9  : 1; // [8]
    Uint32 EPWM10 : 1; // [9]
    Uint32 EPWM11 : 1; // [10]
    Uint32 EPWM12 : 1; // [11]
};

union PCLKCR1_REG
{
    Uint32 all;
    struct PCLKCR1_BITS bit;
};

struct PCLKCR2_BITS
{
    Uint32 ECAP1 : 1; // [0]
    Uint32 ECAP2 : 1; // [1]
    Uint32 ECAP3 : 1; // [2]
    Uint32 ECAP4 : 1; // [3]
    Uint32 ECAP5 : 1; // [4]
    Uint32 ECAP6 : 1; // [5]
    Uint32 ECAP7 : 1; // [6]
};

union PCLKCR2_REG
{
    Uint32 all;
    struct PCLKCR2_BITS bit;
};

struct PCLKCR3_BITS
{
    Uint32 EQEP1 : 1; // [0]
    Uint32 EQEP2 : 1; // [1]
};

union PCLKCR3_REG
{
    Uint32 all;
    struct PCLKCR3_BITS bit;
};

struct PCLKCR4_BITS
{
    Uint32 SD1 : 1; // [0]
};

union PCLKCR4_REG
{
    Uint32 all;
    struct PCLKCR4_BITS bit;
};

struct PCLKCR5_BITS
{
    Uint32 SCIA : 1; // [0]
    Uint32 SCIB : 1; // [1]
};

union PCLKCR5_REG
{
    Uint32 all;
    struct PCLKCR5_BITS bit;
};

struct PCLKCR6_BITS
{
    Uint32 SPIA : 1; // [0]
    Uint32 SPIB : 1; // [1]
};

union PCLKCR6_REG
{
    Uint32 all;
    struct PCLKCR6_BITS bit;
};

struct PCLKCR7_BITS
{
    Uint32 I2CA   : 1; // [0]
    Uint32 PMBUSA : 1; // [1]
};

union PCLKCR7_REG
{
    Uint32 all;
    struct PCLKCR7_BITS bit;
};

struct PCLKCR8_BITS
{
    Uint32 CANA : 1; // [0]
    Uint32 CANB : 1; // [1]
};

union PCLKCR8_REG
{
    Uint32 all;
    struct PCLKCR8_BITS bit;
};

struct PCLKCR9_BITS
{
    Uint32 ADCA    : 1; // [0]
    Uint32 ADCB    : 1; // [1]
    Uint32 ADCC    : 1; // [2]
    Uint32 rsvd    : 3; // [5:3]
    Uint32 ADCA_HR : 1; // [6]
    Uint32 ADCB_HR : 1; // [7]
    Uint32 ADCC_HR : 1; // [8]
};

union PCLKCR9_REG
{
    Uint32 all;
    struct PCLKCR9_BITS bit;
};

struct PCLKCR10_BITS
{
    Uint32 CMPSS1 : 1; // [0]
    Uint32 CMPSS2 : 1; // [1]
    Uint32 CMPSS3 : 1; // [2]
    Uint32 CMPSS4 : 1; // [3]
    Uint32 CMPSS5 : 1; // [4]
    Uint32 CMPSS6 : 1; // [5]
    Uint32 CMPSS7 : 1; // [6]
};

union PCLKCR10_REG
{
    Uint32 all;
    struct PCLKCR10_BITS bit;
};

struct PCLKCR11_BITS
{
    Uint32 PGA1 : 1; // [0]
    Uint32 PGA2 : 1; // [1]
    Uint32 PGA3 : 1; // [2]
    Uint32 PGA4 : 1; // [3]
    Uint32 PGA5 : 1; // [4]
    Uint32 PGA6 : 1; // [5]
    Uint32 PGA7 : 1; // [6]
};

union PCLKCR11_REG
{
    Uint32 all;
    struct PCLKCR11_BITS bit;
};

struct PCLKCR12_BITS
{
    Uint32 DACA : 1; // [0]
    Uint32 DACB : 1; // [1]
};

union PCLKCR12_REG
{
    Uint32 all;
    struct PCLKCR12_BITS bit;
};

struct PCLKCR13_BITS
{
    Uint32 LINEA : 1; // [0]
    Uint32 XINTF : 1; // [1]
};

union PCLKCR13_REG
{
    Uint32 all;
    struct PCLKCR13_BITS bit;
};

struct CPUEXPSTART_BITS
{
    Uint32 EXPSTART : 3; // [2:0]
};

union CPU0EXPSTART_REG
{
    Uint32 all;
    struct CPUEXPSTART_BITS bit;
};

union CPU1EXPSTART_REG
{
    Uint32 all;
    struct CPUEXPSTART_BITS bit;
};

struct LPMCR_BITS
{                         // bits description
    Uint32 LPMCR     : 2; // 1:0 Low Power Mode setting
    Uint32 WDINTE    : 1; // 2 watchdog interrupt enable
    Uint32 GPIOLPSEL : 1; // 3 gpio low power select
};

union LPMCR_REG
{
    Uint32 all;
    struct LPMCR_BITS bit;
};

struct TMR2CLKCTL_BITS
{                                   // bits description
    Uint32 CPU0TMR2CLKSRCSEL   : 2; // 1:0 CPU0 Timer 2 Clock Source Select Bit
    Uint32 rsvd0               : 1; // 2
    Uint32 CPU0TMR2CLKPRESCALE : 3; // 5:3 CPU0 Timer 2 Clock Pre-Scale Value
    Uint32 rsvd1               : 2; // 7:6
    Uint32 CPU1TMR2CLKSRCSEL   : 2; // 9:8 CPU1 Timer 2 Clock Source Select Bit
    Uint32 rsvd3               : 1; // 10
    Uint32 CPU1TMR2CLKPRESCALE : 3; // 13:11 CPU1 Timer 2 Clock Pre-Scale Value
};

union TMR2CLKCTL_REG
{
    Uint32 all;
    struct TMR2CLKCTL_BITS bit;
};

struct GPIOLPMSEL0_BITS
{                      // bits description
    Uint32 GPIO0  : 1; // 0 GPIO0 Enable for LPM Wakeup
    Uint32 GPIO1  : 1; // 1 GPIO1 Enable for LPM Wakeup
    Uint32 GPIO2  : 1; // 2 GPIO2 Enable for LPM Wakeup
    Uint32 GPIO3  : 1; // 3 GPIO3 Enable for LPM Wakeup
    Uint32 GPIO4  : 1; // 4 GPIO4 Enable for LPM Wakeup
    Uint32 GPIO5  : 1; // 5 GPIO5 Enable for LPM Wakeup
    Uint32 GPIO6  : 1; // 6 GPIO6 Enable for LPM Wakeup
    Uint32 GPIO7  : 1; // 7 GPIO7 Enable for LPM Wakeup
    Uint32 GPIO8  : 1; // 8 GPIO8 Enable for LPM Wakeup
    Uint32 GPIO9  : 1; // 9 GPIO9 Enable for LPM Wakeup
    Uint32 GPIO10 : 1; // 10 GPIO10 Enable for LPM Wakeup
    Uint32 GPIO11 : 1; // 11 GPIO11 Enable for LPM Wakeup
    Uint32 GPIO12 : 1; // 12 GPIO12 Enable for LPM Wakeup
    Uint32 GPIO13 : 1; // 13 GPIO13 Enable for LPM Wakeup
    Uint32 GPIO14 : 1; // 14 GPIO14 Enable for LPM Wakeup
    Uint32 GPIO15 : 1; // 15 GPIO15 Enable for LPM Wakeup
    Uint32 GPIO16 : 1; // 16 GPIO16 Enable for LPM Wakeup
    Uint32 GPIO17 : 1; // 17 GPIO17 Enable for LPM Wakeup
    Uint32 GPIO18 : 1; // 18 GPIO18 Enable for LPM Wakeup
    Uint32 GPIO19 : 1; // 19 GPIO19 Enable for LPM Wakeup
    Uint32 GPIO20 : 1; // 20 GPIO20 Enable for LPM Wakeup
    Uint32 GPIO21 : 1; // 21 GPIO21 Enable for LPM Wakeup
    Uint32 GPIO22 : 1; // 22 GPIO22 Enable for LPM Wakeup
    Uint32 GPIO23 : 1; // 23 GPIO23 Enable for LPM Wakeup
    Uint32 GPIO24 : 1; // 24 GPIO24 Enable for LPM Wakeup
    Uint32 GPIO25 : 1; // 25 GPIO25 Enable for LPM Wakeup
    Uint32 GPIO26 : 1; // 26 GPIO26 Enable for LPM Wakeup
    Uint32 GPIO27 : 1; // 27 GPIO27 Enable for LPM Wakeup
    Uint32 GPIO28 : 1; // 28 GPIO28 Enable for LPM Wakeup
    Uint32 GPIO29 : 1; // 29 GPIO29 Enable for LPM Wakeup
    Uint32 GPIO30 : 1; // 30 GPIO30 Enable for LPM Wakeup
    Uint32 GPIO31 : 1; // 31 GPIO31 Enable for LPM Wakeup
};

union GPIOLPMSEL0_REG
{
    Uint32 all;
    struct GPIOLPMSEL0_BITS bit;
};

struct GPIOLPMSEL1_BITS
{                      // bits description
    Uint32 GPIO32 : 1; // 0 GPIO32 Enable for LPM Wakeup
    Uint32 GPIO33 : 1; // 1 GPIO33 Enable for LPM Wakeup
    Uint32 GPIO34 : 1; // 2 GPIO34 Enable for LPM Wakeup
    Uint32 GPIO35 : 1; // 3 GPIO35 Enable for LPM Wakeup
    Uint32 GPIO36 : 1; // 4 GPIO36 Enable for LPM Wakeup
    Uint32 GPIO37 : 1; // 5 GPIO37 Enable for LPM Wakeup
    Uint32 GPIO38 : 1; // 6 GPIO38 Enable for LPM Wakeup
    Uint32 GPIO39 : 1; // 7 GPIO39 Enable for LPM Wakeup
    Uint32 GPIO40 : 1; // 8 GPIO40 Enable for LPM Wakeup
    Uint32 GPIO41 : 1; // 9 GPIO41 Enable for LPM Wakeup
    Uint32 GPIO42 : 1; // 10 GPIO42 Enable for LPM Wakeup
    Uint32 GPIO43 : 1; // 11 GPIO43 Enable for LPM Wakeup
    Uint32 GPIO44 : 1; // 12 GPIO44 Enable for LPM Wakeup
    Uint32 GPIO45 : 1; // 13 GPIO45 Enable for LPM Wakeup
    Uint32 GPIO46 : 1; // 14 GPIO46 Enable for LPM Wakeup
    Uint32 GPIO47 : 1; // 15 GPIO47 Enable for LPM Wakeup
    Uint32 GPIO48 : 1; // 16 GPIO48 Enable for LPM Wakeup
    Uint32 GPIO49 : 1; // 17 GPIO49 Enable for LPM Wakeup
    Uint32 GPIO50 : 1; // 18 GPIO50 Enable for LPM Wakeup
    Uint32 GPIO51 : 1; // 19 GPIO51 Enable for LPM Wakeup
    Uint32 GPIO52 : 1; // 20 GPIO52 Enable for LPM Wakeup
    Uint32 GPIO53 : 1; // 21 GPIO53 Enable for LPM Wakeup
    Uint32 GPIO54 : 1; // 22 GPIO54 Enable for LPM Wakeup
    Uint32 GPIO55 : 1; // 23 GPIO55 Enable for LPM Wakeup
    Uint32 GPIO56 : 1; // 24 GPIO56 Enable for LPM Wakeup
    Uint32 GPIO57 : 1; // 25 GPIO57 Enable for LPM Wakeup
    Uint32 GPIO58 : 1; // 26 GPIO58 Enable for LPM Wakeup
    Uint32 GPIO59 : 1; // 27 GPIO59 Enable for LPM Wakeup
    Uint32 GPIO60 : 1; // 28 GPIO60 Enable for LPM Wakeup
    Uint32 GPIO61 : 1; // 29 GPIO61 Enable for LPM Wakeup
    Uint32 GPIO62 : 1; // 30 GPIO62 Enable for LPM Wakeup
    Uint32 GPIO63 : 1; // 31 GPIO63 Enable for LPM Wakeup
};

union GPIOLPMSEL1_REG
{
    Uint32 all;
    struct GPIOLPMSEL1_BITS bit;
};

struct RESCCLR_BITS
{                             // bits description
    Uint32 CPU0_POR      : 1; // 0 CPU0 POR Reset Cause Clear Bit
    Uint32 CPU0_XRSn     : 1; // 1 CPU0 XRSn Reset Cause Clear Bit
    Uint32 CPU0_WDRSn    : 1; // 2 CPU0 WDRSn Reset Cause Clear Bit
    Uint32 CPU0_NMIWDRSn : 1; // 3 CPU0 NMIWDRSn Reset Cause Clear Bit
    Uint32 CPU1_POR      : 1; // 4 CPU1 POR Reset Cause Clear Bit
    Uint32 CPU1_XRSn     : 1; // 5 CPU1 XRSn Reset Cause Clear Bit
    Uint32 CPU1_WDRSn    : 1; // 6 CPU1 WDRSn Reset Cause Clear Bit
    Uint32 CPU1_NMIWDRSn : 1; // 7 CPU1 NMIWDRSn Reset Cause Clear Bit
    Uint32 CPU0_DBGRSn   : 1; // 8 CPU0 Debug Reset Cause Clear Bit
    Uint32 CPU1_DBGRSn   : 1; // 9 CPU1 Debug Reset Cause Clear Bit
};

union RESCCLR_REG
{
    Uint32 all;
    struct RESCCLR_BITS bit;
};

struct RESC_BITS
{                                // bits description
    Uint32 CPU0_POR        : 1;  // 0 CPU0 POR Reset Cause Indication Bit
    Uint32 CPU0_XRSn       : 1;  // 1 CPU0 XRSn Reset Cause Indication Bit
    Uint32 CPU0_WDRSn      : 1;  // 2 CPU0 WDRSn Reset Cause Indication Bit
    Uint32 CPU0_NMIWDRSn   : 1;  // 3 CPU0 NMIWDRSn Reset Cause Indication Bit
    Uint32 CPU1_POR        : 1;  // 4 CPU1 POR Reset Cause Indication Bit
    Uint32 CPU1_XRSn       : 1;  // 5 CPU1 XRSn Reset Cause Indication Bit
    Uint32 CPU1_WDRSn      : 1;  // 6 CPU1 WDRSn Reset Cause Indication Bit
    Uint32 CPU1_NMIWDRSn   : 1;  // 7 CPU1 NMIWDRSn Reset Cause Indication Bit
    Uint32 CPU0_DBGRSn     : 1;  // 8 CPU0 Debug Reset Cause Indication Bit
    Uint32 CPU1_DBGRSn     : 1;  // 9 CPU1 Debug Reset Cause Indication Bit
    Uint32 rsvd0           : 19; // 28:10 reserved
    Uint32 XRSn_PIN_STATUS : 1;  // 29 XRSn Current Pin Status
    Uint32 CPU0_DCON       : 1;  // 30 CPU0 Debug Connect Status Bit
    Uint32 CPUl_DCON       : 1;  // 31 CPu1 Debug Connect Status Bit
};

union RESC_REG
{
    Uint32 all;
    struct RESC_BITS bit;
};

struct CPU_SYS_REGS
{
    union PCLKCR0_REG PCLKCR0;           // offset:0x00
    union PCLKCR1_REG PCLKCR1;           // offset:0x04
    union PCLKCR2_REG PCLKCR2;           // offset:0x08
    union PCLKCR3_REG PCLKCR3;           // offset:0x0C
    union PCLKCR4_REG PCLKCR4;           // offset:0x10
    union PCLKCR5_REG PCLKCR5;           // offset:0x14
    union PCLKCR6_REG PCLKCR6;           // offset:0x18
    union PCLKCR7_REG PCLKCR7;           // offset:0x1C
    union PCLKCR8_REG PCLKCR8;           // offset:0x20
    union PCLKCR9_REG PCLKCR9;           // offset:0x24
    union PCLKCR10_REG PCLKCR10;         // offset:0x28
    union PCLKCR11_REG PCLKCR11;         // offset:0x2C
    union PCLKCR12_REG PCLKCR12;         // offset:0x30
    union PCLKCR13_REG PCLKCR13;         // offset:0x34
    union CPU0EXPSTART_REG CPU0EXPSTART; // offset: 0x38
    union CPU1EXPSTART_REG CPU1EXPSTART; // offset: 0x3c
    Uint32 reserve1[14];                 // offset:0x74 ~ 0x40
    union LPMCR_REG LPMCR;               // offset:0x78 LPM Control Register
    Uint32 HHRPWM;                       // offset:0x7C
    union TMR2CLKCTL_REG TMR2CLKCTL;     // offset:0x80
    union GPIOLPMSEL0_REG GPIOLPMSEL0;   // GPIO LPM Wakeup select registers, offset:0x84
    union GPIOLPMSEL1_REG GPIOLPMSEL1;   // GPIO LPM Wakeup select registers, offset:0x88
    union RESCCLR_REG RESCCLR;           // Reset Cause Clear Register, offset:0x8C
    union RESC_REG RESC;                 // Reset Cause register, offset:0x90
};

//---------------------------------------------------------------------------
// SYNC_SOC Register Bit Definitions:
//---------------------------------------------------------------------------

struct SYNCSELECT_BITS
{                           // bits description
    Uint32 EPWM4SYNCIN : 3; // 2:0 Selects Sync Input Source for EPWM4
    Uint32 EPWM7SYNCIN : 3; // 5:3 Selects Sync Input Source for EPWM7
    Uint32 rsvd1       : 3; // 8:6 Reserved
    Uint32 ECAP1SYNCIN : 3; // 11:9 Selects Sync Input Source for ECAP1
    Uint32 ECAP4SYNCIN : 3; // 14:12 Selects Sync Input Source for ECAP4
    Uint32 ECAP6SYNCIN : 3; // 17:15 Selects Sync Input Source for ECAP6
    Uint32 rsvd2       : 9; // 26:18 Reserved
    Uint32 SYNCOUT     : 2; // 28:27 Select Syncout Source
    Uint32 EPWM1SYNCIN : 3; // 31:29 Selects Sync Input Source for EPWM1
};

union SYNCSELECT_REG
{
    Uint32 all;
    struct SYNCSELECT_BITS bit;
};

struct ADCSOCOUTSELECT_BITS
{                          // bits description
    Uint32 PWM1SOCAEN : 1; // 0 PWM1SOCAEN Enable for ADCSOCAOn
    Uint32 PWM2SOCAEN : 1; // 1 PWM2SOCAEN Enable for ADCSOCAOn
    Uint32 PWM3SOCAEN : 1; // 2 PWM3SOCAEN Enable for ADCSOCAOn
    Uint32 PWM4SOCAEN : 1; // 3 PWM4SOCAEN Enable for ADCSOCAOn
    Uint32 PWM5SOCAEN : 1; // 4 PWM5SOCAEN Enable for ADCSOCAOn
    Uint32 PWM6SOCAEN : 1; // 5 PWM6SOCAEN Enable for ADCSOCAOn
    Uint32 PWM7SOCAEN : 1; // 6 PWM7SOCAEN Enable for ADCSOCAOn
    Uint32 PWM8SOCAEN : 1; // 7 PWM8SOCAEN Enable for ADCSOCAOn
    Uint32 rsvd1      : 1; // 8 Reserved
    Uint32 rsvd2      : 1; // 9 Reserved
    Uint32 rsvd3      : 1; // 10 Reserved
    Uint32 rsvd4      : 1; // 11 Reserved
    Uint32 rsvd5      : 4; // 15:12 Reserved
    Uint32 PWM1SOCBEN : 1; // 16 PWM1SOCBEN Enable for ADCSOCBOn
    Uint32 PWM2SOCBEN : 1; // 17 PWM2SOCBEN Enable for ADCSOCBOn
    Uint32 PWM3SOCBEN : 1; // 18 PWM3SOCBEN Enable for ADCSOCBOn
    Uint32 PWM4SOCBEN : 1; // 19 PWM4SOCBEN Enable for ADCSOCBOn
    Uint32 PWM5SOCBEN : 1; // 20 PWM5SOCBEN Enable for ADCSOCBOn
    Uint32 PWM6SOCBEN : 1; // 21 PWM6SOCBEN Enable for ADCSOCBOn
    Uint32 PWM7SOCBEN : 1; // 22 PWM7SOCBEN Enable for ADCSOCBOn
    Uint32 PWM8SOCBEN : 1; // 23 PWM8SOCBEN Enable for ADCSOCBOn
    Uint32 rsvd6      : 1; // 24 Reserved
    Uint32 rsvd7      : 1; // 25 Reserved
    Uint32 rsvd8      : 1; // 26 Reserved
    Uint32 rsvd9      : 1; // 27 Reserved
    Uint32 rsvd10     : 4; // 31:28 Reserved
};

union ADCSOCOUTSELECT_REG
{
    Uint32 all;
    struct ADCSOCOUTSELECT_BITS bit;
};

struct SYNCSOCLOCK_BITS
{                                // bits description
    Uint32 SYNCSELECT      : 1;  // 0 SYNCSEL Register Lock bit
    Uint32 ADCSOCOUTSELECT : 1;  // 1 ADCSOCOUTSELECT Register Lock bit
    Uint32 rsvd1           : 14; // 15:2 Reserved
    Uint32 rsvd2           : 16; // 31:16 Reserved
};

union SYNCSOCLOCK_REG
{
    Uint32 all;
    struct SYNCSOCLOCK_BITS bit;
};

struct SYNC_SOC_REGS
{
    union SYNCSELECT_REG SYNCSELECT;           // Sync Input and Output Select Register
    union ADCSOCOUTSELECT_REG ADCSOCOUTSELECT; // External ADCSOC Select Register
    union SYNCSOCLOCK_REG SYNCSOCLOCK;         // SYNCSEL and EXTADCSOC Select Lock register
};

//---------------------------------------------------------------------------
// NMI_INTRUPT Register Bit Definitions:
//---------------------------------------------------------------------------

struct NMICFG_BITS
{                      // bits description
    Uint32 NMIE  : 1;  // 0 Global NMI Enable
    Uint32 rsvd1 : 31; // 31:1 Reserved
};

union NMICFG_REG
{
    Uint32 all;
    struct NMICFG_BITS bit;
};

struct NMI_BITS
{                          // bits description
    Uint32 NMIINT     : 1; // 0 NMI Interrupt Flag
    Uint32 CLOCKFAIL  : 1; // 1 Clock Fail Interrupt Flag
    Uint32 RAMUNCERR  : 1; // 2 RAM Unreachable Error Interrupt Flag
    Uint32 FLUNCERR   : 1; // 3 Flash Unreachable Error Interrupt Flag
    Uint32 rsvd0      : 2; // 5:4 Reserved
    Uint32 PIEVECTERR : 1; // 6 PIE Vector Unreachable Error Flag
    Uint32 DMEMERR    : 1; // 7 Data memory ERROR
    Uint32 IMEMERR1   : 1; // 8 Inst memory ERROR 1
    Uint32 IMEMERR2   : 1; // 9 Inst memory ERROR 2
    Uint32 rsvd1      : 3; // 12:10 Reserved
    Uint32 SWERR      : 1; // 13 SW Error Force NMI Flag
};

union NMI_REG
{
    Uint32 all;
    struct NMI_BITS bit;
};

struct NMI_INTRUPT_REGS
{
    union NMICFG_REG NMICFG; // NMI Configuration Register, offset:0x00
    union NMI_REG NMIFLG;    // NMI Flag Register (SYSRsn Clear), offset:0x04
    union NMI_REG NMIFLGCLR; // NMI Flag Clear Register, offset:0x08
    union NMI_REG NMIFLGFRC; // NMI Flag Force Register, offset:0x0C
    Uint32 NMIWDCNT;         // NMI Watchdog Counter Register, offset:0x10
    Uint32 NMIWDPRD;         // NMI Watchdog Period Register, offset:0x14
    union NMI_REG NMISHDFLG; // NMI Shadow Flag Register, offset:0x18
};

//---------------------------------------------------------------------------
// NMI_INTRUPT Register Bit Definitions:
//---------------------------------------------------------------------------
struct ECC_DMEM_MODE_BITS
{
    Uint32 CHECK_MODE : 2;  // [1:0], 1 = Parity Check, 2 = Hamming Code error correction
    Uint32 rsvd       : 30; // [31:2]
};

union ECC_DMEM_MODE_REG
{
    Uint32 all;
    struct ECC_DMEM_MODE_BITS bit;
};

struct ECC_IMEM_MODE_BITS
{
    Uint32 ECC_FLASH_EN : 1;  // [0] flash data ecc check enable, 0 = disable, 1 = enable
    Uint32 ECC_IMEM_EN  : 1;  // [1] inst mem read ecc check enable, 0 = disable, 1 = enable
    Uint32 rsvd         : 30; // [31:2]
};

union ECC_IMEM_MODE_REG
{
    Uint32 all;
    struct ECC_IMEM_MODE_BITS bit;
};

struct ECC_REGS
{
    Uint32 rsvd;                           // offset: 0x00
    union ECC_DMEM_MODE_REG ECC_DMEM_MODE; // offset: 0x08
    union ECC_IMEM_MODE_REG ECC_IMEM_MODE; // offset: 0x04
};

//---------------------------------------------------------------------------

extern volatile struct WD_REGS WdRegs;
extern volatile struct CLK_CFG_REGS ClkCfgRegs;
extern volatile struct CPU_SYS_REGS CpuSysRegs;
extern volatile struct DEV_CFG_REGS DevCfgRegs;
extern volatile struct SYNC_SOC_REGS SyncSocRegs;
extern volatile struct NMI_INTRUPT_REGS NmiIntruptRegs;
extern volatile struct ECC_REGS EccRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
