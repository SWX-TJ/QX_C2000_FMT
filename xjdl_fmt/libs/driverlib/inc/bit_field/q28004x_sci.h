#ifndef Q28004X_SCI_H
#define Q28004X_SCI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_types.h"

struct IER_BITS
{
    Uint32 ERBFI : 1;  /* [0] */
    Uint32 ETBEI : 1;  /* [1] */
    Uint32 ELSI  : 1;  /* [2] */
    Uint32 EDSSI : 1;  /* [3] */
    Uint32 rsvd0 : 3;  /* [6:4] */
    Uint32 PTIME : 1;  /* [7] */
    Uint32 rsvd1 : 24; /* [31:8] */
};

union IER_REG
{
    Uint32 all;
    struct IER_BITS bit;
};

struct IIR_BITS
{
    Uint32 INTID   : 4;  /* [3:0] */
    Uint32 RESERVE : 2;  /* [5:4] */
    Uint32 FIFO_EN : 2;  /* [7:6] */
    Uint32 RSVD    : 24; /* [31:8] */
};

union IIR_REG
{
    Uint32 all;
    struct IIR_BITS bit;
};

struct FCR_BITS
{
    Uint32 FIFOE  : 1;  /* [0] */
    Uint32 RFIFOR : 1;  /* [1] */
    Uint32 XFIFOR : 1;  /* [2] */
    Uint32 DMAM   : 1;  /* [3] */
    Uint32 TET    : 2;  /* [5:4] */
    Uint32 RCVR   : 2;  /* [7:6] */
    Uint32 rsvd   : 24; /* [31:8] */
};

union FCR_REG
{
    Uint32 all;
    struct FCR_BITS bit;
};

struct LCR_BITS
{
    Uint32 DLS          : 2;  /* [1:0] */
    Uint32 STOP         : 1;  /* [2] */
    Uint32 PEN          : 1;  /* [3] */
    Uint32 EPS          : 1;  /* [4] */
    Uint32 STICK_PARITY : 1;  /* [5] */
    Uint32 BC           : 1;  /* [6] */
    Uint32 DLAB         : 1;  /* [7] */
    Uint32 rsvd         : 24; /* [31:8] */
};

union LCR_REG
{
    Uint32 all;
    struct LCR_BITS bit;
};

struct MCR_BITS
{
    Uint32 rsvd0    : 4;  /* [3:0] DTR/RTS/OUT1/OUT2 reserved */
    Uint32 LOOPBACK : 1;  /* [4] */
    Uint32 rsvd1    : 27; /* [31:5] AFCE/SIRE reserved */
};

union MCR_REG
{
    Uint32 all;
    struct MCR_BITS bit;
};

struct LSR_BITS
{
    Uint32 DR   : 1;  /* [0] */
    Uint32 OE   : 1;  /* [1] */
    Uint32 PE   : 1;  /* [2] */
    Uint32 FE   : 1;  /* [3] */
    Uint32 BI   : 1;  /* [4] */
    Uint32 THRE : 1;  /* [5] */
    Uint32 TEMT : 1;  /* [6] */
    Uint32 RFE  : 1;  /* [7] */
    Uint32 rsvd : 24; /* [31:8] ADDR_RCVD reserved */
};

union LSR_REG
{
    Uint32 all;
    struct LSR_BITS bit;
};

struct MSR_BITS
{
    Uint32 DCTS : 1;  /* [0] */
    Uint32 DDSR : 1;  /* [1] */
    Uint32 TERI : 1;  /* [2] */
    Uint32 DDCD : 1;  /* [3] */
    Uint32 CTS  : 1;  /* [4] */
    Uint32 DSR  : 1;  /* [5] */
    Uint32 RI   : 1;  /* [6] */
    Uint32 DCD  : 1;  /* [7] */
    Uint32 rsvd : 24; /* [31:8] */
};

union MSR_REG
{
    Uint32 all;
    struct MSR_BITS bit;
};

struct USR_BITS
{
    Uint32 BUSY : 1;  /* [0] */
    Uint32 TFNF : 1;  /* [1] */
    Uint32 TFE  : 1;  /* [2] */
    Uint32 RFNE : 1;  /* [3] */
    Uint32 RFF  : 1;  /* [4] */
    Uint32 rsvd : 27; /* [31:5] */
};

union USR_REG
{
    Uint32 all;
    struct USR_BITS bit;
};

struct TFL_BITS
{
    Uint32 TFL  : 5;  /* [0:4] */
    Uint32 rsvd : 27; /* [31:5] */
};

union TFL_REG
{
    Uint32 all;
    struct TFL_BITS bit;
};

struct RFL_BITS
{
    Uint32 RFL  : 5;  /* [0:4] */
    Uint32 rsvd : 27; /* [31:5] */
};

union RFL_REG
{
    Uint32 all;
    struct RFL_BITS bit;
};

struct HTX_BITS
{
    Uint32 HTX  : 1;  /* [0] */
    Uint32 rsvd : 31; /* [31:1] */
};

union HTX_REG
{
    Uint32 all;
    struct HTX_BITS bit;
};

struct DMASA_BITS
{
    Uint32 DMASA : 1;  /* [0] */
    Uint32 rsvd  : 31; /* [31:1] */
};

union DMASA_REG
{
    Uint32 all;
    struct DMASA_BITS bit;
};

struct LCR_EXT_BITS
{
    Uint32 DLS_E         : 1;  /* [0] */
    Uint32 ADDR_MATCH    : 1;  /* [1] */
    Uint32 SEND_ADDR     : 1;  /* [2] */
    Uint32 TRANSMIT_MODE : 1;  /* [3] */
    Uint32 rsvd          : 28; /* [31:4] */
};

union LCR_EXT_REG
{
    Uint32 all;
    struct LCR_EXT_BITS bit;
};

struct SCI_REGS
{
    union /* offset:0x00 */
    {
        Uint32 RBR;
        Uint32 THR;
        Uint32 DLL;
    };
    union /* offset:0x04 */
    {
        Uint32 DLH;
        union IER_REG IER;
    };
    union /* offset:0x08 */
    {
        union IIR_REG IIR;
        union FCR_REG FCR;
    };
    union LCR_REG LCR;         /* offset:0x0C */
    union MCR_REG MCR;         /* offset:0x10 */
    union LSR_REG LSR;         /* offset:0x14 */
    union MSR_REG MSR;         /* offset:0x18 */
    Uint32 SCR;                /* offset:0x1C */
    Uint32 rsvd0[23];          /* offset:0x20-0x78 */
    union USR_REG USR;         /* offset:0x7C */
    union TFL_REG TFL;         /* offset:0x80 */
    union RFL_REG RFL;         /* offset:0x84 */
    Uint32 rsvd1[7];           /* offset:0x88-0xA0 */
    union HTX_REG HTX;         /* offset:0xA4 */
    union DMASA_REG DAMSA;     /* offset:0xA8 */
    Uint32 revd2[5];           /* offset:0xAC-0xBC */
    Uint32 DLF;                /* offset:0xC0 */
    Uint32 RAR;                /* offset:0xC4 */
    Uint32 TAR;                /* offset:0xC8 */
    union LCR_EXT_REG LCR_EXT; /* offset:0xCC */
    Uint32 revd3[12];          /* offset:0xD0-0xFC */
};

extern volatile struct SCI_REGS SciaRegs;
extern volatile struct SCI_REGS ScibRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
