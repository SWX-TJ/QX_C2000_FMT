#ifndef Q28004X_I2C_H
#define Q28004X_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_types.h"

struct CON_BITS
{
    Uint32 MASTER_MODE               : 1;  /* [0] */
    Uint32 SPEED                     : 2;  /* [2:1] */
    Uint32 IC_10BITADDR_SLAVE        : 1;  /* [3] */
    Uint32 IC_10BITADDR_MASTER       : 1;  /* [4] */
    Uint32 IC_RESTART_EN             : 1;  /* [5] */
    Uint32 IC_SLAVE_DISABLE          : 1;  /* [6] */
    Uint32 STOP_DET_IFADDRESSED      : 1;  /* [7] */
    Uint32 TX_EMPTY_CTRL             : 1;  /* [8] */
    Uint32 RX_FIFO_FULL_HLD_CTRL     : 1;  /* [9] */
    Uint32 STOP_DET_IF_MASTER_ACTIVE : 1;  /* [10] */
    Uint32 BUS_CLEAR_FEATURE_CTRL    : 1;  /* [11] */
    Uint32 reserved                  : 20; /* [31:12] */
};

union IC_CON_REG
{
    Uint32 all;
    struct CON_BITS bit;
};

struct TAR_BITS
{
    Uint32 TAR                 : 10; /* [9:0] */
    Uint32 GC_OR_START         : 1;  /* [10] */
    Uint32 SPECIAL             : 1;  /* [11] */
    Uint32 IC_10BITADDR_MASTER : 1;  /* [12] */
    Uint32 Device_ID           : 1;  /* [13] */
    Uint32 Reserved            : 18; /* [31:14] */
};

union IC_TAR_REG
{
    Uint32 all;
    struct TAR_BITS bit;
};

struct SAR_BITS
{
    Uint32 SAR      : 10; /* [9:0] */
    Uint32 Reserved : 12; /* [31:10] */
};

union IC_SAR_REG
{
    Uint32 all;
    struct SAR_BITS bit;
};

struct IC_DATA_CMD_BIT
{
    Uint32 DATA            : 8;  /* [7:0] */
    Uint32 CMD             : 1;  /* [8] */
    Uint32 STOP            : 1;  /* [9] */
    Uint32 RESTART         : 1;  /* [10] */
    Uint32 FIRST_DATA_BYTE : 1;  /* [11] */
    Uint32 Reserved        : 20; /* [31:12] */
};

union IC_DATA_CMD_REG
{
    Uint32 all;
    struct IC_DATA_CMD_BIT bit;
};

struct SS_SCL_HCNT_BITS
{
    Uint32 SS_SCL_HCNT : 16; /* [15:0] */
    Uint32 Reserved    : 16; /* [31:16] */
};

union IC_SS_SCL_HCNT_REG
{
    Uint32 all;
    struct SS_SCL_HCNT_BITS bit;
};

struct SS_SCL_LCNT_BITS
{
    Uint32 SS_SCL_LCNT : 16; /* [15:0] */
    Uint32 Reserved    : 16; /* [31:16] */
};

union IC_SS_SCL_LCNT_REG
{
    Uint32 all;
    struct SS_SCL_LCNT_BITS bit;
};

struct FS_SCL_HCNT_BITS
{
    Uint32 FS_SCL_HCNT : 16; /* [15:0] */
    Uint32 Reserved    : 16; /* [31:16] */
};

union IC_FS_SCL_HCNT_REG
{
    Uint32 all;
    struct FS_SCL_HCNT_BITS bit;
};

struct FS_SCL_LCNT_BITS
{
    Uint32 FS_SCL_LCNT : 16; /* [15:0] */
    Uint32 Reserved    : 16; /* [31:16] */
};

union IC_FS_SCL_LCNT_REG
{
    Uint32 all;
    struct FS_SCL_LCNT_BITS bit;
};

struct INTR_STAT_BITS
{
    Uint32 RX_UNDE          : 1;  /* [0] */
    Uint32 RX_OVER          : 1;  /* [1] */
    Uint32 RX_FULL          : 1;  /* [2] */
    Uint32 TX_OVER          : 1;  /* [3] */
    Uint32 TX_EMPTY         : 1;  /* [4] */
    Uint32 RD_REQ           : 1;  /* [5] */
    Uint32 TX_ABRT          : 1;  /* [6] */
    Uint32 RX_DONE          : 1;  /* [7] */
    Uint32 ACTIVITY         : 1;  /* [8] */
    Uint32 STOP_DET         : 1;  /* [9] */
    Uint32 START_DET        : 1;  /* [10] */
    Uint32 GEN_CALL         : 1;  /* [11] */
    Uint32 RESTART_DET      : 1;  /* [12] */
    Uint32 MST_ON_HOLD      : 1;  /* [13] */
    Uint32 SCL_STUCK_AT_LOW : 1;  /* [14] */
    Uint32 Reserved         : 17; /* [31:15] */
};

union IC_INTR_STAT_REG
{
    Uint32 all;
    struct INTR_STAT_BITS bit;
};

struct INTR_MASK_BITS
{
    Uint32 M_RX_UNDER         : 1;  /* [0] */
    Uint32 M_RX_OVER          : 1;  /* [1] */
    Uint32 M_RX_FULL          : 1;  /* [2] */
    Uint32 M_TX_OVER          : 1;  /* [3] */
    Uint32 M_TX_EMPTY         : 1;  /* [4] */
    Uint32 M_RD_REQ           : 1;  /* [5] */
    Uint32 M_TX_ABRT          : 1;  /* [6] */
    Uint32 M_RX_DONE          : 1;  /* [7] */
    Uint32 M_ACTIVITY         : 1;  /* [8] */
    Uint32 M_STOP_DET         : 1;  /* [9] */
    Uint32 M_START_DET        : 1;  /* [10] */
    Uint32 M_GEN_CALL         : 1;  /* [11] */
    Uint32 M_RESTART_DET      : 1;  /* [12] */
    Uint32 M_MST_ON_HOLD      : 1;  /* [13] */
    Uint32 M_SCL_STUCK_AT_LOW : 1;  /* [14] */
    Uint32 Reserved           : 17; /* [31:15] */
};

union IC_INTR_MASK_REG
{
    Uint32 all;
    struct INTR_MASK_BITS bit;
};

struct RAW_INTR_STAT_BITS
{
    Uint32 RX_UNDE          : 1;  /* [0] */
    Uint32 RX_OVER          : 1;  /* [1] */
    Uint32 RX_FULL          : 1;  /* [2] */
    Uint32 TX_OVER          : 1;  /* [3] */
    Uint32 TX_EMPTY         : 1;  /* [4] */
    Uint32 RD_REQ           : 1;  /* [5] */
    Uint32 TX_ABRT          : 1;  /* [6] */
    Uint32 RX_DONE          : 1;  /* [7] */
    Uint32 ACTIVITY         : 1;  /* [8] */
    Uint32 STOP_DET         : 1;  /* [9] */
    Uint32 START_DET        : 1;  /* [10] */
    Uint32 GEN_CALL         : 1;  /* [11] */
    Uint32 RESTART_DET      : 1;  /* [12] */
    Uint32 MST_ON_HOLD      : 1;  /* [13] */
    Uint32 SCL_STUCK_AT_LOW : 1;  /* [14] */
    Uint32 Reserved         : 17; /* [31:15] */
};

union IC_RAW_INTR_STAT_REG
{
    Uint32 all;
    struct RAW_INTR_STAT_BITS bit;
};

struct ENABLE_BITS
{
    Uint32 ENABLE                    : 1;  /* [0] */
    Uint32 ABORT                     : 1;  /* [1] */
    Uint32 TX_CMD_BLOCK              : 1;  /* [2] */
    Uint32 SDA_STUCK_RECOVERY_ENABLE : 1;  /* [3] */
    Uint32 Reserved1                 : 12; /* [15:4] */
    Uint32 Reserved2                 : 16; /* [31:16] */
};

union IC_ENABLE_REG
{
    Uint32 all;
    struct ENABLE_BITS bit;
};

struct IC_STATUS_BITS
{
    Uint32 ACTIVITY                : 1;  /* [0] */
    Uint32 TFNF                    : 1;  /* [1] */
    Uint32 TFE                     : 1;  /* [2] */
    Uint32 RFNE                    : 1;  /* [3] */
    Uint32 RFF                     : 1;  /* [4] */
    Uint32 MST_ACTIVITY            : 1;  /* [5] */
    Uint32 SLV_ACTIVITY            : 1;  /* [6] */
    Uint32 MST_HOLD_TX_FIFO_EMPTY  : 1;  /* [7] */
    Uint32 MST_HOLD_RX_FIFO_FULL   : 1;  /* [8] */
    Uint32 SLV_HOLD_TX_FIFO_EMPTY  : 1;  /* [9] */
    Uint32 SLV_HOLD_RX_FIFO_FULL   : 1;  /* [10] */
    Uint32 SDA_STUCK_NOT_RECOVERED : 1;  /* [11] */
    Uint32 Reserved1               : 4;  /* [15:12] */
    Uint32 Reserved2               : 16; /* [31:16] */
};

union IC_STATUS_REG
{
    Uint32 all;
    struct IC_STATUS_BITS bit;
};

struct SDA_HOLD_BITS
{
    Uint32 IC_SDA_TX_HOLD : 16; /* [15:0] */
    Uint32 IC_SDA_RX_HOLD : 8;  /* [23:16] */
    Uint32 Reserved       : 8;  /* [31:24] */
};

union IC_SDA_HOLD_REG
{
    Uint32 all;
    struct SDA_HOLD_BITS bit;
};

struct DMA_CR_BITS
{
    Uint32 RDMAE    : 1;  /* [0] */
    Uint32 TDMAE    : 1;  /* [1] */
    Uint32 Reserved : 30; /* [31:2] */
};

union IC_DMA_CR_REG
{
    Uint32 all;
    struct DMA_CR_BITS bit;
};

struct SDA_SETUP_BITS
{
    Uint32 SDA_SETUP : 8;  /* [7:0] */
    Uint32 Reserved  : 24; /* [31:8] */
};

union IC_SDA_SETUP_REG
{
    Uint32 all;
    struct SDA_SETUP_BITS bit;
};

struct ENABLE_STATUS_BITS
{
    Uint32 IC_EN                   : 1; /* [0] */
    Uint32 SLV_DISABLED_WHILE_BUSY : 1; /* [1] */
    Uint32 SLV_RX_DATA_LOST        : 1; /* [2] */
};

union IC_ENABLE_STATUS_REG
{
    Uint32 all;
    struct ENABLE_STATUS_BITS bit;
};

struct I2C_REGS
{
    union IC_CON_REG IC_CON;                     /* offset:0x00 */
    union IC_TAR_REG IC_TAR;                     /* offset:0x04 */
    union IC_SAR_REG IC_SAR;                     /* offset:0x08 */
    Uint32 IC_HS_MAR;                            /* offset:0x0C */
    union IC_DATA_CMD_REG IC_DATA_CMD;           /* offset:0x10 */
    union IC_SS_SCL_HCNT_REG IC_SS_SCL_HCNT;     /* offset:0x14 */
    union IC_SS_SCL_LCNT_REG IC_SS_SCL_LCNT;     /* offset:0x18 */
    union IC_FS_SCL_HCNT_REG IC_FS_SCL_HCNT;     /* offset:0x1C */
    union IC_FS_SCL_LCNT_REG IC_FS_SCL_LCNT;     /* offset:0x20 */
    Uint32 Reserved1;                            /* offset:0x24 */
    Uint32 Reserved2;                            /* offset:0x28 */
    union IC_INTR_STAT_REG IC_INTR_STAT;         /* offset:0x2C */
    union IC_INTR_MASK_REG IC_INTR_MASK;         /* offset:0x30 */
    union IC_RAW_INTR_STAT_REG IC_RAW_INTR_STAT; /* offset:0x34 */
    Uint32 IC_RX_TL;                             /* offset:0x38 */
    Uint32 IC_TX_TL;                             /* offset:0x3C */
    Uint32 IC_CLR_INTR;                          /* offset:0x40 */
    Uint32 IC_CLR_RX_UNDER;                      /* offset:0x44 */
    Uint32 IC_CLR_RX_OVER;                       /* offset:0x48 */
    Uint32 IC_CLR_TX_OVER;                       /* offset:0x4C */
    Uint32 IC_CLR_RD_REQ;                        /* offset:0x50 */
    Uint32 IC_CLR_TX_ABRT;                       /* offset:0x54 */
    Uint32 IC_CLR_RX_DONE;                       /* offset:0x58 */
    Uint32 IC_CLR_ACTIVITY;                      /* offset:0x5C */
    Uint32 IC_CLR_STOP_DET;                      /* offset:0x60 */
    Uint32 IC_CLR_START_DET;                     /* offset:0x64 */
    Uint32 IC_CLR_GEN_CALL;                      /* offset:0x68 */
    union IC_ENABLE_REG IC_ENABLE;               /* offset:0x6C */
    union IC_STATUS_REG IC_STATUS;               /* offset:0x70 */
    Uint32 IC_TXFLR;                             /* offset:0x74 */
    Uint32 IC_RXFLR;                             /* offset:0x78 */
    union IC_SDA_HOLD_REG IC_SDA_HOLD;           /* offset:0x7C */
    Uint32 reserved5;                            /* offset:0x80 */
    Uint32 IC_SLV_DATA_NACK_ONLY;                /* offset:0x84 */
    union IC_DMA_CR_REG IC_DMA_CR;               /* offset:0x88 */
    Uint32 IC_DMA_TDLR;                          /* offset:0x8C */
    Uint32 IC_DMA_RDLR;                          /* offset:0x90 */
    union IC_SDA_SETUP_REG IC_SDA_SETUP;         /* offset:0x94 */
    Uint32 IC_ACK_GENERAL_CALL;                  /* offset:0x98 */
    union IC_ENABLE_STATUS_REG IC_ENABLE_STATUS; /* offset:0x9C */
    Uint32 IC_FS_SPKLEN;                         /* offset:0xA0 */
    Uint32 Reserved9;                            /* offset:0xA4 */
    Uint32 IC_CLR_RESTART_DET;                   /* offset:0xA8 */
};

extern volatile struct I2C_REGS I2caRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
