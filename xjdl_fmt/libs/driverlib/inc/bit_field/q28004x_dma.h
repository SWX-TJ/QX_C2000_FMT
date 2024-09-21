#ifndef Q28004X_DMA_H
#define Q28004X_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_types.h"

struct CFG_BITS
{
    Uint32 DMAC_EN : 1;  // [0]
    Uint32 INT_EN  : 1;  // [1]
    Uint32 rsvd    : 30; // [31:2]
};

union CFG_REG
{
    Uint32 all;
    struct CFG_BITS bit;
};

struct CTL_L_BITS
{
    Uint32 SMS       : 1; // [0]
    Uint32 rsvd0     : 1; // [1]
    Uint32 DMS       : 1; // [2]
    Uint32 rsvd1     : 1; // [3]
    Uint32 SINC      : 1; // [4]
    Uint32 rsvd2     : 1; // [5]
    Uint32 DINC      : 1; // [6]
    Uint32 rsvd3     : 1; // [7]
    Uint32 SRC_WIDTH : 3; // [10:8]
    Uint32 DST_WIDTH : 3; // [13:11]
    Uint32 SRC_MSIZE : 4; // [17:14]
    Uint32 DST_MSIZE : 4; // [21:18]
    Uint32 AR_CACHE  : 4; // [25:22]
    Uint32 AW_CACHE  : 4; // [29:26]
    Uint32 rsvd4     : 2; // [31:30]
};

union CTL_L_REG
{
    Uint32 all;
    struct CTL_L_BITS bit;
};

struct CTL_H_BITS
{
    Uint32 AR_PROT     : 3; // [2:0]
    Uint32 AW_PROT     : 3; // [5:3}
    Uint32 ARLEN_EN    : 1; // [6]
    Uint32 ARLEN       : 8; // [14:7]
    Uint32 AWLEN_EN    : 1; // [15]
    Uint32 AW_LEN      : 8; // [23:16]
    Uint32 SRC_STAT_EN : 1; // [24]
    Uint32 DST_STAT_EN : 1; // [25]
    Uint32 IOC_BLKTFR  : 1; // [26]
    Uint32 rsvd        : 5; // [31:27]
};

union CTL_H_REG
{
    Uint32 all;
    struct CTL_H_BITS bit;
};

struct CFG_L_BITS
{
    Uint32 SRC_MULTBLK_TYPE : 2;  // [1:0]
    Uint32 DST_MULTBLK_TYPE : 2;  // [3:2]
    Uint32 rsvd             : 28; // [31:4]
};

union CFG_L_REG
{
    Uint32 all;
    struct CFG_L_BITS bit;
};

struct CFG_H_BITS
{
    Uint32 TT_FC        : 3; // [2:0]
    Uint32 HS_SEL_SRC   : 1; // [3]
    Uint32 HS_SEL_DST   : 1; // [4]
    Uint32 SRC_HWHS_POL : 1; // [5]
    Uint32 DST_HWHS_POL : 1; // [6]
    Uint32 SRC_PER      : 4; // [10:7]
    Uint32 rsvd0        : 1; // [11]
    Uint32 DST_PER      : 4; // [15:12]
    Uint32 rsvd1        : 1; // [16]
    Uint32 CH_PRIOR     : 3; // [19:17]
    Uint32 LOCK_CH      : 1; // [20]
    Uint32 LOCK_CH_L    : 2; // [22:21]
    Uint32 SRC_OSR_LMT  : 4; // [26:23]
    Uint32 DST_OSR_LMT  : 4; // [30:27]
};

union CFG_H_REG
{
    Uint32 all;
    struct CFG_H_BITS bit;
};

struct CFG2_L_BITS
{
    Uint32 SRC_MULTBLK_TYPE : 2; // [1:0]
    Uint32 DST_MULTBLK_TYPE : 2; // [3:2]
    Uint32 SRC_PER          : 6; // [9:4]
    Uint32 rsvd0            : 1; // [10]
    Uint32 DST_PER          : 6; // [16:11]
    Uint32 rsvd1            : 1; // [17]
    Uint32 RD_UID           : 4; // [21:18]
    Uint32 rsvd2            : 3; // [24:22]
    Uint32 WR_UID           : 4; // [21:18]
};

union CFG2_L_REG
{
    Uint32 all;
    struct CFG2_L_BITS bit;
};

struct CFG2_H_BITS
{
    Uint32 TT_FC        : 3; // [2:0]
    Uint32 HS_SEL_SRC   : 1; // [3]
    Uint32 HS_SEL_DST   : 1; // [4]
    Uint32 SRC_HWHS_POL : 1; // [5]
    Uint32 DST_HWHS_POL : 1; // [6]
    Uint32 rsvd0        : 8; // [14:7]
    Uint32 CH_PRIOR     : 5; // [19:15]
    Uint32 LOCK_CH      : 1; // [20]
    Uint32 LOCK_CH_L    : 2; // [22:21]
    Uint32 SRC_OSR_LMT  : 4; // [26:23]
    Uint32 DST_OSR_LMT  : 4; // [30:27]
};

union CFG2_H_REG
{
    Uint32 all;
    struct CFG2_H_BITS bit;
};

struct LLP_BITS
{
    Uint32 LMS  : 1;  // [0]
    Uint32 rsvd : 5;  // [5:1]
    Uint32 LOC  : 26; // [31:6]
};

union LLP_REG
{
    Uint32 all;
    struct LLP_BITS bit;
};

struct SWHSSRC_BITS
{
    Uint32 SWHS_REQ_SRC       : 1; // [0]
    Uint32 SWHS_REQ_SRC_EN    : 1; // [1]
    Uint32 SWHS_SGLREQ_SRC    : 1; // [2]
    Uint32 SWHS_SGLREQ_SRC_WE : 1; // [3]
    Uint32 SWHS_LST_SRC       : 1; // [4]
    Uint32 SWHS_LST_SRC_WE    : 1; // [5]
};

union SWHSSRC_REG
{
    Uint32 all;
    struct SWHSSRC_BITS bit;
};

struct SWHSDST_BITS
{
    Uint32 SWHS_REQ_DST       : 1; // [0]
    Uint32 SWHS_REQ_DST_EN    : 1; // [1]
    Uint32 SWHS_SGLREQ_DST    : 1; // [2]
    Uint32 SWHS_SGLREQ_DST_WE : 1; // [3]
    Uint32 SWHS_LST_DST       : 1; // [4]
    Uint32 SWHS_LST_DST_WE    : 1; // [5]
};

union SWHSDST_REG
{
    Uint32 all;
    struct SWHSDST_BITS bit;
};

struct DMA_CH_REGS
{
    Uint32 SAR;            // 0x00
    Uint32 rsvd1;          // 0x04
    Uint32 DAR;            // 0x08
    Uint32 rsvd2;          // 0x0C
    Uint32 BLOCK_TS;       // 0x10
    Uint32 rsvd3;          // 0x14
    union CTL_L_REG CTL_L; // 0x18
    union CTL_H_REG CTL_H; // rsvd2
    union                  // 0x20
    {
        union CFG_L_REG CFG_L;
        union CFG2_L_REG CFG2_L;
    };
    union // 0x24
    {
        union CFG_H_REG CFG_H;
        union CFG2_H_REG CFG2_H;
    };
    union LLP_REG LLP;         // 0x28
    Uint32 rsvd4;              // 0x2C
    Uint32 STATUS_L;           // 0x30
    Uint32 STATUS_H;           // 0x34
    union SWHSSRC_REG SWHSSRC; // 0x38
    Uint32 rsvd5;              // 0x3C
    union SWHSDST_REG SWHSDST; // 0x40
    Uint32 rsvd6;              // 0x44
    Uint32 BLK_TFR_RESUMEREQ;  // 0x48
    Uint32 rsvd7;              // 0x4C
    Uint32 AIX_ID;             // 0x50
    Uint32 rsvd8;              // 0x54
    Uint32 AIX_QOS;            // 0x58
    Uint32 rsvd9;              // 0x5C
    Uint32 SSTAT;              // 0x50
    Uint32 rsvd10;             // 0x64
    Uint32 DSTAT;              // 0x68
    Uint32 rsvd11;             // 0x6C
    Uint32 SSTATA;             // 0x70
    Uint32 rsvd12;             // 0x74
    Uint32 DSTATA;             // 0x78
    Uint32 rsvd13;             // 0x7C
    Uint32 INTSTATUS_EN;       // 0x80
    Uint32 rsvd14;             // 0x84
    Uint32 INTSTATUS;          // 0x88
    Uint32 rsvd15;             // 0x8C
    Uint32 INTSIGNAL_EN;       // 0x90
    Uint32 rsvd16;             // 0x94
    Uint32 INTCLEAR;           // 0x98
    Uint32 rsvd17;             // 0x9C
};

struct DMA_REGS
{
    Uint32 ID;         // 0x00
    Uint32 rsvd1;      // 0x04
    Uint32 COMPVER;    // 0x08
    Uint32 rsvd2;      // 0x0C
    union CFG_REG CFG; // 0x10
    Uint32 rsvd3;      // 0x14
    union              // 0x18
    {
        Uint32 CHEN;
        Uint32 CHEN2;
    };
    Uint32 rsvd4;     // 0x1c
    Uint32 CHLSUSP_L; // 0x20
    Uint32 CHLSUSP_H; // 0x24
    Uint32 CHABORT_H; // 0x28
    Uint32 CHABORT_L; // 0x2C
    union             // 0x30
    {
        Uint32 INTSTATUS;
        Uint32 INTSTATUS2;
    };
    Uint32 rsvd8;               // 0x34
    Uint32 COMMON_INTCLEAR;     // 0x38
    Uint32 rsvd9;               // 0x3C
    Uint32 COMMON_INTSTATUS_EN; // 0x40
    Uint32 rsvd10;              // 0x44
    Uint32 COMMON_INTSIGNAL_EN; // 0x48
    Uint32 rsvd11;              // 0x4C
    Uint32 COMMON_INTSTATUS;    // 0x50
    Uint32 rsvd12;              // 0x54
    Uint32 RESET;               // 0x58
    Uint32 rsvd13;              // 0x5C
    Uint32 LOWPOWER;            // 0x60
    Uint32 rsvd14;              // 0x64
    Uint32 rsvd15[2];           // 0x68-0x6C
    Uint32 COMMON_PARCTL;       // 0x70
    Uint32 rsvd16;              // 0x74
    Uint32 COMMON_ECCCTLSTATUS; // 0x78
};

extern volatile struct DMA_REGS DmaRegs;

extern volatile struct DMA_CH_REGS DmaCh1Regs;
extern volatile struct DMA_CH_REGS DmaCh2Regs;
extern volatile struct DMA_CH_REGS DmaCh3Regs;
extern volatile struct DMA_CH_REGS DmaCh4Regs;
extern volatile struct DMA_CH_REGS DmaCh5Regs;
extern volatile struct DMA_CH_REGS DmaCh6Regs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
