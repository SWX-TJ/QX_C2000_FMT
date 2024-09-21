#ifndef Q28004X_ASYSCTL_H
#define Q28004X_ASYSCTL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_types.h"

//---------------------------------------------------------------------------
// ANALOG SUBSYSTEM Register Bit Definitions:

struct ANAREFPP_BITS
{
    Uint32 ANAREFBDIS : 1; // 0 Disable ANAREFB
    Uint32 ANAREFCDIS : 1; // 1 Disable ANAREFC
};

union ANAREFPP_REG
{
    Uint32 all;
    struct ANAREFPP_BITS bit;
};

struct TSNSCTL_BITS
{
    Uint32 ENABLE : 1; // 0 Temperature Sensor Enable
};

union TSNSCTL_REG
{
    Uint32 all;
    struct TSNSCTL_BITS bit;
};

struct ANAREFCTL_BITS
{
    Uint32 rsvd1          : 1; // 0 Reserved (EN_VR_EX)
    Uint32 EN_HIZ_A       : 1; // 1 Control signal for enabling high-impedance state when built-in reference is disabled
    Uint32 EN_HIZ_BC      : 1; // 2 Control signal for enabling high-impedance state when built-in reference is disabled
    Uint32 EN_VREFBI_A    : 1; // 3 built-in reference voltage A enable signal
    Uint32 EN_VREFBI_BC   : 1; // 4 built-in reference voltage A enable signal
    Uint32 SEL_VREFBIBI_A : 2; // 6:5 built-in reference A output voltage selected signal
    Uint32 SEL_VREFBIBI_BC : 2; // 8:7 built-in reference B output voltage selected signal
};

union ANAREFCTL_REG
{
    Uint32 all;
    struct ANAREFCTL_BITS bit;
};

struct VMONCTL_BITS
{
    Uint32 rsvd1       : 3; // 2:0 Reserved (ADJ_PVD)
    Uint32 rsvd2       : 5; // 7:3 Reserved
    Uint32 BORLVMONEN  : 1; // 8 Enable BORL on VDDIO
};

union VMONCTL_REG
{
    Uint32 all;
    struct VMONCTL_BITS bit;
};

struct DCDCCTL_BITS
{
    Uint32 DCDCEN   : 1; // 0 enable DC-DC
    Uint32 rsvd1    : 2; // 2:1 work mode
    Uint32 rsvd2    : 2; // 4:3 offset detail
    Uint32 rsvd3    : 2; // 6:5 Current adjust detail
    Uint32 rsvd4    : 2; // 8:7 Ripple adjust detail
    Uint32 rsvd5    : 4; // 12:9 frequency adjust
    Uint32 rsvd6    : 1; // 13 operation mode
    Uint32 MD_LXDET : 2; // 15:14 LX Detect
};

union DCDCCTL_REG
{
    Uint32 all;
    struct DCDCCTL_BITS bit;
};

struct DCDCSTS_BITS
{
    Uint32 INDDETECT : 1; // 0 Detect the status of the inductor
    Uint32 SWSEQDONE : 1; // 1 DC-DC switch sequence has been completed
};

union DCDCSTS_REG
{
    Uint32 all;
    struct DCDCSTS_BITS bit;
};

struct CMPHPMXSEL_BITS
{
    Uint32 CMP1HPMXSEL : 3; // 2:0 CMP-1HPMXSEL bits
    Uint32 CMP2HPMXSEL : 3; // 5:3 CMP-1HPMXSEL bits
    Uint32 CMP3HPMXSEL : 3; // 8:6 CMP-1HPMXSEL bits
    Uint32 CMP4HPMXSEL : 3; // 11:9 CMP-1HPMXSEL bits
    Uint32 CMP5HPMXSEL : 3; // 14:12 CMP-1HPMXSEL bits
    Uint32 rsvd1       : 1; // 15 Reserved
    Uint32 CMP6HPMXSEL : 3; // 18:16 CMP-1HPMXSEL bits
    Uint32 CMP7HPMXSEL : 3; // 21:19 CMP-1HPMXSEL bits
};

union CMPHPMXSEL_REG
{
    Uint32 all;
    struct CMPHPMXSEL_BITS bit;
};

struct CMPLPMXSEL_BITS
{
    Uint32 CMP1LPMXSEL : 3; // 2:0 CMP-1LPMXSEL bits
    Uint32 CMP2LPMXSEL : 3; // 5:3 CMP-2LPMXSEL bits
    Uint32 CMP3LPMXSEL : 3; // 8:6 CMP-3LPMXSEL bits
    Uint32 CMP4LPMXSEL : 3; // 11:9 CMP-4LPMXSEL bits
    Uint32 CMP5LPMXSEL : 3; // 14:12 CMP-5LPMXSEL bits
    Uint32 rsvd1       : 1; // 15 Reserved
    Uint32 CMP6LPMXSEL : 3; // 18:16 CMP-6LPMXSEL bits
    Uint32 CMP7LPMXSEL : 3; // 21:19 CMP-7LPMXSEL bits
};

union CMPLPMXSEL_REG
{
    Uint32 all;
    struct CMPLPMXSEL_BITS bit;
};

struct CMPHNMXSEL_BITS
{
    Uint32 CMP1HNMXSEL : 2; // 1:0 CMP-1HNMXSEL bit
    Uint32 CMP2HNMXSEL : 2; // 3:2 CMP-2HNMXSEL bit
    Uint32 CMP3HNMXSEL : 2; // 5:4 CMP-3HNMXSEL bit
    Uint32 CMP4HNMXSEL : 2; // 7:6 CMP-4HNMXSEL bit
    Uint32 CMP5HNMXSEL : 2; // 9:8 CMP-5HNMXSEL bit
    Uint32 CMP6HNMXSEL : 2; // 11:10 CMP-6HNMXSEL bit
    Uint32 CMP7HNMXSEL : 2; // 13:12 CMP-7HNMXSEL bit
};

union CMPHNMXSEL_REG
{
    Uint32 all;
    struct CMPHNMXSEL_BITS bit;
};

struct CMPLNMXSEL_BITS
{
    Uint32 CMP1LNMXSEL : 2; // 1:0  CMP-1LNMXSEL bit
    Uint32 CMP2LNMXSEL : 2; // 3:2  CMP-2LNMXSEL bit
    Uint32 CMP3LNMXSEL : 2; // 5:4  CMP-3LNMXSEL bit
    Uint32 CMP4LNMXSEL : 2; // 7:6  CMP-4LNMXSEL bit
    Uint32 CMP5LNMXSEL : 2; // 9:8  CMP-5LNMXSEL bit
    Uint32 CMP6LNMXSEL : 2; // 11:10 CMP-6LNMXSEL bit
    Uint32 CMP7LNMXSEL : 2; // 13:12 CMP-7LNMXSEL bit
};

union CMPLNMXSEL_REG
{
    Uint32 all;
    struct CMPLNMXSEL_BITS bit;
};

struct ADCDACLOOPBACK_BITS
{
    Uint32 ENLB2ADCA : 1;  // 0 Enable DACA loopback to ADCA
    Uint32 ENLB2ADCB : 1;  // 1 Enable DACA loopback to ADCB
    Uint32 ENLB2ADCC : 1;  // 2 Enable DACA loopback to ADCC
    Uint32 rsvd      : 13; // 15:3 Reserved
    Uint32 KEY       : 16; // 31:16 Key to enable writes
};

union ADCDACLOOPBACK_REG
{
    Uint32 all;
    struct ADCDACLOOPBACK_BITS bit;
};

struct ANALOG_SUBSYS_REGS
{
    union ANAREFPP_REG ANAREFPP;             // ADC Analog Reference Peripheral Properties register.
    union TSNSCTL_REG TSNSCTL;               // Temperature Sensor Control Register
    union ANAREFCTL_REG ANAREFCTL;           // Analog Reference Control Register
    union VMONCTL_REG VMONCTL;               // Voltage Monitor Control Register
    union DCDCCTL_REG DCDCCTL;               // DC-DC control register.
    union DCDCSTS_REG DCDCSTS;               // DC-DC status register.
    union CMPHPMXSEL_REG CMPHPMXSEL;         // Bits to select one of the many sources on CopmHP inputs.
    union CMPLPMXSEL_REG CMPLPMXSEL;         // Bits to select one of the many sources on CopmLP inputs.
    union CMPHNMXSEL_REG CMPHNMXSEL;         // Bits to select one of the many sources on CopmHN inputs.
    union CMPLNMXSEL_REG CMPLNMXSEL;         // Bits to select one of the many sources on CopmLN inputs.
    union ADCDACLOOPBACK_REG ADCDACLOOPBACK; // Enabble loopback from DAC to ADCs
    Uint32 rsvd;                             // rsvd for TEMP_VOUT_SEL
};

extern volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
