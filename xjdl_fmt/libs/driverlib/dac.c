#include "driverlib.h"

//*****************************************************************************
//
// DAC_tuneOffsetTrim()
//
//*****************************************************************************

void DAC_tuneOffsetTrim(uint32_t base, float32_t referenceVoltage)
{
    uint16_t oldOffsetTrim;
    float32_t newOffsetTrim;

    //
    // Check the arguments.
    //
    ASSERT(referenceVoltage > 0U);

    //
    // Get the sign-extended offset trim value
    //
    oldOffsetTrim = ((volatile struct DAC_REGS *)base)->DACTRIM.bit.OFFSET_TRIM;
    oldOffsetTrim = (oldOffsetTrim ^ (uint16_t)0x80) - (uint16_t)0x80;

    //
    // Calculate new offset trim value if DAC is operating at a reference
    // voltage other than 2.5v.
    //
    newOffsetTrim = ((float32_t)(2.5 / referenceVoltage) * (int16_t)oldOffsetTrim);

    //
    // Check if the new offset trim value is valid
    //
    ASSERT(((int16_t)newOffsetTrim > -129) && ((int16_t)newOffsetTrim < 128));

    //
    // Set the new offset trim value
    //
    EALLOW;

    ((volatile struct DAC_REGS *)base)->DACTRIM.bit.OFFSET_TRIM = (int16_t)newOffsetTrim;

    EDIS;
}
