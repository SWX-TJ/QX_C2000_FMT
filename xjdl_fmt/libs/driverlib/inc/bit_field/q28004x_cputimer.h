#ifndef Q28004X_CPUTIMER_H
#define Q28004X_CPUTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_types.h"

struct CTRL_BITS
{
    Uint32 ENABLE   : 1;  /* [0] */
    Uint32 MODE     : 1;  /* [1] */
    Uint32 INT_MASK : 1;  /* [2] */
    Uint32 PWM      : 1;  /* [3] */
    Uint32 rsvd     : 28; /* [31:4]*/
};

union CTRL_REG
{
    Uint32 all;
    struct CTRL_BITS bit;
};

struct CPUTIMER_REGS
{
    Uint32 LOADCOUNT;    /* offset: 0x00 */
    Uint32 CURRENTVALUE; /* offset: 0x04 */
    union CTRL_REG CTRL; /* offset: 0x08 */
    Uint32 EOI;          /* offset: 0x0C */
    Uint32 INT_STATUS;   /* offset: 0x10 */
};

struct LOADCOUNT2_REGS
{
    vu32 LOADCOUNT2; /* offset: 0x00 */
};

struct CPUTIMER_SYS_REGS
{
    Uint32 INTSTATUS;    /* offset: 0x00 */
    Uint32 EOI;          /* offset: 0x04 */
    Uint32 RAWINTSTATUS; /* offset: 0x08 */
};

extern volatile struct CPUTIMER_REGS CpuTimer0Regs;
extern volatile struct CPUTIMER_REGS CpuTimer1Regs;
extern volatile struct CPUTIMER_REGS CpuTimer2Regs;

extern volatile struct LOADCOUNT2_REGS CpuTimer0LC2Regs;
extern volatile struct LOADCOUNT2_REGS CpuTimer1LC2Regs;
extern volatile struct LOADCOUNT2_REGS CpuTimer2LC2Regs;

extern volatile struct CPUTIMER_SYS_REGS CpuTimerSysRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
