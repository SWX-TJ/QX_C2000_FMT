#include "driverlib.h"

//*****************************************************************************
//
// SPI_setConfig
//
//*****************************************************************************
void SPI_setConfig(uint32_t base, uint32_t lspclkHz, SPI_TransferProtocol protocol, SPI_Mode mode,
    uint32_t bitRate, uint16_t dataWidth)
{
    uint32_t baud;
    struct COMBINE_REGS *spi;
    struct SPI_REGS *controller;

    ASSERT(SPI_isBaseValid(base));
    ASSERT(bitRate <= (lspclkHz / 4U));
    ASSERT((lspclkHz / bitRate) <= 128U);

    spi = (struct COMBINE_REGS *)base;
    baud = lspclkHz / bitRate;
    if (mode == SPI_MODE_PERIPHERAL)
    {
        spi->SPI_SEL = 0;
        spi->SLAVE.SSIEN = 0;
        spi->SLAVE.CTRL0.bit.FRF = 0;
        spi->SLAVE.CTRL0.bit.TMOD = SPI_TRANS_MODE_TR;
        controller = &spi->SLAVE;
    }
    else if (mode == SPI_MODE_CONTROLLER)
    {
        spi->SPI_SEL = 1;
        spi->MASTER.SSIEN = 0;
        spi->MASTER.CTRL0.bit.FRF = 0;
        spi->MASTER.CTRL0.bit.TMOD = SPI_TRANS_MODE_TR;
        spi->MASTER.BAUD = baud;
        spi->MASTER.SE = 0x1;
        controller = &spi->MASTER;
    }
    else if (SPI_MODE_PERIPHERAL_OD)
    {
        spi->SPI_SEL = 0;
        spi->SLAVE.SSIEN = 0;
        spi->SLAVE.CTRL0.bit.FRF = 0;
        spi->SLAVE.CTRL0.bit.TMOD = SPI_TRANS_MODE_RO;
        controller = &spi->SLAVE;
    }
    else if (SPI_MODE_CONTROLLER_OD)
    {
        spi->SPI_SEL = 1;
        spi->MASTER.SSIEN = 0;
        spi->MASTER.CTRL0.bit.FRF = 0;
        spi->MASTER.CTRL0.bit.TMOD = SPI_TRANS_MODE_RO;
        spi->MASTER.SE = 0x1;
        spi->MASTER.BAUD = baud;
        controller = &spi->MASTER;
    }

    switch (protocol)
    {
        case SPI_PROT_POL0PHA0:
            controller->CTRL0.bit.SCPOL = 0;
            controller->CTRL0.bit.SCPH  = 0;
            break;
        case SPI_PROT_POL0PHA1:
            controller->CTRL0.bit.SCPOL = 1;
            controller->CTRL0.bit.SCPH  = 1;
            break;
        case SPI_PROT_POL1PHA0:
            controller->CTRL0.bit.SCPOL = 1;
            controller->CTRL0.bit.SCPH  = 0;
            break;
        case SPI_PROT_POL1PHA1:
            controller->CTRL0.bit.SCPOL = 0;
            controller->CTRL0.bit.SCPH  = 1;
            break;
        default:
            controller->CTRL0.bit.SCPOL = 0;
            controller->CTRL0.bit.SCPH  = 0;
            break;
    }

    SPI_setcharLength((u32)controller, dataWidth);
    SPI_enableModule((u32)controller);
}

//*****************************************************************************
//
// SPI_setBaudRate
//
//*****************************************************************************
void SPI_setBaudRate(uint32_t base, uint32_t lspclkHz, uint32_t bitRate)
{
    uint32_t baud;
    struct SPI_REGS *spi;

    // Check the arguments.
    ASSERT(bitRate <= (lspclkHz / 4U));
    ASSERT((lspclkHz / bitRate) <= 128U);

    spi = (struct SPI_REGS *)base;
    SPI_disableModule(base);

    baud      = lspclkHz / bitRate;
    spi->BAUD = (u32)baud;

    SPI_enableModule(base);
}

//*****************************************************************************
//
// SPI_setQSPIMode
//
//*****************************************************************************
void SPI_setQSPIMode(uint32_t base, SPI_WireFormat mode )
{
    struct SPI_REGS *spi;

    // Check the arguments.
    ASSERT(SPI_isBaseValid(base));

    spi = (struct SPI_REGS *)base;
    SPI_disableModule(base);

    spi->CTRL0.bit.SPI_FRF = mode;

    SPI_enableModule(base);
}

//*****************************************************************************
//
// SPI_moduleEnableInterrupt
//
//*****************************************************************************
void SPI_enableInterrupt(uint32_t base, uint32_t intFlags)
{
    // Check the arguments.
    ASSERT(SPI_isBaseValid(base));

    // Enable the specified interrupts.
    if ((intFlags & DW_SPI_INT_TXEI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) |= DW_SPI_INT_TXEI;
    }

    if ((intFlags & DW_SPI_INT_TXOI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) |= DW_SPI_INT_TXOI;
    }

    if ((intFlags & DW_SPI_INT_RXUI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) |= DW_SPI_INT_RXUI;
    }

    if ((intFlags & DW_SPI_INT_RXOI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) |= DW_SPI_INT_RXOI;
    }

    if ((intFlags & DW_SPI_INT_RXFI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) |= DW_SPI_INT_RXFI;
    }

    if ((intFlags & DW_SPI_INT_MSTI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) |= DW_SPI_INT_MSTI;
    }
}

//*****************************************************************************
//
// SPI_moduleDisableInterrupt
//
//*****************************************************************************
void SPI_disableInterrupt(uint32_t base, uint32_t intFlags)
{
    // Check the arguments.
    ASSERT(SPI_isBaseValid(base));

    // Disable the specified interrupts.
    if ((intFlags & DW_SPI_INT_TXEI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) &= ~DW_SPI_INT_TXEI;
    }

    if ((intFlags & DW_SPI_INT_TXOI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) &= ~DW_SPI_INT_TXOI;
    }

    if ((intFlags & DW_SPI_INT_RXUI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) &= ~DW_SPI_INT_RXUI;
    }

    if ((intFlags & DW_SPI_INT_RXOI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) &= ~DW_SPI_INT_RXOI;
    }

    if ((intFlags & DW_SPI_INT_RXFI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) &= ~DW_SPI_INT_RXFI;
    }

    if ((intFlags & DW_SPI_INT_MSTI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) &= ~DW_SPI_INT_MSTI;
    }
}

//*****************************************************************************
//
// SPI_getInterruptStatus
//
//*****************************************************************************
uint32_t SPI_getInterruptStatus(uint32_t base)
{
    uint32_t temp = 0;

    // Check the arguments.
    ASSERT(SPI_isBaseValid(base));

    temp |= HWREG(base + DW_SPI_ISR);

    return (temp);
}

//*****************************************************************************
//
// SPI_clearInterruptStatus
//
//*****************************************************************************
void SPI_clearInterruptStatus(uint32_t base, uint32_t intFlags)
{
    uint32_t temp;
    // Check the arguments.
    ASSERT(SPI_isBaseValid(base));

    // Clear the specified interrupt sources.
    if ((intFlags & DW_SPI_INT_TXOI) != 0U)
    {
        temp = HWREG(base + DW_SPI_TXOICR);
    }

    if ((intFlags & DW_SPI_INT_RXOI) != 0U)
    {
        temp = HWREG(base + DW_SPI_RXOICR);
    }

    if ((intFlags & DW_SPI_INT_RXUI) != 0U)
    {
        temp = HWREG(base + DW_SPI_RXUICR);
    }

    if ((intFlags & DW_SPI_INT_MSTI) != 0U)
    {
        temp = HWREG(base + DW_SPI_MSTICR);
    }
}

//*****************************************************************************
//
// SPI_pollingNonFIFOTransaction
//
//*****************************************************************************
uint16_t SPI_pollingNonFIFOTransaction(uint32_t base, uint16_t charLength, uint16_t data)
{
    return 0;
}
//*****************************************************************************
//
// SPI_pollingFIFOTransaction
//
//*****************************************************************************

void SPI_pollingFIFOTransaction(uint32_t base, uint16_t charLength, uint16_t *pTxBuffer,
    uint16_t *pRxBuffer, uint16_t numOfWords, uint16_t txDelay)
{
    int i;

    ASSERT(SPI_isBaseValid(base));

    SPI_setcharLength(base, charLength);

    if (charLength == SPI_DATA_BITS_8)
    {
        u8 *Txchar = (u8 *)pTxBuffer;
        u8 *Rxchar = (u8 *)pRxBuffer;
        while (numOfWords > 0)
        {
        	for ( i = 0; i < SPI_FIFO_TXFULL; i++) {
        		SPI_writeDataBlockingFIFO(base, *Txchar);
        		Txchar += 1;
        		numOfWords -= 1;
        	}

        	while(SPI_getRxFIFOStatus(base) < SPI_FIFO_RXFULL)
        		;

        	for ( i = 0; i < SPI_FIFO_RXFULL; i++) {
        		if (Rxchar == NULL)
        			SPI_readDataBlockingFIFO(base);
        		else {
        			*Txchar = SPI_readDataBlockingFIFO(base);
        			Txchar += 1;
        		}
        	}
        }
    }
    else if (charLength == SPI_DATA_BITS_16)
    {
        u16 *Txshort = (u16 *)pTxBuffer;
        u16 *Rxshort = (u16 *)pRxBuffer;
        while (numOfWords > 0)
        {
        	for ( i = 0; i < SPI_FIFO_TXFULL; i++)
            {
        		SPI_writeDataBlockingFIFO(base, *Txshort);
                Txshort += 1;
                numOfWords -= 2;
            }

        	while(SPI_getRxFIFOStatus(base) < SPI_FIFO_RXFULL)
        		;

        	for ( i = 0; i < SPI_FIFO_RXFULL; i++)
            {
        		if (Rxshort == NULL)
        			SPI_readDataBlockingFIFO(base);
        		else {
        			*Rxshort = (u16)SPI_readDataBlockingFIFO(base);
        			Rxshort += 1;
        		}
            }
        }
    }
    else if (charLength == SPI_DATA_BITS_32)
    {
        u32 *Txint = (u32 *)pTxBuffer;
        u32 *Rxint = (u32 *)pRxBuffer;
        while (numOfWords > 0)
        {
        	for ( i = 0; i < SPI_FIFO_TXFULL; i++)
            {
        		SPI_writeDataBlockingFIFO(base, *Txint);
                Txint += 1;
                numOfWords -= 4;
            }

        	while(SPI_getRxFIFOStatus(base) < SPI_FIFO_RXFULL)
        		;

        	for ( i = 0; i < SPI_FIFO_RXFULL; i++)
            {
        		if (Rxint == NULL)
        			SPI_readDataNonBlocking(base);
        		else {
        			*Rxint = SPI_readDataNonBlocking(base);
        			Rxint += 1;
        		}
            }
        }
    }
}

//*****************************************************************************
//
// SPI_transmit24Bits
//
//*****************************************************************************
void SPI_transmit24Bits(uint32_t base, uint32_t data, uint16_t txDelay)
{
	SPI_writeDataNonBlocking(base, data);
}
//*****************************************************************************
//
// SPI_receive16Bits
//
//*****************************************************************************

uint16_t SPI_receive16Bits(
    uint32_t base, SPI_endianess endianness, uint16_t dummyData, uint16_t txDelay)
{
	return SPI_readDataNonBlocking(base);
}
//*****************************************************************************
//
// SPI_receive24Bits
//
//*****************************************************************************

uint32_t SPI_receive24Bits(
    uint32_t base, SPI_endianess endianness, uint16_t dummyData, uint16_t txDelay)
{
	return SPI_readDataNonBlocking(base);
}
//*****************************************************************************
//
// SPI_transmit32Bits
//
//*****************************************************************************

void SPI_transmit32Bits(uint32_t base, uint32_t data, uint16_t txDelay)
{
	SPI_writeDataNonBlocking(base, data);
}
//*****************************************************************************
//
// SPI_receive32Bits
//
//*****************************************************************************

uint32_t SPI_receive32Bits(
    uint32_t base, SPI_endianess endianness, uint16_t dummyData, uint16_t txDelay)
{
	return SPI_readDataNonBlocking(base);
}
