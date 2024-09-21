#ifndef Q28004X_HR_ADC_H
#define Q28004X_HR_ADC_H

#include "q28004x_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct HR_ADCCTL1_BITS
{
    Uint32 rsvd2         : 2;  /* 1:0 */
    Uint32 intpulsepos   : 1;  /* 2 */
    Uint32 dislvl        : 1;  /* 3 */
    Uint32 enldo         : 1;  /* 4 */
    Uint32 startcal_p    : 1;  /* 5 */
    Uint32 resetz_p      : 1;  /* 6 */
    Uint32 adc_en_p      : 1;  /* 7 */
    Uint32 adc_busychan  : 4;  /* 11:8 */
    Uint32 rsvd1         : 1;  /* 12 */
    Uint32 adcbsy        : 1;  /* 13 */
    Uint32 selrange_ldo  : 1;  /* 14 */
    Uint32 startvoscal_p : 1;  /* 15 */
    Uint32 rsvd0         : 16; /* 31:16 */
};

union HR_ADCCTL1_REG
{
    Uint32 all;
    struct HR_ADCCTL1_BITS bit;
};

struct HR_ADCCTL2_BITS
{
    Uint32 prescale : 5;  /* 4:0 */
    Uint32 selres   : 2;  /* 6:5 */
    Uint32 seldiff  : 1;  /* 7 */
    Uint32 rsvd     : 24; /* 31:8 */
};

union HR_ADCCTL2_REG
{
    /* data */
    Uint32 all;
    struct HR_ADCCTL2_BITS bit;
};

struct HR_ADCINTFLG_BITS
{
    Uint32 adcint1 : 1;  /* 0 */
    Uint32 adcint2 : 1;  /* 1 */
    Uint32 adcint3 : 1;  /* 2 */
    Uint32 adcint4 : 1;  /* 3 */
    Uint32 rsvd    : 28; /* 31:4 */
};

union HR_ADCINTFLG_REG
{
    Uint32 all;
    struct HR_ADCINTFLG_BITS bit;
};

struct HR_ADCINTFLGCLR_BITS
{
    Uint32 adcint1 : 1;  /* 0 */
    Uint32 adcint2 : 1;  /* 1 */
    Uint32 adcint3 : 1;  /* 2 */
    Uint32 adcint4 : 1;  /* 3 */
    Uint32 rsvd    : 28; /* 31:4 */
};

union HR_ADCINTFLGCLR_REG
{
    Uint32 all;
    struct HR_ADCINTFLGCLR_BITS bit;
};

struct HR_ADCINTOVF_BITS
{
    Uint32 adcint1 : 1;  /* 0 */
    Uint32 adcint2 : 1;  /* 1 */
    Uint32 adcint3 : 1;  /* 2 */
    Uint32 adcint4 : 1;  /* 3 */
    Uint32 rsvd    : 28; /* 31:4 */
};

union HR_ADCINTOVF_REG
{
    Uint32 all;
    struct HR_ADCINTOVF_BITS bit;
};

struct HR_ADCINTOVFCLR_BITS
{
    Uint32 adcint1 : 1;  /* 0 */
    Uint32 adcint2 : 1;  /* 1 */
    Uint32 adcint3 : 1;  /* 2 */
    Uint32 adcint4 : 1;  /* 3 */
    Uint32 rsvd    : 28; /* 31:4 */
};

union HR_ADCINTOVFCLR_REG
{
    Uint32 all;
    struct HR_ADCINTOVFCLR_BITS bit;
};

struct HR_ADCINTSELINT_BITS
{
    Uint32 int1sel  : 4; /* 3:0 */
    Uint32 rsvd0    : 1; /* 4 */
    Uint32 int1en   : 1; /* 5 */
    Uint32 int1cont : 1; /* 6 */
    Uint32 rsvd1    : 1; /* 7 */
    Uint32 int2sel  : 4; /* 11:8 */
    Uint32 rsvd2    : 1; /* 12 */
    Uint32 int2en   : 1; /* 13 */
    Uint32 int2cont : 1; /* 14 */
    Uint32 rsvd3    : 1; /* 15 */
    Uint32 int3sel  : 4; /* 19:16 */
    Uint32 rsvd4    : 1; /* 20 */
    Uint32 int3en   : 1; /* 21 */
    Uint32 int3cont : 1; /* 22 */
    Uint32 rsvd5    : 1; /* 23 */
    Uint32 int4sel  : 4; /* 27:24*/
    Uint32 rsvd6    : 1; /* 28 */
    Uint32 int4en   : 1; /* 29 */
    Uint32 int4cont : 1; /* 30 */
    Uint32 rsvd7    : 1; /* 31 */
};

union HR_ADCINTSELINT_REG
{
    Uint32 all;
    struct HR_ADCINTSELINT_BITS bit;
};

struct HR_ADCSOCPRICTL_BITS
{
    Uint32 socpriority : 4;  /* 4:0 */
    Uint32 rrpoint     : 5;  /* 9:5 */
    Uint32 rsvd        : 22; /* 31:10 */
};

union HR_ADCSOCPRICTL_REG
{
    Uint32 all;
    struct HR_ADCSOCPRICTL_BITS bit;
};

struct HR_ADCSOCFLG_BITS
{
    Uint32 SOC0  : 1;  /* 0 */
    Uint32 SOC1  : 1;  /* 1 */
    Uint32 SOC2  : 1;  /* 2 */
    Uint32 SOC3  : 1;  /* 3 */
    Uint32 SOC4  : 1;  /* 4 */
    Uint32 SOC5  : 1;  /* 5 */
    Uint32 SOC6  : 1;  /* 6 */
    Uint32 SOC7  : 1;  /* 7 */
    Uint32 SOC8  : 1;  /* 8 */
    Uint32 SOC9  : 1;  /* 9 */
    Uint32 SOC10 : 1;  /* 10 */
    Uint32 SOC11 : 1;  /* 11 */
    Uint32 SOC12 : 1;  /* 12 */
    Uint32 SOC13 : 1;  /* 13 */
    Uint32 SOC14 : 1;  /* 14 */
    Uint32 SOC15 : 1;  /* 15 */
    Uint32 rsvd  : 16; /* 31:16 */
};

union HR_ADCSOCFLG_REG
{
    Uint32 all;
    struct HR_ADCSOCFLG_BITS bit;
};

struct HR_ADCSOCFRC_BITS
{
    Uint32 SOC0  : 1;  /* 0 */
    Uint32 SOC1  : 1;  /* 1 */
    Uint32 SOC2  : 1;  /* 2 */
    Uint32 SOC3  : 1;  /* 3 */
    Uint32 SOC4  : 1;  /* 4 */
    Uint32 SOC5  : 1;  /* 5 */
    Uint32 SOC6  : 1;  /* 6 */
    Uint32 SOC7  : 1;  /* 7 */
    Uint32 SOC8  : 1;  /* 8 */
    Uint32 SOC9  : 1;  /* 9 */
    Uint32 SOC10 : 1;  /* 10 */
    Uint32 SOC11 : 1;  /* 11 */
    Uint32 SOC12 : 1;  /* 12 */
    Uint32 SOC13 : 1;  /* 13 */
    Uint32 SOC14 : 1;  /* 14 */
    Uint32 SOC15 : 1;  /* 15 */
    Uint32 rsvd  : 16; /* 31:16 */
};
union HR_ADCSOCFRC_REG
{
    Uint32 all;
    struct HR_ADCSOCFRC_BITS bit;
};

struct HR_ADCSOCOVF_BITS
{
    Uint32 SOC0  : 1;  /* 0 */
    Uint32 SOC1  : 1;  /* 1 */
    Uint32 SOC2  : 1;  /* 2 */
    Uint32 SOC3  : 1;  /* 3 */
    Uint32 SOC4  : 1;  /* 4 */
    Uint32 SOC5  : 1;  /* 5 */
    Uint32 SOC6  : 1;  /* 6 */
    Uint32 SOC7  : 1;  /* 7 */
    Uint32 SOC8  : 1;  /* 8 */
    Uint32 SOC9  : 1;  /* 9 */
    Uint32 SOC10 : 1;  /* 10 */
    Uint32 SOC11 : 1;  /* 11 */
    Uint32 SOC12 : 1;  /* 12 */
    Uint32 SOC13 : 1;  /* 13 */
    Uint32 SOC14 : 1;  /* 14 */
    Uint32 SOC15 : 1;  /* 15 */
    Uint32 rsvd  : 16; /* 31:16 */
};
union HR_ADCSOCOVF_REG
{
    Uint32 all;
    struct HR_ADCSOCOVF_BITS bit;
};

struct HR_ADCSOCOVFCLR_BITS
{
    Uint32 SOC0  : 1;  /* 0 */
    Uint32 SOC1  : 1;  /* 1 */
    Uint32 SOC2  : 1;  /* 2 */
    Uint32 SOC3  : 1;  /* 3 */
    Uint32 SOC4  : 1;  /* 4 */
    Uint32 SOC5  : 1;  /* 5 */
    Uint32 SOC6  : 1;  /* 6 */
    Uint32 SOC7  : 1;  /* 7 */
    Uint32 SOC8  : 1;  /* 8 */
    Uint32 SOC9  : 1;  /* 9 */
    Uint32 SOC10 : 1;  /* 10 */
    Uint32 SOC11 : 1;  /* 11 */
    Uint32 SOC12 : 1;  /* 12 */
    Uint32 SOC13 : 1;  /* 13 */
    Uint32 SOC14 : 1;  /* 14 */
    Uint32 SOC15 : 1;  /* 15 */
    Uint32 rsvd  : 16; /* 31:16 */
};
union HR_ADCSOCOVFCLR_REG
{
    Uint32 all;
    struct HR_ADCSOCOVFCLR_BITS bit;
};

struct HR_ADCSOCCTL_BITS
{
    Uint32 rsvd0   : 15; /* 2:0 */
    Uint32 CHSEL   : 4;  /* 7:3 */
    Uint32 rsvd1   : 1;  /* 11:8 */
    Uint32 TRIGSEL : 5;  /* 14:12 */
    Uint32 rsvd2   : 7;  /* 31:15 */
};
union HR_ADCSOCCTL_REG
{
    Uint32 all;
    struct HR_ADCSOCCTL_BITS bit;
};

struct HR_ADCEVTSTAT_BITS
{
    Uint32 ppb1triphi : 1;  /* 0 */
    Uint32 ppb1triplo : 1;  /* 1 */
    Uint32 ppb1zero   : 1;  /* 2 */
    Uint32 ppb2triphi : 1;  /* 3 */
    Uint32 ppb2triplo : 1;  /* 4 */
    Uint32 ppb2zero   : 1;  /* 5 */
    Uint32 ppb3triphi : 1;  /* 6 */
    Uint32 ppb3triplo : 1;  /* 7 */
    Uint32 ppb3zero   : 1;  /* 8 */
    Uint32 ppb4triphi : 1;  /* 9 */
    Uint32 ppb4triplo : 1;  /* 10 */
    Uint32 ppb4zero   : 1;  /* 11 */
    Uint32 rsvd       : 20; /* 31:12 */
};

union HR_ADCEVTSTAT_REG
{
    Uint32 all;
    struct HR_ADCEVTSTAT_BITS bit;
};

struct HR_ADCEVTCLR_BITS
{
    Uint32 ppb1triphi : 1;  /* 0 */
    Uint32 ppb1triplo : 1;  /* 1 */
    Uint32 ppb1zero   : 1;  /* 2 */
    Uint32 ppb2triphi : 1;  /* 3 */
    Uint32 ppb2triplo : 1;  /* 4 */
    Uint32 ppb2zero   : 1;  /* 5 */
    Uint32 ppb3triphi : 1;  /* 6 */
    Uint32 ppb3triplo : 1;  /* 7 */
    Uint32 ppb3zero   : 1;  /* 8 */
    Uint32 ppb4triphi : 1;  /* 9 */
    Uint32 ppb4triplo : 1;  /* 10 */
    Uint32 ppb4zero   : 1;  /* 11 */
    Uint32 rsvd       : 20; /* 31:12 */
};
union HR_ADCEVTCLR_REG
{
    Uint32 all;
    struct HR_ADCEVTCLR_BITS bit;
};

struct HR_ADCEVTSEL_BITS
{
    Uint32 ppb1triphi : 1;  /* 0 */
    Uint32 ppb1triplo : 1;  /* 1 */
    Uint32 ppb1zero   : 1;  /* 2 */
    Uint32 ppb2triphi : 1;  /* 3 */
    Uint32 ppb2triplo : 1;  /* 4 */
    Uint32 ppb2zero   : 1;  /* 5 */
    Uint32 ppb3triphi : 1;  /* 6 */
    Uint32 ppb3triplo : 1;  /* 7 */
    Uint32 ppb3zero   : 1;  /* 8 */
    Uint32 ppb4triphi : 1;  /* 9 */
    Uint32 ppb4triplo : 1;  /* 10 */
    Uint32 ppb4zero   : 1;  /* 11 */
    Uint32 rsvd       : 20; /* 31:12 */
};
union HR_ADCEVTSEL_REG
{
    Uint32 all;
    struct HR_ADCEVTSEL_BITS bit;
};

struct HR_ADCEVTINTSEL_BITS
{
    Uint32 ppb1triphi : 1;  /* 0 */
    Uint32 ppb1triplo : 1;  /* 1 */
    Uint32 ppb1zero   : 1;  /* 2 */
    Uint32 ppb2triphi : 1;  /* 3 */
    Uint32 ppb2triplo : 1;  /* 4 */
    Uint32 ppb2zero   : 1;  /* 5 */
    Uint32 ppb3triphi : 1;  /* 6 */
    Uint32 ppb3triplo : 1;  /* 7 */
    Uint32 ppb3zero   : 1;  /* 8 */
    Uint32 ppb4triphi : 1;  /* 9 */
    Uint32 ppb4triplo : 1;  /* 10 */
    Uint32 ppb4zero   : 1;  /* 11 */
    Uint32 rsvd       : 20; /* 31:12 */
};
union HR_ADCEVTINTSEL_REG
{
    Uint32 all;
    struct HR_ADCEVTINTSEL_BITS bit;
};

struct HR_ADCCOUNT_BITS
{
    Uint32 freecount : 12; /* 11:0*/
    Uint32 rsvd      : 20; /* 31:12 */
};
union HR_ADCCOUNT_REG
{
    Uint32 all;
    struct HR_ADCCOUNT_BITS bit;
};

struct HR_ADCREV_BITS
{
    Uint32 adc_type : 8;  /* 7:0 */
    Uint32 rev      : 8;  /* 15:8 */
    Uint32 rsvd     : 16; /* 31:16 */
};
union HR_ADCREV_REG
{
    Uint32 all;
    struct HR_ADCREV_BITS bit;
};

struct HR_ADCPPBCONFIG_BITS
{
    Uint32 config     : 5;  /* 4:0 */
    Uint32 twoscompen : 1;  /* 1 */
    Uint32 cbcen      : 1;  /* 1 */
    Uint32 rsvd       : 25; /* 31:7 */
};
union HR_ADCPPBCONFIG_REG
{
    Uint32 all;
    struct HR_ADCPPBCONFIG_BITS bit;
};

struct HR_ADCPPBSTAMP_BITS
{
    Uint32 dlystamp : 12; /* 11:0  */
    Uint32 rsvd     : 20; /* 31:12 */
};
union HR_ADCPPBSTAMP_REG
{
    Uint32 all;
    struct HR_ADCPPBSTAMP_BITS bit;
};

struct HR_ADCPPBOFFCAL_BITS
{
    Uint32 offcal : 10; /* 9:0 */
    Uint32 rsvd   : 22; /* 31:10 */
};
union HR_ADCPPBOFFCAL_REG
{
    Uint32 all;
    struct HR_ADCPPBOFFCAL_BITS bit;
};

struct HR_ADCPPBOFFREF_BITS
{
    Uint32 offref : 14; /* 15:0 */
    Uint32 rsvd   : 18; /* 31:16 */
};
union HR_ADCPPBOFFREF_REG
{
    Uint32 all;
    struct HR_ADCPPBOFFREF_BITS bit;
};

struct HR_ADCPPBTRIPHI_BITS
{
    Uint32 limithi : 14; /* 13:0 */
    Uint32 hsign   : 1;  /* 14 */
    Uint32 rsvd    : 17; /* 31:15 */
};
union HR_ADCPPBTRIPHI_REG
{
    Uint32 all;
    struct HR_ADCPPBTRIPHI_BITS bit;
};

struct HR_ADCPPBTRIPLO_BITS
{
    Uint32 limithi : 14; /* 13:0 */
    Uint32 hsign   : 1;  /* 1 */
    Uint32 rsvd    : 17; /* 31:15 */
};
union HR_ADCPPBTRIPLO_REG
{
    Uint32 all;
    struct HR_ADCPPBTRIPLO_BITS bit;
};

struct HR_ADCRESULT_BITS
{
    Uint32 result : 14; /* 13:0 */
    Uint32 rsvd   : 18; /* 31:14*/
};
union HR_ADCRESULT_REG
{
    Uint32 all;
    struct HR_ADCRESULT_BITS bit;
};

struct HR_ADCPPBRESULT_BITS
{
    Uint32 ppbresult : 16; /* 15:0 */
    Uint32 sign      : 16; /* 31:16 */
};
union HR_ADCPPBRESULT_REG
{
    Uint32 all;
    struct HR_ADCPPBRESULT_BITS bit;
};

struct HR_ADC_REGS
{
    union HR_ADCCTL1_REG adcctl1;           /* 0x00 */
    union HR_ADCCTL2_REG adcctl2;           /* 0x04 */
    union HR_ADCINTFLG_REG adcintflg;       /* 0x08 */
    union HR_ADCINTFLGCLR_REG adcintflgclr; /* 0x0c */
    union HR_ADCINTOVF_REG adcintovf;       /* 0x10 */
    union HR_ADCINTOVFCLR_REG adcintovfclr; /* 0x14 */
    union HR_ADCINTSELINT_REG adcintselint; /* 0x18 */
    union HR_ADCSOCPRICTL_REG adcsocprictl; /* 0x1c */
    union HR_ADCSOCFLG_REG adcsocflg;       /* 0x20 */
    union HR_ADCSOCFRC_REG adcsocfrc;       /* 0x24 */
    union HR_ADCSOCOVF_REG adcsocovf;       /* 0x28 */
    union HR_ADCSOCOVFCLR_REG adcsocovfclr; /* 0x2c */
    union HR_ADCSOCCTL_REG adcsoc0ctl;      /* 0x30 */
    union HR_ADCSOCCTL_REG adcsoc1ctl;      /* 0x34 */
    union HR_ADCSOCCTL_REG adcsoc2ctl;      /* 0x38 */
    union HR_ADCSOCCTL_REG adcsoc3ctl;      /* 0x3c */
    union HR_ADCSOCCTL_REG adcsoc4ctl;      /* 0x40 */
    union HR_ADCSOCCTL_REG adcsoc5ctl;      /* 0x44 */
    union HR_ADCSOCCTL_REG adcsoc6ctl;      /* 0x48 */
    union HR_ADCSOCCTL_REG adcsoc7ctl;      /* 0x4c */
    union HR_ADCSOCCTL_REG adcsoc8ctl;      /* 0x50 */
    union HR_ADCSOCCTL_REG adcsoc9ctl;      /* 0x54 */
    union HR_ADCSOCCTL_REG adcsoc10ctl;     /* 0x58 */
    union HR_ADCSOCCTL_REG adcsoc11ctl;     /* 0x5c */
    union HR_ADCSOCCTL_REG adcsoc12ctl;     /* 0x60 */
    union HR_ADCSOCCTL_REG adcsoc13ctl;     /* 0x64 */
    union HR_ADCSOCCTL_REG adcsoc14ctl;     /* 0x68 */
    union HR_ADCSOCCTL_REG adcsoc15ctl;     /* 0x6c */
    union HR_ADCEVTSTAT_REG adcevtstat;     /* 0x70 */
    union HR_ADCEVTCLR_REG adcevtclr;       /* 0x74 */
    union HR_ADCEVTSEL_REG adcevtsel;       /* 0x78 */
    union HR_ADCEVTINTSEL_REG adcevtintsel; /* 0x7c */
    union HR_ADCCOUNT_REG adccounter;       /* 0x80 */
    union HR_ADCREV_REG adcrev;             /* 0x84 */

    union HR_ADCPPBCONFIG_REG adcppb1config; /* 0x88 */
    union HR_ADCPPBSTAMP_REG adcpp1stamp;    /* 0x8c */
    union HR_ADCPPBOFFCAL_REG adcpp1offcal;  /* 0x90 */
    union HR_ADCPPBOFFREF_REG adcpp1offref;  /* 0x94 */
    union HR_ADCPPBTRIPHI_REG adcpp1triphi;  /* 0x98 */
    union HR_ADCPPBTRIPLO_REG adcpp1triplo;  /* 0x9c */

    union HR_ADCPPBCONFIG_REG adcppb2config; /* 0xa0 */
    union HR_ADCPPBSTAMP_REG adcpp2stamp;    /* 0xa4 */
    union HR_ADCPPBOFFCAL_REG adcpp2offcal;  /* 0xa8 */
    union HR_ADCPPBOFFREF_REG adcpp2offref;  /* 0xac */
    union HR_ADCPPBTRIPHI_REG adcpp2triphi;  /* 0xb0 */
    union HR_ADCPPBTRIPLO_REG adcpp2triplo;  /* 0xb4 */

    union HR_ADCPPBCONFIG_REG adcppb3config; /* 0xb8 */
    union HR_ADCPPBSTAMP_REG adcpp3stamp;    /* 0xbc */
    union HR_ADCPPBOFFCAL_REG adcpp3offcal;  /* 0xc0 */
    union HR_ADCPPBOFFREF_REG adcpp3offref;  /* 0xc4 */
    union HR_ADCPPBTRIPHI_REG adcpp3triphi;  /* 0xc8 */
    union HR_ADCPPBTRIPLO_REG adcpp3triplo;  /* 0xcc */

    union HR_ADCPPBCONFIG_REG adcppb4config; /* 0xd0 */
    union HR_ADCPPBSTAMP_REG adcpp4stamp;    /* 0xd4 */
    union HR_ADCPPBOFFCAL_REG adcpp4offcal;  /* 0xd8 */
    union HR_ADCPPBOFFREF_REG adcpp4offref;  /* 0xdc */
    union HR_ADCPPBTRIPHI_REG adcpp4triphi;  /* 0xe0 */
    union HR_ADCPPBTRIPLO_REG adcpp4triplo;  /* 0xe4 */
};

struct HR_ADC_RESULT_REGS
{
    union HR_ADCRESULT_REG adcresult0;  /* 0x100 */
    union HR_ADCRESULT_REG adcresult1;  /* 0x104 */
    union HR_ADCRESULT_REG adcresult2;  /* 0x108 */
    union HR_ADCRESULT_REG adcresult3;  /* 0x10c */
    union HR_ADCRESULT_REG adcresult4;  /* 0x110 */
    union HR_ADCRESULT_REG adcresult5;  /* 0x114 */
    union HR_ADCRESULT_REG adcresult6;  /* 0x118 */
    union HR_ADCRESULT_REG adcresult7;  /* 0x11c */
    union HR_ADCRESULT_REG adcresult8;  /* 0x120 */
    union HR_ADCRESULT_REG adcresult9;  /* 0x124 */
    union HR_ADCRESULT_REG adcresult10; /* 0x128 */
    union HR_ADCRESULT_REG adcresult11; /* 0x12c */
    union HR_ADCRESULT_REG adcresult12; /* 0x130 */
    union HR_ADCRESULT_REG adcresult13; /* 0x134 */
    union HR_ADCRESULT_REG adcresult14; /* 0x138 */
    union HR_ADCRESULT_REG adcresult15; /* 0x13c */
};

struct HR_ADC_PPBRESULT_REGS
{
    union HR_ADCPPBRESULT_REG adcppb1result; /* 0x150 */
    union HR_ADCPPBRESULT_REG adcppb2result; /* 0x154 */
    union HR_ADCPPBRESULT_REG adcppb3result; /* 0x158 */
    union HR_ADCPPBRESULT_REG adcppb4result; /* 0x15c */
};

// FIXME : IF YOU NEED ZW-LIN
#if 0
struct I_APB_ADDR_BITS
{
    /* data */
    Uint32  addr            : 8  ;          /* 7:0 */
    Uint32  rsvd            : 24 ;          /* 31:8 */
};
union I_APB_ADDR_REG{
    Uint32  all;
    struct  I_APB_ADDR_BITS bit;
};


struct I_APB_DATA_BITS
{
    /* data */
    Uint32  data           : 8  ;           /* 7:0 */
    Uint32  rsvd           : 24 ;           /* 31:8 */
};
union I_APB_DATA_REG{
    Uint32  all;
    struct  I_APB_DATA_BITS bit;
};

struct I_APB_CTRL_BITS
{
    /* data */
    Uint32  validity       : 1 ;            /* 0 */
    Uint32  rsvd           : 31 ;           /* 31:1 */
};
union I_APB_CTRL_REG{
    Uint32   all;
    struct  I_APB_CTRL_BITS bit;
};

struct I_COEF_CTRL_BITS
{
    /* data */
    Uint32  latch_coef         : 1 ;        /* 0 */
    Uint32  capture_coe        : 1 ;        /* 1 */
    Uint32  rsvd               : 30 ;       /* 31:2 */
};
union I_COEF_CTRL_REG{
    Uint8   all;
    struct  I_COEF_CTRL_BITS bit;
};

struct I_COEF_BITS
{
    /* data */
    Uint32  calibration         : 8  ;      /* 7:0 */
    Uint32  rsvd                : 24 ;      /* 31:8 */
};
union I_COEF_REG{
    Uint32   all;
    struct  I_COEF_BITS bit;
};

struct I_COEFS_RO_BITS
{
    /* data */
    Uint32  inter_calibration   : 8  ;       /* 7:0 */
    Uint32  rsvd                : 24 ;       /* 31:0 */
};
union I_COEFS_RO_REG{
    Uint32  all;
    struct  I_COEFS_RO_BITS bit;
};


struct APB_REGS{
    union   I_APB_ADDR_REG      i_apb_addr;             /* 0x200 */
    union   I_APB_DATA_REG      i_apb_data;             /* 0x204 */
    union   I_APB_CTRL_REG      i_apb_ctrl;             /* 0x208 */
    union   I_COEF_CTRL_REG     i_coef_ctrl;            /* 0x20c */
};

struct APB_COEFS_REGS{
    union   I_COEFS_REG         i_coefs_8;              /* 0x220 */
    union   I_COEFS_REG         i_coefs_9;              /* 0x224 */
    union   I_COEFS_REG         i_coefs_a;              /* 0x228 */
    union   I_COEFS_REG         i_coefs_b;              /* 0x22c */
    union   I_COEFS_REG         i_coefs_c;              /* 0x230 */
    union   I_COEFS_REG         i_coefs_d;              /* 0x234 */
    union   I_COEFS_REG         i_coefs_e;              /* 0x238 */
    union   I_COEFS_REG         i_coefs_f;              /* 0x23c */
    union   I_COEFS_REG         i_coefs_10;              /* 0x240 */
    union   I_COEFS_REG         i_coefs_11;              /* 0x244 */
    union   I_COEFS_REG         i_coefs_12;              /* 0x248 */
    union   I_COEFS_REG         i_coefs_13;              /* 0x24c */
    union   I_COEFS_REG         i_coefs_14;              /* 0x250 */
    union   I_COEFS_REG         i_coefs_15;              /* 0x254 */
    union   I_COEFS_REG         i_coefs_16;              /* 0x258 */
    union   I_COEFS_REG         i_coefs_17;              /* 0x25c */
    union   I_COEFS_REG         i_coefs_18;              /* 0x260 */
    union   I_COEFS_REG         i_coefs_19;              /* 0x264 */
    union   I_COEFS_REG         i_coefs_1a;              /* 0x268 */
    union   I_COEFS_REG         i_coefs_1b;              /* 0x26c */
    union   I_COEFS_REG         i_coefs_1c;              /* 0x270 */
    union   I_COEFS_REG         i_coefs_1d;              /* 0x274 */
    union   I_COEFS_REG         i_coefs_1e;              /* 0x278 */
    union   I_COEFS_REG         i_coefs_1f;              /* 0x27c */
    union   I_COEFS_REG         i_coefs_20;              /* 0x280 */
    union   I_COEFS_REG         i_coefs_21;              /* 0x284 */
    union   I_COEFS_REG         i_coefs_22;              /* 0x288 */
    union   I_COEFS_REG         i_coefs_23;              /* 0x28c */
    union   I_COEFS_REG         i_coefs_24;              /* 0x290 */
    union   I_COEFS_REG         i_coefs_25;              /* 0x294 */
    union   I_COEFS_REG         i_coefs_26;              /* 0x298 */
};

struct APB_COEFS_RO_REGS
{
    /* data */
    union   I_COEFS_RO_REG      i_coefs_ro_2c;           /* 0x2b0 */
    union   I_COEFS_RO_REG      i_coefs_ro_2d;           /* 0x2b4 */
    union   I_COEFS_RO_REG      i_coefs_ro_2e;           /* 0x2b8 */
    union   I_COEFS_RO_REG      i_coefs_ro_2f;           /* 0x2bc */
    union   I_COEFS_RO_REG      i_coefs_ro_30;           /* 0x2c0 */
    union   I_COEFS_RO_REG      i_coefs_ro_31;           /* 0x2c4 */
    union   I_COEFS_RO_REG      i_coefs_ro_32;           /* 0x2c8 */
    union   I_COEFS_RO_REG      i_coefs_ro_33;           /* 0x2cc */
    union   I_COEFS_RO_REG      i_coefs_ro_34;           /* 0x2d0 */
    union   I_COEFS_RO_REG      i_coefs_ro_35;           /* 0x2d4 */
    union   I_COEFS_RO_REG      i_coefs_ro_36;           /* 0x2d8 */
    union   I_COEFS_RO_REG      i_coefs_ro_37;           /* 0x2dc */
    union   I_COEFS_RO_REG      i_coefs_ro_38;           /* 0x2e0 */
    union   I_COEFS_RO_REG      i_coefs_ro_39;           /* 0x2e4 */
    union   I_COEFS_RO_REG      i_coefs_ro_3a;           /* 0x2e8 */
    union   I_COEFS_RO_REG      i_coefs_ro_3b;           /* 0x2ec */
    union   I_COEFS_RO_REG      i_coefs_ro_3c;           /* 0x2f0 */
    union   I_COEFS_RO_REG      i_coefs_ro_3d;           /* 0x2f4 */
    union   I_COEFS_RO_REG      i_coefs_ro_3e;           /* 0x2f8 */
    union   I_COEFS_RO_REG      i_coefs_ro_3f;           /* 0x2fc */
    union   I_COEFS_RO_REG      i_coefs_ro_40;           /* 0x300 */
    union   I_COEFS_RO_REG      i_coefs_ro_41;           /* 0x304 */
    union   I_COEFS_RO_REG      i_coefs_ro_42;           /* 0x308 */
    union   I_COEFS_RO_REG      i_coefs_ro_43;           /* 0x30c */
    union   I_COEFS_RO_REG      i_coefs_ro_44;           /* 0x310 */
    union   I_COEFS_RO_REG      i_coefs_ro_45;           /* 0x314 */
    union   I_COEFS_RO_REG      i_coefs_ro_46;           /* 0x318 */
    union   I_COEFS_RO_REG      i_coefs_ro_47;           /* 0x31c */
    union   I_COEFS_RO_REG      i_coefs_ro_48;           /* 0x320 */
    union   I_COEFS_RO_REG      i_coefs_ro_49;           /* 0x324 */
    union   I_COEFS_RO_REG      i_coefs_ro_4a;           /* 0x328 */
    union   I_COEFS_RO_REG      i_coefs_ro_4b;           /* 0x32c */
    union   I_COEFS_RO_REG      i_coefs_ro_4c;           /* 0x330 */
    union   I_COEFS_RO_REG      i_coefs_ro_4d;           /* 0x334 */
    union   I_COEFS_RO_REG      i_coefs_ro_4e;           /* 0x338 */
    union   I_COEFS_RO_REG      i_coefs_ro_4f;           /* 0x33c */
};
#endif

//---------------------------------------------------------------------------
// HR_ADC External References & Function Declarations:
//

extern volatile struct HR_ADC_REGS HrAdcaRegs;
extern volatile struct HR_ADC_REGS HrAdcbRegs;
extern volatile struct HR_ADC_REGS HrAdccRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
