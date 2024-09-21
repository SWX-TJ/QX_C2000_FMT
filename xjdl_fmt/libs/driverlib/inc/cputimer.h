#ifndef QX_CPUTIMER_H
#define QX_CPUTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_sysctl.h"
#include "q28004x_cputimer.h"
#include "define.h"

//*****************************************************************************
//
//! Values that can be passed to CPUTimer_setEmulationMode() as the
//! \e mode parameter.
//
//****************************************************************************
typedef enum
{
    //! Denotes that the timer will stop after the next decrement
    CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT = 0x0000,
    //! Denotes that the timer will stop when it reaches zero
    CPUTIMER_EMULATIONMODE_STOPATZERO = 0x0400,
    //! Denotes that the timer will run free
    CPUTIMER_EMULATIONMODE_RUNFREE = 0x0800
} CPUTimer_EmulationMode;

//*****************************************************************************
//
//! The following are values that can be passed to
//! CPUTimer_selectClockSource() as the \e source parameter.
//
//*****************************************************************************
typedef enum
{
    //! System Clock Source
    CPUTIMER_CLOCK_SOURCE_SYS = 0x0,
    //! Internal Oscillator 1 Clock Source
    CPUTIMER_CLOCK_SOURCE_INTOSC1 = 0x1,
    //! Internal Oscillator 2 Clock Source
    CPUTIMER_CLOCK_SOURCE_INTOSC2 = 0x2,
    //! External Clock Source
    CPUTIMER_CLOCK_SOURCE_XTAL = 0x3,
} CPUTimer_ClockSource;

//*****************************************************************************
//
//! The following are values that can be passed to
//! CPUTimer_selectClockSource() as the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    CPUTIMER_CLOCK_PRESCALER_1  = 0, //!< Prescaler value of / 1
    CPUTIMER_CLOCK_PRESCALER_2  = 1, //!< Prescaler value of / 2
    CPUTIMER_CLOCK_PRESCALER_4  = 2, //!< Prescaler value of / 4
    CPUTIMER_CLOCK_PRESCALER_8  = 3, //!< Prescaler value of / 8
    CPUTIMER_CLOCK_PRESCALER_16 = 4, //!< Prescaler value of / 16
} CPUTimer_Prescaler;

//*****************************************************************************
//
//! The following are values that timer mode type
//
//*****************************************************************************
typedef enum
{
    FREE_RUNNING = 0U, // FREE_RUNNING mode will load 0XFFFFFFFF (maximum value)
    USER_DEFINED = 1U, // USER_DEFINED mode will load LOADCOUNT value
} CPUTimer_Mode;

//*****************************************************************************
//
//! \internal
//! Checks CPU timer base address.
//!
//! \param base specifies the Timer module base address.
//!
//! This function determines if a CPU timer module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool CPUTimer_isBaseValid(uint32_t base)
{
    return ((base == CPUTIMER0_BASE) || (base == CPUTIMER1_BASE) || (base == CPUTIMER2_BASE));
}
#endif

//*****************************************************************************
//
//! Clears CPU timer overflow flag.
//!
//! \param base is the base address of the timer module.
//!
//! This function clears the CPU timer overflow flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void CPUTimer_clearOverflowFlag(uint32_t base)
{ }

//*****************************************************************************
//
//! Disables CPU timer interrupt.
//!
//! \param base is the base address of the timer module.
//!
//! This function disables the CPU timer interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void CPUTimer_disableInterrupt(uint32_t base)
{
    ASSERT(CPUTimer_isBaseValid(base));
    ((volatile struct CPUTIMER_REGS *)base)->CTRL.bit.INT_MASK = 1;
}

//*****************************************************************************
//
//! Enables CPU timer interrupt.
//!
//! \param base is the base address of the timer module.
//!
//! This function enables the CPU timer interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void CPUTimer_enableInterrupt(uint32_t base)
{
    ASSERT(CPUTimer_isBaseValid(base));
    ((volatile struct CPUTIMER_REGS *)base)->CTRL.bit.INT_MASK = 0;
}

//*****************************************************************************
//
//! Reloads CPU timer counter.
//!
//! \param base is the base address of the timer module.
//!
//! This function reloads the CPU timer counter with the values contained in
//! the CPU timer period register.
//!
//! \return None.
//
//*****************************************************************************
static inline void CPUTimer_reloadTimerCounter(uint32_t base)
{
    ASSERT(CPUTimer_isBaseValid(base));
    // stop timer, reload Timer Counter will happen after next start timer
    ((volatile struct CPUTIMER_REGS *)base)->CTRL.bit.ENABLE = 0;
    ((volatile struct CPUTIMER_REGS *)base)->CTRL.bit.ENABLE = 1;
}

//*****************************************************************************
//
//! Stops CPU timer.
//!
//! \param base is the base address of the timer module.
//!
//! This function stops the CPU timer.
//!
//! \return None.
//
//*****************************************************************************
static inline void CPUTimer_stopTimer(uint32_t base)
{
    ASSERT(CPUTimer_isBaseValid(base));
#ifdef __CORE0__
    if (base == CPUTIMER0_BASE)
        CpuSysRegs.PCLKCR0.bit.CPU0_TIMER0 = 0;
    else if (base == CPUTIMER1_BASE)
        CpuSysRegs.PCLKCR0.bit.CPU0_TIMER1 = 0;
    else if (base == CPUTIMER2_BASE)
        CpuSysRegs.PCLKCR0.bit.CPU0_TIMER2 = 0;
#else
    if (base == CPUTIMER0_BASE)
        CpuSysRegs.PCLKCR0.bit.CPU1_TIMER0 = 0;
    else if (base == CPUTIMER1_BASE)
        CpuSysRegs.PCLKCR0.bit.CPU1_TIMER1 = 0;
    else if (base == CPUTIMER2_BASE)
        CpuSysRegs.PCLKCR0.bit.CPU1_TIMER2 = 0;
#endif
}

//*****************************************************************************
//
//! Starts(restarts) CPU timer.
//!
//! \param base is the base address of the timer module.
//!
//! This function starts (restarts) the CPU timer.
//!
//! \b Note: This function doesn't reset the timer counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void CPUTimer_resumeTimer(uint32_t base)
{
    ASSERT(CPUTimer_isBaseValid(base));
#ifdef __CORE0__
    if (base == CPUTIMER0_BASE)
        CpuSysRegs.PCLKCR0.bit.CPU0_TIMER0 = 1;
    else if (base == CPUTIMER1_BASE)
        CpuSysRegs.PCLKCR0.bit.CPU0_TIMER1 = 1;
    else if (base == CPUTIMER2_BASE)
        CpuSysRegs.PCLKCR0.bit.CPU0_TIMER2 = 1;
#else
    if (base == CPUTIMER0_BASE)
        CpuSysRegs.PCLKCR0.bit.CPU1_TIMER0 = 1;
    else if (base == CPUTIMER1_BASE)
        CpuSysRegs.PCLKCR0.bit.CPU1_TIMER1 = 1;
    else if (base == CPUTIMER2_BASE)
        CpuSysRegs.PCLKCR0.bit.CPU1_TIMER2 = 1;
#endif
}

//*****************************************************************************
//
//! Starts(restarts) CPU timer.
//!
//! \param base is the base address of the timer module.
//!
//! This function starts (restarts) the CPU timer.
//!
//! \b Note: This function reloads the timer counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void CPUTimer_startTimer(uint32_t base)
{
    ASSERT(CPUTimer_isBaseValid(base));
    // resume timer clock for ensure clock enable
    CPUTimer_resumeTimer(base);
    // alwalys auto set to USER_DEFINED mode befor start timer
    ((volatile struct CPUTIMER_REGS *)base)->CTRL.bit.MODE   = USER_DEFINED;
    ((volatile struct CPUTIMER_REGS *)base)->CTRL.bit.ENABLE = 1;
}

//*****************************************************************************
//
//! Sets CPU timer period.
//!
//! \param base is the base address of the timer module.
//! \param periodCount is the CPU timer period count.
//!
//! This function sets the CPU timer period count.
//!
//! \return None.
//
//*****************************************************************************
static inline void CPUTimer_setPeriod(uint32_t base, uint32_t periodCount)
{
    ASSERT(CPUTimer_isBaseValid(base));
    ((volatile struct CPUTIMER_REGS *)base)->LOADCOUNT = periodCount;
}

//*****************************************************************************
//
//! Returns the current CPU timer counter value.
//!
//! \param base is the base address of the timer module.
//!
//! This function returns the current CPU timer counter value.
//!
//! \return Returns the current CPU timer count value.
//
//*****************************************************************************
static inline uint32_t CPUTimer_getTimerCount(uint32_t base)
{
    ASSERT(CPUTimer_isBaseValid(base));

    return ((volatile struct CPUTIMER_REGS *)base)->CURRENTVALUE;
}

//*****************************************************************************
//
//! Set CPU timer pre-scaler value.
//!
//! \param base is the base address of the timer module.
//! \param prescaler is the CPU timer pre-scaler value.
//!
//! This function sets the pre-scaler value for the CPU timer. For every value
//! of (prescaler*2).
//!
//! \return None.
//
//*****************************************************************************
static inline void CPUTimer_setPreScaler(uint32_t base, uint16_t prescaler)
{
    ASSERT(CPUTimer_isBaseValid(base));

#ifdef __CORE0__
    if (base == CPUTIMER0_BASE)
        DevCfgRegs.CPU0TIMER0_DIV = prescaler;
    else if (base == CPUTIMER1_BASE)
        DevCfgRegs.CPU0TIMER1_DIV = prescaler;
    else if (base == CPUTIMER2_BASE)
        DevCfgRegs.CPU0TIMER2_DIV = prescaler;
#else
    if (base == CPUTIMER0_BASE)
        DevCfgRegs.CPU1TIMER0_DIV = prescaler;
    else if (base == CPUTIMER1_BASE)
        DevCfgRegs.CPU1TIMER1_DIV = prescaler;
    else if (base == CPUTIMER2_BASE)
        DevCfgRegs.CPU1TIMER2_DIV = prescaler;
#endif
}

//*****************************************************************************
//
//! Return the CPU timer overflow status.
//!
//! \param base is the base address of the timer module.
//!
//! This function returns the CPU timer overflow status.
//!
//! \return Returns true if the CPU timer has overflowed, false if not.
//
//*****************************************************************************
static inline bool CPUTimer_getTimerOverflowStatus(uint32_t base)
{
    return 0; // no overflow flag, alwalys return 0
}

//*****************************************************************************
//
//! Select CPU Timer 2 Clock Source and Prescaler
//!
//! \param base is the base address of the timer module.
//! \param source is the clock source to use for CPU Timer 2
//! \param prescaler is the value that configures the selected clock source
//! relative to the system clock
//!
//! This function selects the specified clock source and prescaler value
//! for the CPU timer (CPU timer 2 only).
//!
//! The \e source parameter can be any one of the following:
//! - \b CPUTIMER_CLOCK_SOURCE_SYS     - System Clock
//! - \b CPUTIMER_CLOCK_SOURCE_INTOSC1 - Internal Oscillator 1 Clock
//! - \b CPUTIMER_CLOCK_SOURCE_INTOSC2 - Internal Oscillator 2 Clock
//! - \b CPUTIMER_CLOCK_SOURCE_XTAL    - External Clock
//!
//! The \e prescaler parameter can be any one of the following:
//! - \b CPUTIMER_CLOCK_PRESCALER_1  - Prescaler value of / 1
//! - \b CPUTIMER_CLOCK_PRESCALER_2  - Prescaler value of / 2
//! - \b CPUTIMER_CLOCK_PRESCALER_4  - Prescaler value of / 4
//! - \b CPUTIMER_CLOCK_PRESCALER_8  - Prescaler value of / 8
//! - \b CPUTIMER_CLOCK_PRESCALER_16 - Prescaler value of / 16
//!
//! \return None.
//
//*****************************************************************************
static inline void CPUTimer_selectClockSource(
    uint32_t base, CPUTimer_ClockSource source, CPUTimer_Prescaler prescaler)
{
    ASSERT(base == CPUTIMER2_BASE);

    // Set source and prescaler for CPU Timer 2
    if (base == CPUTIMER2_BASE)
    {
#ifdef __CORE0__
        CpuSysRegs.TMR2CLKCTL.bit.CPU0TMR2CLKSRCSEL = source; // Set Clock Source
        CpuSysRegs.TMR2CLKCTL.bit.CPU0TMR2CLKPRESCALE = prescaler; // Set Clock Prescaler
#else
        CpuSysRegs.TMR2CLKCTL.bit.CPU1TMR2CLKSRCSEL = source; // Set Clock Source
        CpuSysRegs.TMR2CLKCTL.bit.CPU1TMR2CLKPRESCALE = prescaler; // Set Clock Prescaler
#endif
    }
}

//*****************************************************************************
//
//! disable the CPU timer, timer will reload after next start.
//!
//! \param base is the base address of the timer module.
//!
//! This function disable CPU timer.
//
//*****************************************************************************
static inline void CPUTimer_disableTimer(uint32_t base)
{
    ((volatile struct CPUTIMER_REGS *)base)->CTRL.bit.ENABLE = 0;
}

//*****************************************************************************
//
//! clear CPU timer interrupt flag.
//!
//! \param base is the base address of the timer module.
//!
//! This function clear CPU timer interrupt flag.
//
//*****************************************************************************
static inline void CPUTimer_clearInterrupt(uint32_t base)
{
    u32 val = ((volatile struct CPUTIMER_REGS *)base)->EOI;
}

//*****************************************************************************
//
//! set the CPU timer Load Count 2 register.
//!
//! \param base is the base address of the timer module.
//!
//! This function set the CPU timer Load Count 2 register.
//
//*****************************************************************************
static inline void CPUTimer_setLoadCount2(uint32_t base, u32 count2)
{
    ASSERT(CPUTimer_isBaseValid(base));

    if (base == CPUTIMER0_BASE)
        HWREG(CPUTIMER0LC2_BASE) = count2;
    else if (base == CPUTIMER1_BASE)
        HWREG(CPUTIMER1LC2_BASE) = count2;
    else
        HWREG(CPUTIMER2LC2_BASE) = count2;
}

//*****************************************************************************
//
//! enable the CPU timer PWM Output signal.
//!
//! \param base is the base address of the timer module.
//!
//! This function enable the CPU timer PWM Output signal.
//
//*****************************************************************************
static inline void CPUTimer_enablePWMOutput(uint32_t base)
{
    ASSERT(CPUTimer_isBaseValid(base));

    ((volatile struct CPUTIMER_REGS *)base)->CTRL.bit.PWM = 1;
}

//*****************************************************************************
//
//! disable the CPU timer PWM Output signal.
//!
//! \param base is the base address of the timer module.
//!
//! This function disable the CPU timer PWM Output signal.
//
//*****************************************************************************
static inline void CPUTimer_disablePWMOutput(uint32_t base)
{
    ASSERT(CPUTimer_isBaseValid(base));

    ((volatile struct CPUTIMER_REGS *)base)->CTRL.bit.PWM = 0;
}

//*****************************************************************************
//
//! Sets Emulation mode for CPU timer.
//!
//! \param base is the base address of the timer module.
//! \param mode is the emulation mode of the timer.
//!
//! This function sets the behaviour of CPU timer during emulation. Valid
//! values mode are: CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT,
//! CPUTIMER_EMULATIONMODE_STOPATZERO and CPUTIMER_EMULATIONMODE_RUNFREE.
//!
//! \return None.
//
//*****************************************************************************
static inline void CPUTimer_setEmulationMode(uint32_t base, CPUTimer_EmulationMode mode)
{ }

#ifdef __cplusplus
}
#endif

#endif
