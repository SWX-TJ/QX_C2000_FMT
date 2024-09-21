#ifndef Q28004X_DCC_H
#define Q28004X_DCC_H

#include "q28004x_types.h"

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// DCC Individual Register Bit Definitions:

struct DCCGCTRL_BITS
{                           // bits description
    Uint32 DCCENA     : 4;  // 3:0 DCC Enable
    Uint32 ERRENA     : 4;  // 7:4 Error Enable
    Uint32 SINGLESHOT : 4;  // 11:8 Single-Shot Enable
    Uint32 DONEENA    : 4;  // 15:12 DONE Enable
    Uint32 rsvd1      : 16; // 31:16 Reserved
};

union DCCGCTRL_REG
{
    Uint32 all;
    struct DCCGCTRL_BITS bit;
};

struct DCCREV_BITS
{                      // bits description
    Uint32 MINOR : 6;  // 5:0 Minor Revision Number
    Uint32 rsvd1 : 2;  // 7:6 Reserved
    Uint32 MAJOR : 3;  // 10:8 Major Revision Number
    Uint32 rsvd2 : 5;  // 15:11 Reserved
    Uint32 rsvd3 : 12; // 27:16 Reserved
    Uint32 rsvd4 : 2;  // 29:28 Reserved
    Uint32 rsvd5 : 2;  // 31:30 Reserved
};

union DCCREV_REG
{
    Uint32 all;
    struct DCCREV_BITS bit;
};

struct DCCCNTSEED0_BITS
{                           // bits description
    Uint32 COUNTSEED0 : 20; // 19:0 Seed Value for Counter 0
    Uint32 rsvd1      : 12; // 31:20 Reserved
};

union DCCCNTSEED0_REG
{
    Uint32 all;
    struct DCCCNTSEED0_BITS bit;
};

struct DCCVALIDSEED0_BITS
{                          // bits description
    Uint32 VALIDSEED : 16; // 15:0 Seed Value for Valid Duration Counter 0
    Uint32 rsvd1     : 16; // 31:16 Reserved
};

union DCCVALIDSEED0_REG
{
    Uint32 all;
    struct DCCVALIDSEED0_BITS bit;
};

struct DCCCNTSEED1_BITS
{                           // bits description
    Uint32 COUNTSEED1 : 20; // 19:0 Seed Value for Counter 1
    Uint32 rsvd1      : 12; // 31:20 Reserved
};

union DCCCNTSEED1_REG
{
    Uint32 all;
    struct DCCCNTSEED1_BITS bit;
};

struct DCCSTATUS_BITS
{                      // bits description
    Uint32 ERR   : 1;  // 0 Error Flag
    Uint32 DONE  : 1;  // 1 Single-Shot Done Flag
    Uint32 rsvd1 : 14; // 15:2 Reserved
    Uint32 rsvd2 : 16; // 31:16 Reserved
};

union DCCSTATUS_REG
{
    Uint32 all;
    struct DCCSTATUS_BITS bit;
};

struct DCCCNT0_BITS
{                       // bits description
    Uint32 COUNT0 : 20; // 19:0 Current Value of Counter 0
    Uint32 rsvd1  : 12; // 31:20 Reserved
};

union DCCCNT0_REG
{
    Uint32 all;
    struct DCCCNT0_BITS bit;
};

struct DCCVALID0_BITS
{                       // bits description
    Uint32 VALID0 : 16; // 15:0 Current Value of Valid 0
    Uint32 rsvd1  : 16; // 31:16 Reserved
};

union DCCVALID0_REG
{
    Uint32 all;
    struct DCCVALID0_BITS bit;
};

struct DCCCNT1_BITS
{                       // bits description
    Uint32 COUNT1 : 20; // 19:0 Current Value of Counter 1
    Uint32 rsvd1  : 12; // 31:20 Reserved
};

union DCCCNT1_REG
{
    Uint32 all;
    struct DCCCNT1_BITS bit;
};

struct DCCCLKSRC1_BITS
{                        // bits description
    Uint32 CLKSRC1 : 4;  // 3:0 Clock Source Select for Counter 1
    Uint32 rsvd1   : 8;  // 11:4 Reserved
    Uint32 KEY     : 4;  // 15:12 Enables or Disables Clock Source Selection for COUNT1
    Uint32 rsvd2   : 16; // 31:16 Reserved
};

union DCCCLKSRC1_REG
{
    Uint32 all;
    struct DCCCLKSRC1_BITS bit;
};

struct DCCCLKSRC0_BITS
{                        // bits description
    Uint32 CLKSRC0 : 4;  // 3:0 Clock Source Select for Counter 0
    Uint32 rsvd1   : 12; // 15:4 Reserved
    Uint32 rsvd2   : 16; // 31:16 Reserved
};

union DCCCLKSRC0_REG
{
    Uint32 all;
    struct DCCCLKSRC0_BITS bit;
};

struct DCC_REGS
{
    union DCCGCTRL_REG DCCGCTRL;           // Global Control Register
    union DCCREV_REG DCCREV;               // DCC Revision Register
    union DCCCNTSEED0_REG DCCCNTSEED0;     // Counter 0 Seed Value
    union DCCVALIDSEED0_REG DCCVALIDSEED0; // Valid 0 Seed Value
    union DCCCNTSEED1_REG DCCCNTSEED1;     // Counter 1 Seed Value
    union DCCSTATUS_REG DCCSTATUS;         // DCC Status
    union DCCCNT0_REG DCCCNT0;             // Counter 0 Value
    union DCCVALID0_REG DCCVALID0;         // Valid Value 0
    union DCCCNT1_REG DCCCNT1;             // Counter 1 Value
    union DCCCLKSRC1_REG DCCCLKSRC1;       // Clock Source 1
    union DCCCLKSRC0_REG DCCCLKSRC0;       // Clock Source 0
};

extern volatile struct DCC_REGS Dcc0Regs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
