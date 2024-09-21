#ifndef QX_ASYSCTL_H
#define QX_ASYSCTL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_asysctl.h"
#include "inc/hw_asysctl.h"
#include "define.h"
#include "sysctl.h"

//*****************************************************************************
// Defines used for setting AnalogReference functions.
//*****************************************************************************
typedef enum
{
    ASYSCTL_VREFHIA = 0, //!< VREFHIA
    ASYSCTL_VREFHIB = 1, //!< VREFHIB is same as VREFHIC
    ASYSCTL_VREFHIC = 1, //!< VREFHIC is same as VREFHIB
} ASysCtl_VREFHI;

//*****************************************************************************
// Built-in reference output voltage selected signal VREFBI_A/VREFBI_BC
//*****************************************************************************
typedef enum
{
    ASYSCTL_VOL_1_65V = 0x00,
    ASYSCTL_VOL_2_0V  = 0x01,
    ASYSCTL_VOL_2_5V  = 0x02,
} AsysCtl_VREFHISelect;

//*****************************************************************************
//! ASysCtl_CMPHPMuxSelect used for function ASysCtl_selectCMPHPMux().
//*****************************************************************************
typedef enum
{
    ASYSCTL_CMPHPMUX_SELECT_1 = 0U,  //!< CMPHPMUX select 1
    ASYSCTL_CMPHPMUX_SELECT_2 = 3U,  //!< CMPHPMUX select 2
    ASYSCTL_CMPHPMUX_SELECT_3 = 6U,  //!< CMPHPMUX select 3
    ASYSCTL_CMPHPMUX_SELECT_4 = 9U,  //!< CMPHPMUX select 4
    ASYSCTL_CMPHPMUX_SELECT_5 = 12U, //!< CMPHPMUX select 5
    ASYSCTL_CMPHPMUX_SELECT_6 = 16U, //!< CMPHPMUX select 6
    ASYSCTL_CMPHPMUX_SELECT_7 = 19U  //!< CMPHPMUX select 7
} ASysCtl_CMPHPMuxSelect;

//*****************************************************************************
//! ASysCtl_CMPLPMuxSelect used for function ASysCtl_selectCMPLPMux().
//*****************************************************************************
typedef enum
{
    ASYSCTL_CMPLPMUX_SELECT_1 = 0U,  //!< CMPLPMUX select 1
    ASYSCTL_CMPLPMUX_SELECT_2 = 3U,  //!< CMPLPMUX select 2
    ASYSCTL_CMPLPMUX_SELECT_3 = 6U,  //!< CMPLPMUX select 3
    ASYSCTL_CMPLPMUX_SELECT_4 = 9U,  //!< CMPLPMUX select 4
    ASYSCTL_CMPLPMUX_SELECT_5 = 12U, //!< CMPLPMUX select 5
    ASYSCTL_CMPLPMUX_SELECT_6 = 16U, //!< CMPLPMUX select 6
    ASYSCTL_CMPLPMUX_SELECT_7 = 19U  //!< CMPLPMUX select 7
} ASysCtl_CMPLPMuxSelect;

//*****************************************************************************
// Values used for function ASysCtl_selectCMPHNMux() and
// ASysCtl_selectCMPHNMuxValue().  These values can be OR-ed together and
// passed to ASysCtl_selectCMPHNMux().
//*****************************************************************************
typedef enum
{
    ASYSCTL_CMPHNMUX_SELECT_1 = 0x1U,  //!< CMPHNMUX select 1
    ASYSCTL_CMPHNMUX_SELECT_2 = 0x2U,  //!< CMPHNMUX select 2
    ASYSCTL_CMPHNMUX_SELECT_3 = 0x4U,  //!< CMPHNMUX select 3
    ASYSCTL_CMPHNMUX_SELECT_4 = 0x8U,  //!< CMPHNMUX select 4
    ASYSCTL_CMPHNMUX_SELECT_5 = 0x10U, //!< CMPHNMUX select 5
    ASYSCTL_CMPHNMUX_SELECT_6 = 0x20U, //!< CMPHNMUX select 6
    ASYSCTL_CMPHNMUX_SELECT_7 = 0x40U, //!< CMPHNMUX select 7
} ASysCtl_CMPHNMuxSelect;

//*****************************************************************************
// Values used for function ASysCtl_selectCMPLNMux() and
// ASysCtl_selectCMPLNMuxValue().  These values can be OR-ed together and
// passed to ASysCtl_selectCMPLNMux().
//*****************************************************************************
typedef enum
{
    ASYSCTL_CMPLNMUX_SELECT_1 = 0x1U,  //!< CMPLNMUX select 1
    ASYSCTL_CMPLNMUX_SELECT_2 = 0x2U,  //!< CMPLNMUX select 2
    ASYSCTL_CMPLNMUX_SELECT_3 = 0x4U,  //!< CMPLNMUX select 3
    ASYSCTL_CMPLNMUX_SELECT_4 = 0x8U,  //!< CMPLNMUX select 4
    ASYSCTL_CMPLNMUX_SELECT_5 = 0x10U, //!< CMPLNMUX select 5
    ASYSCTL_CMPLNMUX_SELECT_6 = 0x20U, //!< CMPLNMUX select 6
    ASYSCTL_CMPLNMUX_SELECT_7 = 0x40U, //!< CMPLNMUX select 7
} ASysCtl_CMPLNMuxSelect;

//*****************************************************************************
//
//! ASysCtl_getInductorFaultStatus &  ASysCtl_getSwitchSequenceStatus used
//! for function ASysCtl_enableDCDC().
//
//*****************************************************************************
static inline bool ASysCtl_getInductorFaultStatus(void);
static inline bool ASysCtl_getSwitchSequenceStatus(void);

//*****************************************************************************
//! This function endable the temperature sensor output to the ADC.
//*****************************************************************************
static inline void ASysCtl_enableTemperatureSensor()
{
    EALLOW;
    AnalogSubsysRegs.TSNSCTL.bit.ENABLE = 1;
    EDIS;
}

//*****************************************************************************
//! This function disables the temperature sensor output to the ADC.
//*****************************************************************************
static inline void ASysCtl_disableTemperatureSensor(void)
{
    EALLOW;
    AnalogSubsysRegs.TSNSCTL.bit.ENABLE = 0;
    EDIS;
}

//*****************************************************************************
//
//! Set the analog voltage reference selection to internal.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_VREFHIA
//! - \b ASYSCTL_VREFHIB or ASYSCTL_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setAnalogReferenceInternal(ASysCtl_VREFHI reference)
{
    EALLOW;
    if (reference == ASYSCTL_VREFHIA)
    {
        AnalogSubsysRegs.ANAREFCTL.bit.EN_HIZ_A    = 0;
        AnalogSubsysRegs.ANAREFCTL.bit.EN_VREFBI_A = 1;
    }
    else
    {
        AnalogSubsysRegs.ANAREFCTL.bit.EN_HIZ_BC    = 0;
        AnalogSubsysRegs.ANAREFCTL.bit.EN_VREFBI_BC = 1;
    }
    EDIS;
}

//*****************************************************************************
//
//! Set the analog voltage reference selection to external.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_VREFHIA
//! - \b ASYSCTL_VREFHIB or ASYSCTL_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setAnalogReferenceExternal(ASysCtl_VREFHI reference)
{
    EALLOW;
    if (reference == ASYSCTL_VREFHIA)
    {
        AnalogSubsysRegs.ANAREFCTL.bit.EN_HIZ_A    = 1;
        AnalogSubsysRegs.ANAREFCTL.bit.EN_VREFBI_A = 0;
    }
    else
    {
        AnalogSubsysRegs.ANAREFCTL.bit.EN_HIZ_BC    = 1;
        AnalogSubsysRegs.ANAREFCTL.bit.EN_VREFBI_BC = 0;
    }
    EDIS;
}

//*****************************************************************************
//
//! Set the internal analog voltage reference selection to 2.5V.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_VREFHIA
//! - \b ASYSCTL_VREFHIB or ASYSCTL_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setAnalogReferenceVol(ASysCtl_VREFHI reference, AsysCtl_VREFHISelect vol)
{
    EALLOW;
    if (reference == ASYSCTL_VREFHIA)
        AnalogSubsysRegs.ANAREFCTL.bit.SEL_VREFBIBI_A = vol;
    else
        AnalogSubsysRegs.ANAREFCTL.bit.SEL_VREFBIBI_BC = vol;
    EDIS;
}

//*****************************************************************************
//
//! Enable DC-DC.
//!
//! This function enables the DC-DC and checks if the enable was successful
//! when switching from the VREG to the DC-DC .
//!
//! \return Return value \b true indicates that the DC-DC enable was
//! successful when switching from the VREG to the DC-DC . Return
//! value of \b false indicates that the DC-DC enable with switch failed.
//!
//! \note The internal DC-DC regulator is disabled by default. To use this
//! supply, the device must power up initially with the internal LDO (VREG)
//! and then transition to the internal DC-DC regulator.
//
//*****************************************************************************
static inline bool ASysCtl_enableDCDC(void)
{
    EALLOW;
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCCTL) |= ASYSCTL_DCDCCTL_DCDCEN;
    EDIS;

    // Wait till the transition from VREG to DC-DC was successful
    while (ASysCtl_getSwitchSequenceStatus() == false)
        ;

    // Check if the external inductor connected to the DC-DC is functional
    if (ASysCtl_getInductorFaultStatus() == true)
    {
        // Delay 80us for the DC-DC regulator output to settle
        SysCtl_delay(1599U);

        // The DC-DC enable was successful when switching
        // from the VREG to the DC-DC
        return (true);
    }
    else
    {
        // The DC-DC enable was unsuccessful when switching
        // from the VREG to the DC-DC
        return (false);
    }
}

//*****************************************************************************
//
//! Disable DC-DC.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_disableDCDC(void)
{
    EALLOW;
    // Write 0 to enable bit.
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCCTL) &= ~ASYSCTL_DCDCCTL_DCDCEN;
    // Delay 80us for the internal LDO (VREG) to power back up
    SysCtl_delay(1599U);
    EDIS;
}

//*****************************************************************************
//
//! Gets the inductor status.
//!
//! This function returns the inductor status.
//!
//! \return Return value \b true indicates that the external inductor connected
//! to DC-DC is functional.  Return value of \b false indicates it is faulty or
//! not connected.
//
//*****************************************************************************
static inline bool ASysCtl_getInductorFaultStatus(void)
{
    // Return the status the INDDETECT bit.
    return ((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCSTS) & ASYSCTL_DCDCSTS_INDDETECT) == ASYSCTL_DCDCSTS_INDDETECT);
}

//*****************************************************************************
//
//! Gets the Switch Sequence Status.
//!
//! This function returns the Switch Sequence Status.
//!
//! \return Return value \b false indicates that the switch to DC-DC is not
//! complete. Return value of \b true indicates it is complete.
//
//*****************************************************************************
static inline bool ASysCtl_getSwitchSequenceStatus(void)
{
    // Return the status the SWSEQDONE bit.
    return ((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCSTS) & ASYSCTL_DCDCSTS_SWSEQDONE) == ASYSCTL_DCDCSTS_SWSEQDONE);
}

//*****************************************************************************
//
//! Select the value for CMPHNMXSEL.
//!
//! \param select is a combination of CMPHNMXSEL values.
//!
//! The parameter \e select can be a bitwise OR of the below values:
//!
//! - \b ASYSCTL_CMPHNMUX_SELECT_1
//! - \b ASYSCTL_CMPHNMUX_SELECT_2
//! - \b ASYSCTL_CMPHNMUX_SELECT_3
//! - \b ASYSCTL_CMPHNMUX_SELECT_4
//! - \b ASYSCTL_CMPHNMUX_SELECT_5
//! - \b ASYSCTL_CMPHNMUX_SELECT_6
//! - \b ASYSCTL_CMPHNMUX_SELECT_7
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectCMPHNMux(uint16_t select)
{
    ASSERT(select <= 0x7FU);
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHNMXSEL) = select;
    EDIS;
}

//*****************************************************************************
//
//! Select the value for individual CMPxHNMXSEL.
//!
//! \param select is the CMPxHNMXSEL to be set.
//! \param value is 0 or 1.
//!
//! The parameter \e select can be one of the below values:
//!
//! - \b ASYSCTL_CMPHNMUX_SELECT_1
//! - \b ASYSCTL_CMPHNMUX_SELECT_2
//! - \b ASYSCTL_CMPHNMUX_SELECT_3
//! - \b ASYSCTL_CMPHNMUX_SELECT_4
//! - \b ASYSCTL_CMPHNMUX_SELECT_5
//! - \b ASYSCTL_CMPHNMUX_SELECT_6
//! - \b ASYSCTL_CMPHNMUX_SELECT_7
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectCMPHNMuxValue(uint16_t select, uint16_t value)
{
    ASSERT(select <= 0x7FU);
    ASSERT(value <= 1U);
    EALLOW;
    if (value == 0U)
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHNMXSEL) &= ~select;
    else if (value == 1U)
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHNMXSEL) |= select;
    EDIS;
}

//*****************************************************************************
//
//! Select the value for individual CMPxLNMXSEL.
//!
//! \param select is a combination of CMPLNMXSEL values.
//!
//! The parameter \e select can be the bitwise OR of the below values:
//!
//! - \b ASYSCTL_CMPLNMUX_SELECT_1
//! - \b ASYSCTL_CMPLNMUX_SELECT_2
//! - \b ASYSCTL_CMPLNMUX_SELECT_3
//! - \b ASYSCTL_CMPLNMUX_SELECT_4
//! - \b ASYSCTL_CMPLNMUX_SELECT_5
//! - \b ASYSCTL_CMPLNMUX_SELECT_6
//! - \b ASYSCTL_CMPLNMUX_SELECT_7
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectCMPLNMux(uint16_t select)
{
    ASSERT(select <= 0x7FU);
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLNMXSEL) = select;
    EDIS;
}

//*****************************************************************************
//
//! Select the value for CMPLNMXSEL.
//!
//! \param select is the CMPxHNMXSEL to be set.
//! \param value is 0 or 1.
//!
//! The parameter \e select can be one of the below values:
//!
//! - \b ASYSCTL_CMPLNMUX_SELECT_1
//! - \b ASYSCTL_CMPLNMUX_SELECT_2
//! - \b ASYSCTL_CMPLNMUX_SELECT_3
//! - \b ASYSCTL_CMPLNMUX_SELECT_4
//! - \b ASYSCTL_CMPLNMUX_SELECT_5
//! - \b ASYSCTL_CMPLNMUX_SELECT_6
//! - \b ASYSCTL_CMPLNMUX_SELECT_7
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectCMPLNMuxValue(uint16_t select, uint16_t value)
{
    ASSERT(select <= 0x7FU);
    ASSERT(value <= 1U);
    EALLOW;
    if (value == 0U)
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLNMXSEL) &= ~select;
    else if (value == 1U)
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLNMXSEL) |= select;
    EDIS;
}

//*****************************************************************************
//
//! Select the value for CMPHPMXSEL.
//!
//! \param select is of type ASysCtl_CMPHPMuxSelect.
//! \param value is 0, 1, 2, 3, or 4.
//!
//! This function is used to write a value to one mux select at a time.
//! The parameter \e select can be one of the following values:
//!
//! - \b ASYSCTL_CMPHPMUX_SELECT_1
//! - \b ASYSCTL_CMPHPMUX_SELECT_2
//! - \b ASYSCTL_CMPHPMUX_SELECT_3
//! - \b ASYSCTL_CMPHPMUX_SELECT_4
//! - \b ASYSCTL_CMPHPMUX_SELECT_5
//! - \b ASYSCTL_CMPHPMUX_SELECT_6
//! - \b ASYSCTL_CMPHPMUX_SELECT_7
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectCMPHPMux(ASysCtl_CMPHPMuxSelect select, uint32_t value)
{
    ASSERT(value <= 4);
    EALLOW;
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHPMXSEL)
        = (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHPMXSEL)
              & ~((uint32_t)ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_M << (uint32_t)select))
          | (value << (uint32_t)select);
    EDIS;
}

//*****************************************************************************
//
//! Select the value for CMPLPMXSEL.
//!
//! \param select is of type ASysCtl_CMPLPMuxSelect.
//! \param value is 0, 1, 2, 3, or 4.
//!
//! This function is used to write a value to one mux select at a time.
//! The parameter \e select can be one of the following values:
//!
//! - \b ASYSCTL_CMPLPMUX_SELECT_1
//! - \b ASYSCTL_CMPLPMUX_SELECT_2
//! - \b ASYSCTL_CMPLPMUX_SELECT_3
//! - \b ASYSCTL_CMPLPMUX_SELECT_4
//! - \b ASYSCTL_CMPLPMUX_SELECT_5
//! - \b ASYSCTL_CMPLPMUX_SELECT_6
//! - \b ASYSCTL_CMPLPMUX_SELECT_7
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectCMPLPMux(ASysCtl_CMPLPMuxSelect select, uint32_t value)
{
    ASSERT(value <= 4);
    EALLOW;
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL)
        = (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL)
              & ~((uint32_t)ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_M << (uint32_t)select))
          | (value << (uint32_t)select);
    EDIS;
}

//*****************************************************************************
//! Locks the temperature sensor control register.
//! \return None.
//*****************************************************************************
static inline void ASysCtl_lockTemperatureSensor(void)
{
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_TSNSCTL;
    EDIS;
}

//*****************************************************************************
//
//! Locks the analog reference control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockANAREF(void)
{
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_ANAREFCTL;
    EDIS;
}

//*****************************************************************************
//
//! Locks the voltage monitor control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockVMON(void)
{
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_VMONCTL;
    EDIS;
}

//*****************************************************************************
//
//! Locks the DCDC control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockDCDC(void)
{
    EALLOW;
    // Write a 1 to the lock bit in the LOCK register.
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_DCDCCTL;
    EDIS;
}

//*****************************************************************************
//
//! Locks the ADCIN control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockPGAADCINMux(void)
{
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_ADCINMXSEL;
    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPHPMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPHPMux(void)
{
    EALLOW;
    // Write a 1 to the lock bit in the LOCK register.
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPHPMXSEL;
    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPLPMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPLPMux(void)
{
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPLPMXSEL;
    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPHNMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPHNMux(void)
{
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPHNMXSEL;
    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPLNMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPLNMux(void)
{
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPLNMXSEL;
    EDIS;
}

//*****************************************************************************
//
//! Locks the VREG control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockVREG(void)
{
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_VREGCTL;
    EDIS;
}

static inline void ASysCtl_setAnalogReference1P65(uint16_t reference) {}

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
#ifdef __cplusplus
}
#endif

#endif
