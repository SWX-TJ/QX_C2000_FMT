#ifndef Q28004X_XBAR_H
#define Q28004X_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_types.h"

//---------------------------------------------------------------------------
// INPUT_XBAR Individual Register Bit Definitions:

struct INPUTSELECTLOCK_BITS
{                              // bits description
    Uint32 INPUT1SELECT  : 1;  // 0 Lock bit for INPUT1SELECT Register
    Uint32 INPUT2SELECT  : 1;  // 1 Lock bit for INPUT2SELECT Register
    Uint32 INPUT3SELECT  : 1;  // 2 Lock bit for INPUT3SELECT Register
    Uint32 INPUT4SELECT  : 1;  // 3 Lock bit for INPUT4SELECT Register
    Uint32 INPUT5SELECT  : 1;  // 4 Lock bit for INPUT5SELECT Register
    Uint32 INPUT6SELECT  : 1;  // 5 Lock bit for INPUT6SELECT Register
    Uint32 INPUT7SELECT  : 1;  // 6 Lock bit for INPUT7SELECT Register
    Uint32 INPUT8SELECT  : 1;  // 7 Lock bit for INPUT8SELECT Register
    Uint32 INPUT9SELECT  : 1;  // 8 Lock bit for INPUT9SELECT Register
    Uint32 INPUT10SELECT : 1;  // 9 Lock bit for INPUT10SELECT Register
    Uint32 INPUT11SELECT : 1;  // 10 Lock bit for INPUT11SELECT Register
    Uint32 INPUT12SELECT : 1;  // 11 Lock bit for INPUT12SELECT Register
    Uint32 INPUT13SELECT : 1;  // 12 Lock bit for INPUT13SELECT Register
    Uint32 INPUT14SELECT : 1;  // 13 Lock bit for INPUT14SELECT Register
    Uint32 INPUT15SELECT : 1;  // 14 Lock bit for INPUT15SELECT Register
    Uint32 INPUT16SELECT : 1;  // 15 Lock bit for INPUT16SELECT Register
    Uint32 rsvd1         : 16; // 31:16 Reserved
};

union INPUTSELECTLOCK_REG
{
    Uint32 all;
    struct INPUTSELECTLOCK_BITS bit;
};

struct INPUT_XBAR_REGS
{
    Uint32 INPUT1SELECT;                       // INPUT1 Input Select Register (GPIO0 to x)
    Uint32 INPUT2SELECT;                       // INPUT2 Input Select Register (GPIO0 to x)
    Uint32 INPUT3SELECT;                       // INPUT3 Input Select Register (GPIO0 to x)
    Uint32 INPUT4SELECT;                       // INPUT4 Input Select Register (GPIO0 to x)
    Uint32 INPUT5SELECT;                       // INPUT5 Input Select Register (GPIO0 to x)
    Uint32 INPUT6SELECT;                       // INPUT6 Input Select Register (GPIO0 to x)
    Uint32 INPUT7SELECT;                       // INPUT7 Input Select Register (GPIO0 to x)
    Uint32 INPUT8SELECT;                       // INPUT8 Input Select Register (GPIO0 to x)
    Uint32 INPUT9SELECT;                       // INPUT9 Input Select Register (GPIO0 to x)
    Uint32 INPUT10SELECT;                      // INPUT10 Input Select Register (GPIO0 to x)
    Uint32 INPUT11SELECT;                      // INPUT11 Input Select Register (GPIO0 to x)
    Uint32 INPUT12SELECT;                      // INPUT12 Input Select Register (GPIO0 to x)
    Uint32 INPUT13SELECT;                      // INPUT13 Input Select Register (GPIO0 to x)
    Uint32 INPUT14SELECT;                      // INPUT14 Input Select Register (GPIO0 to x)
    Uint32 INPUT15SELECT;                      // INPUT15 Input Select Register (GPIO0 to x)
    Uint32 INPUT16SELECT;                      // INPUT16 Input Select Register (GPIO0 to x)
    Uint32 rsvd1[16];                          // Reserved
    union INPUTSELECTLOCK_REG INPUTSELECTLOCK; // Input Select Lock Register, offset: 0x80
};

//---------------------------------------------------------------------------
// OUTPUT_XBAR Individual Register Bit Definitions:

struct OUTPUTxMUX0TO15CFG_BITS
{                     // bits description
    Uint32 MUX0  : 2; // 1:0 Mux0 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX1  : 2; // 3:2 Mux1 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX2  : 2; // 5:4 Mux2 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX3  : 2; // 7:6 Mux3 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX4  : 2; // 9:8 Mux4 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX5  : 2; // 11:10 Mux5 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX6  : 2; // 13:12 Mux6 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX7  : 2; // 15:14 Mux7 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX8  : 2; // 17:16 Mux8 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX9  : 2; // 19:18 Mux9 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX10 : 2; // 21:20 Mux10 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX11 : 2; // 23:22 Mux11 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX12 : 2; // 25:24 Mux12 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX13 : 2; // 27:26 Mux13 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX14 : 2; // 29:28 Mux14 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX15 : 2; // 31:30 Mux15 Configuration for OUTPUT1 of OUTPUT-XBAR
};

union OUTPUTxMUX0TO15CFG_REG
{
    Uint32 all;
    struct OUTPUTxMUX0TO15CFG_BITS bit;
};

struct OUTPUTxMUX16TO31CFG_BITS
{                     // bits description
    Uint32 MUX16 : 2; // 1:0 Mux16 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX17 : 2; // 3:2 Mux17 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX18 : 2; // 5:4 Mux18 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX19 : 2; // 7:6 Mux19 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX20 : 2; // 9:8 Mux20 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX21 : 2; // 11:10 Mux21 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX22 : 2; // 13:12 Mux22 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX23 : 2; // 15:14 Mux23 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX24 : 2; // 17:16 Mux24 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX25 : 2; // 19:18 Mux25 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX26 : 2; // 21:20 Mux26 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX27 : 2; // 23:22 Mux27 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX28 : 2; // 25:24 Mux28 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX29 : 2; // 27:26 Mux29 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX30 : 2; // 29:28 Mux30 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX31 : 2; // 31:30 Mux31 Configuration for OUTPUT1 of OUTPUT-XBAR
};

union OUTPUTxMUX16TO31CFG_REG
{
    Uint32 all;
    struct OUTPUTxMUX16TO31CFG_BITS bit;
};

struct OUTPUTxMUXENABLE_BITS
{                     // bits description
    Uint32 MUX0  : 1; // 0 Mux0 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX1  : 1; // 1 Mux1 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX2  : 1; // 2 Mux2 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX3  : 1; // 3 Mux3 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX4  : 1; // 4 Mux4 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX5  : 1; // 5 Mux5 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX6  : 1; // 6 Mux6 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX7  : 1; // 7 Mux7 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX8  : 1; // 8 Mux8 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX9  : 1; // 9 Mux9 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX10 : 1; // 10 Mux10 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX11 : 1; // 11 Mux11 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX12 : 1; // 12 Mux12 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX13 : 1; // 13 Mux13 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX14 : 1; // 14 Mux14 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX15 : 1; // 15 Mux15 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX16 : 1; // 16 Mux16 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX17 : 1; // 17 Mux17 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX18 : 1; // 18 Mux18 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX19 : 1; // 19 Mux19 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX20 : 1; // 20 Mux20 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX21 : 1; // 21 Mux21 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX22 : 1; // 22 Mux22 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX23 : 1; // 23 Mux23 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX24 : 1; // 24 Mux24 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX25 : 1; // 25 Mux25 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX26 : 1; // 26 Mux26 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX27 : 1; // 27 Mux27 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX28 : 1; // 28 Mux28 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX29 : 1; // 29 Mux29 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX30 : 1; // 30 Mux30 to drive OUTPUT1 of OUTPUT-XBAR
    Uint32 MUX31 : 1; // 31 Mux31 to drive OUTPUT1 of OUTPUT-XBAR
};

union OUTPUTxMUXENABLE_REG
{
    Uint32 all;
    struct OUTPUTxMUXENABLE_BITS bit;
};

struct OUTPUTLATCH_BITS
{                        // bits description
    Uint32 OUTPUT1 : 1;  // 0 Records the OUTPUT1 of OUTPUT-XBAR
    Uint32 OUTPUT2 : 1;  // 1 Records the OUTPUT2 of OUTPUT-XBAR
    Uint32 OUTPUT3 : 1;  // 2 Records the OUTPUT3 of OUTPUT-XBAR
    Uint32 OUTPUT4 : 1;  // 3 Records the OUTPUT4 of OUTPUT-XBAR
    Uint32 OUTPUT5 : 1;  // 4 Records the OUTPUT5 of OUTPUT-XBAR
    Uint32 OUTPUT6 : 1;  // 5 Records the OUTPUT6 of OUTPUT-XBAR
    Uint32 OUTPUT7 : 1;  // 6 Records the OUTPUT7 of OUTPUT-XBAR
    Uint32 OUTPUT8 : 1;  // 7 Records the OUTPUT8 of OUTPUT-XBAR
    Uint32 rsvd1   : 8;  // 15:8 Reserved
    Uint32 rsvd2   : 16; // 31:16 Reserved
};

union OUTPUTLATCH_REG
{
    Uint32 all;
    struct OUTPUTLATCH_BITS bit;
};

struct OUTPUTINV_BITS
{                        // bits description
    Uint32 OUTPUT1 : 1;  // 0 Selects polarity for OUTPUT1 of OUTPUT-XBAR
    Uint32 OUTPUT2 : 1;  // 1 Selects polarity for OUTPUT2 of OUTPUT-XBAR
    Uint32 OUTPUT3 : 1;  // 2 Selects polarity for OUTPUT3 of OUTPUT-XBAR
    Uint32 OUTPUT4 : 1;  // 3 Selects polarity for OUTPUT4 of OUTPUT-XBAR
    Uint32 OUTPUT5 : 1;  // 4 Selects polarity for OUTPUT5 of OUTPUT-XBAR
    Uint32 OUTPUT6 : 1;  // 5 Selects polarity for OUTPUT6 of OUTPUT-XBAR
    Uint32 OUTPUT7 : 1;  // 6 Selects polarity for OUTPUT7 of OUTPUT-XBAR
    Uint32 OUTPUT8 : 1;  // 7 Selects polarity for OUTPUT8 of OUTPUT-XBAR
    Uint32 rsvd1   : 8;  // 15:8 Reserved
    Uint32 rsvd2   : 16; // 31:16 Reserved
};

union OUTPUTINV_REG
{
    Uint32 all;
    struct OUTPUTINV_BITS bit;
};

struct OUTPUTLOCK_BITS
{                      // bits description
    Uint32 LOCK  : 1;  // 0 Locks the configuration for OUTPUT-XBAR
    Uint32 rsvd1 : 15; // 15:1 Reserved
    Uint32 KEY   : 16; // 31:16 Write Protection KEY
};

union OUTPUTLOCK_REG
{
    Uint32 all;
    struct OUTPUTLOCK_BITS bit;
};

struct OUTPUT_XBAR_REGS
{
    union OUTPUTxMUX0TO15CFG_REG OUTPUT1MUX0TO15CFG;   // Output X-BAR Mux for Output 1
    union OUTPUTxMUX16TO31CFG_REG OUTPUT1MUX16TO31CFG; // Output X-BAR Mux for Output 1
    union OUTPUTxMUX0TO15CFG_REG OUTPUT2MUX0TO15CFG;   // Output X-BAR Mux for Output 2
    union OUTPUTxMUX16TO31CFG_REG OUTPUT2MUX16TO31CFG; // Output X-BAR Mux for Output 2
    union OUTPUTxMUX0TO15CFG_REG OUTPUT3MUX0TO15CFG;   // Output X-BAR Mux for Output 3
    union OUTPUTxMUX16TO31CFG_REG OUTPUT3MUX16TO31CFG; // Output X-BAR Mux for Output 3
    union OUTPUTxMUX0TO15CFG_REG OUTPUT4MUX0TO15CFG;   // Output X-BAR Mux for Output 4
    union OUTPUTxMUX16TO31CFG_REG OUTPUT4MUX16TO31CFG; // Output X-BAR Mux for Output 4
    union OUTPUTxMUX0TO15CFG_REG OUTPUT5MUX0TO15CFG;   // Output X-BAR Mux for Output 5
    union OUTPUTxMUX16TO31CFG_REG OUTPUT5MUX16TO31CFG; // Output X-BAR Mux for Output 5
    union OUTPUTxMUX0TO15CFG_REG OUTPUT6MUX0TO15CFG;   // Output X-BAR Mux for Output 6
    union OUTPUTxMUX16TO31CFG_REG OUTPUT6MUX16TO31CFG; // Output X-BAR Mux for Output 6
    union OUTPUTxMUX0TO15CFG_REG OUTPUT7MUX0TO15CFG;   // Output X-BAR Mux for Output 7
    union OUTPUTxMUX16TO31CFG_REG OUTPUT7MUX16TO31CFG; // Output X-BAR Mux for Output 7
    union OUTPUTxMUX0TO15CFG_REG OUTPUT8MUX0TO15CFG;   // Output X-BAR Mux for Output 8
    union OUTPUTxMUX16TO31CFG_REG OUTPUT8MUX16TO31CFG; // Output X-BAR Mux for Output 8
    union OUTPUTxMUXENABLE_REG OUTPUT1MUXENABLE;       // Output X-BAR Mux Enable  for Output 1
    union OUTPUTxMUXENABLE_REG OUTPUT2MUXENABLE;       // Output X-BAR Mux Enable  for Output 2
    union OUTPUTxMUXENABLE_REG OUTPUT3MUXENABLE;       // Output X-BAR Mux Enable  for Output 3
    union OUTPUTxMUXENABLE_REG OUTPUT4MUXENABLE;       // Output X-BAR Mux Enable  for Output 4
    union OUTPUTxMUXENABLE_REG OUTPUT5MUXENABLE;       // Output X-BAR Mux Enable  for Output 5
    union OUTPUTxMUXENABLE_REG OUTPUT6MUXENABLE;       // Output X-BAR Mux Enable  for Output 6
    union OUTPUTxMUXENABLE_REG OUTPUT7MUXENABLE;       // Output X-BAR Mux Enable  for Output 7
    union OUTPUTxMUXENABLE_REG OUTPUT8MUXENABLE;       // Output X-BAR Mux Enable  for Output 8
    union OUTPUTLATCH_REG OUTPUTLATCH;                 // Output X-BAR Output Latch
    union OUTPUTLATCH_REG OUTPUTLATCHCLR;              // Output X-BAR Output Latch Clear
    union OUTPUTLATCH_REG OUTPUTLATCHFRC;              // Output X-BAR Output Latch Force
    union OUTPUTLATCH_REG OUTPUTLATCHENABLE;           // Output X-BAR Output Latch Enable
    union OUTPUTINV_REG OUTPUTINV;                     // Output X-BAR Output Inversion
    Uint32 rsvd1[4];                                   // Reserved
    union OUTPUTLOCK_REG OUTPUTLOCK;                   // Output X-BAR Configuration Lock register
};

//---------------------------------------------------------------------------
// EPWM_XBAR Individual Register Bit Definitions:

struct TRIPxMUX0TO15CFG_BITS
{                     // bits description
    Uint32 MUX0  : 2; // 1:0 Mux0 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX1  : 2; // 3:2 Mux1 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX2  : 2; // 5:4 Mux2 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX3  : 2; // 7:6 Mux3 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX4  : 2; // 9:8 Mux4 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX5  : 2; // 11:10 Mux5 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX6  : 2; // 13:12 Mux6 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX7  : 2; // 15:14 Mux7 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX8  : 2; // 17:16 Mux8 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX9  : 2; // 19:18 Mux9 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX10 : 2; // 21:20 Mux10 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX11 : 2; // 23:22 Mux11 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX12 : 2; // 25:24 Mux12 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX13 : 2; // 27:26 Mux13 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX14 : 2; // 29:28 Mux14 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX15 : 2; // 31:30 Mux15 Configuration for TRIP4 of EPWM-XBAR
};

union TRIPxMUX0TO15CFG_REG
{
    Uint32 all;
    struct TRIPxMUX0TO15CFG_BITS bit;
};

struct TRIPxMUX16TO31CFG_BITS
{                     // bits description
    Uint32 MUX16 : 2; // 1:0 Mux16 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX17 : 2; // 3:2 Mux17 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX18 : 2; // 5:4 Mux18 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX19 : 2; // 7:6 Mux19 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX20 : 2; // 9:8 Mux20 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX21 : 2; // 11:10 Mux21 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX22 : 2; // 13:12 Mux22 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX23 : 2; // 15:14 Mux23 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX24 : 2; // 17:16 Mux24 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX25 : 2; // 19:18 Mux25 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX26 : 2; // 21:20 Mux26 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX27 : 2; // 23:22 Mux27 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX28 : 2; // 25:24 Mux28 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX29 : 2; // 27:26 Mux29 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX30 : 2; // 29:28 Mux30 Configuration for TRIP4 of EPWM-XBAR
    Uint32 MUX31 : 2; // 31:30 Mux31 Configuration for TRIP4 of EPWM-XBAR
};

union TRIPxMUX16TO31CFG_REG
{
    Uint32 all;
    struct TRIPxMUX16TO31CFG_BITS bit;
};

struct TRIPxMUXENABLE_BITS
{                     // bits description
    Uint32 MUX0  : 1; // 0 mux0 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX1  : 1; // 1 Mux1 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX2  : 1; // 2 Mux2 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX3  : 1; // 3 Mux3 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX4  : 1; // 4 Mux4 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX5  : 1; // 5 Mux5 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX6  : 1; // 6 Mux6 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX7  : 1; // 7 Mux7 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX8  : 1; // 8 Mux8 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX9  : 1; // 9 Mux9 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX10 : 1; // 10 Mux10 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX11 : 1; // 11 Mux11 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX12 : 1; // 12 Mux12 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX13 : 1; // 13 Mux13 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX14 : 1; // 14 Mux14 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX15 : 1; // 15 Mux15 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX16 : 1; // 16 Mux16 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX17 : 1; // 17 Mux17 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX18 : 1; // 18 Mux18 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX19 : 1; // 19 Mux19 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX20 : 1; // 20 Mux20 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX21 : 1; // 21 Mux21 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX22 : 1; // 22 Mux22 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX23 : 1; // 23 Mux23 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX24 : 1; // 24 Mux24 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX25 : 1; // 25 Mux25 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX26 : 1; // 26 Mux26 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX27 : 1; // 27 Mux27 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX28 : 1; // 28 Mux28 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX29 : 1; // 29 Mux29 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX30 : 1; // 30 Mux30 to drive TRIP4 of EPWM-XBAR
    Uint32 MUX31 : 1; // 31 Mux31 to drive TRIP4 of EPWM-XBAR
};

union TRIPxMUXENABLE_REG
{
    Uint32 all;
    struct TRIPxMUXENABLE_BITS bit;
};

struct TRIPOUTINV_BITS
{                       // bits description
    Uint32 TRIP4  : 1;  // 0 Selects polarity for TRIP4 of EPWM-XBAR
    Uint32 TRIP5  : 1;  // 1 Selects polarity for TRIP5 of EPWM-XBAR
    Uint32 TRIP7  : 1;  // 2 Selects polarity for TRIP7 of EPWM-XBAR
    Uint32 TRIP8  : 1;  // 3 Selects polarity for TRIP8 of EPWM-XBAR
    Uint32 TRIP9  : 1;  // 4 Selects polarity for TRIP9 of EPWM-XBAR
    Uint32 TRIP10 : 1;  // 5 Selects polarity for TRIP10 of EPWM-XBAR
    Uint32 TRIP11 : 1;  // 6 Selects polarity for TRIP11 of EPWM-XBAR
    Uint32 TRIP12 : 1;  // 7 Selects polarity for TRIP12 of EPWM-XBAR
    Uint32 rsvd1  : 8;  // 15:8 Reserved
    Uint32 rsvd2  : 16; // 31:16 Reserved
};

union TRIPOUTINV_REG
{
    Uint32 all;
    struct TRIPOUTINV_BITS bit;
};

struct TRIPLOCK_BITS
{                      // bits description
    Uint32 LOCK  : 1;  // 0 Locks the configuration for EPWM-XBAR
    Uint32 rsvd1 : 15; // 15:1 Reserved
    Uint32 KEY   : 16; // 31:16 Write protection KEY
};

union TRIPLOCK_REG
{
    Uint32 all;
    struct TRIPLOCK_BITS bit;
};

struct EPWM_XBAR_REGS
{
    union TRIPxMUX0TO15CFG_REG TRIP4MUX0TO15CFG;    // ePWM XBAR Mux Configuration for TRIP4 0x00
    union TRIPxMUX16TO31CFG_REG TRIP4MUX16TO31CFG;  // ePWM XBAR Mux Configuration for TRIP4 0x04
    union TRIPxMUX0TO15CFG_REG TRIP5MUX0TO15CFG;    // ePWM XBAR Mux Configuration for TRIP5 0x08
    union TRIPxMUX16TO31CFG_REG TRIP5MUX16TO31CFG;  // ePWM XBAR Mux Configuration for TRIP5 0x0c
    union TRIPxMUX0TO15CFG_REG TRIP7MUX0TO15CFG;    // ePWM XBAR Mux Configuration for TRIP7 0x10
    union TRIPxMUX16TO31CFG_REG TRIP7MUX16TO31CFG;  // ePWM XBAR Mux Configuration for TRIP7 0x14
    union TRIPxMUX0TO15CFG_REG TRIP8MUX0TO15CFG;    // ePWM XBAR Mux Configuration for TRIP8 0x18
    union TRIPxMUX16TO31CFG_REG TRIP8MUX16TO31CFG;  // ePWM XBAR Mux Configuration for TRIP8 0x1c
    union TRIPxMUX0TO15CFG_REG TRIP9MUX0TO15CFG;    // ePWM XBAR Mux Configuration for TRIP9 0x20
    union TRIPxMUX16TO31CFG_REG TRIP9MUX16TO31CFG;  // ePWM XBAR Mux Configuration for TRIP9 0x24
    union TRIPxMUX0TO15CFG_REG TRIP10MUX0TO15CFG;   // ePWM XBAR Mux Configuration for TRIP10 0x28
    union TRIPxMUX16TO31CFG_REG TRIP10MUX16TO31CFG; // ePWM XBAR Mux Configuration for TRIP10 0x2C
    union TRIPxMUX0TO15CFG_REG TRIP11MUX0TO15CFG;   // ePWM XBAR Mux Configuration for TRIP11 0x30
    union TRIPxMUX16TO31CFG_REG TRIP11MUX16TO31CFG; // ePWM XBAR Mux Configuration for TRIP11 0x34
    union TRIPxMUX0TO15CFG_REG TRIP12MUX0TO15CFG;   // ePWM XBAR Mux Configuration for TRIP12 0x38
    union TRIPxMUX16TO31CFG_REG TRIP12MUX16TO31CFG; // ePWM XBAR Mux Configuration for TRIP12 0x3c
    union TRIPxMUXENABLE_REG TRIP4MUXENABLE;        // ePWM XBAR Mux Enable for TRIP4
    union TRIPxMUXENABLE_REG TRIP5MUXENABLE;        // ePWM XBAR Mux Enable for TRIP5
    union TRIPxMUXENABLE_REG TRIP7MUXENABLE;        // ePWM XBAR Mux Enable for TRIP7
    union TRIPxMUXENABLE_REG TRIP8MUXENABLE;        // ePWM XBAR Mux Enable for TRIP8
    union TRIPxMUXENABLE_REG TRIP9MUXENABLE;        // ePWM XBAR Mux Enable for TRIP9
    union TRIPxMUXENABLE_REG TRIP10MUXENABLE;       // ePWM XBAR Mux Enable for TRIP10
    union TRIPxMUXENABLE_REG TRIP11MUXENABLE;       // ePWM XBAR Mux Enable for TRIP11
    union TRIPxMUXENABLE_REG TRIP12MUXENABLE;       // ePWM XBAR Mux Enable for TRIP12
    Uint32 rsvd1[8];                                // Reserved
    union TRIPOUTINV_REG TRIPOUTINV;                // ePWM XBAR Output Inversion Register
    Uint32 rsvd2[4];                                // Reserved
    union TRIPLOCK_REG TRIPLOCK;                    // ePWM XBAR Configuration Lock register
};

//---------------------------------------------------------------------------
// EPWM_XBAR External References & Function Declarations:
extern volatile struct EPWM_XBAR_REGS EPwmXbarRegs;

struct XBAR1_BITS
{                                // bits description
    Uint32 CMPSS1_CTRIPH    : 1; // 0 Input Flag for CMPSS1.CTRIPH Signal
    Uint32 CMPSS1_CTRIPL    : 1; // 1 Input Flag for CMPSS1.CTRIPL Signal
    Uint32 CMPSS1_CTRIPOUTH : 1; // 2 Input Flag for CMPSS1.CTRIPOUTH Signal
    Uint32 CMPSS1_CTRIPOUTL : 1; // 3 Input Flag for CMPSS1.CTRIPOUTL Signal
    Uint32 CMPSS2_CTRIPH    : 1; // 4 Input Flag for CMPSS2.CTRIPH Signal
    Uint32 CMPSS2_CTRIPL    : 1; // 5 Input Flag for CMPSS2.CTRIPL Signal
    Uint32 CMPSS2_CTRIPOUTH : 1; // 6 Input Flag for CMPSS2.CTRIPOUTH Signal
    Uint32 CMPSS2_CTRIPOUTL : 1; // 7 Input Flag for CMPSS2.CTRIPOUTL Signal
    Uint32 CMPSS3_CTRIPH    : 1; // 8 Input Flag for CMPSS3.CTRIPH Signal
    Uint32 CMPSS3_CTRIPL    : 1; // 9 Input Flag for CMPSS3.CTRIPL Signal
    Uint32 CMPSS3_CTRIPOUTH : 1; // 10 Input Flag for CMPSS3.CTRIPOUTH Signal
    Uint32 CMPSS3_CTRIPOUTL : 1; // 11 Input Flag for CMPSS3.CTRIPOUTL Signal
    Uint32 CMPSS4_CTRIPH    : 1; // 12 Input Flag for CMPSS4.CTRIPH Signal
    Uint32 CMPSS4_CTRIPL    : 1; // 13 Input Flag for CMPSS4.CTRIPL Signal
    Uint32 CMPSS4_CTRIPOUTH : 1; // 14 Input Flag for CMPSS4.CTRIPOUTH Signal
    Uint32 CMPSS4_CTRIPOUTL : 1; // 15 Input Flag for CMPSS4.CTRIPOUTL Signal
    Uint32 CMPSS5_CTRIPH    : 1; // 16 Input Flag for CMPSS5.CTRIPH Signal
    Uint32 CMPSS5_CTRIPL    : 1; // 17 Input Flag for CMPSS5.CTRIPL Signal
    Uint32 CMPSS5_CTRIPOUTH : 1; // 18 Input Flag for CMPSS5.CTRIPOUTH Signal
    Uint32 CMPSS5_CTRIPOUTL : 1; // 19 Input Flag for CMPSS5.CTRIPOUTL Signal
    Uint32 CMPSS6_CTRIPH    : 1; // 20 Input Flag for CMPSS6.CTRIPH Signal
    Uint32 CMPSS6_CTRIPL    : 1; // 21 Input Flag for CMPSS6.CTRIPL Signal
    Uint32 CMPSS6_CTRIPOUTH : 1; // 22 Input Flag for CMPSS6.CTRIPOUTH Signal
    Uint32 CMPSS6_CTRIPOUTL : 1; // 23 Input Flag for CMPSS6.CTRIPOUTL Signal
    Uint32 CMPSS7_CTRIPH    : 1; // 24 Input Flag for CMPSS7.CTRIPH Signal
    Uint32 CMPSS7_CTRIPL    : 1; // 25 Input Flag for CMPSS7.CTRIPL Signal
    Uint32 CMPSS7_CTRIPOUTH : 1; // 26 Input Flag for CMPSS7.CTRIPOUTH Signal
    Uint32 CMPSS7_CTRIPOUTL : 1; // 27 Input Flag for CMPSS7.CTRIPOUTL Signal
};

union XBAR1_REG
{
    Uint32 all;
    struct XBAR1_BITS bit;
};

struct XBAR2_BITS
{                          // bits description
    Uint32 INPUT1     : 1; // 0 Input Flag for INPUT1 Signal
    Uint32 INPUT2     : 1; // 1 Input Flag for INPUT2 Signal
    Uint32 INPUT3     : 1; // 2 Input Flag for INPUT3 Signal
    Uint32 INPUT4     : 1; // 3 Input Flag for INPUT4 Signal
    Uint32 INPUT5     : 1; // 4 Input Flag for INPUT5 Signal
    Uint32 INPUT6     : 1; // 5 Input Flag for INPUT6 Signal
    Uint32 ADCSOCA    : 1; // 6 Input Flag for ADCSOCA Signal
    Uint32 ADCSOCB    : 1; // 7 Input Flag for ADCSOCB Signal
    Uint32 INPUT7     : 1; // 8 Input Flag for INPUT7 Signal
    Uint32 INPUT8     : 1; // 9 Input Flag for INPUT8 Signal
    Uint32 INPUT9     : 1; // 10 Input Flag for INPUT9 Signal
    Uint32 INPUT10    : 1; // 11 Input Flag for INPUT10\ Signal
    Uint32 INPUT11    : 1; // 12 Input Flag for INPUT11 Signal
    Uint32 INPUT12    : 1; // 13 Input Flag for INPUT12 Signal
    Uint32 INPUT13    : 1; // 14 Input Flag for INPUT13 Signal
    Uint32 INPUT14    : 1; // 15 Input Flag for INPUT14 Signal
    Uint32 ECAP1_OUT  : 1; // 16 Input Flag for ECAP1.OUT Signal
    Uint32 ECAP2_OUT  : 1; // 17 Input Flag for ECAP2.OUT Signal
    Uint32 ECAP3_OUT  : 1; // 18 Input Flag for ECAP3.OUT Signal
    Uint32 ECAP4_OUT  : 1; // 19 Input Flag for ECAP4.OUT Signal
    Uint32 ECAP5_OUT  : 1; // 20 Input Flag for ECAP5.OUT Signal
    Uint32 ECAP6_OUT  : 1; // 21 Input Flag for ECAP6.OUT Signal
    Uint32 EXTSYNCOUT : 1; // 22 Input Flag for EXTSYNCOUT Signal
    Uint32 ECAP7_OUT  : 1; // 23 Input Flag for ECAP6.OUT Signal
    Uint32 ERRORSTS   : 1; // 24 Input Flag for ERRORSTS Signal
};

union XBAR2_REG
{
    Uint32 all;
    struct XBAR2_BITS bit;
};

struct XBAR3_BITS
{                               // bits description
    Uint32 ADCAEVT1        : 1; // 0 Input Flag for ADCAEVT1 Signal
    Uint32 ADCBEVT1        : 1; // 1 Input Flag for ADCBEVT1 Signal
    Uint32 ADCCEVT1        : 1; // 2 Input Flag for ADCCEVT1 Signal
    Uint32 ADCAEVT2        : 1; // 3 Input Flag for ADCAEVT2 Signal
    Uint32 ADCBEVT2        : 1; // 4 Input Flag for ADCBEVT2 Signal
    Uint32 ADCCEVT2        : 1; // 5 Input Flag for ADCCEVT2 Signal
    Uint32 ADCAEVT3        : 1; // 6 Input Flag for ADCAEVT3 Signal
    Uint32 ADCBEVT3        : 1; // 7 Input Flag for ADCBEVT3 Signal
    Uint32 ADCCEVT3        : 1; // 8 Input Flag for ADCCEVT3 Signal
    Uint32 ADCAEVT4        : 1; // 9 Input Flag for ADCAEVT4 Signal
    Uint32 ADCBEVT4        : 1; // 10 Input Flag for ADCBEVT4 Signal
    Uint32 ADCCEVT4        : 1; // 11 Input Flag for ADCCEVT4 Signal
    Uint32 SD1FLT1_COMPH   : 1; // 12 Input Flag for SD1FLT1.COMPH Signal
    Uint32 SD1FLT1_COMPL   : 1; // 13 Input Flag for SD1FLT1.COMPL Signal
    Uint32 SD1FLT1_COMPZ   : 1; // 14 Input Flag for SD1FLT1.COMPZ Signal
    Uint32 SD1FLT1_COMPH_L : 1; // 15 Input Flag for SD1FLT1.COMPH OR SD1FLT1.COMPL Signal
    Uint32 SD1FLT2_COMPH   : 1; // 16 Input Flag for SD1FLT2.COMPH Signal
    Uint32 SD1FLT2_COMPL   : 1; // 17 Input Flag for SD1FLT2.COMPL Signal
    Uint32 SD1FLT2_COMPZ   : 1; // 18 Input Flag for SD1FLT2.COMPZ Signal
    Uint32 SD1FLT2_COMPH_L : 1; // 19 Input Flag for SD1FLT2.COMPH OR SD1FLT1.COMPL Signal
    Uint32 SD1FLT3_COMPH   : 1; // 20 Input Flag for SD1FLT3.COMPH Signal
    Uint32 SD1FLT3_COMPL   : 1; // 21 Input Flag for SD1FLT3.COMPL Signal
    Uint32 SD1FLT3_COMPZ   : 1; // 22 Input Flag for SD1FLT3.COMPZ Signal
    Uint32 SD1FLT3_COMPH_L : 1; // 23 Input Flag for SD1FLT3.COMPH OR SD1FLT1.COMPL Signal
    Uint32 SD1FLT4_COMPH   : 1; // 24 Input Flag for SD1FLT4.COMPH Signal
    Uint32 SD1FLT4_COMPL   : 1; // 25 Input Flag for SD1FLT4.COMPL Signal
    Uint32 SD1FLT4_COMPZ   : 1; // 26 Input Flag for SD1FLT4.COMPZ Signal
    Uint32 SD1FLT4_COMPH_L : 1; // 27 Input Flag for SD1FLT4.COMPH OR SD1FLT1.COMPL Signal
    Uint32 SD1FLT1_DRINT   : 1; // 28 Input Flag for SD1FLT1.DRINT Signal
    Uint32 SD1FLT2_DRINT   : 1; // 29 Input Flag for SD1FLT2.DRINT Signal
    Uint32 SD1FLT3_DRINT   : 1; // 30 Input Flag for SD1FLT3.DRINT Signal
    Uint32 SD1FLT4_DRINT   : 1; // 31 Input Flag for SD1FLT4.DRINT Signal
};

union XBAR3_REG
{
    Uint32 all;
    struct XBAR3_BITS bit;
};

struct XBAR_REGS
{
    union XBAR2_REG XBARFLG2; // 0x00 X-Bar Input Flag Register 2
    union XBAR3_REG XBARFLG3; // 0x04 X-Bar Input Flag Register 3
    union XBAR1_REG XBARFLG1; // 0x08 X-Bar Input Flag Register 1
    union XBAR2_REG XBARCLR2; // 0x0C X-Bar Input Flag Clear Register 2
    union XBAR3_REG XBARCLR3; // 0x10 X-Bar Input Flag Clear Register 3
    union XBAR1_REG XBARCLR1; // 0x14 X-Bar Input Flag Clear Register 1
};

extern volatile struct OUTPUT_XBAR_REGS OutputXbarRegs;
extern volatile struct INPUT_XBAR_REGS InputXbarRegs;
extern volatile struct XBAR_REGS XbarRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
