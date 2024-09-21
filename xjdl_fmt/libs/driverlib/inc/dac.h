#ifndef QX_DAC_H
#define QX_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_dac.h"

//*****************************************************************************
//
//! Values that can be passed to DAC_setReferenceVoltage() as the \e source
//! parameter.
//
//*****************************************************************************
typedef enum
{
    DAC_REF_VDAC       = 0, //!< VDAC reference voltage
    DAC_REF_ADC_VREFHI = 1  //!< ADC VREFHI reference voltage
} DAC_ReferenceVoltage;

//*****************************************************************************
//
//! Values that can be passed to DAC_setGainMode() as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    DAC_GAIN_ONE = 0, //!< Gain set to 1
    DAC_GAIN_TWO = 1, //!< Gain set to 2
    DAC_BYPASS   = 2  //!< Bypass
} DAC_GainMode;

//*****************************************************************************
//
//! Values that can be passed to DAC_setLoadMode() as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    DAC_LOAD_SYSCLK  = 0, //!< Load on next SYSCLK
    DAC_LOAD_PWMSYNC = 1  //!< Load on next PWMSYNC specified by SYNCSEL
} DAC_LoadMode;

typedef enum
{
    EPWM1SYNCPER = 0,
    EPWM2SYNCPER = 1,
    EPWM3SYNCPER = 2,
    EPWM4SYNCPER = 3,
    EPWM5SYNCPER = 4,
    EPWM6SYNCPER = 5,
    EPWM7SYNCPER = 6,
    EPWM8SYNCPER = 7
} DAC_SyncSel;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks DAC base address.
//!
//! \param base specifies the DAC module base address.
//!
//! This function determines if an DAC module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool DAC_isBaseValid(uint32_t base)
{
    return ((base == DACA_BASE) || (base == DACB_BASE));
}
#endif

//*****************************************************************************
//
//! Get the DAC Revision value
//!
//! \param base is the DAC module base address
//!
//! This function gets the DAC revision value.
//!
//! \return Returns the DAC revision value.
//
//*****************************************************************************
static inline uint16_t DAC_getRevision(uint32_t base)
{
    //
    // Get the revision value.
    //
    return (((volatile struct DAC_REGS *)base)->DACREV.all);
}

//*****************************************************************************
//
//! Sets the DAC Reference Voltage
//!
//! \param base is the DAC module base address
//! \param source is the selected reference voltage
//!
//! This function sets the DAC reference voltage.
//!
//! The \e source parameter can have one of two values:
//! - \b DAC_REF_VDAC       - The VDAC reference voltage
//! - \b DAC_REF_ADC_VREFHI - The ADC VREFHI reference voltage
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_setReferenceVoltage(uint32_t base, DAC_ReferenceVoltage source)
{
    //
    // Set the reference  voltage
    //
    EALLOW;

    ((volatile struct DAC_REGS *)base)->DACCTL.bit.DACREFSEL = source;

    EDIS;
}

//*****************************************************************************
//
//! Sets the DAC Gain Mode
//!
//! \param base is the DAC module base address
//! \param mode is the selected gain mode
//!
//! This function sets the DAC gain mode for the buffered output.
//!
//! The \e mode parameter can have one of two values:
//! - \b DAC_GAIN_ONE  - Gain is set to 1
//! - \b DAC_GAIN_TWO  - Gain is set to 2
//!
//! \note This value is only used when \e DAC_REF_ADC_VREFHI is set using
//! DAC_setReferenceVoltage() and internal ADC reference mode is selected.
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_setGainMode(uint32_t base, DAC_GainMode mode)
{
    //
    // Set the gain mode
    //
    EALLOW;

    ((volatile struct DAC_REGS *)base)->DACCTL.bit.MODE = mode;

    EDIS;
}

//*****************************************************************************
//
//! Sets the DAC Load Mode
//!
//! \param base is the DAC module base address
//! \param mode is the selected load mode
//!
//! This function sets the DAC load mode.
//!
//! The \e mode parameter can have one of two values:
//! - \b DAC_LOAD_SYSCLK   - Load on next SYSCLK
//! - \b DAC_LOAD_PWMSYNC  - Load on next PWMSYNC specified by SYNCSEL
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_setLoadMode(uint32_t base, DAC_LoadMode mode)
{
    //
    // Set the load mode
    //
    EALLOW;

    ((volatile struct DAC_REGS *)base)->DACCTL.bit.LOADMODE = mode;

    EDIS;
}

//*****************************************************************************
//
//! Sets the DAC PWMSYNC Signal
//!
//! \param base is the DAC module base address
//! \param signal is the selected PWM signal
//!
//! This function sets the DAC PWMSYNC signal.
//!
//! The \e signal parameter must be set to a number that represents the PWM
//! signal that will be set. For instance, passing 2 into \e signal will
//! select PWM sync signal 2.
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_setPWMSyncSignal(uint32_t base, DAC_SyncSel signal)
{
    //
    // Set the PWM sync signal
    //
    EALLOW;
    ((volatile struct DAC_REGS *)base)->DACCTL.bit.SYNCSEL = signal;

    EDIS;
}

//*****************************************************************************
//
//! Get the DAC Active Output Value
//!
//! \param base is the DAC module base address
//!
//! This function gets the DAC active output value.
//!
//! \return Returns the DAC active output value.
//
//*****************************************************************************
static inline uint16_t DAC_getActiveValue(uint32_t base)
{
    //
    // Get the active value
    //
    return (((volatile struct DAC_REGS *)base)->DACVALA.bit.DACVALA);
}

//*****************************************************************************
//
//! Set the DAC Shadow Output Value
//!
//! \param base is the DAC module base address
//! \param value is the 12-bit code to be loaded into the active value register
//!
//! This function sets the DAC shadow output value.
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_setShadowValue(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(value <= 0xFFFU);

    //
    // Set the shadow value
    //
    ((volatile struct DAC_REGS *)base)->DACVALS.bit.DACVALS = value;
}

//*****************************************************************************
//
//! Get the DAC Shadow Output Value
//!
//! \param base is the DAC module base address
//!
//! This function gets the DAC shadow output value.
//!
//! \return Returns the DAC shadow output value.
//
//*****************************************************************************
static inline uint16_t DAC_getShadowValue(uint32_t base)
{
    //
    // Get the shadow value
    //
    return (((volatile struct DAC_REGS *)base)->DACVALS.bit.DACVALS);
}

//*****************************************************************************
//
//! Enable the DAC Output
//!
//! \param base is the DAC module base address
//!
//! This function enables the DAC output.
//!
//! \note A delay is required after enabling the DAC. Further details
//! regarding the exact delay time length can be found in the device datasheet.
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_enableOutput(uint32_t base)
{
    //
    // Enable the output
    //
    EALLOW;

    ((volatile struct DAC_REGS *)base)->DACOUTEN.bit.DACOUTEN = 1;

    EDIS;
}
//*****************************************************************************
//
//! Disable the DAC Output
//!
//! \param base is the DAC module base address
//!
//! This function disables the DAC output.
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_disableOutput(uint32_t base)
{
    //
    // Enable the output
    //
    EALLOW;

    ((volatile struct DAC_REGS *)base)->DACOUTEN.bit.DACOUTEN = 0;

    EDIS;
}

//*****************************************************************************
//
//! Set DAC Offset Trim
//!
//! \param base is the DAC module base address
//! \param offset is the specified value for the offset trim
//!
//! This function sets the DAC offset trim. The \e offset value should be a
//! signed number in the range of -128 to 127.
//!
//! \note The offset should not be modified unless specifically indicated by
//! TI Errata or other documentation. Modifying the offset value could cause
//! this module to operate outside of the datasheet specifications.
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_setOffsetTrim(uint32_t base, int16_t offset)
{
    //
    // Check the arguments.
    //
    ASSERT((offset > -129) && (offset < 128));

    //
    // Set the offset trim value
    //
    EALLOW;

    ((volatile struct DAC_REGS *)base)->DACTRIM.bit.OFFSET_TRIM = offset;

    EDIS;
}

//*****************************************************************************
//
//! Get DAC Offset Trim
//!
//! \param base is the DAC module base address
//!
//! This function gets the DAC offset trim value.
//!
//! \return None.
//
//*****************************************************************************
static inline int16_t DAC_getOffsetTrim(uint32_t base)
{
    uint16_t value;

    //
    // Get the sign-extended offset trim value
    //
    value = ((volatile struct DAC_REGS *)base)->DACTRIM.bit.OFFSET_TRIM;
    value = (value ^ (uint16_t)0x80) - (uint16_t)0x80;

    return ((int16_t)value);
}

//*****************************************************************************
//
//! Lock write-access to DAC Register
//!
//! \param base is the DAC module base address
//! \param reg is the selected DAC registers
//!
//! This function locks the write-access to the specified DAC register. Only a
//! system reset can unlock the register once locked.
//!
//! The \e reg parameter can be an ORed combination of any of the following
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_lockRegister(uint32_t base, uint16_t reg)
{
    //
    // Check the arguments.
    //
    ASSERT((reg & ~(0x7U)) == 0U);

    //
    // Lock the specified registers
    //
    EALLOW;

    ((volatile struct DAC_REGS *)base)->DACLOCK.all = (0xA000U | reg)

        EDIS;
}

//*****************************************************************************
//
//! Check if DAC Register is locked
//!
//! \param base is the DAC module base address
//! \param reg is the selected DAC register locks to check
//!
//! This function checks if write-access has been locked on the specified DAC
//! register.
//!
//! The \e reg parameter can be an ORed combination of any of the following
//!
//! \return Returns \b true if any of the registers specified are locked, and
//! \b false if all specified registers aren't locked.
//
//*****************************************************************************
static inline bool DAC_isRegisterLocked(uint32_t base, uint16_t reg)
{
    //
    // Check the arguments.
    //
    ASSERT((reg & ~(0x7U)) == 0U);

    //
    // Return the lock status on the specified registers
    //
    return ((bool)(((((volatile struct DAC_REGS *)base)->DACLOCK.all) & reg) != 0U));
}

//*****************************************************************************
//
//! Tune DAC Offset Trim
//!
//! \param base is the DAC module base address
//! \param referenceVoltage is the reference voltage the DAC
//! module is operating at.
//!
//! This function adjusts/tunes the DAC offset trim. The \e referenceVoltage
//! value should be a floating point number in the range specified in the
//! device data manual.
//!
//! \note Use this function to adjust the DAC offset trim if operating
//! at a reference voltage other than 2.5v. Since this function modifies
//! the DAC offset trim register, it should only be called once after
//! Device_cal. If it is called multiple times after Device_cal, the offset
//! value scaled would be the wrong value.
//!
//! \return None.
//
//*****************************************************************************
extern void DAC_tuneOffsetTrim(uint32_t base, float32_t referenceVoltage);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // DAC_H
