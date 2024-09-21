#ifndef QX_PGA_H
#define QX_PGA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_pga.h"
#include "define.h"

//*****************************************************************************
//
//! Values that can be passed to PGA_setGain() as the \e gainValue parameter.
//
//*****************************************************************************
typedef enum
{
    PGA_GAIN_3  = 0x0, //!< PGA gain value of 3
    PGA_GAIN_6  = 0x1, //!< PGA gain value of 6
    PGA_GAIN_12 = 0x2, //!< PGA gain value of 12
    PGA_GAIN_24 = 0x3  //!< PGA gain value of 24
} PGA_GainValue;

//*****************************************************************************
//
//! Values that can be passed to PGA_setFilterResistor() as the \e
//! resistorValue parameter.
//
//*****************************************************************************
typedef enum
{
    //! Low pass filter disabled (open circuit)
    PGA_LOW_PASS_FILTER_DISABLED         = 0, //! Resistor value of 200 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_200_OHM = 1, //! Resistor value of 160 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_160_OHM = 2, //! Resistor value of 130 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_130_OHM = 3, //! Resistor value of 100 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_100_OHM = 4, //! Resistor value of 80 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_80_OHM  = 5, //! Resistor value of 50 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_50_OHM  = 6
} PGA_LowPassResistorValue;

//*****************************************************************************
//
//! \internal
//! Checks PGA wrapper base address.
//!
//! \param base specifies the PGA wrapper base address.
//!
//! This function determines if a PGA wrapper base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool PGA_isBaseValid(uint32_t base)
{
    return ((base == PGA1_BASE) || (base == PGA2_BASE) || (base == PGA3_BASE) || (base == PGA4_BASE)
            || (base == PGA5_BASE) || (base == PGA6_BASE) || (base == PGA7_BASE));
}
#endif

#if 0
//*****************************************************************************
//
//! Enables PGA.
//!
//! \param base is the base address of the PGA module.
//!
//! This function enables the PGA module.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_enable(uint32_t base)
{
    ASSERT(PGA_isBaseValid(base));
    ((volatile struct PGA_REGS *)base)->PGACTL.bit.PGAEN = 1;
}

//*****************************************************************************
//
//! Disables PGA.
//!
//! \param base is the base address of the PGA module.
//!
//! This function disables the PGA module.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_disable(uint32_t base)
{
    ASSERT(PGA_isBaseValid(base));

    ((volatile struct PGA_REGS *)base)->PGACTL.bit.PGAEN = 0;
}

//*****************************************************************************
//
//! Sets PGA gain value
//!
//! \param base is the base address of the PGA module.
//! \param gainValue is the PGA gain value.
//!
//! This function sets the PGA gain value.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_setGain(uint32_t base, PGA_GainValue gainValue)
{
    ASSERT(PGA_isBaseValid(base));

    ((volatile struct PGA_REGS *)base)->PGACTL.bit.GAIN = gainValue;
}

//*****************************************************************************
//
//! Sets PGA output filter resistor value
//!
//! \param base is the base address of the PGA module.
//! \param resistorValue is the PGA output resistor value.
//!
//! This function sets the resistor value for the PGA output low pass RC
//! filter. The resistance for the RC low pass filter is provided within the
//! microprocessor and is determined by the value of resistorValue. The
//! capacitor, however, has to be connected outside the microprocessor.
//!
//! \b Note: Setting a value of PGA_LOW_PASS_FILTER_RESISTOR_0_OHM will
//!          disable the internal resistance value.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_setFilterResistor(uint32_t base, PGA_LowPassResistorValue resistorValue)
{
    ASSERT(PGA_isBaseValid(base));

    ((volatile struct PGA_REGS *)base)->PGACTL.bit.FILTRESSEL = resistorValue;
}

//*****************************************************************************
//
//! Returns the PGA revision number.
//!
//! \param base is the base address of the PGA module.
//!
//! This function returns the PGA revision number.
//!
//! \return Returns PGA revision.
//
//*****************************************************************************
static inline uint16_t PGA_getPGARevision(uint32_t base)
{
    ASSERT(PGA_isBaseValid(base));

    return ((volatile struct PGA_REGS *)base)->PGATYPE.bit.REV;
}

//*****************************************************************************
//
//! Returns the PGA Type.
//!
//! \param base is the base address of the PGA module.
//!
//! This function returns the PGA Type number.
//!
//! \return Returns PGA type.
//
//*****************************************************************************
static inline uint16_t PGA_getPGAType(uint32_t base)
{

    ASSERT(PGA_isBaseValid(base));

    return ((volatile struct PGA_REGS *)base)->PGATYPE.bit.TYPE;
}

//*****************************************************************************
//
//! Locks PGA registers.
//!
//! \param base is the base address of the PGA module.
//! \param registerType is the PGA register to be locked.
//!
//! This function locks the PGA registers specified by registerType. Valid
//! values for registerType are:
//! PGA_REGISTER_PGACTL, PGA_REGISTER_GAINxTRIM, where x is
//! 3,6,12 or 24.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_lockRegisters(uint32_t base, uint16_t registerType)
{

    ASSERT(PGA_isBaseValid(base));
    ASSERT((registerType < 0x3DU) && ((registerType & 0x2U) == 0U));

    ((volatile struct PGA_REGS *)base)->PGALOCK.all = registerType;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#endif

#ifdef __cplusplus
}
#endif

#endif
