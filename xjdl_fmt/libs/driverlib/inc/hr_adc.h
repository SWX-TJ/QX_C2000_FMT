#ifndef QX_HR_ADC_H
#define QX_HR_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_hr_adc.h"
#include "inc/hw_adc.h"
#include "define.h"

//*****************************************************************************
//
//! Configures the hr analog-to-digital converter module prescaler.
//!
//! \param base is the base address of the ADC module.
//! \param clkPrescale is the ADC clock prescaler.
//!
//! This function configures the ADC module's ADCCLK.
//!
//! The \e clkPrescale parameter specifies the value by which the input clock
//! is divided to make the ADCCLK.  The clkPrescale value can be specified with
//! any of the following enum values:
//! \b ADC_CLK_DIV_1_0, \b ADC_CLK_DIV_2_0, \b ADC_CLK_DIV_3_0, ...,
//! \b ADC_CLK_DIV_6_0, \b ADC_CLK_DIV_7_0, or \b ADC_CLK_DIV_8_0.
//!
//! \return None.
//
//*****************************************************************************
static void HR_ADC_setPrescaler(uint32_t base, ADC_ClkPrescale clkPrescale)
{
    //
    // Set the configuration of the ADC module prescaler.
    //
    EALLOW;
    ((volatile struct HR_ADC_REGS *)base)->adcctl2.bit.prescale = clkPrescale;
    EDIS;
}

// FIXME : IF YOU NEED ZW-LIN 2024.1.25

#ifdef __cplusplus
}
#endif

#endif
