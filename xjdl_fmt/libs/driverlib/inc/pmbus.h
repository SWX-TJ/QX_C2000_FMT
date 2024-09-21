#ifndef QX_PMBUS_H
#define QX_PMBUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_pmbus.h"
#include "define.h"


#define PMBUS_INCLUDE_CRC8_TABLE        0x1U

#define PMBUS_INT_ALL 0x000007FFUL

#define PMBUS_O_PMBINTM   0xCC
#define PMBUS_O_PMBSTS    0x70
#define PMBUS_O_PMBENABLE 0x6C
#define PMBUS_O_PMBSAR    0x08
#define PMBUS_O_PMBTAR    0x04
#define PMBUS_O_PMBCON 	  0x00
#define PMBUS_O_PMBDATACMD 	0x10

#define PMBUS_PMBSTS_BUS_FREE 0x0001U // PMBus Free Indicator

#define PMBUS_PMBENABLE_ALERT_EN 0x40000U


#define PMBUS_PMBCCR_RW                  0x100U
#define PMBUS_PMBCCR_TARGET_ADDR_S       1U
#define PMBUS_PMBCCR_TARGET_ADDR_M       0xFEU			// Slave Address
#define PMBUS_PMBCCR_BYTE_COUNT_S        8U
#define PMBUS_PMBCCR_BYTE_COUNT_M        0xFF00U		// Number of Bytes Transmitted
#define PMBUS_PMBCCR_CMD_ENA             0x10000U		// Master Command Code Enable
#define PMBUS_PMBCCR_EXT_CMD             0x20000U		// Master Extended Command Code Enable
#define PMBUS_PMBCCR_PEC_ENA             0x40000U		// Master PEC Processing Enable
#define PMBUS_PMBCCR_GRP_CMD             0x80000U 		// Master Group Command Message Enable
#define PMBUS_PMBCCR_PRC_CALL            0x100000U		// Master Process Call Message Enable


#define PMBUS_PMBTCR_TARGET_ADDR_S       0U
#define PMBUS_PMBTCR_TARGET_ADDR_M       0x7FU       // Configures the current device address of the slave.
#define PMBUS_PMBTCR_MAN_TARGET_ACK      0x80U       // Manual Slave Address Acknowledgement Mode
#define PMBUS_PMBTCR_TARGET_MASK_S       8U
#define PMBUS_PMBTCR_TARGET_MASK_M       0x7F00U     // Slave address mask
#define PMBUS_PMBTCR_PEC_ENA             0x8000U     // PEC Processing Enable
#define PMBUS_PMBTCR_TX_COUNT_S          16U
#define PMBUS_PMBTCR_TX_COUNT_M          0x70000U    // Number of valid bytes in Transmit Data Register
#define PMBUS_PMBTCR_TX_PEC              0x80000U    // send a PEC byte at end of message
#define PMBUS_PMBTCR_MAN_CMD             0x100000U   // Manual Command Acknowledgement Mode
#define PMBUS_PMBTCR_RX_BYTE_ACK_CNT_S   21U
#define PMBUS_PMBTCR_RX_BYTE_ACK_CNT_M   0x600000U   // Number of data bytes to automatically acknowledge

//*****************************************************************************
//
//! Clock Mode Descriptor
//!
//! Used in PMBus_configBusClock() to set up the bus speed. There are two
//! possible modes of operation:
//! -# Standard Mode 100 kHz
//! -# Fast Mode 400 kHz
//
//*****************************************************************************
typedef enum
{
    PMBUS_CLOCKMODE_STANDARD = 0U, //!< Standard mode 100 kHz
    PMBUS_CLOCKMODE_FAST     = 1U  //!< Fast Mode 400 kHz
} PMBus_ClockMode;

//*****************************************************************************
//
//! Access Type Descriptor
//!
//! Used in PMBus_getCurrentAccessType() to determine if the device, in target
//! mode, was accessed with read or write enabled.
//
//*****************************************************************************
typedef enum{
    PMBUS_ACCESSTYPE_WRITE  = 0U, //!< Target last address for write transaction
    PMBUS_ACCESSTYPE_READ   = 1U  //!< Target last address for read transaction
}PMBus_accessType;

//*****************************************************************************
//
//! Interrupt Edge Descriptor
//!
//! Used in PMBus_setCtrlIntEdge() and PMBus_setClkLowTimeoutIntEdge() to set
//! the edge, falling or rising, that triggers an interrupt
//
//*****************************************************************************
typedef enum{
    PMBUS_INTEDGE_FALLING   = 0U, //!< Interrupt generated on falling edge
    PMBUS_INTEDGE_RISING    = 1U  //!< Interrupt generated on rising edge
}PMBus_intEdge;

//*****************************************************************************
//
//! \internal
//! Checks a PMBus base address.
//!
//! \param base is the base address of the PMBus instance used.
//!
//! This function determines if a PMBus module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool PMBus_isBaseValid(uint32_t base)
{
    return (base == PMBUSA_BASE);
}
#endif

//*****************************************************************************
//
// PCBCCR Commands -> used in PMBus_configControlleer()
//
//*****************************************************************************

//*****************************************************************************
//
//! Disables the PMBus module.
//!
//! \param base is the base address of the PMBus instance used.
//!
//! This function resets the internal state machine of the PMBus module and
//! holds it in that state
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;
    PmbusaRegs.IC_ENABLE.bit.ENABLE = 0;
    HWREG(base + PMBUS_O_PMBENABLE) &= ~(0x1U);
    EDIS;
}

//*****************************************************************************
//
//! Enables the PMBus module.
//!
//! \param base is the base address of the PMBus instance used.
//!
//! This function enables operation of the PMBus module by removing it from the
//! reset state
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;
    PmbusaRegs.IC_ENABLE.bit.ENABLE |= 0x01;
    EDIS;
}

//*****************************************************************************
//
//! Enables PMBus interrupt sources.
//!
//! \param base is the base address of the PMBus instance used.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated PMBus interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b PMBUS_INT_BUS_FREE          - Bus Free Interrupt
//! - \b PMBUS_INT_CLK_LOW_TIMEOUT   - Clock Low Time-out Interrupt
//! - \b PMBUS_INT_DATA_READY        - Data Ready Interrupt
//! - \b PMBUS_INT_DATA_REQUEST      - Data Request Interrupt
//! - \b PMBUS_INT_TARGET_ADDR_READY  - Target Address Ready Interrupt
//! - \b PMBUS_INT_EOM               - End of Message Interrupt
//! - \b PMBUS_INT_ALERT             - Alert Detection Interrupt
//! - \b PMBUS_INT_CONTROL           - Control Detection Interrupt
//! - \b PMBUS_INT_LOST_ARB          - Lost Arbitration Interrupt
//! - \b PMBUS_INT_CLK_HIGH_DETECT   - Clock High Detection Interrupt
//! - \b PMBUS_INT_ALL               - all PMBus interrupts
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_enableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;

    //
    // Enable the desired basic interrupts, that is, clear their mask bits
    // in PMBINTM
    //
    HWREG(base + PMBUS_O_PMBINTM) &= ~(intFlags & 0x07FFU);
    EDIS;
}

//*****************************************************************************
//
//! Disables PMBus interrupt sources.
//!
//! \param base is the base address of the PMBus instance used.
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//!
//! This function disables the indicated PMBus interrupt sources.  Only
//! the sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter has the same definition as the \e intFlags
//! parameter to PMBus_enableInterrupt().
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_disableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;

    //
    // Disable the desired interrupts
    //
    HWREG(base + PMBUS_O_PMBINTM) |= (intFlags & 0x07FFU);
    EDIS;
}

//*****************************************************************************
//
//! Indicates whether or not the PMBus bus is busy.
//!
//! \param status  the value of the status register (PMBUS_O_PMBSTS)
//!
//! This function returns an indication of whether or not the PMBus bus is busy
//!
//! \note The status register is cleared each time it is read, therefore, it
//! should be read once at the beginning of an interrupt service routine using
//! PMBus_getInterruptStatus() and saved to a temporary variable for further
//! processing.
//!
//! \return Returns \b true if the PMBus bus is busy; otherwise, returns
//! \b false.
//
//*****************************************************************************
static inline bool PMBus_isBusBusy(uint32_t status)
{
    return (((status & PMBUS_PMBSTS_BUS_FREE) == 0U) ? true : false);
}

//*****************************************************************************
//
//! Enable I2C mode
//!
//! \param base is the base address of the PMBus instance used.
//!
//! Set the PMBus module to work in I2C mode
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_enableI2CMode(uint32_t base)
{
    //
    // Locals
    //
    uint32_t interruptState;

    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    EALLOW;

    //
    // Save off the interrupt state and disable them
    //
    interruptState                = HWREG(base + PMBUS_O_PMBINTM);
    HWREG(base + PMBUS_O_PMBINTM) = PMBUS_INT_ALL;

    EDIS;
}

//*****************************************************************************
//
//! Disable I2C mode
//!
//! \param base is the base address of the PMBus instance used.
//!
//! Set the PMBus module to work in PMBus mode
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_disableI2CMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    EALLOW;

    EDIS;
}

//*****************************************************************************
//
//! Read the status register
//!
//! \param base is the base address of the PMBus instance used.
//!
//! \return Contents of the status register.
//
//*****************************************************************************
static inline uint32_t PMBus_getStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    return (HWREG(base + PMBUS_O_PMBSTS));
}

//*****************************************************************************
//
//! Acknowledge the transaction by writing to the PMBACK register
//!
//! \param base is the base address of the PMBus instance used.
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_ackTransaction(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    //
    // Acknowledge
    //
    //    HWREG(base + PMBUS_O_PMBACK) |= PMBUS_PMBACK_ACK;
}

//*****************************************************************************
//
//! Nack the transaction by writing to the PMBACK register
//!
//! \param base is the base address of the PMBus instance used.
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_nackTransaction(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    //
    // NACK
    //
    //    HWREG(base + PMBUS_O_PMBACK) &= ~(uint32_t)PMBUS_PMBACK_ACK;
}

//*****************************************************************************
//
//! Alert the controller by asserting the ALERT line
//!
//! \param base is the base address of the PMBus instance used.
//!
//! A target PMBus can alert the controller by pulling the alert line low.
//! This triggers an Alert Response from the controller`, where the ,controller issues
//! the \b Alert \b Response \b Address on the bus with a read bit and the
//! alerting target is required to reply with its address.
//!
//! \note The alerting device should be in target mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_assertAlertLine(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    EALLOW;

    //
    // Pull the alert line low
    //
    HWREG(base + PMBUS_O_PMBENABLE) |= PMBUS_PMBENABLE_ALERT_EN;

    EDIS;
}

//*****************************************************************************
//
//! De-assert the alert line
//!
//! \param base is the base address of the PMBus instance used.
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_deassertAlertLine(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    EALLOW;

    //
    // Pull the alert line low

    //
    HWREG(base + PMBUS_O_PMBENABLE) &= ~(uint32_t)PMBUS_PMBENABLE_ALERT_EN;

    EDIS;
}

//*****************************************************************************
//
//! Configure the PMBus operation in Controller Mode.
//!
//! \param base is the base address of the PMBus instance used.
//! \param targetAddress address of the Target device
//! \param byteCount number of bytes transmitted (or read) in the message
//! (up to 255)
//! \param configWord can be a combination of the following
//! -# PMBUS_CONTROLLER_ENABLE_PRC_CALL
//! -# PMBUS_CONTROLLER_ENABLE_GRP_CMD
//! -# PMBUS_CONTROLLER_ENABLE_PEC
//! -# PMBUS_CONTROLLER_ENABLE_EXT_CMD
//! -# PMBUS_CONTROLLER_ENABLE_CMD
//! -# PMBUS_CONTROLLER_ENABLE_READ
//!
//! Assuming the PMBus module is set to Controller mode this function will
//! configure the PMBCCR register. It overwrites the contents of the PMBCCR
//! register.
//! \note
//! -# Writing to the PMBCCR register initiates a message on the bus once
//! the bus is free. In the event of a write the TXBUF must be loaded prior
//! to configuration, or very quickly after configuration, before the module
//! starts the bus clock.
//! -# If the user does not specify an option for example,
//! PMBUS_CONTROLLER_ENABLE_READ, the code will write a 0 (a write) in its
//! bit field.
//! -# setting byteCount to 0U (on a write) triggers a quick command; there
//! is no need to precede this command with the PMBus_putControllerData()
//! -# If transmitting with a non-zero byteCount the user must precede this
//! with the PMBus_putControlllerData(), supplying it with the location of the data
//! and the number of bytes (<= 4). For block transmissions the user will have
//! to call PMBus_putControllerData(), PMBus_configController() and then continue
//! calling PMBus_putControllerData() transmitting 4 (or less for the final
//! transmit) bytes at a time till all the data bytes are transmitted.
//! -# If receiving the user must follow up with the PMBus_getData(),
//!  supplying it with the location of an empty buffer and the status byte
//! -# In cases where the controller must transmit for example, process call,
//! the user must call PMBus_putControllerData(), then configure the controlller to
//! transmit the command and two bytes, then call PMBus_getData() to
//! read two bytes from the target. The controller module need not be reconfigured
//! between write and read whenever a repeated start is involved in the
//! transaction
//! \return None.
//
//*****************************************************************************
extern uint8_t PEC_ENA_FLAG;
static inline void PMBus_configController(uint32_t base, uint16_t targetAddress,
                               uint16_t byteCount, uint32_t configWord)
{
    //
    // Locals
    // Form a bit mask of the bit fields configWord changes
    //
    const uint32_t bitmask = (PMBUS_PMBCCR_RW | PMBUS_PMBCCR_CMD_ENA |
               PMBUS_PMBCCR_EXT_CMD | PMBUS_PMBCCR_PEC_ENA |
               PMBUS_PMBCCR_GRP_CMD | PMBUS_PMBCCR_PRC_CALL);

    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    ASSERT(targetAddress <= 0x7FU);
    ASSERT(byteCount <= 0xFFU);


    EALLOW;

    if(PMBUS_PMBCCR_RW & configWord)
    {
    	PmbusaRegs.IC_DATA_CMD.bit.CMD = PMBUS_ACCESSTYPE_READ;
    }
    else
    {
    	PmbusaRegs.IC_DATA_CMD.bit.CMD = PMBUS_ACCESSTYPE_WRITE;
    }

    if(PMBUS_PMBCCR_PRC_CALL & configWord)
    {
    	PmbusaRegs.IC_DATA_CMD.bit.CMD = PMBUS_ACCESSTYPE_WRITE;
    }

    if(PMBUS_PMBCCR_PEC_ENA & configWord)
    {
    	PEC_ENA_FLAG = 1;
    }
    else
    {
    	PEC_ENA_FLAG = 0;
    }

    PmbusaRegs.IC_TAR.bit.TAR = (targetAddress&0xFE);

    EDIS;
}


//*****************************************************************************
//
//! Get the address that the PMBus module will respond to (in target mode)
//!
//! \param base is the base address of the PMBus instance used.
//!
//! This function will query the PMBUS_O_PMBHTA register, this
//! will be the address of the module when used in Target Mode.
//! \return Address of the PMBus device (in slave mode).
//
//*****************************************************************************
static inline uint16_t PMBus_getOwnAddress(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    return (HWREG(base + PMBUS_O_PMBSAR) & 0x3FFU);
}

//*****************************************************************************
//
//! Set the current device address
//!
//! \param base is the base address of the PMBus instance used.
//! \param address : Address to be configured.
//!
//! This function configures the current device address, this
//! will be the own address of the module.
//! \return None.
//
//*****************************************************************************
static inline void PMBus_setOwnAddress(uint32_t base, uint16_t Ownaddress)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    ASSERT(Ownaddress <= 0x3FFU);

    EALLOW;

    //
    // Write the address to the PMBSC register (bits 6:0)
    //
    HWREG(base + PMBUS_O_PMBSAR) = (Ownaddress & 0x3FF);

    EDIS;
}

//*****************************************************************************
//
//! Set the target address
//!
//! \param base is the base address of the PMBus instance used.
//! \param address : Target Address to be configured.
//!
//! This function configures the current device address, this
//! will be the target address.
//! \return None.
//
//*****************************************************************************
static inline void PMBus_setTargetAddress(uint32_t base, uint16_t targetAddress)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    ASSERT(targetAddress <= 0x3FFU);

    EALLOW;

    //
    // Write the target address to PMBMC register
    //
    HWREG(base + PMBUS_O_PMBTAR) |= ((uint32_t)targetAddress & 0x3ff);
    EDIS;
}

//*****************************************************************************
//
//! Determine the current access (read/write) type
//!
//! \param base is the base address of the PMBus instance used.
//!
//! This function will query the PMBUS_O_PMBHTA register, to determine if
//! the current access type was a read or write access. This bit is relevant
//! only when the PMBus module is addressed as a target.
//!
//! \return an enum of the type PMBus_accessType which specifies if the device,
//! in target mode, was addressed for a read or write operation
//
//*****************************************************************************
static inline PMBus_accessType PMBus_getCurrentAccessType(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    uint16_t type = PmbusaRegs.IC_DATA_CMD.bit.CMD;

    return((PMBus_accessType)(type));
}

//*****************************************************************************
//
//! Sets the triggering edge of the Control Interrupt
//!
//! \param base is the base address of the PMBus instance used.
//! \param intEdge interrupt to trigger on rising or falling edge
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_setCtrlIntEdge(uint32_t base, PMBus_intEdge intEdge)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    EALLOW;

    EDIS;
}

//*****************************************************************************
//
//! Sets the triggering edge of the Clock Low Time-out Interrupt
//!
//! \param base is the base address of the PMBus instance used.
//! \param intEdge interrupt to trigger on rising or falling edge
//!
//! \return None.
//
//*****************************************************************************
static inline
void PMBus_setClkLowTimeoutIntEdge(uint32_t base, PMBus_intEdge intEdge)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    EALLOW;

    EDIS;
}


//*****************************************************************************
//
//! Initializes the PMBus to Target Mode.
//!
//! \param base is the base address of the PMBus instance used.
//! \param address Target address
//! \param mask Target address mask - Used in address detection, the Target
//!  mask enables acknowledgement of multiple device addresses by the Target.
//!  Writing a '0' to a bit within the Target mask enables the corresponding bit
//!  in the Target address to be either '1' or '0' and still allow for a match.
//!  Writing a '0' to all bits in the mask enables the PMBus Interface to
//!  acknowledge any device address. Upon power-up, the controller mask defaults to
//!  7Fh, indicating the controller will only acknowledge the address programmed
//!  into the Controller Address (Bits 6-0).
//!  Set to PMBUS_DISABLE_TARGET_ADDRESS_MASK if you do not wish to have a mask
//!
//! This function sets up the PMBus in target mode and also configures the target
//! address for the PMBus module
//!
//! \return None.
//
//*****************************************************************************
extern
void PMBus_initTargetMode(uint32_t base, uint16_t address, uint16_t mask);

//*****************************************************************************
//
//! Configure the PMBus operation in Target Mode.
//!
//! \param base is the base address of the PMBus instance used.
//! \param configWord can be a combination of the following
//! -# PMBUS_CONTROLLER_ENABLE_MANUAL_ACK
//! -# PMBUS_CONTROLLER_ENABLE_PEC_PROCESSING
//! -# PMBUS_CONTROLLER_ENABLE_MANUAL_CMD_ACK
//! -# PMBUS_CONTROLLER_AUTO_ACK_1_BYTES
//! -# PMBUS_CONTROLLER_AUTO_ACK_2_BYTES
//! -# PMBUS_CONTROLLER_AUTO_ACK_3_BYTES
//! -# PMBUS_CONTROLLER_AUTO_ACK_4_BYTES
//!
//! Assuming the PMBus module is set to target mode, this function will
//! configure the PMBSC register. It overwrites the contents of the PMBSC
//! register, with the exception of the address, target mask, TXPEC and byte
//! count bit fields.
//! \note If the user does not specify an option, for example,
//! PMBUS_TARGET_ENABLE_PEC_PROCESSING, the code will write a 0 (a write) in
//! its  bit field.
//!
//! \return None.
//
//*****************************************************************************
extern void PMBus_configTarget(uint32_t base, uint32_t configWord);


//*****************************************************************************
//
//! Gets the current PMBus interrupt status.
//!
//! \param base is the base address of the PMBus instance used.
//!
//! This function returns the interrupt status for the PMBus module.
//!
//! \return The current interrupt status, as a bit field of
//! - \b PMBUS_INTSRC_BUS_FREE
//! - \b PMBUS_INTSRC_CLK_LOW_TIMEOUT
//! - \b PMBUS_INTSRC_DATA_READY
//! - \b PMBUS_INTSRC_DATA_REQUEST
//! - \b PMBUS_INTSRC_TARGET_ADDR_READY
//! - \b PMBUS_INTSRC_EOM
//! - \b PMBUS_INTSRC_ALERT
//! - \b PMBUS_INTSRC_CONTROL
//! - \b PMBUS_INTSRC_LOST_ARB
//! - \b PMBUS_INTSRC_CLK_HIGH_DETECT
//
//*****************************************************************************
extern uint32_t PMBus_getInterruptStatus(uint32_t base);

//*****************************************************************************
//
//! Read the receive buffer (Target or Controller mode)
//!
//! \param base is the base address of the PMBus instance used.
//! \param buffer pointer to the message buffer where the received bytes
//!         will be written to
//! \param status  the value of the status register (PMBUS_O_PMBSTS)
//!
//! This function can read up to 4 bytes in the receive buffer.
//! \note
//! -# The status register is cleared each time it is read, therefore, it
//! should be read once at the beginning of an interrupt service routine using
//! PMBus_getStatus() and saved to a temporary variable for further
//! processing.
//!
//! -# The buffer should be at least 4 words long; anything smaller will
//! lead to the possibility of memory overrun when a transaction of 4 bytes
//! happens.
//!
//! \return Returns the number of byte(s) received by the PMBus in the
//! array pointed to by buffer.
//
//*****************************************************************************
extern uint16_t
PMBus_getData(uint32_t base, uint16_t *buffer, uint32_t status);

#define PMBus_getControllerData PMBus_getData
#define PMBus_getTargetData  PMBus_getData
//*****************************************************************************
//
//! write to the transmit buffer (Target mode)
//!
//! \param base is the base address of the PMBus instance used.
//! \param buffer pointer to the message buffer where the transmit bytes
//!   are stored
//! \param nBytes number of transmit bytes, up to 4
//! \param txPEC 1 transmit PEC at end of message, 0 no PEC
//!
//! This function can write up to 4 bytes in the transmit buffer.
//!
//! \note
//! -# The user must check the UNIT_BUSY bit before attempting a transmission.
//! -# The buffer should be at least 4 words long; anything smaller will
//! lead to the possibility of memory overrun when a transaction of 4 bytes
//! happens.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBus_putTargetData(uint32_t base, uint16_t *buffer, uint16_t nBytes,
                   bool txPEC);

//*****************************************************************************
//
//! Manual acknowledgement of the target address
//!
//! \param base is the base address of the PMBus instance used.
//! \param address address of the target
//! \param status  the value of the status register (PMBUS_O_PMBSTS)
//! \param buffer pointer to a buffer to store the received data
//!//! This function will read the address that was put on the bus, compare it
//! with address passed to this function and then acknowledge on a match (or
//! nack on mismatch). For this function to work, TARGET_ADDR_READY bit in
//! PBINTM must be enabled. This function checks the TARGET_ADDR_READY bit in
//! the status register before acknowledging so it would be preferable to use
//! this function in an interrupt handler that responds to the TARGET_ADDR_READY
//! interrupt.
//!
//! \note
//! -# The status register is cleared each time it is read, therefore, it
//! should be read once at the beginning of an interrupt service routine using
//! PMBus_getStatus() and saved to a temporary variable for further
//! processing.
//! -# The buffer should be at least 4 words long; anything smaller will
//! lead to the possibility of memory overrun when a transaction of 4 bytes
//! happens.
//!
//! \return None.
//
//*****************************************************************************
extern void PMBus_ackAddress(uint32_t base, uint32_t address, uint32_t status,
                             uint16_t *buffer);

//*****************************************************************************
//
//! Manual acknowledgement of a command
//!
//! \param base is the base address of the PMBus instance used.
//! \param command command to manually acknowledge - it can be any of the
//!  commands listed in this header file. All commands have the common
//!  prefix \b PMBUS_CMD.
//! \param status contents of the status register PMBUS_O_PMBSTS
//! \param buffer pointer to a buffer to store the received data
//!
//! This function will read the command that was put on the bus, compare it
//! with command passed to this function and then acknowledge on a match (or
//! nack on mismatch). For this function to work, DATA_READY bit in PBINTM
//! must be enabled. This function checks the DATA_READY bit in the status
//! register before acknowledging so it would be preferable to use this
//! function in an interrupt handler that responds to the DATA_READY interrupt.
//!
//! \note
//! -# The status register is cleared each time it is read, therefore, it
//! should be read once at the beginning of an interrupt service routine using
//! PMBus_getStatus() and saved to a temporary variable for further
//! processing.
//! -# The buffer should be at least 4 words long; anything smaller will
//! lead to the possibility of memory overrun when a transaction of 4 bytes
//! happens.
//!
//! \return None.
//
//*****************************************************************************
extern void PMBus_ackCommand(uint32_t base, uint32_t command, uint32_t status,
                             uint16_t *buffer);

//*****************************************************************************
//
//! Generate a CRC table at run time
//!
//! \param crcTable points to the CRC8 Table (must be size 256)
//!
//! This function generates a CRC lookup table to run a CRC on the
//! received data. The table is generated from the polynomial
//! x^8 + x^2 + x^1 + 1 (0x7 - leading 1 is implicit)
//!
//! \return None.
//
//*****************************************************************************
extern void PMBus_generateCRCTable(uint16_t *crcTable);

//*****************************************************************************
//
//! Run a CRC on the received data and check against the
//! received PEC to validate the integrity of the data
//!
//! \param base is the base address of the PMBus instance used.
//! \param buffer points to the received message
//! \param crcTable points to the CRC8 Table
//! \param byteCount size of the message, does not include the PEC byte
//! \param pec is the received PEC to check against
//!
//! This function uses a CRC lookup table to run a CRC on the
//! received data. The table was generated from the polynomial
//! x^8 + x^2 + x^1 + 1 (0x7 - leading 1 is implicit)
//!
//! \note The buffer should be at least 4 words long; anything smaller will
//! lead to the possibility of memory overrun when a transaction of 4 bytes
//! happens.
//!
//! \return \b true if the calculated CRC is equal to the PEC, \b false
//! otherwise.
//
//*****************************************************************************
extern bool PMBus_verifyPEC(uint32_t base, uint16_t *buffer,
                  const uint16_t *crcTable, uint16_t byteCount, uint16_t pec);

//*****************************************************************************
//
//! Initializes the PMBus to Controller Mode.
//!
//! \param base is the base address of the PMBus instance used.
//!
//! This function sets up the PMBus in controller mode.
//!
//! \return None.
//
//*****************************************************************************
extern void PMBus_initControllerMode(uint32_t base);

//*****************************************************************************
//
//! write to the transmit buffer (Controller mode)
//!
//! \param base is the base address of the PMBus instance used.
//! \param buffer pointer to the message buffer where the transmit bytes
//!   are stored
//! \param nBytes number of transmit bytes, up to 255
//!
//! This function can write up to 255 bytes in the transmit buffer.
//!
//! \note
//! -# The user must check the UNIT_BUSY bit before attempting the
//! first transmission.
//! -# The buffer should be at least 4 words long; anything smaller will
//! lead to the possibility of memory overrun when a transaction of 4 bytes
//! happens.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBus_putControllerData(uint32_t base, uint16_t *buffer, uint16_t nBytes);

//*****************************************************************************
//
//! Configure the PMBus module clock
//!
//! \param base is the base address of the PMBus instance used.
//! \param moduleFrequency desired module frequency; can range from
//! PMBUS_MODULE_FREQ_MIN Hz to PMBUS_MODULE_FREQ_MAX Hz. Please input the
//! frequency in Hz, for example, 312500 for 312.4 kHz
//! \param sysFrequency Frequency of the system clock (input to PMBus). The
//! values may range anywhere from PMBUS_SYS_FREQ_MIN Hz to PMBUS_SYS_FREQ_MAX
//! Hz. Please input the frequency in Hz, for example, 100000000 for 100 MHz.
//!
//! The frequency to the PMBus module may not exceed PMBUS_MODULE_FREQ_MAX Hz,
//! the appropriate clock divider is chosen to bring the module clock to the
//! desired frequency - this value is then returned by the function.
//! In the event that the desired bus frequency is unattainable, the clock
//! divider is set to the maximum possible value
//!
//! \return module frequency calculated from the system frequency and clock
//! divider.
//
//*****************************************************************************
extern uint32_t
PMBus_configModuleClock(uint32_t base, uint32_t moduleFrequency,
                        uint32_t sysFrequency);

//*****************************************************************************
//
//! Configure the bus clock by overriding the default settings
//!
//! \param base is the base address of the PMBus instance used.
//! \param mode is the operating mode for the PMBus, can be
//!  - Standard Mode
//!  - Fast Mode
//! \param moduleFrequency desired module frequency; can range from
//! PMBUS_MODULE_FREQ_MIN Hz to PMBUS_MODULE_FREQ_MAX Hz. Please input the
//! frequency in Hz, for example, 312500 for 312.4 kHz.
//!
//! The frequency to the PMBus module may not exceed PMBUS_MODULE_FREQ_MAX Hz.
//!
//! \note
//! -# The module comes out of reset with preprogrammed values that allow
//! it to work in standard mode with a module clock of 10MHz. The module clock
//! is set to 10MHz at power cycle, therefore, the user does not have to call
//! this function unless they wish to change the operating frequency of the
//! module clock from the default 10 MHz.
//!
//! \return \b true for successful override, \b false on failure.
//
//*****************************************************************************
extern bool
PMBus_configBusClock(uint32_t base, PMBus_ClockMode mode,
                     uint32_t moduleFrequency);

#ifdef __cplusplus
}
#endif
#endif
