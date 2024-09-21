#include "driverlib.h"

//*****************************************************************************
//
// XBAR_setOutputMuxConfig
//
//*****************************************************************************
void XBAR_setOutputMuxConfig(XBAR_OutputNum output, XBAR_OutputMuxConfig muxConfig)
{
    uint32_t shift;
    uint16_t offset;

    // If the configuration is for MUX16-31, we'll need an odd value to index
    // into the config registers.
    if (((uint32_t)muxConfig & 0x2000U) != 0U)
        offset = ((uint16_t)output << 1U) + 4U;
    else
        offset = (uint16_t)output << 1U;

    // Extract the shift from the input value.
    shift = ((uint32_t)muxConfig >> 8U) & 0x1FU;

    // Write the requested muxing value for this XBAR output.
    EALLOW;
    HWREG(OUTPUTXBAR_BASE + offset) = (HWREG(OUTPUTXBAR_BASE + offset) & ~((uint32_t)0x3U << shift))
                                      | (((uint32_t)muxConfig & 0x3U) << shift);
    EDIS;
}

//*****************************************************************************
//
// XBAR_setEPWMMuxConfig
//
//*****************************************************************************
void XBAR_setEPWMMuxConfig(XBAR_TripNum trip, XBAR_EPWMMuxConfig muxConfig)
{
    uint32_t shift;
    uint16_t offset;

    // If the configuration is for MUX16-31, we'll need an odd value to index
    // into the config registers.
    if (((uint32_t)muxConfig & 0x2000U) != 0U)
        offset = ((uint16_t)trip << 1U) + 4U;
    else
        offset = (uint16_t)trip << 1U;

    // Extract the shift from the input value.
    shift = ((uint32_t)muxConfig >> 8U) & 0x1FU;

    // Write the requested muxing value for this XBAR trip.
    EALLOW;
    HWREG(EPWMXBAR_BASE + (uint32_t)offset)
        = (HWREG(EPWMXBAR_BASE + (uint32_t)offset) & ~(0x3UL << shift))
          | (((uint32_t)muxConfig & 0x3UL) << shift);
    EDIS;
}

//*****************************************************************************
//
// XBAR_getInputFlagStatus
//
//*****************************************************************************
bool XBAR_getInputFlagStatus(XBAR_InputFlag inputFlag)
{
    uint32_t offset;
    uint32_t inputMask;

    // Determine flag register offset.
    offset = (uint16_t)inputFlag >> 8U;
    // Get the status of the X-BAR input latch.
    inputMask = (uint32_t)1U << ((uint32_t)inputFlag & 0xFF);

    return (HWREG(XBAR_BASE + offset * 4) & inputMask);
}

//*****************************************************************************
//
// XBAR_clearInputFlag
//
//*****************************************************************************
void XBAR_clearInputFlag(XBAR_InputFlag inputFlag)
{
    uint32_t offset;
    uint32_t inputMask;

    // Determine flag clear register offset.
    offset = ((uint16_t)inputFlag >> 8U) + 0x08;
    // Set the bit that clears the X-BAR input latch.
    inputMask = 1UL << ((uint32_t)inputFlag & 0xFF);

    HWREG(XBAR_BASE + 0x0C + offset * 4) = inputMask;
}
