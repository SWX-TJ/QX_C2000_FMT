#ifndef Q28004X_EQEP_H
#define Q28004X_EQEP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_types.h"

//---------------------------------------------------------------------------
// EQEP Individual Register Bit Definitions:

struct QDECCTL_BITS
{                     // bits description
    Uint16 rsvd1 : 5; // 4:0 Reserved
    Uint16 QSP   : 1; // 5 QEPS input polarity
    Uint16 QIP   : 1; // 6 QEPI input polarity
    Uint16 QBP   : 1; // 7 QEPB input polarity
    Uint16 QAP   : 1; // 8 QEPA input polarity
    Uint16 IGATE : 1; // 9 Index pulse gating option
    Uint16 SWAP  : 1; // 10 CLK/DIR Signal Source for Position Counter
    Uint16 XCR   : 1; // 11 External Clock Rate
    Uint16 SPSEL : 1; // 12 Sync output pin selection
    Uint16 SOEN  : 1; // 13 Sync output-enable
    Uint16 QSRC  : 2; // 15:14 Position-counter source selection
};

union QDECCTL_REG
{
    Uint16 all;
    struct QDECCTL_BITS bit;
};

struct QEPCTL_BITS
{                         // bits description
    Uint16 WDE       : 1; // 0 QEP watchdog enable
    Uint16 UTE       : 1; // 1 QEP unit timer enable
    Uint16 QCLM      : 1; // 2 QEP capture latch mode
    Uint16 QPEN      : 1; // 3 Quadrature postotion counter enable
    Uint16 IEL       : 2; // 5:4 Index event latch
    Uint16 SEL       : 1; // 6 Strobe event latch
    Uint16 SWI       : 1; // 7 Software init position counter
    Uint16 IEI       : 2; // 9:8 Index event init of position count
    Uint16 SEI       : 2; // 11:10 Strobe event init
    Uint16 PCRM      : 2; // 13:12 Postion counter reset
    Uint16 FREE_SOFT : 2; // 15:14 Emulation mode
};

union QEPCTL_REG
{
    Uint16 all;
    struct QEPCTL_BITS bit;
};

struct QCAPCTL_BITS
{                     // bits description
    Uint16 UPPS  : 4; // 3:0 Unit position event prescaler
    Uint16 CCPS  : 3; // 6:4 eQEP capture timer clock prescaler
    Uint16 rsvd1 : 8; // 14:7 Reserved
    Uint16 CEN   : 1; // 15 Enable eQEP capture
};

union QCAPCTL_REG
{
    Uint16 all;
    struct QCAPCTL_BITS bit;
};

struct QPOSCTL_BITS
{                       // bits description
    Uint16 PCSPW  : 12; // 11:0 Position compare sync pulse width
    Uint16 PCE    : 1;  // 12 Position compare enable/disable
    Uint16 PCPOL  : 1;  // 13 Polarity of sync output
    Uint16 PCLOAD : 1;  // 14 Position compare of shadow load
    Uint16 PCSHDW : 1;  // 15 Position compare of shadow enable
};

union QPOSCTL_REG
{
    Uint16 all;
    struct QPOSCTL_BITS bit;
};

struct QEINT_BITS
{                     // bits description
    Uint16 rsvd1 : 1; // 0 Reserved
    Uint16 PCE   : 1; // 1 Position counter error interrupt enable
    Uint16 QPE   : 1; // 2 Quadrature phase error interrupt enable
    Uint16 QDC   : 1; // 3 Quadrature direction change interrupt enable
    Uint16 WTO   : 1; // 4 Watchdog time out interrupt enable
    Uint16 PCU   : 1; // 5 Position counter underflow interrupt enable
    Uint16 PCO   : 1; // 6 Position counter overflow interrupt enable
    Uint16 PCR   : 1; // 7 Position-compare ready interrupt enable
    Uint16 PCM   : 1; // 8 Position-compare match interrupt enable
    Uint16 SEL   : 1; // 9 Strobe event latch interrupt enable
    Uint16 IEL   : 1; // 10 Index event latch interrupt enable
    Uint16 UTO   : 1; // 11 Unit time out interrupt enable
    Uint16 QMAE  : 1; // 12 QMA error interrupt enable
    Uint16 rsvd2 : 3; // 15:13 Reserved
};

union QEINT_REG
{
    Uint16 all;
    struct QEINT_BITS bit;
};

struct QFLG_BITS
{                     // bits description
    Uint16 INT   : 1; // 0 Global interrupt status flag
    Uint16 PCE   : 1; // 1 Position counter error interrupt flag
    Uint16 PHE   : 1; // 2 Quadrature phase error interrupt flag
    Uint16 QDC   : 1; // 3 Quadrature direction change interrupt flag
    Uint16 WTO   : 1; // 4 Watchdog timeout interrupt flag
    Uint16 PCU   : 1; // 5 Position counter underflow interrupt flag
    Uint16 PCO   : 1; // 6 Position counter overflow interrupt flag
    Uint16 PCR   : 1; // 7 Position-compare ready interrupt flag
    Uint16 PCM   : 1; // 8 eQEP compare match event interrupt flag
    Uint16 SEL   : 1; // 9 Strobe event latch interrupt flag
    Uint16 IEL   : 1; // 10 Index event latch interrupt flag
    Uint16 UTO   : 1; // 11 Unit time out interrupt flag
    Uint16 QMAE  : 1; // 12 QMA error interrupt flag
    Uint16 rsvd1 : 3; // 15:13 Reserved
};

union QFLG_REG
{
    Uint16 all;
    struct QFLG_BITS bit;
};

struct QCLR_BITS
{                     // bits description
    Uint16 INT   : 1; // 0 Global interrupt clear flag
    Uint16 PCE   : 1; // 1 Clear position counter error interrupt flag
    Uint16 PHE   : 1; // 2 Clear quadrature phase error interrupt flag
    Uint16 QDC   : 1; // 3 Clear quadrature direction change interrupt flag
    Uint16 WTO   : 1; // 4 Clear watchdog timeout interrupt flag
    Uint16 PCU   : 1; // 5 Clear position counter underflow interrupt flag
    Uint16 PCO   : 1; // 6 Clear position counter overflow interrupt flag
    Uint16 PCR   : 1; // 7 Clear position-compare ready interrupt flag
    Uint16 PCM   : 1; // 8 Clear eQEP compare match event interrupt flag
    Uint16 SEL   : 1; // 9 Clear strobe event latch interrupt flag
    Uint16 IEL   : 1; // 10 Clear index event latch interrupt flag
    Uint16 UTO   : 1; // 11 Clear unit time out interrupt flag
    Uint16 QMAE  : 1; // 12 Clear QMA error interrupt flag
    Uint16 rsvd1 : 3; // 15:13 Reserved
};

union QCLR_REG
{
    Uint16 all;
    struct QCLR_BITS bit;
};

struct QFRC_BITS
{                     // bits description
    Uint16 rsvd1 : 1; // 0 Reserved
    Uint16 PCE   : 1; // 1 Force position counter error interrupt
    Uint16 PHE   : 1; // 2 Force quadrature phase error interrupt
    Uint16 QDC   : 1; // 3 Force quadrature direction change interrupt
    Uint16 WTO   : 1; // 4 Force watchdog time out interrupt
    Uint16 PCU   : 1; // 5 Force position counter underflow interrupt
    Uint16 PCO   : 1; // 6 Force position counter overflow interrupt
    Uint16 PCR   : 1; // 7 Force position-compare ready interrupt
    Uint16 PCM   : 1; // 8 Force position-compare match interrupt
    Uint16 SEL   : 1; // 9 Force strobe event latch interrupt
    Uint16 IEL   : 1; // 10 Force index event latch interrupt
    Uint16 UTO   : 1; // 11 Force unit time out interrupt
    Uint16 QMAE  : 1; // 12 Force QMA error interrupt
    Uint16 rsvd2 : 3; // 15:13 Reserved
};

union QFRC_REG
{
    Uint16 all;
    struct QFRC_BITS bit;
};

struct QEPSTS_BITS
{                      // bits description
    Uint16 PCEF   : 1; // 0 Position counter error flag.
    Uint16 FIMF   : 1; // 1 First index marker flag
    Uint16 CDEF   : 1; // 2 Capture direction error flag
    Uint16 COEF   : 1; // 3 Capture overflow error flag
    Uint16 QDLF   : 1; // 4 eQEP direction latch flag
    Uint16 QDF    : 1; // 5 Quadrature direction flag
    Uint16 FIDF   : 1; // 6 The first index marker
    Uint16 UPEVNT : 1; // 7 Unit position event flag
    Uint16 rsvd1  : 8; // 15:8 Reserved
};

union QEPSTS_REG
{
    Uint16 all;
    struct QEPSTS_BITS bit;
};

struct REV_BITS
{                      // bits description
    Uint16 MAJOR : 3;  // 2:0 Major Revision Number
    Uint16 MINOR : 3;  // 5:3 Minor Revision Number
    Uint16 rsvd1 : 10; // 15:6 Reserved
    Uint16 rsvd2 : 16; // 31:16 Reserved
};

union REV_REG
{
    Uint32 all;
    struct REV_BITS bit;
};

struct QEPSTROBESEL_BITS
{                          // bits description
    Uint16 STROBESEL : 2;  // 1:0 QMA Mode Select
    Uint16 rsvd1     : 14; // 15:2 Reserved
    Uint16 rsvd2     : 16; // 31:16 Reserved
};

union QEPSTROBESEL_REG
{
    Uint32 all;
    struct QEPSTROBESEL_BITS bit;
};

struct QMACTRL_BITS
{                      // bits description
    Uint16 MODE  : 3;  // 2:0 QMA Mode Select
    Uint16 rsvd1 : 13; // 15:3 Reserved
    Uint16 rsvd2 : 16; // 31:16 Reserved
};

union QMACTRL_REG
{
    Uint32 all;
    struct QMACTRL_BITS bit;
};

struct EQEP_REGS
{
    Uint32 QPOSCNT;                      // Position Counter, offset: 0x00
    Uint32 QPOSINIT;                     // Position Counter Init, offset: 0x04
    Uint32 QPOSMAX;                      // Maximum Position Count, offset: 0x08
    Uint32 QPOSCMP;                      // Position Compare, offset: 0x0C
    Uint32 QPOSILAT;                     // Index Position Latch, offset: 0x10
    Uint32 QPOSSLAT;                     // Strobe Position Latch, offset: 0x14
    Uint32 QPOSLAT;                      // Position Latch, offset: 0x18
    Uint32 QUTMR;                        // QEP Unit Timer, offset: 0x1C
    Uint32 QUPRD;                        // QEP Unit Period, offset: 0x20
    Uint16 QWDTMR;                       // QEP Watchdog Timer, offset: 0x24
    Uint16 QWDPRD;                       // QEP Watchdog Period, offset: 0x26
    union QDECCTL_REG QDECCTL;           // Quadrature Decoder Control, offset: 0x28
    union QEPCTL_REG QEPCTL;             // QEP Control, offset: 0x2A
    union QCAPCTL_REG QCAPCTL;           // Qaudrature Capture Control, offset: 0x2C
    union QPOSCTL_REG QPOSCTL;           // Position Compare Control, offset: 0x2E
    union QEINT_REG QEINT;               // QEP Interrupt Control, offset: 0x30
    union QFLG_REG QFLG;                 // QEP Interrupt Flag, offset: 0x32
    union QCLR_REG QCLR;                 // QEP Interrupt Clear, offset: 0x34
    union QFRC_REG QFRC;                 // QEP Interrupt Force, offset: 0x36
    union QEPSTS_REG QEPSTS;             // QEP Status, offset: 0x38
    Uint16 QCTMR;                        // QEP Capture Timer, offset: 0x3A
    Uint16 QCPRD;                        // QEP Capture Period, offset: 0x3C
    Uint16 QCTMRLAT;                     // QEP Capture Latch, offset: 0x3E
    Uint16 QCPRDLAT;                     // QEP Capture Period Latch, offset: 0x40
    Uint16 rsvd1[15];                    // Reserved, offset: 0x40~0x5C
    union REV_REG REV;                   // QEP Revision Number, offset: 0x60
    union QEPSTROBESEL_REG QEPSTROBESEL; // QEP Strobe select register, offset: 0x64
    union QMACTRL_REG QMACTRL;           // QMA Control register, offset: 0x68
};

extern volatile struct EQEP_REGS EQep1Regs;
extern volatile struct EQEP_REGS EQep2Regs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
