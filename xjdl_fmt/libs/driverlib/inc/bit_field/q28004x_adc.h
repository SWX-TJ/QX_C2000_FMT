#ifndef Q28004X_ADC_H
#define Q28004X_ADC_H

#include "q28004x_types.h"

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// ADC Individual Register Bit Definitions:

struct ADCCTL_BITS
{                           // bits description
    Uint32 SWLDO_HS_LU : 1; // 0 Output data type selection
    Uint32 SELVI_HD_LS : 1; // 1 Input type selection
    Uint32 INTPULSEPOS : 1; // 2 ADC Interrupt Pulse Position
    Uint32 rsvd1       : 1; // 3 Reserved
    Uint32 BIAS_C      : 3; // 6:4 SAR comparator power dissipation control signal
    Uint32 ADCPWDNZ    : 1; // 7 ADC Power Down
    Uint32 CLK_DLY_SEL : 2; // 9:8 Data sampling clock delay selection signal
    Uint32 MD_ADC      : 2; // 11:10 ADC work mode control signal
    Uint32 rsvd2       : 4; // 15:12 Reserved
    Uint32 ADCBSY      : 1; // 16 ADC Busy
    Uint32 PRESCALE    : 5; // 21:17 ADC clock divider
    Uint32 ADCBSYCHN   : 5; // 26:22 Reserved
    Uint32 rsvd3       : 5; // 31:27 Reserved
};

union ADCCTL_REG
{
    Uint32 all;
    struct ADCCTL_BITS bit;
};

struct ADCINT_BITS
{                        // bits description
    Uint32 ADCINT1 : 1;  // 0: ADC Interrupt 1 Flag
    Uint32 ADCINT2 : 1;  // 1: ADC Interrupt 2 Flag
    Uint32 ADCINT3 : 1;  // 2: ADC Interrupt 3 Flag
    Uint32 ADCINT4 : 1;  // 3: ADC Interrupt 4 Flag
    Uint32 rsvd1   : 28; // 31:4 Reserved
};

union ADCINT_REG
{
    Uint32 all;
    struct ADCINT_BITS bit;
};

struct ADCINTSEL_BITS
{                        // bits description
    Uint32 INT1SEL  : 5; // 4:0 ADCINT EOC Source Select
    Uint32 INT1EN   : 1; // 5 ADCINT Interrupt Enable
    Uint32 INT1CONT : 1; // 6 ADCINT Continue to Interrupt Mode
    Uint32 rsvd1    : 1; // 7 Reserved
    Uint32 INT2SEL  : 5; // 12:8 ADCINT EOC Source Select
    Uint32 INT2EN   : 1; // 13 ADCINT Interrupt Enable
    Uint32 INT2CONT : 1; // 14 ADCINT Continue to Interrupt Mode
    Uint32 rsvd2    : 1; // 15 Reserved
    Uint32 INT3SEL  : 5; // 20:16 ADCINT EOC Source Select
    Uint32 INT3EN   : 1; // 21 ADCINT Interrupt Enable
    Uint32 INT3CONT : 1; // 22 ADCINT Continue to Interrupt Mode
    Uint32 rsvd3    : 1; // 23 Reserved
    Uint32 INT4SEL  : 5; // 28:24 ADCINT EOC Source Select
    Uint32 INT4EN   : 1; // 29 ADCINT Interrupt Enable
    Uint32 INT4CONT : 1; // 30 ADCINT Continue to Interrupt Mode
    Uint32 rsvd4    : 1; // 31 Reserved
};

union ADCINTSEL_REG
{
    Uint32 all;
    struct ADCINTSEL_BITS bit;
};

struct ADCSOCCTL_BITS
{                        // bits description
    Uint32 rsvd1   : 3;  // 2:0 Reserved
    Uint32 TRIGSEL : 5;  // 7:3 SOC0 Trigger Source Select
    Uint32 ACQPS   : 4;  // 11:8 SOC0 Acquisition Prescale
    Uint32 CHSEL   : 5;  // 16:12 SOC0 Channel Select
    Uint32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOCCTL_REG
{
    Uint32 all;
    struct ADCSOCCTL_BITS bit;
};

struct ADCEVT_BITS
{                           // bits description
    Uint32 PPB1TRIPHI : 1;  // 0  Post Processing Block Trip High Flag
    Uint32 PPB1TRIPLO : 1;  // 1  Post Processing Block Trip Low Flag
    Uint32 PPB1ZERO   : 1;  // 2  Post Processing Block Zero Crossing Flag
    Uint32 PPB2TRIPHI : 1;  // 3  Post Processing Block Trip High Flag
    Uint32 PPB2TRIPLO : 1;  // 4  Post Processing Block Trip Low Flag
    Uint32 PPB2ZERO   : 1;  // 5  Post Processing Block Zero Crossing Flag
    Uint32 PPB3TRIPHI : 1;  // 6  Post Processing Block Trip High Flag
    Uint32 PPB3TRIPLO : 1;  // 7  Post Processing Block Trip Low Flag
    Uint32 PPB3ZERO   : 1;  // 8  Post Processing Block Zero Crossing Flag
    Uint32 PPB4TRIPHI : 1;  // 9  Post Processing Block Trip High Flag
    Uint32 PPB4TRIPLO : 1;  // 10 Post Processing Block Trip Low Flag
    Uint32 PPB4ZERO   : 1;  // 11 Post Processing Block Zero Crossing Flag
    Uint32 rsvd1      : 20; // 31:12 Reserved
};

union ADCEVT_REG
{
    Uint32 all;
    struct ADCEVT_BITS bit;
};

struct ADCCOUNTER_BITS
{                          // bits description
    Uint32 FREECOUNT : 12; // 11:0 ADC Free Running Counter Value
    Uint32 rsvd1     : 4;  // 15:12 Reserved
};

union ADCCOUNTER_REG
{
    Uint32 all;
    struct ADCCOUNTER_BITS bit;
};

struct ADCREV_BITS
{                    // bits description
    Uint32 TYPE : 8; // 7:0 ADC Type
    Uint32 REV  : 8; // 15:8 ADC Revision
};

union ADCREV_REG
{
    Uint32 all;
    struct ADCREV_BITS bit;
};

struct ADCPPBCONFIG_BITS
{                           // bits description
    Uint32 CONFIG     : 5;  // 4:0 ADC Post Processing Block 1 Configuration
    Uint32 TWOSCOMPEN : 1;  // 5 ADC Post Processing Block 1 Two's Complement Enable
    Uint32 CBCEN      : 1;  // 6 Cycle By Cycle Enable
    Uint32 rsvd1      : 25; // 31:6 Reserved
};

union ADCPPBCONFIG_REG
{
    Uint32 all;
    struct ADCPPBCONFIG_BITS bit;
};

struct ADCPPBSTAMP_BITS
{                         // bits description
    Uint32 DLYSTAMP : 12; // 11:0 ADC Post Processing Block 1 Delay Time Stamp
    Uint32 rsvd1    : 20; // 31:12 Reserved
};

union ADCPPBSTAMP_REG
{
    Uint32 all;
    struct ADCPPBSTAMP_BITS bit;
};

struct ADCPPBOFFREF_BITS
{                       // bits description
    Uint32 OFFREF : 16; // 15:0 ADC Post Processing Block Offset Correction
    Uint32 rsvd   : 16; // 31:16 Reserved
};

union ADCPPBOFFREF_REG
{
    Uint32 all;
    struct ADCPPBOFFREF_BITS bit;
};

struct ADCPPBTRIPHI_BITS
{                        // bits description
    Uint32 LIMITHI : 12; // 11:0 ADC Post Processing Block 1 Trip High Limit
    Uint32 HSIGN   : 1;  // 12 High Limit Sign Bit
    Uint32 rsvd1   : 19; // 31:13 Reserved
};

union ADCPPBTRIPHI_REG
{
    Uint32 all;
    struct ADCPPBTRIPHI_BITS bit;
};

struct ADCPPBTRIPLO_BITS
{                         // bits description
    Uint32 LIMITLO  : 12; // 11:0 ADC Post Processing Block Trip Low Limit
    Uint32 LSIGN    : 1;  // 12 Low Limit Sign Bit
    Uint32 rsvd1    : 7;  // 19:13 Reserved
    Uint32 REQSTAMP : 12; // 31:20 ADC Post Processing Block Request Time Stamp
};

union ADCPPBTRIPLO_REG
{
    Uint32 all;
    struct ADCPPBTRIPLO_BITS bit;
};

struct ADCPPBOFFCAL_BITS
{                       // bits description
    Uint32 OFFCAL : 10; // 9:0 ADC Post Processing Block Offset Correction
    Uint32 rsvd1  : 22; // 31:10 Reserved
};

union ADCPPBOFFCAL_REG
{
    Uint32 all;
    struct ADCPPBOFFCAL_BITS bit;
};

struct ADCSOC_BITS
{                      // bits description
    Uint32 SOC0  : 1;  // 0 SOC0 Force Start of Conversion Bit
    Uint32 SOC1  : 1;  // 1 SOC1 Force Start of Conversion Bit
    Uint32 SOC2  : 1;  // 2 SOC2 Force Start of Conversion Bit
    Uint32 SOC3  : 1;  // 3 SOC3 Force Start of Conversion Bit
    Uint32 SOC4  : 1;  // 4 SOC4 Force Start of Conversion Bit
    Uint32 SOC5  : 1;  // 5 SOC5 Force Start of Conversion Bit
    Uint32 SOC6  : 1;  // 6 SOC6 Force Start of Conversion Bit
    Uint32 SOC7  : 1;  // 7 SOC7 Force Start of Conversion Bit
    Uint32 SOC8  : 1;  // 8 SOC8 Force Start of Conversion Bit
    Uint32 SOC9  : 1;  // 9 SOC9 Force Start of Conversion Bit
    Uint32 SOC10 : 1;  // 10 SOC10 Force Start of Conversion Bit
    Uint32 SOC11 : 1;  // 11 SOC11 Force Start of Conversion Bit
    Uint32 SOC12 : 1;  // 12 SOC12 Force Start of Conversion Bit
    Uint32 SOC13 : 1;  // 13 SOC13 Force Start of Conversion Bit
    Uint32 SOC14 : 1;  // 14 SOC14 Force Start of Conversion Bit
    Uint32 SOC15 : 1;  // 15 SOC15 Force Start of Conversion Bit
    Uint32 SOC16 : 1;  // 16 SOC16 Force Start of Conversion Bit
    Uint32 SOC17 : 1;  // 17 SOC17 Force Start of Conversion Bit
    Uint32 SOC18 : 1;  // 18 SOC18 Force Start of Conversion Bit
    Uint32 SOC19 : 1;  // 19 SOC19 Force Start of Conversion Bit
    Uint32 rsvd  : 12; // 20:31 Reserved
};

union ADCSOC_REG
{
    Uint32 all;
    struct ADCSOC_BITS bit;
};

struct ADCINTCYCLE_BITS
{                      // bits description
    Uint32 DELAY : 16; // 15:0 ADC Interrupt Pulse Positiont
    Uint32 rsvd  : 16; // 31:16 Reserved
};

union ADCINTCYCLE_REG
{
    Uint32 all;
    struct ADCINTCYCLE_BITS bit;
};

struct ADCSOCPRIORITYCTL_BITS
{
    Uint32 SOCPRIORITY : 5;
    Uint32 RRPOINT     : 5;
    Uint32 rsvd        : 22;
};

union ADCSOCPRIORITYCTL_REG
{
    Uint32 all;
    struct ADCSOCPRIORITYCTL_BITS bit;
};

struct ADCBURSTCTL_BITS
{
    Uint32 BURSTTRIGSEL : 6; // SOC Burst Trigger Source Select
    Uint32 rsvd0        : 2;
    Uint32 BURSTSIZE    : 4; // SOC Burst Size Select
    Uint32 rsvd1        : 3;
    Uint32 BURSTEN      : 1; // SOC Burst Mode Enable
};

union ADCBURSTCTL_REG
{
    Uint32 all;
    struct ADCBURSTCTL_BITS bit;
};

/* clang-format off */
struct ADC_REGS
{
    union ADCCTL_REG ADCCTL;              // ADC Control Register, offset:0x00
    union ADCINT_REG ADCINTFLG;           // ADC Interrupt Flag Register, offset:0x04
    union ADCINTSEL_REG ADCINTSEL;        // ADC Interrupt Enable/Disable Register, offset:0x08
    union ADCINT_REG ADCINTFLGCLR;        // ADC Interrupt Flag Clear Register, offset:0x0C
    union ADCINT_REG ADCINTOVF;           // ADC Interrupt Overflow Register, offset:0x10
    union ADCINT_REG ADCINTOVFCLR;        // ADC Interrupt Overflow Clear Register, offset:0x14
    union ADCSOCCTL_REG ADCSOC0CTL;       // ADC SOC0 Control Register, offset:0x18
    union ADCSOCCTL_REG ADCSOC1CTL;       // ADC SOC1 Control Register, offset:0x1C
    union ADCSOCCTL_REG ADCSOC2CTL;       // ADC SOC2 Control Register, offset:0x20
    union ADCSOCCTL_REG ADCSOC3CTL;       // ADC SOC3 Control Register, offset:0x24
    union ADCSOCCTL_REG ADCSOC4CTL;       // ADC SOC4 Control Register, offset:0x28
    union ADCSOCCTL_REG ADCSOC5CTL;       // ADC SOC5 Control Register, offset:0x2C
    union ADCSOCCTL_REG ADCSOC6CTL;       // ADC SOC6 Control Register, offset:0x30
    union ADCSOCCTL_REG ADCSOC7CTL;       // ADC SOC7 Control Register, offset:0x34
    union ADCSOCCTL_REG ADCSOC8CTL;       // ADC SOC8 Control Register, offset:0x38
    union ADCSOCCTL_REG ADCSOC9CTL;       // ADC SOC9 Control Register, offset:0x3C
    union ADCSOCCTL_REG ADCSOC10CTL;      // ADC SOC10 Control Register, offset:0x40
    union ADCSOCCTL_REG ADCSOC11CTL;      // ADC SOC11 Control Register, offset:0x44
    union ADCSOCCTL_REG ADCSOC12CTL;      // ADC SOC12 Control Register, offset:0x48
    union ADCSOCCTL_REG ADCSOC13CTL;      // ADC SOC13 Control Register, offset:0x4C
    union ADCSOCCTL_REG ADCSOC14CTL;      // ADC SOC14 Control Register, offset:0x50
    union ADCSOCCTL_REG ADCSOC15CTL;      // ADC SOC15 Control Register, offset:0x54
    union ADCSOCCTL_REG ADCSOC16CTL;      // ADC SOC16 Control Register, offset:0x58
    union ADCSOCCTL_REG ADCSOC17CTL;      // ADC SOC17 Control Register, offset:0x5C
    union ADCSOCCTL_REG ADCSOC18CTL;      // ADC SOC18 Control Register, offset:0x60
    union ADCSOCCTL_REG ADCSOC19CTL;      // ADC SOC19 Control Register, offset:0x64
    union ADCEVT_REG ADCEVTSTAT;          // ADC Event Status Register, offset:0x68
    union ADCEVT_REG ADCEVTCLR;           // ADC Event Clear Register, offset:0x6C
    union ADCEVT_REG ADCEVTSEL;           // ADC Event Selection Register, offset:0x70
    union ADCEVT_REG ADCEVTINTSEL;        // ADC Event Interrupt Selection Register, offset:0x74
    union ADCCOUNTER_REG ADCCOUNTER;      // ADC Counter Register, offset:0x78
    union ADCREV_REG ADCREV;              // ADC Revision Register, offset:0x7C
    union ADCPPBCONFIG_REG ADCPPB1CONFIG; // ADC Post Processing Block 1 Configuration Register, offset:0x80
    union ADCPPBSTAMP_REG ADCPPB1STAMP;   // ADC Post Processing Block 1 Timestamp Register, offset:0x84
    union ADCPPBOFFREF_REG ADCPPB1OFFREF; // ADC PPB1 Offset Reference Register, offset:0x88
    union ADCPPBTRIPHI_REG ADCPPB1TRIPHI; // ADC PPB1 Trip High Register, offset:0x8C
    union ADCPPBTRIPLO_REG ADCPPB1TRIPLO; // ADC PPB1 Trip Low/Trigger Time Stamp Register, offset:0x90
    union ADCPPBOFFCAL_REG ADCPPB1OFFCAL; // ADC PPB1 Offset Calibration Register, offset:0x94
    union ADCPPBCONFIG_REG ADCPPB2CONFIG; // ADC Post Processing Block 2 Configuration Register, offset:0x98
    union ADCPPBSTAMP_REG ADCPPB2STAMP;   // ADC Post Processing Block 2 Timestamp Register, offset:0x9C
    union ADCPPBOFFREF_REG ADCPPB2OFFREF; // ADC PPB2 Offset Reference Register, offset:0xA0
    union ADCPPBTRIPHI_REG ADCPPB2TRIPHI; // ADC PPB2 Trip High Register, offset:0xA4
    union ADCPPBTRIPLO_REG ADCPPB2TRIPLO; // ADC PPB2 Trip Low/Trigger Time Stamp Register, offset:0xA8
    union ADCPPBOFFCAL_REG ADCPPB2OFFCAL; // ADC PPB2 Offset Calibration Register, offset:0xAC
    union ADCPPBCONFIG_REG ADCPPB3CONFIG; // ADC Post Processing Block 3 Configuration Register, offset:0xB0
    union ADCPPBSTAMP_REG ADCPPB3STAMP;   // ADC Post Processing Block 3 Timestamp Register, offset:0xB4
    union ADCPPBOFFREF_REG ADCPPB3OFFREF; // ADC PPB3 Offset Reference Register, offset:0xB8
    union ADCPPBTRIPHI_REG ADCPPB3TRIPHI; // ADC PPB3 Trip High Register, offset:0xBC
    union ADCPPBTRIPLO_REG ADCPPB3TRIPLO; // ADC PPB3 Trip Low/Trigger Time Stamp Register, offset:0xC0
    union ADCPPBOFFCAL_REG ADCPPB3OFFCAL; // ADC PPB3 Offset Calibration Register, offset:0xC4
    union ADCPPBCONFIG_REG ADCPPB4CONFIG; // ADC Post Processing Block 4 Configuration Register, offset:0xC8
    union ADCPPBSTAMP_REG ADCPPB4STAMP;   // ADC Post Processing Block 4 Timestamp Register, offset:0xCC
    union ADCPPBOFFREF_REG ADCPPB4OFFREF; // ADC PPB4 Offset Reference Register, offset:0xD0
    union ADCPPBTRIPHI_REG ADCPPB4TRIPHI; // ADC PPB4 Trip High Register, offset:0xD4
    union ADCPPBTRIPLO_REG ADCPPB4TRIPLO; // ADC PPB4 Trip Low/Trigger Time Stamp Register, offset:0xD8
    union ADCPPBOFFCAL_REG ADCPPB4OFFCAL; // ADC PPB4 Offset Calibration Register, offset:0xDC
    union ADCSOC_REG ADCSOCFRC;           // ADC SOC Force Register, offset:0xE0
    union ADCSOC_REG ADCSOCFLG;           // ADC SOC Flag Register, offset:0xE4
    union ADCSOC_REG ADCSOCOVF;           // ADC SOC Covf Register, offset:0xE8
    union ADCSOC_REG ADCSOCOVFCLR;        // ADC SOC Covf clear Register, offset:0xEC
    union ADCINTCYCLE_REG ADCINTCYCLE;    // ADC Early Interrupt Generation Cycle, offset:0xF0
    union ADCSOCPRIORITYCTL_REG ADCSOCPRIORITYCTL; // ADC socpriority ctrl reg, offset:0xF4
    union ADCBURSTCTL_REG ADCBURSTCTL;    // ADC socpriority ctrl reg, offset:0xF8
    union ADCSOC_REG ADCINTSOCSEL;        // ADC Interrupt SOC Selection Register, offset:0xFC
};
/* clang-format on */

struct ADCRESULT_BITS
{
    Uint32 RESULT : 12; // ADC Result
    Uint32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT_REG
{
    Uint32 all;
    struct ADCRESULT_BITS bit;
};

struct ADCPPBRESULT_BITS
{                           // bits description
    Uint32 PPB1RESULT : 12; // 11:0 ADC Post Processing Block 1 Result
    Uint32 SIGN       : 20; // 31:12 Sign Extended Bits
};

union ADCPPBRESULT_REG
{
    Uint32 all;
    struct ADCPPBRESULT_BITS bit;
};

struct ADC_RESULT_REGS
{
    union ADCRESULT_REG ADCRESULT0;       // ADC Result 0 Register, offset:0x00
    union ADCRESULT_REG ADCRESULT1;       // ADC Result 1 Register, offset:0x04
    union ADCRESULT_REG ADCRESULT2;       // ADC Result 2 Register, offset:0x08
    union ADCRESULT_REG ADCRESULT3;       // ADC Result 3 Register, offset:0x0C
    union ADCRESULT_REG ADCRESULT4;       // ADC Result 4 Register, offset:0x10
    union ADCRESULT_REG ADCRESULT5;       // ADC Result 5 Register, offset:0x14
    union ADCRESULT_REG ADCRESULT6;       // ADC Result 6 Register, offset:0x18
    union ADCRESULT_REG ADCRESULT7;       // ADC Result 7 Register, offset:0x1C
    union ADCRESULT_REG ADCRESULT8;       // ADC Result 8 Register, offset:0x20
    union ADCRESULT_REG ADCRESULT9;       // ADC Result 9 Register, offset:0x24
    union ADCRESULT_REG ADCRESULT10;      // ADC Result 10 Register, offset:0x28
    union ADCRESULT_REG ADCRESULT11;      // ADC Result 11 Register, offset:0x2C
    union ADCRESULT_REG ADCRESULT12;      // ADC Result 12 Register, offset:0x30
    union ADCRESULT_REG ADCRESULT13;      // ADC Result 13 Register, offset:0x34
    union ADCRESULT_REG ADCRESULT14;      // ADC Result 14 Register, offset:0x38
    union ADCRESULT_REG ADCRESULT15;      // ADC Result 15 Register, offset:0x3C
    union ADCRESULT_REG ADCRESULT16;      // ADC Result 16 Register, offset:0x40
    union ADCRESULT_REG ADCRESULT17;      // ADC Result 17 Register, offset:0x44
    union ADCRESULT_REG ADCRESULT18;      // ADC Result 18 Register, offset:0x48
    union ADCRESULT_REG ADCRESULT19;      // ADC Result 19 Register, offset:0x4C
    union ADCPPBRESULT_REG ADCPPB1RESULT; // ADC Post Processing Block1 Result Register, offset:0x50
    union ADCPPBRESULT_REG ADCPPB2RESULT; // ADC Post Processing Block2 Result Register, offset:0x54
    union ADCPPBRESULT_REG ADCPPB3RESULT; // ADC Post Processing Block3 Result Register, offset:0x58
    union ADCPPBRESULT_REG ADCPPB4RESULT; // ADC Post Processing Block4 Result Register, offset:0x5C
};

//---------------------------------------------------------------------------
// ADC External References & Function Declarations:
//

extern volatile struct ADC_REGS AdcaRegs;
extern volatile struct ADC_RESULT_REGS AdcaResultRegs;

extern volatile struct ADC_REGS AdcbRegs;
extern volatile struct ADC_RESULT_REGS AdcbResultRegs;

extern volatile struct ADC_REGS AdccRegs;
extern volatile struct ADC_RESULT_REGS AdccResultRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
