#ifndef Q28004X_SPI_H
#define Q28004X_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_types.h"

struct CTRL0_BITS
{
    vu32 rsvd0   : 4; /* [3:0] */
    vu32 FRF     : 2; /* [5:4] */
    vu32 SCPH    : 1; /* [6] */
    vu32 SCPOL   : 1; /* [7] */
    vu32 TMOD    : 2; /* [9:8] */
    vu32 SLV_OE  : 1; /* [10] */
    vu32 SRL     : 1; /* [11] */
    vu32 CFS     : 4; /* [15:12] */
    vu32 DFS_32  : 5; /* [20:16] */
    vu32 SPI_FRF : 2; /* [22:21] */
    vu32 rsvd1   : 1; /* [23] */
    vu32 SSTE    : 1; /* [24] */
    vu32 SECONV  : 1; /* [25] */
};

union CTRL0_REG
{
    vu32 all;
    struct CTRL0_BITS bit;
};

struct CTRL1_BITS
{
    vu32 NDF : 16; /* [15:0] */
};

union CTRL1_REG
{
    vu32 all;
    struct CTRL1_BITS bit;
};

struct MWC_BITS
{
    vu32 MWMOD : 1; /* [0] */
    vu32 MDD   : 1; /* [1] */
    vu32 MHS   : 1; /* [2] */
};

union MWC_REG
{
    vu32 all;
    struct MWC_BITS bit;
};

struct STAT_BITS
{
    vu32 BUSY : 1; /* [0] */
    vu32 TFNF : 1; /* [1] */
    vu32 TFE  : 1; /* [2] */
    vu32 RFNE : 1; /* [3] */
    vu32 RFF  : 1; /* [4] */
    vu32 TXE  : 1; /* [5] */
    vu32 DCOL : 1; /* [6] */
};

union STAT_REG
{
    vu32 all;
    struct STAT_BITS bit;
};

struct IM_BITS
{
    vu32 TXEIM : 1; /* [0] */
    vu32 TXOIM : 1; /* [1] */
    vu32 RXUIM : 1; /* [2] */
    vu32 RXOIM : 1; /* [3] */
    vu32 RXFIM : 1; /* [4] */
    vu32 MSTIM : 1; /* [5] */
};

union IM_REG
{
    vu32 all;
    struct IM_BITS bit;
};

struct IS_BITS
{
    vu32 TXEIS : 1; /* [0] */
    vu32 TXOIS : 1; /* [1] */
    vu32 RXUIS : 1; /* [2] */
    vu32 RXOIS : 1; /* [3] */
    vu32 RXFIS : 1; /* [4] */
    vu32 MSTIS : 1; /* [5] */
};

union IS_REG
{
    vu32 all;
    struct IS_BITS bit;
};

struct RIS_BITS
{
    vu32 TXEIR : 1; /* [0] */
    vu32 TXOIR : 1; /* [1] */
    vu32 RXUIR : 1; /* [2] */
    vu32 RXOIR : 1; /* [3] */
    vu32 RXFIR : 1; /* [4] */
    vu32 MSTIR : 1; /* [5] */
};

union IRS_REG
{
    vu32 all;
    struct RIS_BITS bit;
};

struct DMAC_BITS
{
    vu32 RDMAE : 1; /* [0] */
    vu32 TDMAE : 1; /* [1] */
};

union DMAC_REG
{
    vu32 all;
    struct DMAC_BITS bit;
};

struct SPI_CTRL0_BITS
{
    vu32 TRANS_TYPE  : 2; /* [1:0] */
    vu32 ADDR_L      : 4; /* [5:2] */
    vu32 reserved0   : 2; /* [7:6] */
    vu32 INST_L      : 2; /* [9:8] */
    vu32 reserved1   : 1; /* [10] */
    vu32 WAIT_CYCLES : 4; /* [14:11] */
};

union SPI_CTRL0_REG
{
    vu32 all;
    struct SPI_CTRL0_BITS bit;
};

struct SPI_REGS
{
    union CTRL0_REG CTRL0;         /* offset:0x00 */
    union CTRL1_REG CTRL1;         /* offset:0x04 */
    vu32 SSIEN;                    /* offset:0x08 */
    union MWC_REG MWC;             /* offset:0x0c */
    vu32 SE;                       /* offset:0x10 */
    vu32 BAUD;                     /* offset:0x14 */
    vu32 TXFTL;                    /* offset:0x18 */
    vu32 RXFTL;                    /* offset:0x1c */
    vu32 TXFL;                     /* offset:0x20 */
    vu32 RXFL;                     /* offset:0x24 */
    union STAT_REG STAT;           /* offset:0x28 */
    union IM_REG IM;               /* offset:0x2c */
    union IS_REG IS;               /* offset:0x30 */
    union IRS_REG RIS;             /* offset:0x34 */
    vu32 TXOIC;                    /* offset:0x38 */
    vu32 RXOIS;                    /* offset:0x3c */
    vu32 RXUIC;                    /* offset:0x40 */
    vu32 MSTIC;                    /* offset:0x44 */
    vu32 IC;                       /* offset:0x48 */
    union DMAC_REG DMAC;           /* offset:0x4c */
    vu32 DMATDL;                   /* offset:0x50 */
    vu32 DMARDL;                   /* offset:0x54 */
    vu32 ID;                       /* offset:0x58 */
    vu32 SSI_VERSION_ID;           /* offset:0x5c */
    vu32 DATA[0x24];               /* offset:0x60 */
    vu32 RX_SAMPLE_DLY;            /* offset:0xf0 */
    union SPI_CTRL0_REG SPI_CTRL0; /* offset:0xf4 */
    vu32 rsvd_1;                   /* offset:0xf8 */
    vu32 rsvd_2;                   /* offset:0xfc */
};

struct COMBINE_REGS
{
    struct SPI_REGS MASTER;
    u32 rsvd1[0xC0];
    struct SPI_REGS SLAVE;
    u32 rsvd2[0xC0];
    vu32 SPI_SEL;
};

extern volatile struct COMBINE_REGS SpiaRegs;
extern volatile struct COMBINE_REGS SpibRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
