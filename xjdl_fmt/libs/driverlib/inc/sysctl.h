#ifndef QX_SYSCTL_H
#define QX_SYSCTL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "q28004x_sysctl.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_nmi.h"
#include "define.h"

//*****************************************************************************
// Defines for system control functions. Not intended for use by application code
//*****************************************************************************

// Values to help decode peripheral parameter
#define SYSCTL_PERIPH_REG_M 0x001FU
#define SYSCTL_PERIPH_REG_S 0x0000U
#define SYSCTL_PERIPH_BIT_M 0x1F00U
#define SYSCTL_PERIPH_BIT_S 0x0008U

// Keys for the System control registers write protection
#define SYSCTL_REG_KEY 0xA5A50000U
#define SYSCTL_PLL_KEY 0XCAFE0000U

// Values to help access shifting of bits
#define SYSCTL_TYPE_LOCK_S 0xFU

// LPM defines for LPMCR.LPM
#define SYSCTL_LPM_IDLE    0x0000U
#define SYSCTL_LPM_STANDBY 0x0001U
#define SYSCTL_LPM_HALT    0x0002U

// Default internal oscillator frequency, 10 MHz
#define SYSCTL_DEFAULT_OSC_FREQ 10000000U

// Mask for SYNCSELECT.SYNCIN
#define SYSCTL_SYNCSELECT_SYNCIN_M SYSCTL_SYNCSELECT_EPWM4SYNCIN_M

// Boot ROM Booting and Reset Status
#define SYSCTL_BOOT_ROM_STATUS 0x0002U
#define SYSCTL_BOOT_ROM_POR    0x2000U
#define SYSCTL_BOOT_ROM_XRS    0x1000U

#define SYSCTL_DEVICECAL_CONTEXT_SAVE \
    asm(" PUSH ACC  \n\
                                            PUSH DP   \n\
                                            PUSH XAR0 \n\
                                            PUSH XAR2 \n\
                                            PUSH XAR3 \n\
                                            PUSH XAR4 \n\
                                            PUSH XAR5 \n\
                                           ")

#define SYSCTL_DEVICECAL_CONTEXT_RESTORE \
    asm(" POP XAR5 \n\
                                                POP XAR4 \n\
                                                POP XAR3 \n\
                                                POP XAR2 \n\
                                                POP XAR0 \n\
                                                POP DP   \n\
                                                POP ACC  \n\
                                              ")

// Device_cal function which is available in OTP memory
// This function is called in SysCtl_resetPeripheral after resetting
// analog peripherals
// #define Device_cal ((void (*)(void))((uintptr_t)0x070282))

//*****************************************************************************
// The following are values that can be passed to the SysCtl_setClock() API as
// the config parameter.
//*****************************************************************************

// PLL_CLK = OSCCLK_IN * IMULT/ IDIV / ODIV
// CPU_CLK = PLL_CLK / SYSDIV
// WARNINGS: OSCCLK * IMULT/IDIV need at 400Mhz~800Mhz, OSCCLK_IN need at 8Mhz~240Mhz

// WARNINGS: QX C2000 no support FMULT parameter, instead, It add a IDIV parameter

#define SYSCTL_IDIV_M  0x000FUL // Mask for IDIV value in config
#define SYSCTL_IDIV_S  0U       // Shift for IDIV value in config
#define SYSCTL_IDIV(x) (((x) << SYSCTL_IDIV_S) & SYSCTL_IDIV_M)

#define SYSCTL_IMULT_M  0x3F00UL // Mask for IMULT value in config
#define SYSCTL_IMULT_S  8U       // Shift for IMULT value in config
#define SYSCTL_IMULT(x) (((x) << SYSCTL_IMULT_S) & SYSCTL_IMULT_M)

#define SYSCTL_ODIV_M  0xF0000UL // Mask for ODIV value in config
#define SYSCTL_ODIV_S  16U       // Shfit for ODIV value in config
#define SYSCTL_ODIV(x) (((x) << SYSCTL_ODIV_S) & SYSCTL_ODIV_M)

#define SYSCTL_SYSDIV_M  0x3F00000UL // Mask for SYSDIV value in config
#define SYSCTL_SYSDIV_S  20U         // Shift for SYSDIV value in config
#define SYSCTL_SYSDIV(x) ((((x) / 2U) << SYSCTL_SYSDIV_S) & SYSCTL_SYSDIV_M)

// Oscillator source
#define SYSCTL_OSCSRC_M 0x30000000UL // Mask for OSCSRC value in config
#define SYSCTL_OSCSRC_S 28U          // Shift for OSCSRC value in config
//! Internal oscillator INTOSC2
#define SYSCTL_OSCSRC_OSC2 0x00000000UL
//! External oscillator (XTAL) in crystal mode
#define SYSCTL_OSCSRC_XTAL 0x10000000U
//! Internal oscillator INTOSC1
#define SYSCTL_OSCSRC_OSC1 0x20000000UL
//! External oscillator (XTAL) in single-ended mode
#define SYSCTL_OSCSRC_XTAL_SE 0x30000000U

// Enable/disable PLL
#define SYSCTL_PLL_ENABLE  0x80000000U //!< Enable PLL
#define SYSCTL_PLL_DISABLE 0x00000000U //!< Disable PLL

// Number of PLL retries for SW work around
#define SYSCTL_PLL_RETRIES         10U   // Number of PLL retries
#define SYSCTL_PLLLOCK_TIMEOUT     2000U // PLL Lock timeout
#define SYSCTL_DCC_COUNTER0_WINDOW 100U  // DCC Counter0 Window
//*****************************************************************************
//
// Values that can be passed to SysCtl_clearNMIStatus(),
// SysCtl_forceNMIFlags(), SysCtl_isNMIFlagSet(), and
// SysCtl_isNMIShadowFlagSet() as the nmiFlags parameter and returned by
// SysCtl_getNMIFlagStatus() and SysCtl_getNMIShadowFlagStatus().
//
//*****************************************************************************
#define SYSCTL_NMI_NMIINT     0x1U    //!<  NMI Interrupt Flag
#define SYSCTL_NMI_CLOCKFAIL  0x2U    //!<  Clock Fail Interrupt Flag
#define SYSCTL_NMI_RAMUNCERR  0x4U    //!<  RAM Uncorrectable Error NMI Flag
#define SYSCTL_NMI_FLUNCERR   0x8U    //!<  Flash Uncorrectable Error NMI Flag
#define SYSCTL_NMI_PIEVECTERR 0x40U   //!<  PIE Vector Fetch Error Flag
#define SYSCTL_NMI_CLBNMI     0x100U  //!<  Configurable Logic Block NMI Flag
#define SYSCTL_NMI_SWERR      0x2000U //!<  SW Error Force NMI Flag

//*****************************************************************************
// The following are values that can be passed to the SysCtl_clearResetCause()
// API as rstCauses or returned by the SysCtl_getResetCause() API.
//*****************************************************************************
#define SYSCTL_CAUSE_POR      0x00000001U //!< Power-on reset
#define SYSCTL_CAUSE_XRS      0x00000002U //!< External reset pin
#define SYSCTL_CAUSE_WDRS     0x00000004U //!< Watchdog reset
#define SYSCTL_CAUSE_NMIWDRS  0x00000008U //!< NMI watchdog reset
#define SYSCTL_CAUSE_SCCRESET 0x00000100U //!< SCCRESETn by DCSM
//*****************************************************************************
// The following values define the adcsocSrc parameter for
// SysCtl_enableExtADCSOCSource() and SysCtl_disableExtADCSOCSource().
//*****************************************************************************
#define SYSCTL_ADCSOC_SRC_PWM1SOCA 0x1U      //!< ePWM1 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM2SOCA 0x2U      //!< ePWM2 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM3SOCA 0x4U      //!< ePWM3 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM4SOCA 0x8U      //!< ePWM4 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM5SOCA 0x10U     //!< ePWM5 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM6SOCA 0x20U     //!< ePWM6 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM7SOCA 0x40U     //!< ePWM7 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM8SOCA 0x80U     //!< ePWM8 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM1SOCB 0x10000U  //!< ePWM1 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM2SOCB 0x20000U  //!< ePWM2 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM3SOCB 0x40000U  //!< ePWM3 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM4SOCB 0x80000U  //!< ePWM4 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM5SOCB 0x100000U //!< ePWM5 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM6SOCB 0x200000U //!< ePWM6 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM7SOCB 0x400000U //!< ePWM7 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM8SOCB 0x800000U //!< ePWM8 SOCB for ADCSOCBO

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_enablePeripheral()
//! and SysCtl_disablePeripheral() as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_PERIPH_CLK_CPU1        = 0x0000, //!< CPU1 clock
    SYSCTL_PERIPH_CLK_DMA         = 0x0200, //!< DMA clock
    SYSCTL_PERIPH_CLK_CPU0_TIMER0 = 0x0500, //!< CPU0 TIMER0 clock
    SYSCTL_PERIPH_CLK_CPU0_TIMER1 = 0x0600, //!< CPU0 TIMER1 clock
    SYSCTL_PERIPH_CLK_CPU0_TIMER2 = 0x0700, //!< CPU0 TIMER2 clock
    SYSCTL_PERIPH_CLK_CPU1_TIMER0 = 0x0800, //!< CPU1 TIMER0 clock
    SYSCTL_PERIPH_CLK_CPU1_TIMER1 = 0x0900, //!< CPU1 TIMER1 clock
    SYSCTL_PERIPH_CLK_CPU1_TIMER2 = 0x0A00, //!< CPU1 TIMER2 clock
    SYSCTL_PERIPH_CLK_TBCLKSYNC   = 0x1200, //!< TBCLKSYNC clock
    SYSCTL_PERIPH_CLK_EPWM1       = 0x0001, //!< EPWM1 clock
    SYSCTL_PERIPH_CLK_EPWM2       = 0x0101, //!< EPWM2 clock
    SYSCTL_PERIPH_CLK_EPWM3       = 0x0201, //!< EPWM3 clock
    SYSCTL_PERIPH_CLK_EPWM4       = 0x0301, //!< EPWM4 clock
    SYSCTL_PERIPH_CLK_EPWM5       = 0x0401, //!< EPWM5 clock
    SYSCTL_PERIPH_CLK_EPWM6       = 0x0501, //!< EPWM6 clock
    SYSCTL_PERIPH_CLK_EPWM7       = 0x0601, //!< EPWM7 clock
    SYSCTL_PERIPH_CLK_EPWM8       = 0x0701, //!< EPWM8 clock
    SYSCTL_PERIPH_CLK_EPWM9       = 0x0801, //!< EPWM9 clock
    SYSCTL_PERIPH_CLK_EPWM10      = 0x0901, //!< EPWM10 clock
    SYSCTL_PERIPH_CLK_EPWM11      = 0x0A01, //!< EPWM11 clock
    SYSCTL_PERIPH_CLK_EPWM12      = 0x0B01, //!< EPWM12 clock
    SYSCTL_PERIPH_CLK_ECAP1       = 0x0002, //!< ECAP1 clock
    SYSCTL_PERIPH_CLK_ECAP2       = 0x0102, //!< ECAP2 clock
    SYSCTL_PERIPH_CLK_ECAP3       = 0x0202, //!< ECAP3 clock
    SYSCTL_PERIPH_CLK_ECAP4       = 0x0302, //!< ECAP4 clock
    SYSCTL_PERIPH_CLK_ECAP5       = 0x0402, //!< ECAP5 clock
    SYSCTL_PERIPH_CLK_ECAP6       = 0x0502, //!< ECAP6 clock
    SYSCTL_PERIPH_CLK_ECAP7       = 0x0602, //!< ECAP7 clock
    SYSCTL_PERIPH_CLK_EQEP1       = 0x0003, //!< EQEP1 clock
    SYSCTL_PERIPH_CLK_EQEP2       = 0x0103, //!< EQEP2 clock
    SYSCTL_PERIPH_CLK_SD1         = 0x0004, //!< SD1 clock
    SYSCTL_PERIPH_CLK_SCIA        = 0x0005, //!< SCI_A clock
    SYSCTL_PERIPH_CLK_SCIB        = 0x0105, //!< SCI_B clock
    SYSCTL_PERIPH_CLK_SCIC        = 0x0205, //!< SCI_B clock
    SYSCTL_PERIPH_CLK_SCID        = 0x0305, //!< SCI_B clock
    SYSCTL_PERIPH_CLK_SPIA        = 0x0006, //!< SPI_A clock
    SYSCTL_PERIPH_CLK_SPIB        = 0x0106, //!< SPI_B clock
    SYSCTL_PERIPH_CLK_SPIC        = 0x0206, //!< SPI_B clock
    SYSCTL_PERIPH_CLK_SPID        = 0x0306, //!< SPI_B clock
    SYSCTL_PERIPH_CLK_I2CA        = 0x0007, //!< I2C_A clock
    SYSCTL_PERIPH_CLK_PMBUSA      = 0x0107, //!< PMBUS_A clock
    SYSCTL_PERIPH_CLK_CANA        = 0x0008, //!< CAN_A clock
    SYSCTL_PERIPH_CLK_CANB        = 0x0108, //!< CAN_B clock
    SYSCTL_PERIPH_CLK_ADCA        = 0x0009, //!< ADC_A clock
    SYSCTL_PERIPH_CLK_ADCB        = 0x0109, //!< ADC_B clock
    SYSCTL_PERIPH_CLK_ADCC        = 0x0209, //!< ADC_C clock
    SYSCTL_PERIPH_CLK_ADCA_HR     = 0x0609, //!< ADC_A_HR clock
    SYSCTL_PERIPH_CLK_ADCB_HR     = 0x0709, //!< ADC_B_HR clock
    SYSCTL_PERIPH_CLK_ADCC_HR     = 0x0809, //!< ADC_C_HR clock
    SYSCTL_PERIPH_CLK_CMPSS1      = 0x000A, //!< CMPSS1 clock
    SYSCTL_PERIPH_CLK_CMPSS2      = 0x010A, //!< CMPSS2 clock
    SYSCTL_PERIPH_CLK_CMPSS3      = 0x020A, //!< CMPSS3 clock
    SYSCTL_PERIPH_CLK_CMPSS4      = 0x030A, //!< CMPSS4 clock
    SYSCTL_PERIPH_CLK_CMPSS5      = 0x040A, //!< CMPSS5 clock
    SYSCTL_PERIPH_CLK_CMPSS6      = 0x050A, //!< CMPSS6 clock
    SYSCTL_PERIPH_CLK_CMPSS7      = 0x060A, //!< CMPSS7 clock
    SYSCTL_PERIPH_CLK_PGA1        = 0x000B, //!< PGA1 clock
    SYSCTL_PERIPH_CLK_PGA2        = 0x010B, //!< PGA2 clock
    SYSCTL_PERIPH_CLK_PGA3        = 0x020B, //!< PGA3 clock
    SYSCTL_PERIPH_CLK_PGA4        = 0x030B, //!< PGA4 clock
    SYSCTL_PERIPH_CLK_PGA5        = 0x040B, //!< PGA5 clock
    SYSCTL_PERIPH_CLK_PGA6        = 0x050B, //!< PGA6 clock
    SYSCTL_PERIPH_CLK_PGA7        = 0x060B, //!< PGA7 clock
    SYSCTL_PERIPH_CLK_DACA        = 0x000C, //!< DAC_A clock
    SYSCTL_PERIPH_CLK_DACB        = 0x010C, //!< DAC_B clock
    SYSCTL_PERIPH_CLK_LINA        = 0x000D, //!< LIN_A clock
    SYSCTL_PERIPH_CLK_XINTF       = 0x010D, //!< XINTF clock
} SysCtl_PeripheralPCLOCKCR;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_resetPeripheral() as
//! the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_PERIPH_RES_CPU1    = 0x0000, //!< CPU1 reset
    SYSCTL_PERIPH_RES_EPWM1   = 0x0001, //!< EPWM1 reset
    SYSCTL_PERIPH_RES_EPWM2   = 0x0101, //!< EPWM2 reset
    SYSCTL_PERIPH_RES_EPWM3   = 0x0201, //!< EPWM3 reset
    SYSCTL_PERIPH_RES_EPWM4   = 0x0301, //!< EPWM4 reset
    SYSCTL_PERIPH_RES_EPWM5   = 0x0401, //!< EPWM5 reset
    SYSCTL_PERIPH_RES_EPWM6   = 0x0501, //!< EPWM6 reset
    SYSCTL_PERIPH_RES_EPWM7   = 0x0601, //!< EPWM7 reset
    SYSCTL_PERIPH_RES_EPWM8   = 0x0701, //!< EPWM8 reset
    SYSCTL_PERIPH_RES_EPWM9   = 0x0801, //!< EPWM9 reset
    SYSCTL_PERIPH_RES_EPWM10  = 0x0901, //!< EPWM10 reset
    SYSCTL_PERIPH_RES_EPWM11  = 0x0A01, //!< EPWM11 reset
    SYSCTL_PERIPH_RES_EPWM12  = 0x0B01, //!< EPWM12 reset
    SYSCTL_PERIPH_RES_ECAP1   = 0x0002, //!< ECAP1 reset
    SYSCTL_PERIPH_RES_ECAP2   = 0x0102, //!< ECAP2 reset
    SYSCTL_PERIPH_RES_ECAP3   = 0x0202, //!< ECAP3 reset
    SYSCTL_PERIPH_RES_ECAP4   = 0x0302, //!< ECAP4 reset
    SYSCTL_PERIPH_RES_ECAP5   = 0x0402, //!< ECAP5 reset
    SYSCTL_PERIPH_RES_ECAP6   = 0x0502, //!< ECAP6 reset
    SYSCTL_PERIPH_RES_ECAP7   = 0x0602, //!< ECAP7 reset
    SYSCTL_PERIPH_RES_EQEP1   = 0x0003, //!< EQEP1 reset
    SYSCTL_PERIPH_RES_EQEP2   = 0x0103, //!< EQEP2 reset
    SYSCTL_PERIPH_RES_SD1     = 0x0004, //!< SD1 reset
    SYSCTL_PERIPH_RES_SCIA    = 0x0005, //!< SCI_A reset
    SYSCTL_PERIPH_RES_SCIB    = 0x0105, //!< SCI_B reset
    SYSCTL_PERIPH_RES_SPIA    = 0x0006, //!< SPI_A reset
    SYSCTL_PERIPH_RES_SPIB    = 0x0106, //!< SPI_B reset
    SYSCTL_PERIPH_RES_I2CA    = 0x0007, //!< I2C_A reset
    SYSCTL_PERIPH_RES_PMBUSA  = 0x0107, //!< PMBUS_A reset
    SYSCTL_PERIPH_RES_CANA    = 0x0008, //!< CAN_A reset
    SYSCTL_PERIPH_RES_CANB    = 0x0108, //!< CAN_B reset
    SYSCTL_PERIPH_RES_ADCA    = 0x0009, //!< ADC_A reset
    SYSCTL_PERIPH_RES_ADCB    = 0x0109, //!< ADC_B reset
    SYSCTL_PERIPH_RES_ADCC    = 0x0209, //!< ADC_C reset
    SYSCTL_PERIPH_RES_ADCA_HR = 0x0609, //!< ADC_A_HR reset
    SYSCTL_PERIPH_RES_ADCB_HR = 0x0709, //!< ADC_B_HR reset
    SYSCTL_PERIPH_RES_ADCC_HR = 0x0809, //!< ADC_C_HR reset
    SYSCTL_PERIPH_RES_CMPSS1  = 0x000A, //!< CMPSS1 reset
    SYSCTL_PERIPH_RES_CMPSS2  = 0x010A, //!< CMPSS2 reset
    SYSCTL_PERIPH_RES_CMPSS3  = 0x020A, //!< CMPSS3 reset
    SYSCTL_PERIPH_RES_CMPSS4  = 0x030A, //!< CMPSS4 reset
    SYSCTL_PERIPH_RES_CMPSS5  = 0x040A, //!< CMPSS5 reset
    SYSCTL_PERIPH_RES_CMPSS6  = 0x050A, //!< CMPSS6 reset
    SYSCTL_PERIPH_RES_CMPSS7  = 0x060A, //!< CMPSS7 reset
    SYSCTL_PERIPH_RES_PGA1    = 0x000B, //!< PGA1 reset
    SYSCTL_PERIPH_RES_PGA2    = 0x010B, //!< PGA2 reset
    SYSCTL_PERIPH_RES_PGA3    = 0x020B, //!< PGA3 reset
    SYSCTL_PERIPH_RES_PGA4    = 0x030B, //!< PGA4 reset
    SYSCTL_PERIPH_RES_PGA5    = 0x040B, //!< PGA5 reset
    SYSCTL_PERIPH_RES_PGA6    = 0x050B, //!< PGA6 reset
    SYSCTL_PERIPH_RES_PGA7    = 0x060B, //!< PGA7 reset
    SYSCTL_PERIPH_RES_DACA    = 0x000C, //!< DAC_A reset
    SYSCTL_PERIPH_RES_DACB    = 0x010C, //!< DAC_B reset
    SYSCTL_PERIPH_RES_LINA    = 0x000D, //!< LIN_A reset
    SYSCTL_PERIPH_RES_XINTF   = 0x010D, //!< XINTF reset
} SysCtl_PeripheralSOFTPRES;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogResetPeriod() as the \e period parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_WD_PERIOD_2_16 = 0,
    SYSCTL_WD_PERIOD_2_17 = 1,
    SYSCTL_WD_PERIOD_2_18 = 2,
    SYSCTL_WD_PERIOD_2_19 = 3,
    SYSCTL_WD_PERIOD_2_20 = 4,
    SYSCTL_WD_PERIOD_2_21 = 5,
    SYSCTL_WD_PERIOD_2_22 = 6,
    SYSCTL_WD_PERIOD_2_23 = 7,
    SYSCTL_WD_PERIOD_2_24 = 8,
    SYSCTL_WD_PERIOD_2_25 = 9,
    SYSCTL_WD_PERIOD_2_26 = 10,
    SYSCTL_WD_PERIOD_2_27 = 11,
    SYSCTL_WD_PERIOD_2_28 = 12,
    SYSCTL_WD_PERIOD_2_29 = 13,
    SYSCTL_WD_PERIOD_2_30 = 14,
    SYSCTL_WD_PERIOD_2_31 = 15,
} SysCtl_WDResetPeriod;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogMode() as the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    //! Watchdog can generate a reset signal
    SYSCTL_WD_MODE_RESET,
    //! Watchdog can generate an interrupt signal; reset signal is disabled
    SYSCTL_WD_MODE_INTERRUPT
} SysCtl_WDMode;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_setLowSpeedClock() as
//! the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_LSPCLK_PRESCALE_1  = 0, //!< LSPCLK = SYSCLK / 1
    SYSCTL_LSPCLK_PRESCALE_2  = 1, //!< LSPCLK = SYSCLK / 2
    SYSCTL_LSPCLK_PRESCALE_4  = 2, //!< LSPCLK = SYSCLK / 4 (default)
    SYSCTL_LSPCLK_PRESCALE_6  = 3, //!< LSPCLK = SYSCLK / 6
    SYSCTL_LSPCLK_PRESCALE_8  = 4, //!< LSPCLK = SYSCLK / 8
    SYSCTL_LSPCLK_PRESCALE_10 = 5, //!< LSPCLK = SYSCLK / 10
    SYSCTL_LSPCLK_PRESCALE_12 = 6, //!< LSPCLK = SYSCLK / 12
    SYSCTL_LSPCLK_PRESCALE_14 = 7  //!< LSPCLK = SYSCLK / 14
} SysCtl_LSPCLKPrescaler;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_selectClockOutSource() as the \e source parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_CLOCKOUT_PLLSYS  = 0U, //!< PLL System Clock post SYSCLKDIV
    SYSCTL_CLOCKOUT_PLLRAW  = 1U, //!< PLL Raw Clock
    SYSCTL_CLOCKOUT_SYSCLK  = 2U, //!< CPU System Clock
    SYSCTL_CLOCKOUT_INTOSC1 = 5U, //!< Internal Oscillator 1
    SYSCTL_CLOCKOUT_INTOSC2 = 6U, //!< Internal Oscillator 2
    SYSCTL_CLOCKOUT_XTALOSC = 7U, //!< External Oscillator
} SysCtl_ClockOut;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setExternalOscMode() as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_XTALMODE_CRYSTAL = 1U, //!< XTAL Oscillator Crystal Mode
    SYSCTL_XTALMODE_SINGLE  = 2U  //!< XTAL Oscillator Single-Ended Mode
} SysCtl_ExternalOscMode;

//*****************************************************************************
//
//! The following values define the \e syncInput parameter for
//! SysCtl_setSyncInputConfig().
//
//*****************************************************************************
typedef enum
{
    SYSCTL_SYNC_IN_EPWM4  = 0,  //!< Sync input to EPWM4
    SYSCTL_SYNC_IN_EPWM7  = 3,  //!< Sync input to EPWM7
    SYSCTL_SYNC_IN_EPWM10 = 6,  //!< Sync input to EPWM10
    SYSCTL_SYNC_IN_ECAP1  = 9,  //!< Sync input to ECAP1
    SYSCTL_SYNC_IN_ECAP4  = 12, //!< Sync input to ECAP4
    SYSCTL_SYNC_IN_ECAP6  = 15, //!< Sync input to ECAP6
    SYSCTL_SYNC_IN_EPWM1  = 29  //!< Sync input to EPWM1
} SysCtl_SyncInput;

//*****************************************************************************
//
//! The following values define the \e syncSrc parameter for
//! SysCtl_setSyncInputConfig(). Note that some of these are only valid for
//! certain values of \e syncInput. See device technical reference manual for
//! info on time-base counter synchronization for details.
//
//*****************************************************************************
typedef enum
{
    //! EPWM1SYNCOUT
    SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT = 0,
    //! EPWM4SYNCOUT
    SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT = 1,
    //! EPWM7SYNCOUT
    SYSCTL_SYNC_IN_SRC_EPWM7SYNCOUT = 2,
    //! ECAP1SYNCOUT
    SYSCTL_SYNC_IN_SRC_ECAP1SYNCOUT = 4,
    //! EXTSYNCIN1--Valid for all values of syncInput
    SYSCTL_SYNC_IN_SRC_EXTSYNCIN1 = 5,
    //! EXTSYNCIN2--Valid for all values of syncInput
    SYSCTL_SYNC_IN_SRC_EXTSYNCIN2 = 6,
} SysCtl_SyncInputSource;

//*****************************************************************************
//
//! The following values define the \e syncSrc parameter for
//! SysCtl_setSyncOutputConfig().
//
//*****************************************************************************
typedef enum
{
    SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT, //!< EPWM1SYNCOUT --> EXTSYNCOUT
    SYSCTL_SYNC_OUT_SRC_EPWM4SYNCOUT, //!< EPWM4SYNCOUT --> EXTSYNCOUT
    SYSCTL_SYNC_OUT_SRC_EPWM7SYNCOUT, //!< EPWM7SYNCOUT --> EXTSYNCOUT
    SYSCTL_SYNC_OUT_SRC_EPWM10SYNCOUT //!< EPWM10SYNCOUT --> EXTSYNCOUT

} SysCtl_SyncOutputSource;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setXClk() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_XCLKOUT_DIV_1 = 0, //!<  XCLKOUT =  XCLKOUT / 1
    SYSCTL_XCLKOUT_DIV_2 = 1, //!<  XCLKOUT =  XCLKOUT / 2
    SYSCTL_XCLKOUT_DIV_4 = 2, //!<  XCLKOUT =  XCLKOUT / 4
    SYSCTL_XCLKOUT_DIV_8 = 3  //!<  XCLKOUT =  XCLKOUT / 8

} SysCtl_XClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setCputimer2Clk() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_TMR2CLKPRESCALE_1, //!<  Cputimer2 clock =  Cputimer2 clock / 1
    SYSCTL_TMR2CLKPRESCALE_2, //!<  Cputimer2 clock =  Cputimer2 clock / 2
    SYSCTL_TMR2CLKPRESCALE_4, //!<  Cputimer2 clock =  Cputimer2 clock / 4
    SYSCTL_TMR2CLKPRESCALE_8, //!<  Cputimer2 clock =  Cputimer2 clock / 8
    SYSCTL_TMR2CLKPRESCALE_16 //!<  Cputimer2 clock =  Cputimer2 clock / 16

} SysCtl_Cputimer2ClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_setCputimer2Clk()
//! as \e source parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_TMR2CLKSRCSEL_SYSCLK  = 0U, //!< System Clock
    SYSCTL_TMR2CLKSRCSEL_INTOSC1 = 1U, //!< Internal Oscillator 1
    SYSCTL_TMR2CLKSRCSEL_INTOSC2 = 2U, //!< Internal Oscillator 2
    SYSCTL_TMR2CLKSRCSEL_XTAL    = 3U, //!< Crystal oscillator
} SysCtl_Cputimer2ClkSource;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_selectCPUForPeripheralInstance() as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_CPUSEL_EPWM1  = 0x0001, //!< EPWM1 reset
    SYSCTL_CPUSEL_EPWM2  = 0x0101, //!< EPWM2 reset
    SYSCTL_CPUSEL_EPWM3  = 0x0201, //!< EPWM3 reset
    SYSCTL_CPUSEL_EPWM4  = 0x0301, //!< EPWM4 reset
    SYSCTL_CPUSEL_EPWM5  = 0x0401, //!< EPWM5 reset
    SYSCTL_CPUSEL_EPWM6  = 0x0501, //!< EPWM6 reset
    SYSCTL_CPUSEL_EPWM7  = 0x0601, //!< EPWM7 reset
    SYSCTL_CPUSEL_EPWM8  = 0x0701, //!< EPWM8 reset
    SYSCTL_CPUSEL_ECAP1  = 0x0002, //!< ECAP1 reset
    SYSCTL_CPUSEL_ECAP2  = 0x0102, //!< ECAP2 reset
    SYSCTL_CPUSEL_ECAP3  = 0x0202, //!< ECAP3 reset
    SYSCTL_CPUSEL_ECAP4  = 0x0302, //!< ECAP4 reset
    SYSCTL_CPUSEL_ECAP5  = 0x0402, //!< ECAP5 reset
    SYSCTL_CPUSEL_ECAP6  = 0x0502, //!< ECAP6 reset
    SYSCTL_CPUSEL_ECAP7  = 0x0602, //!< ECAP7 reset
    SYSCTL_CPUSEL_EQEP1  = 0x0003, //!< EQEP1 reset
    SYSCTL_CPUSEL_EQEP2  = 0x0103, //!< EQEP2 reset
    SYSCTL_CPUSEL_SD1    = 0x0004, //!< SD1 reset
    SYSCTL_CPUSEL_SCIA   = 0x0005, //!< SCI_A reset
    SYSCTL_CPUSEL_SCIB   = 0x0105, //!< SCI_B reset
    SYSCTL_CPUSEL_SPIA   = 0x0006, //!< SPI_A reset
    SYSCTL_CPUSEL_SPIB   = 0x0106, //!< SPI_B reset
    SYSCTL_CPUSEL_I2CA   = 0x0007, //!< I2C_A reset
    SYSCTL_CPUSEL_I2CB   = 0x0107, //!< I2C_B reset
    SYSCTL_CPUSEL_CANA   = 0x0008, //!< CAN_A reset
    SYSCTL_CPUSEL_CANB   = 0x0108, //!< CAN_B reset
    SYSCTL_CPUSEL_ADCA   = 0x0009, //!< ADC_A reset
    SYSCTL_CPUSEL_ADCB   = 0x0109, //!< ADC_B reset
    SYSCTL_CPUSEL_ADCC   = 0x0209, //!< ADC_C reset
    SYSCTL_CPUSEL_CMPSS1 = 0x000A, //!< CMPSS1 reset
    SYSCTL_CPUSEL_CMPSS2 = 0x010A, //!< CMPSS2 reset
    SYSCTL_CPUSEL_CMPSS3 = 0x020A, //!< CMPSS3 reset
    SYSCTL_CPUSEL_CMPSS4 = 0x030A, //!< CMPSS4 reset
    SYSCTL_CPUSEL_CMPSS5 = 0x040A, //!< CMPSS5 reset
    SYSCTL_CPUSEL_CMPSS6 = 0x050A, //!< CMPSS6 reset
    SYSCTL_CPUSEL_CMPSS7 = 0x060A, //!< CMPSS7 reset
    SYSCTL_CPUSEL_PGA1   = 0x000B, //!< PGA1 reset
    SYSCTL_CPUSEL_PGA2   = 0x010B, //!< PGA2 reset
    SYSCTL_CPUSEL_PGA3   = 0x020B, //!< PGA3 reset
    SYSCTL_CPUSEL_PGA4   = 0x030B, //!< PGA4 reset
    SYSCTL_CPUSEL_PGA5   = 0x040B, //!< PGA5 reset
    SYSCTL_CPUSEL_PGA6   = 0x050B, //!< PGA6 reset
    SYSCTL_CPUSEL_PGA7   = 0x060B, //!< PGA7 reset
    SYSCTL_CPUSEL_DACA   = 0x000C, //!< DAC_A reset
    SYSCTL_CPUSEL_DACB   = 0x010C, //!< DAC_B reset
    SYSCTL_CPUSEL_LINA   = 0x000D, //!< LIN_A reset
} SysCtl_CPUSelPeriphInstance;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_selectCPUForPeripheral() as \e cpuInst parameter.
//
//*****************************************************************************
typedef enum
{
    //! Connect the peripheral (indicated by SysCtl_CPUSelPeripheral) to CPU0
    SYSCTL_CPUSEL_CPU0 = 0x0U,
    //! Connect the peripheral (indicated by SysCtl_CPUSelPeripheral) to CPU1
    SYSCTL_CPUSEL_CPU1 = 0x1U
} SysCtl_CPUSel;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Wrapper function for Device_cal function
//!
//! \param None
//!
//! This is a wrapper function for the Device_cal function available in the OTP
//! memory.
//! The function saves and restores the core registers which are being
//! used by the Device_cal function
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_deviceCal(void)
{
    // Save the core registers used by Device_cal function in the stack
    SYSCTL_DEVICECAL_CONTEXT_SAVE;
    // Call the Device_cal function
    // Device_cal();
    // Restore the core registers
    SYSCTL_DEVICECAL_CONTEXT_RESTORE;
}

//*****************************************************************************
//
//! Resets a peripheral
//!
//! \param peripheral is the peripheral to reset.
//!
//! This function uses the SOFTPRESx registers to reset a specified peripheral.
//! Module registers will be returned to their reset states.
//!
//! \note This includes registers containing trim values.The peripheral
//! software reset needed by CPU2 can be communicated to CPU1 via
//! IPC for all shared peripherals.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_resetPeripheral(SysCtl_PeripheralSOFTPRES peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    // Decode the peripheral variable.
    regIndex = (uint16_t)4U * ((uint16_t)peripheral & (uint16_t)0x001FU);
    bitIndex = ((uint16_t)peripheral & 0x1F00U) >> 0x0008U;

    EALLOW;
    // Sets the appropriate reset bit and then clears it.
    HWREG(DEVCFG_BASE + 0x40U + regIndex) |= (1UL << bitIndex);
    HWREG(DEVCFG_BASE + 0x40U + regIndex) &= ~(1UL << bitIndex);
    // Call Device_cal function
    /* if ((((uint16_t)peripheral & SYSCTL_PERIPH_REG_M) == 0xDU) || // ADCx
        (((uint16_t)peripheral & SYSCTL_PERIPH_REG_M) == 0xFU) || // PGAx
        (((uint16_t)peripheral & SYSCTL_PERIPH_REG_M) == 0x10U)   // DACx
    )
    {
        SysCtl_deviceCal();
    } */
    EDIS;
}

//*****************************************************************************
//
//! Configures whether a peripheral is connected to CPU1 or CPU2.
//!
//! \param peripheral is the peripheral for which CPU needs to be configured.
//! \param cpuInst is the CPU to which the peripheral instance need to be
//!                connected.
//!
//! The \e peripheral parameter can have one enumerated value from
//! SysCtl_CPUSelPeriphInstance
//!
//! The \e cpuInst parameter can have one the following values:
//! - \b SYSCTL_CPUSEL_CPU1 - to connect to CPU1
//! - \b SYSCTL_CPUSEL_CPU2 - to connect to CPU2
//!
//! \note This API is applicable only for the CPU1 subsystem.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_selectCPUForPeripheralInstance(
    SysCtl_CPUSelPeriphInstance peripheral, SysCtl_CPUSel cpuInst)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Identify the register index and bit position
    //
    regIndex = (uint16_t)4U * ((uint16_t)peripheral & (uint16_t)0x001FU);
    bitIndex = ((uint16_t)peripheral & 0x1F00U) >> 0x0008U;

    EALLOW;

    //
    // Configure the CPU owner for the specified peripheral instance
    //
    HWREG(DEVCFG_BASE + 0x140U + regIndex)
        = (HWREG(DEVCFG_BASE + 0x140U + regIndex) & ~(1UL << bitIndex))
          | ((uint32_t)cpuInst << bitIndex);

    EDIS;
}

//*****************************************************************************
//
//! Enables a peripheral.
//!
//! \param peripheral is the peripheral to enable.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! \note Note that there should be atleast 5 cycles delay between enabling the
//! peripheral clock and accessing the peripheral registers. The delay should be
//! added by the user if the peripheral is accessed immediately after this
//! function call.
//! Use asm(" RPT #5 || NOP"); to add 5 cycle delay post this function call.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_enablePeripheral(SysCtl_PeripheralPCLOCKCR peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    // Decode the peripheral variable.
    regIndex = (uint16_t)4U * ((uint16_t)peripheral & (uint16_t)0x001FU);
    bitIndex = ((uint16_t)peripheral & 0x1F00U) >> 0x0008U;

    EALLOW;
    // Turn on the module clock.
    HWREG(CPUSYS_BASE + regIndex) |= (1UL << bitIndex);
    EDIS;
}

//*****************************************************************************
//
//! Disables a peripheral.
//!
//! \param peripheral is the peripheral to disable.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_disablePeripheral(SysCtl_PeripheralPCLOCKCR peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    // Decode the peripheral variable.
    regIndex = (uint16_t)4U * ((uint16_t)peripheral & (uint16_t)0x001FU);
    bitIndex = ((uint16_t)peripheral & 0x1F00U) >> 0x0008U;

    EALLOW;
    // Turn off the module clock.
    HWREG(CPUSYS_BASE + regIndex) &= ~(1UL << bitIndex);
    EDIS;
}

//*****************************************************************************
//
//! Resets the device.
//!
//! This function performs a watchdog reset of the device.
//!
//! \return This function does not return.
//
//*****************************************************************************
static inline void SysCtl_resetDevice(void)
{
    // Write an incorrect check value to the watchdog control register
    // This will cause a device reset
    EALLOW;

    // Enable the watchdog
    // HWREGH(WD_BASE + SYSCTL_O_WDCR) = SYSCTL_WD_CHKBITS;

    // Write a bad check value
    // HWREGH(WD_BASE + SYSCTL_O_WDCR) = 0U;

    EDIS;

    // The device should have reset, so this should never be reached.  Just in
    // case, loop forever.
    while ((uint32_t)1)
    { }
}

//*****************************************************************************
//
//! Gets the reason for a reset.
//!
//! This function will return the reason(s) for a reset.  Since the reset
//! reasons are sticky until either cleared by software or an external reset,
//! multiple reset reasons may be returned if multiple resets have occurred.
//! The reset reason will be a logical OR of
//! - \b SYSCTL_CAUSE_POR - Power-on reset
//! - \b SYSCTL_CAUSE_XRS - External reset pin
//! - \b SYSCTL_CAUSE_WDRS - Watchdog reset
//! - \b SYSCTL_CAUSE_NMIWDRS - NMI watchdog reset
//! - \b SYSCTL_CAUSE_SCCRESET - SCCRESETn reset from DCSM
//!
//! \note If you re-purpose the reserved boot ROM RAM, the POR and XRS reset
//! statuses won't be accurate.
//!
//! \return Returns the reason(s) for a reset.
//
//*****************************************************************************
static inline uint32_t SysCtl_getResetCause(void)
{
    /* uint32_t resetCauses;

    // Read CPU reset register
    resetCauses = HWREG(CPUSYS_BASE + SYSCTL_O_RESC)
                  & ((uint32_t)SYSCTL_RESC_POR | (uint32_t)SYSCTL_RESC_XRSN |
    (uint32_t)SYSCTL_RESC_WDRSN | (uint32_t)SYSCTL_RESC_NMIWDRSN | (uint32_t)SYSCTL_RESC_SCCRESETN);

    // Set POR and XRS Causes from boot ROM Status
    if ((HWREG(SYSCTL_BOOT_ROM_STATUS) & (uint32_t)SYSCTL_BOOT_ROM_POR) ==
    (uint32_t)SYSCTL_BOOT_ROM_POR)
    {
        resetCauses |= SYSCTL_RESC_POR;
    }
    if ((HWREG(SYSCTL_BOOT_ROM_STATUS) & (uint32_t)SYSCTL_BOOT_ROM_XRS) ==
    (uint32_t)SYSCTL_BOOT_ROM_XRS)
    {
        resetCauses |= SYSCTL_RESC_XRSN;
    }

    // Return the reset reasons.
    return (resetCauses); */
    return 0;
}

//*****************************************************************************
//
//! Clears reset reasons.
//!
//! \param rstCauses are the reset causes to be cleared; must be a logical
//! OR of
//! - \b SYSCTL_CAUSE_POR - Power-on reset
//! - \b SYSCTL_CAUSE_XRS - External reset pin
//! - \b SYSCTL_CAUSE_WDRS - Watchdog reset
//! - \b SYSCTL_CAUSE_NMIWDRS - NMI watchdog reset
//! - \b SYSCTL_CAUSE_SCCRESET - SCCRESETn reset from DCSM
//!
//! This function clears the specified sticky reset reasons.  Once cleared,
//! another reset for the same reason can be detected, and a reset for a
//! different reason can be distinguished (instead of having two reset causes
//! set).  If the reset reason is used by an application, all reset causes
//! should be cleared after they are retrieved with SysCtl_getResetCause().
//!
//! \note Some reset causes are cleared by the boot ROM.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_clearResetCause(uint32_t rstCauses)
{
    // Clear the given reset reasons.
    CpuSysRegs.RESCCLR.all = rstCauses;
}

//*****************************************************************************
//
//! Sets the low speed peripheral clock rate prescaler.
//!
//! \param prescaler is the LSPCLK rate relative to SYSCLK
//!
//! This function configures the clock rate of the low speed peripherals. The
//! \e prescaler parameter is the value by which the SYSCLK rate is divided to
//! get the LSPCLK rate. For example, a \e prescaler of
//! \b SYSCTL_LSPCLK_PRESCALE_4 will result in a LSPCLK rate that is a quarter
//! of the SYSCLK rate.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_setLowSpeedClock(SysCtl_LSPCLKPrescaler prescaler)
{
    EALLOW;
    ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = prescaler;
    EDIS;
}

//*****************************************************************************
//
//! Selects a clock source to mux to an external GPIO pin (XCLKOUT).
//!
//! \param source is the internal clock source to be configured.
//!
//! This function configures the specified clock source to be muxed to an
//! external clock out (XCLKOUT) GPIO pin. The \e source parameter may take a
//! value of one of the following values:
//! - \b SYSCTL_CLOCKOUT_PLLSYS
//! - \b SYSCTL_CLOCKOUT_PLLRAW
//! - \b SYSCTL_CLOCKOUT_SYSCLK
//! - \b SYSCTL_CLOCKOUT_INTOSC1
//! - \b SYSCTL_CLOCKOUT_INTOSC2
//! - \b SYSCTL_CLOCKOUT_XTALOSC
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_selectClockOutSource(SysCtl_ClockOut source)
{
    EALLOW;
    ClkCfgRegs.CLKSRCCTL3.bit.XCLKOUTSEL = source;
    EDIS;
}

//*****************************************************************************
//
//! Set the external oscillator mode.
//!
//! \param mode is the external oscillator mode to be configured.
//!
//! This function sets the external oscillator mode specified by the \e mode
//! parameter which may take one of two values:
//! - \b SYSCTL_XTALMODE_CRYSTAL - Crystal Mode
//! - \b SYSCTL_XTALMODE_SINGLE  - Single-Ended Mode
//!
//! \note The external oscillator must be powered off before this configuration
//! can be performed.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_setExternalOscMode(SysCtl_ExternalOscMode mode)
{
    EALLOW;
    switch (mode)
    {
        case SYSCTL_XTALMODE_CRYSTAL:
            // Set mode to Crystal
            ClkCfgRegs.XTALCR.bit.SE = 0;
            break;
        case SYSCTL_XTALMODE_SINGLE:
            // Set mode to Single-Ended
            ClkCfgRegs.XTALCR.bit.SE = 1;
            break;
        default:
            // Do nothing. Not a valid mode value.
            break;
    }
    EDIS;
}

//*****************************************************************************
//
//! Gets the external oscillator counter value.
//!
//! This function returns the X1 clock counter value. When the return value
//! reaches 0x3FF, it freezes. Before switching from INTOSC2 to an external
//! oscillator (XTAL), an application should call this function to make sure
//! the counter is saturated.
//!
//! \return Returns the value of the 10-bit X1 clock counter.
//
//*****************************************************************************
static inline uint16_t SysCtl_getExternalOscCounterValue(void)
{
    return ClkCfgRegs.X1CNT.bit.X1CNT;
}

//*****************************************************************************
//
//! Clears the external oscillator counter value.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_clearExternalOscCounterValue(void)
{
    ClkCfgRegs.X1CNT.bit.CLR = 1;
}

//*****************************************************************************
//
//! Turns on the specified oscillator sources.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function turns on the oscillator specified by the \e oscSource
//! parameter which may take a value of  \b SYSCTL_OSCSRC_XTAL
//! or \b SYSCTL_OSCSRC_OSC2.
//!
//! \note \b SYSCTL_OSCSRC_OSC1 is not a valid value for \e oscSource.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_turnOnOsc(uint32_t oscSource)
{
    ASSERT((oscSource == SYSCTL_OSCSRC_OSC2) || (oscSource == SYSCTL_OSCSRC_XTAL));

    EALLOW;
    switch (oscSource)
    {
        case SYSCTL_OSCSRC_OSC2:
            ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF = 0; // Turn on INTOSC2
            break;
        case SYSCTL_OSCSRC_XTAL:
            ClkCfgRegs.XTALCR.bit.OSCOFF = 0; // Turn on XTALOSC
            break;
        default:
            // Do nothing. Not a valid oscSource value.
            break;
    }
    EDIS;
}

//*****************************************************************************
//
//! Turns off the specified oscillator sources.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function turns off the oscillator specified by the \e oscSource
//! parameter which may take a value of  \b SYSCTL_OSCSRC_XTAL
//! or \b SYSCTL_OSCSRC_OSC2.
//!
//! \note \b SYSCTL_OSCSRC_OSC1 is not a valid value for \e oscSource.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_turnOffOsc(uint32_t oscSource)
{
    ASSERT((oscSource == SYSCTL_OSCSRC_OSC2) || (oscSource == SYSCTL_OSCSRC_XTAL));

    EALLOW;

    switch (oscSource)
    {
        case SYSCTL_OSCSRC_OSC2:
            // Turn off INTOSC2
            ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF = 1;
            break;
        case SYSCTL_OSCSRC_XTAL:
            // Turn off XTALOSC
            ClkCfgRegs.XTALCR.bit.OSCOFF = 1;
            break;
        default:
            // Do nothing. Not a valid oscSource value.
            break;
    }

    EDIS;
}

//*****************************************************************************
//
//! Enters IDLE mode.
//!
//! This function puts the device into IDLE mode. The CPU clock is gated while
//! all peripheral clocks are left running. Any enabled interrupt will wake the
//! CPU up from IDLE mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_enterIdleMode(void)
{
    EALLOW;
    CpuSysRegs.LPMCR.bit.LPMCR = 0;
    EDIS;
    IDLE;
}

//*****************************************************************************
//
//! Enters STANDBY mode.
//!
//! This function puts the device into IDLE mode. The CPU clock is gated while
//! all peripheral clocks are left running. Any enabled interrupt will wake the
//! CPU up from IDLE mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_enterStandbyMode(void)
{
    EALLOW;
    CpuSysRegs.LPMCR.bit.LPMCR = 1;
    EDIS;
    IDLE;
}

//*****************************************************************************
//
//! Enters HALT mode.
//!
//! This function puts the device into HALT mode. This will gate almost all
//! systems and clocks and allows for the power-down of oscillators and analog
//! blocks. The watchdog may be left clocked to produce a reset. See
//! SysCtl_enableWatchdogInHalt() to enable this. GPIOs should be
//! configured to wake the CPU subsystem. See SysCtl_enableLPMWakeupPin().
//!
//!
//! The CPU will receive an interrupt (WAKEINT) on wakeup.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_enterHaltMode(void)
{
    EALLOW;
    CpuSysRegs.LPMCR.bit.LPMCR = 2;
    // disable PLL and PLL clock
    // ClkCfgRegs.SYSPLLCTL1.all = 0; // do not need close pll always
    EDIS;
    IDLE;
}

//*****************************************************************************
//! Enables a pin to wake up the device from the following mode(s):
//!  - HALT
//!
//! \param pin is the identifying number of the pin.
//!
//! This function connects a pin to the LPM circuit, allowing an event on the
//! pin to wake up the device when when it is in following mode(s):
//!  - HALT
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin. Only GPIOs 0 through 63 are capable of
//! being connected to the LPM circuit.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_enableLPMWakeupPin(uint32_t pin)
{
    ASSERT(pin <= 63U); // Check the arguments.
    uint32_t pinMask = 1UL << (pin % 32U);

    EALLOW;
    if (pin < 32U)
        CpuSysRegs.GPIOLPMSEL0.all |= pinMask;
    else
        CpuSysRegs.GPIOLPMSEL1.all |= pinMask;
    EDIS;
}

//*****************************************************************************
//! Disables a pin to wake up the device from the following mode(s):
//!  - HALT
//!
//! \param pin is the identifying number of the pin.
//!
//! This function disconnects a pin to the LPM circuit, disallowing an event on
//! the pin to wake up the device when when it is in following mode(s):
//!  - HALT
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin. Only GPIOs 0 through 63 are valid.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_disableLPMWakeupPin(uint32_t pin)
{
    uint32_t pinMask;
    // Check the arguments.
    ASSERT(pin <= 63U);
    pinMask = 1UL << (pin % 32U);

    EALLOW;
    if (pin < 32U)
        CpuSysRegs.GPIOLPMSEL0.all &= ~pinMask;
    else
        CpuSysRegs.GPIOLPMSEL1.all &= ~pinMask;
    EDIS;
}

//*****************************************************************************
//
//! Enable the watchdog to run while in HALT mode.
//!
//! This function configures the watchdog to continue to run while in HALT
//! mode. Additionally, INTOSC1 and INTOSC2 are not powered down when the
//! system enters HALT mode. By default the watchdog is gated when the system
//! enters HALT.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_enableWatchdogInHalt(void)
{
    EALLOW;
    ClkCfgRegs.CLKSRCCTL1.bit.WDHALTI = 1;
    EDIS;
}

//*****************************************************************************
//
//! Disable the watchdog from running while in HALT mode.
//!
//! This function gates the watchdog when the system enters HALT mode. INTOSC1
//! and INTOSC2 will be powered down. This is the default behavior of the
//! device.
//!
//! \return None.
//
//*****************************************************************************
/*
static inline void SysCtl_disableWatchdogInHalt(void)
{
    EALLOW;

    //
    // Clear the watchdog HALT mode ignore bit.
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &= ~SYSCTL_CLKSRCCTL1_WDHALTI;

    EDIS;
}
*/
static inline void SysCtl_disableWatchdogInHalt(void)
{
    EALLOW;
    ClkCfgRegs.CLKSRCCTL1.bit.WDHALTI = 0;
    EDIS;
}

//*****************************************************************************
//
//! Configures whether the watchdog generates a reset or an interrupt signal.
//!
//! \param mode is a flag to select the watchdog mode.
//!
//! This function configures the action taken when the watchdog counter reaches
//! its maximum value. When the \e mode parameter is
//! \b SYSCTL_WD_MODE_INTERRUPT, the watchdog is enabled to generate a watchdog
//! interrupt signal and disables the generation of a reset signal. This will
//! allow the watchdog module to wake up the device from IDLE
//!
//! When the \e mode parameter is \b SYSCTL_WD_MODE_RESET, the watchdog will
//! be put into reset mode and generation of a watchdog interrupt signal will
//! be disabled. This is how the watchdog is configured by default.
//!
//! \note Check the status of the watchdog interrupt using
//! SysCtl_isWatchdogInterruptActive() before calling this function. If the
//! interrupt is still active, switching from interrupt mode to reset mode will
//! immediately reset the device.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_setWatchdogMode(SysCtl_WDMode mode)
{
    EALLOW;
    // Either set or clear the WDENINT bit to that will determine whether the
    // watchdog will generate a reset signal or an interrupt signal.
    if (mode == SYSCTL_WD_MODE_INTERRUPT)
        WdRegs.WD_CR.bit.RMOD = 1;
    else
        WdRegs.WD_CR.bit.RMOD = 0;
    EDIS;
}

//*****************************************************************************
//
//! Gets the status of the watchdog interrupt signal.
//!
//! This function returns the status of the watchdog interrupt signal. If the
//! interrupt is active, this function will return \b true. If \b false, the
//! interrupt is NOT active.
//!
//! \note Make sure to call this function to ensure that the interrupt is not
//! active before making any changes to the configuration of the watchdog to
//! prevent any unexpected behavior. For instance, switching from interrupt
//! mode to reset mode while the interrupt is active will immediately reset the
//! device.
//!
//! \return \b true if the interrupt is active and \b false if it is not.
//
//*****************************************************************************
static inline uint32_t SysCtl_isWatchdogInterruptActive(void)
{
    // If the status bit is cleared, the WDINTn signal is active.
    return (WdRegs.WD_STAT.bit.WD_STAT);
}

//*****************************************************************************
//
//! Disables the watchdog.
//!
//! This function disables the watchdog timer. Note that the watchdog timer is
//! enabled on reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_disableWatchdog(void)
{
    EALLOW;
    WdRegs.WD_CR.bit.WD_EN = 0;
    EDIS;
}

//*****************************************************************************
//
//! Enables the watchdog.
//!
//! This function enables the watchdog timer. Note that the watchdog timer is
//! enabled on reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_enableWatchdog(void)
{
    EALLOW;
    WdRegs.WD_CR.bit.WD_EN = 1;
    EDIS;
}

//*****************************************************************************
//
//! Services the watchdog.
//!
//! This function resets the watchdog.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_serviceWatchdog(void)
{
    EALLOW;
    // Enable the counter to be reset and then reset it.
    WdRegs.WD_CRR.all = 0X76;
    EDIS;
}

//*****************************************************************************
//
//! Sets up watchdog reset period clock
//!
//! \param period is the value that configures the reset period.
//!
//! This function sets up the watchdog reset count period. the reset period equal
//! to 2^(16 + period) clock. The period clock range is 2^16 ~ 2^31 clock
//! watchdog is use OSC1 as clock source
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_setWatchdogResetPeriod(SysCtl_WDResetPeriod peroid)
{
    // reset peroid = 2^(16 + peroid) clock
    WdRegs.WD_TORR = peroid;
}

//*****************************************************************************
//
//! Gets the watchdog counter value.
//!
//! \return Returns the current value of the 8-bit watchdog counter. If this
//! count value overflows, a watchdog output pulse is generated.
//
//*****************************************************************************
static inline uint32_t SysCtl_getWatchdogCounterValue(void)
{
    return (WdRegs.WD_CCVR);
}

//*****************************************************************************
//
//! Gets the watchdog reset status.
//!
//! This function returns the watchdog reset status. If this function returns
//! \b true, that indicates that a watchdog reset generated the last reset
//! condition. Otherwise, it was an external device or power-up reset
//! condition.
//!
//! \return Returns \b true if the watchdog generated the last reset condition.
//
//*****************************************************************************
static inline uint32_t SysCtl_getWatchdogResetStatus(vu32 cpu_id)
{
    // Read and return the status of the watchdog reset status flag.
    if (cpu_id)
        return (CpuSysRegs.RESC.bit.CPU1_WDRSn != 0);
    else
        return (CpuSysRegs.RESC.bit.CPU0_WDRSn != 0);
}

//*****************************************************************************
//
//! Clears the watchdog reset status.
//!
//! This function clears the watchdog reset status. To check if it was set
//! first, see SysCtl_getWatchdogResetStatus().
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_clearWatchdogResetStatus(vu32 cpu_id)
{
    EALLOW;
    // Read and return the status of the watchdog reset status flag.
    if (cpu_id)
        CpuSysRegs.RESCCLR.bit.CPU1_WDRSn = 1;
    else
        CpuSysRegs.RESCCLR.bit.CPU0_WDRSn = 1;
    EDIS;
}

//*****************************************************************************
//
//! Enable the NMI Global interrupt bit
//!
//! \b Note: This bit should be set after the device security related
//! initialization is complete.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_enableNMIGlobalInterrupt(void)
{
    EALLOW;
    HWREGH(NMI_BASE + NMI_O_CFG) |= NMI_CFG_NMIE;
    EDIS;
}

//*****************************************************************************
//
//! Read NMI interrupts.
//!
//! Read the current state of NMI interrupt.
//!
//! \return \b true if NMI interrupt is triggered, \b false if not.
//
//*****************************************************************************
static inline uint32_t SysCtl_getNMIStatus(void)
{
    return ((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_NMIINT) != 0U);
}

//*****************************************************************************
//
//! Read NMI Flags.
//!
//! Read the current state of individual NMI interrupts
//!
//! \return Value of NMIFLG register. These defines are provided to decode
//! the value:
//! - \b SYSCTL_NMI_NMIINT        -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL     -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_RAMUNCERR     -  RAM Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_FLUNCERR      -  Flash Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_PIEVECTERR    -  PIE Vector Fetch Error Flag
//! - \b SYSCTL_NMI_CLBNMI        -  Configurable Logic Block NMI Flag
//! - \b SYSCTL_NMI_SWERR         -  SW Error Force NMI Flag
//
//*****************************************************************************
static inline uint16_t SysCtl_getNMIFlagStatus(void)
{
    return (HWREGH(NMI_BASE + NMI_O_FLG));
}

//*****************************************************************************
//
//! Check if the individual NMI interrupts are set.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT        -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL     -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_RAMUNCERR     -  RAM Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_FLUNCERR      -  Flash Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_PIEVECTERR    -  PIE Vector Fetch Error Flag
//! - \b SYSCTL_NMI_CLBNMI        -  Configurable Logic Block NMI Flag
//! - \b SYSCTL_NMI_SWERR         -  SW Error Force NMI Flag
//!
//! Check if interrupt flags corresponding to the passed in bit mask are
//! asserted.
//!
//! \return \b true if any of the NMI asked for in the parameter bit mask
//! is set. \b false if none of the NMI requested in the parameter bit mask are
//! set.
//
//*****************************************************************************
static inline uint32_t SysCtl_isNMIFlagSet(uint16_t nmiFlags)
{
    return ((HWREGH(NMI_BASE + NMI_O_FLG) & nmiFlags) != 0U);
}

//*****************************************************************************
//
//! Function to clear individual NMI interrupts.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT        -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL     -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_RAMUNCERR     -  RAM Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_FLUNCERR      -  Flash Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_PIEVECTERR    -  PIE Vector Fetch Error Flag
//! - \b SYSCTL_NMI_CLBNMI        -  Configurable Logic Block NMI Flag
//! - \b SYSCTL_NMI_SWERR         -  SW Error Force NMI Flag
//!
//! Clear NMI interrupt flags that correspond with the passed in bit mask.
//!
//! \b Note: The NMI Interrupt flag is always cleared by default and
//! therefore doesn't have to be included in the bit mask.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_clearNMIStatus(uint16_t nmiFlags)
{
    EALLOW;
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = nmiFlags;
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = NMI_FLG_NMIINT;
    EDIS;
}

//*****************************************************************************
//
//! Clear all the NMI Flags that are currently set.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_clearAllNMIFlags(void)
{
    uint16_t nmiFlags;
    EALLOW;
    nmiFlags                        = SysCtl_getNMIFlagStatus();
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = nmiFlags;
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = NMI_FLG_NMIINT;
    EDIS;
}

//*****************************************************************************
//
//! Function to force individual NMI interrupt fail flags
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT        -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL     -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_RAMUNCERR     -  RAM Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_FLUNCERR      -  Flash Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_PIEVECTERR    -  PIE Vector Fetch Error Flag
//! - \b SYSCTL_NMI_CLBNMI        -  Configurable Logic Block NMI Flag
//! - \b SYSCTL_NMI_SWERR         -  SW Error Force NMI Flag
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_forceNMIFlags(uint16_t nmiFlags)
{
    EALLOW;
    HWREGH(NMI_BASE + NMI_O_FLGFRC) |= nmiFlags;
    EDIS;
}

//*****************************************************************************
//
//! Gets the NMI watchdog counter value.
//!
//! \b Note: The counter is clocked at the SYSCLKOUT rate.
//!
//! \return Returns the NMI watchdog counter register's current value.
//
//*****************************************************************************
static inline uint16_t SysCtl_getNMIWatchdogCounter(void)
{
    return NmiIntruptRegs.NMIWDCNT;
}

//*****************************************************************************
//
//! Sets the NMI watchdog period value.
//!
//! \param wdPeriod is the 16-bit value at which a reset is generated.
//!
//! This function writes to the NMI watchdog period register that holds the
//! value to which the NMI watchdog counter is compared. When the two registers
//! match, a reset is generated. By default, the period is 0xFFFF.
//!
//! \note If a value smaller than the current counter value is passed into the
//! \e wdPeriod parameter, a NMIRSn will be forced.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_setNMIWatchdogPeriod(uint16_t wdPeriod)
{
    EALLOW;
    NmiIntruptRegs.NMIWDPRD = wdPeriod;
    EDIS;
}

//*****************************************************************************
//
//! Gets the NMI watchdog period value.
//!
//! \return Returns the NMI watchdog period register's current value.
//
//*****************************************************************************
static inline uint16_t SysCtl_getNMIWatchdogPeriod(void)
{
    return NmiIntruptRegs.NMIWDPRD;
}

//*****************************************************************************
//
//! Read NMI Shadow Flags.
//!
//! Read the current state of individual NMI interrupts
//!
//! \return Value of NMISHDFLG register. These defines are provided to decode
//! the value:
//! - \b SYSCTL_NMI_NMIINT        -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL     -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_RAMUNCERR     -  RAM Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_FLUNCERR      -  Flash Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_PIEVECTERR    -  PIE Vector Fetch Error Flag
//! - \b SYSCTL_NMI_CLBNMI        -  Configurable Logic Block NMI Flag
//! - \b SYSCTL_NMI_SWERR         -  SW Error Force NMI Flag
//
//*****************************************************************************
static inline uint32_t SysCtl_getNMIShadowFlagStatus(void)
{
    return NmiIntruptRegs.NMISHDFLG.all;
}

//*****************************************************************************
//
//! Check if the individual NMI shadow flags are set.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants  to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT        -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL     -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_RAMUNCERR     -  RAM Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_FLUNCERR      -  Flash Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_PIEVECTERR    -  PIE Vector Fetch Error Flag
//! - \b SYSCTL_NMI_CLBNMI        -  Configurable Logic Block NMI Flag
//! - \b SYSCTL_NMI_SWERR         -  SW Error Force NMI Flag
//!
//! Check if interrupt flags corresponding to the passed in bit mask are
//! asserted.
//!
//! \return \b true if any of the NMI asked for in the parameter bit mask
//! is set. \b false if none of the NMI requested in the parameter bit mask are
//! set.
//
//*****************************************************************************
static inline uint32_t SysCtl_isNMIShadowFlagSet(uint16_t nmiFlags)
{
    return ((NmiIntruptRegs.NMISHDFLG.all & nmiFlags) != 0U);
}

//*****************************************************************************
//
//! Enable the missing clock detection (MCD) Logic
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_enableMCD(void)
{
    ClkCfgRegs.MCDCR.bit.MCLKOFF = 0;
}

//*****************************************************************************
//
//! Disable the missing clock detection (MCD) Logic
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_disableMCD(void)
{
    ClkCfgRegs.MCDCR.bit.MCLKOFF = 1;
}

//*****************************************************************************
//
//! Get the missing clock detection Failure Status
//!
//! \note A failure means the oscillator clock is missing
//!
//! \return Returns \b true if a failure is detected or \b false if a
//! failure isn't detected
//
//*****************************************************************************
static inline uint32_t SysCtl_isMCDClockFailureDetected(void)
{
    //  Check the status bit to determine failure
    return (ClkCfgRegs.MCDCR.bit.MCLKSTS != 0U);
}

//*****************************************************************************
//
//! Reset the missing clock detection logic after clock failure
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_resetMCD(void)
{
    ClkCfgRegs.MCDCR.bit.MCLKCLR = 1;
}

//*****************************************************************************
//
//! Re-connect missing clock detection clock source to stop simulating clock
//! failure
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_connectMCDClockSource(void)
{
    ClkCfgRegs.MCDCR.bit.OSCOFF = 0;
}

//*****************************************************************************
//
//! Disconnect missing clock detection clock source to simulate clock failure.
//! This is for testing the MCD functionality.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_disconnectMCDClockSource(void)
{
    ClkCfgRegs.MCDCR.bit.OSCOFF = 1;
}

//*****************************************************************************
//
//! Configures the sync input source for the ePWM and eCAP signals.
//!
//! \param syncInput is the sync input being configured
//! \param syncSrc is sync input source selection.
//!
//! This function configures the sync input source for the ePWM and eCAP
//! modules. The \e syncInput parameter is the sync input being configured. It
//! should be passed a value of \b SYSCTL_SYNC_IN_XXXX, where XXXX is the ePWM
//! or eCAP instance the sync signal is entering.
//!
//! The \e syncSrc parameter is the sync signal selected as the source of the
//! sync input. It should be passed a value of \b SYSCTL_SYNC_IN_SRC_XXXX,
//! XXXX is a sync signal coming from an ePWM, eCAP or external sync output.
//! where For example, a \e syncInput value of \b SYSCTL_SYNC_IN_ECAP1 and a
//! \e syncSrc value of \b SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT will make the
//! EPWM1SYNCOUT signal drive eCAP1's SYNCIN signal.
//!
//! Note that some \e syncSrc values are only valid for certain values of
//! \e syncInput. See device technical reference manual for details on
//! time-base counter synchronization.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_setSyncInputConfig(
    SysCtl_SyncInput syncInput, SysCtl_SyncInputSource syncSrc)
{
    uint32_t clearMask;

    // Write the input sync source selection to the appropriate register.
    EALLOW;
    if (syncInput == SYSCTL_SYNC_IN_EPWM1)
    {
        // Note that EXTSYNCIN1 is the only valid option for ePWM1
        HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSELECT) &= ~SYSCTL_SYNCSELECT_EPWM1SYNCIN_M;
    }
    else
    {
        clearMask = (uint32_t)SYSCTL_SYNCSELECT_SYNCIN_M << (uint32_t)syncInput;

        HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSELECT)
            = (HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSELECT) & ~clearMask)
              | ((uint32_t)syncSrc << (uint32_t)syncInput);
    }

    EDIS;
}

//*****************************************************************************
//
//! Configures the sync output source.
//!
//! \param syncSrc is sync output source selection.
//!
//! This function configures the sync output source from the ePWM modules. The
//! \e syncSrc parameter is a value \b SYSCTL_SYNC_OUT_SRC_XXXX, where XXXX is
//! a sync signal coming from an ePWM such as SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_setSyncOutputConfig(SysCtl_SyncOutputSource syncSrc)
{
    // Write the sync output source selection to the appropriate register.
    EALLOW;
    HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSELECT)
        = (HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSELECT) & ~((uint32_t)SYSCTL_SYNCSELECT_SYNCOUT_M))
          | ((uint32_t)syncSrc << SYSCTL_SYNCSELECT_SYNCOUT_S);
    EDIS;
}

//*****************************************************************************
//
//! Enables ePWM SOC signals to drive an external (off-chip) ADCSOC signal.
//!
//! \param adcsocSrc is a bit field of the selected signals to be enabled
//!
//! This function configures which ePWM SOC signals are enabled as a source for
//! either ADCSOCAO or ADCSOCBO. The \e adcsocSrc parameter takes a logical OR
//! of \b SYSCTL_ADCSOC_SRC_PWMxSOCA/B values that correspond to different
//! signals.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_enableExtADCSOCSource(uint32_t adcsocSrc)
{
    EALLOW;
    HWREG(SYNCSOC_BASE + SYSCTL_O_ADCSOCOUTSELECT) |= adcsocSrc;
    EDIS;
}

//*****************************************************************************
//
//! Disables ePWM SOC signals from driving an external ADCSOC signal.
//!
//! \param adcsocSrc is a bit field of the selected signals to be disabled
//!
//! This function configures which ePWM SOC signals are disabled as a source
//! for either ADCSOCAO or ADCSOCBO. The \e adcsocSrc parameter takes a logical
//! OR of \b SYSCTL_ADCSOC_SRC_PWMxSOCA/B values that correspond to different
//! signals.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_disableExtADCSOCSource(uint32_t adcsocSrc)
{
    EALLOW;
    HWREG(SYNCSOC_BASE + SYSCTL_O_ADCSOCOUTSELECT) &= ~adcsocSrc;
    EDIS;
}

//*****************************************************************************
//
//! Locks the SOC Select of the Trig X-BAR.
//!
//! This function locks the external ADC SOC select of the Trig X-BAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_lockExtADCSOCSelect(void)
{
    EALLOW;
    HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSOCLOCK) = SYSCTL_SYNCSOCLOCK_ADCSOCOUTSELECT;
    EDIS;
}

//*****************************************************************************
//
//! Locks the Sync Select of the Trig X-BAR.
//!
//! This function locks Sync Input and Output Select of the Trig X-BAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_lockSyncSelect(void)
{
    EALLOW;
    HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSOCLOCK) = SYSCTL_SYNCSOCLOCK_SYNCSELECT;
    EDIS;
}

//*****************************************************************************
//
//! Sets up XCLK divider.
//!
//! \param divider is the value that configures the divider.
//!
//! This function sets up the XCLK divider. There is only one
//! divider that scales INTOSC1 to XCLK.
//!
//! The \e divider parameter can have one enumerated value from
//! SysCtl_XClkDivider
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_setXClk(SysCtl_XClkDivider divider)
{
    EALLOW;
    ClkCfgRegs.XCLKOUTDIVSEL.bit.XCLKOUTDIV = divider;
    EDIS;
}

//*****************************************************************************
//
//! Sets up PLLSYSCLK divider.
//!
//! \param divider is the value that configures the divider.
//!
//! This function sets up the PLLSYSCLK divider. There is only one
//! divider that scales PLLSYSCLK to generate the system clock.
//!
//! The \e divider parameter can have one value from the set below:
//!     0x0 = /1
//!     0x1 = /2
//!     0x2 = /4 (default on reset)
//!     0x3 = /6
//!     0x4 = /8
//!    ......
//!     0x3F =/126
//!
//! \return None.
//!
//! \note Please make sure to check if the PLL is locked and valid using the
//! SysCtl_isPLLValid() before setting the divider.
//
//*****************************************************************************
static inline void SysCtl_setPLLSysClk(uint16_t divider)
{
    EALLOW;
    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divider;
    EDIS;
}

//*****************************************************************************
//
//! Sets up CPU0 Timer 2  CLK source & divider.
//!
//! \param divider is the value that configures the divider.
//! \param source is the source for the clock divider
//!
//! This function sets up the CPU0 Timer 2 CLK divider based on the source that
//! is selected. There is only one divider that scales the "source" to
//! CPU0 Timer 2 CLK.
//!
//! The \e divider parameter can have one enumerated value from
//! SysCtl_Cputimer2ClkDivider
//! The \e source parameter can have one enumerated value from
//! SysCtl_Cputimer2ClkSource
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_setCpu0timer2Clk(
    SysCtl_Cputimer2ClkDivider divider, SysCtl_Cputimer2ClkSource source)
{
    EALLOW;
    CpuSysRegs.TMR2CLKCTL.bit.CPU0TMR2CLKSRCSEL = source;
    CpuSysRegs.TMR2CLKCTL.bit.CPU0TMR2CLKSRCSEL = divider;
    EDIS;
}

//*****************************************************************************
//
//! Sets up CPU1 Timer 2  CLK source & divider.
//!
//! \param divider is the value that configures the divider.
//! \param source is the source for the clock divider
//!
//! This function sets up the CPU1 Timer 2 CLK divider based on the source that
//! is selected. There is only one divider that scales the "source" to
//! CPU1 Timer 2 CLK.
//!
//! The \e divider parameter can have one enumerated value from
//! SysCtl_Cputimer2ClkDivider
//! The \e source parameter can have one enumerated value from
//! SysCtl_Cputimer2ClkSource
//!
//! \return None.
//
//*****************************************************************************
static inline void SysCtl_setCpu1timer2Clk(
    SysCtl_Cputimer2ClkDivider divider, SysCtl_Cputimer2ClkSource source)
{
    EALLOW;
    CpuSysRegs.TMR2CLKCTL.bit.CPU1TMR2CLKSRCSEL = source;
    CpuSysRegs.TMR2CLKCTL.bit.CPU1TMR2CLKSRCSEL = divider;
    EDIS;
}

//*****************************************************************************
//
//! Gets the PIE Vector Fetch Error Handler Routine Address.
//!
//! The function indicates the address of the PIE Vector Fetch Error
//! handler routine.
//!
//! \return Error Handler Address.
//!
//! \note Its the responsibility of user to initialize this register. If this
//! register is not initialized, a default error handler at address
//! 0x3fffbe will get executed.
//
//*****************************************************************************
// static inline uint32_t SysCtl_getPIEVErrAddr(void)
// {
//     return (HWREG(CPUSYS_BASE + SYSCTL_O_PIEVERRADDR));
// }

//*****************************************************************************
//
//! Delays for a fixed number of cycles.
//!
//! \param count is the number of delay loop iterations to perform.
//!
//! This function generates a constant length delay using assembly code. The
//! loop takes 8 cycles per iteration plus 8 cycles of overhead.
//!
//! \note If count is equal to zero, the loop will underflow and run for a
//! very long time.
//!
//! \note Refer to the macro DEVICE_DELAY_US(x) in device.h which can be used to
//! insert a delay in microseconds.
//!
//! \return None.
//
//*****************************************************************************
extern void qx_precise_delay(uint32_t count);
STATIC_ALWAYS_INLINE void SysCtl_delay(uint32_t count)
{
    qx_precise_delay(count);
}

//*****************************************************************************
//
//! Calculates the system clock frequency (SYSCLK).
//!
//! \param clockInHz is the frequency of the oscillator clock source (OSCCLK).
//!
//! This function determines the frequency of the system clock based on the
//! frequency of the oscillator clock source (from \e clockInHz) and the PLL
//! and clock divider configuration registers.
//!
//! \return Returns the system clock frequency. If a missing clock is detected,
//! the function will return the INTOSC1 frequency. This needs to be
//! corrected and cleared (see SysCtl_resetMCD()) before trying to call this
//! function again.
//
//*****************************************************************************
extern uint32_t SysCtl_getClock(uint32_t clockInHz);

//*****************************************************************************
//
//! Configures the clocking of the device.
//!
//! \param config is the required configuration of the device clocking.
//!
//! This function configures the clocking of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! The \e config parameter is the OR of several different values, many of
//! which are grouped into sets where only one can be chosen.
//!
//! - The system clock divider is chosen with the macro \b SYSCTL_SYSDIV(x)
//!   where x is either 1 or an even value up to 126.
//!
//! - The use of the PLL is chosen with either \b SYSCTL_PLL_ENABLE or
//!   \b SYSCTL_PLL_DISABLE.
//!
//! - The integer multiplier is chosen \b SYSCTL_IMULT(x) where x is a value
//!   from 1 to 127.
//!
//! - The fractional multiplier is chosen with either \b SYSCTL_IDIV_0,
//!   \b SYSCTL_IDIV_1_4, \b SYSCTL_IDIV_1_2, or \b SYSCTL_IDIV_3_4.
//!
//! - The oscillator source chosen with \b SYSCTL_OSCSRC_OSC2,
//!   \b SYSCTL_OSCSRC_XTAL, \b SYSCTL_OSCSRC_XTAL_SE or \b SYSCTL_OSCSRC_OSC1.
//!
//! This function uses the DCC to check that the PLLRAWCLK is running at the
//! expected rate. If you are using the DCC, you must back up its configuration
//! before calling this function and restore it afterward.
//! Locking PLL sequence is only done if the multipliers are updated.
//!
//! \note See your device errata for more details about locking the PLL.
//!
//! \return Returns \b false if a missing clock error is detected. This needs
//! to be cleared (see SysCtl_resetMCD()) before trying to call this function
//! again. Also, returns \b false if the PLLRAWCLK is not running and its
//! expected rate after \b SYSCTL_PLL_RETRIES retries. Otherwise, returns
//! \b true.
//
//*****************************************************************************
uint32_t SysCtl_setClock(uint32_t config);

//*****************************************************************************
//
//! Validates PLL Raw Clock Frequency (PLLRAWCLK)
//!
//! \param oscSource is the Clock Source for the PLL that is also used for DCC
//! \param pllMult has the PLL Multiplier Register configuration which include
//!  integer and fractional multiplier used to configure the DCC Counter1 clock
//!
//!  This function uses DCC module to validate the PLL clock frequency.
//!  It uses oscSource as a reference clock for DCC, and PLL is used as clock
//!  under test. As long as the Counter0 (running of oscSource) & Counter1
//!  (running of PLL) expire at the same time, DCC will not generate an Error.
//!  This function gives 100 attempts for PLL to lock and make sure frequency
//!  is as expected.
//!
//!  \note This function does not validate if PLL output frequency (PLLRAWCLK)
//!  is within the operating range as per the datasheet.
//!
//! - The \e oscSource parameter is the oscillator source chosen with
//!   \b SYSCTL_OSCSRC_OSC2, \b SYSCTL_OSCSRC_XTAL, \b SYSCTL_OSCSRC_XTAL_SE
//!    or \b SYSCTL_OSCSRC_OSC1.
//!
//! - The \e pllMult parameter is a bitwise OR of \b SYSCTL_IMULT(x) where x is
//!   a value from 1 to 127 and one of the following fractional values:
//!   \b SYSCTL_IDIV_0, \b SYSCTL_IDIV_1_4, \b SYSCTL_IDIV_1_2, or
//!   \b SYSCTL_IDIV_3_4.
//!
//!  \return Returns \b true if the DCCSTATUS error flag is not set.
//!    Otherwise, returns \b false.
//
//*****************************************************************************
extern uint32_t SysCtl_isPLLValid(uint32_t oscSource, uint32_t pllMult);
//*****************************************************************************
//
//! Configures the external oscillator for the clocking of the device.
//!
//! This function configures the external oscillator (XTAL) to be used for the
//! clocking of the device in crystal mode. It follows the procedure to turn on
//! the oscillator, wait for it to power up, and select it as the source of the
//! system clock.
//!
//! Please note that this function blocks while it waits for the XTAL to power
//! up. If the XTAL does not manage to power up properly, the function will
//! loop for a long time. It is recommended that you modify this function to
//! add an appropriate timeout and error-handling procedure.
//!
//! \return None.
//
//*****************************************************************************
extern void SysCtl_selectXTAL(void);

//*****************************************************************************
//
//! Configures the external oscillator for the clocking of the device in
//! single-ended mode.
//!
//! This function configures the external oscillator (XTAL) to be used for the
//! clocking of the device in single-ended mode. It follows the procedure to
//! turn on the oscillator, wait for it to power up, and select it as the
//! source of the system clock.
//!
//! Please note that this function blocks while it waits for the XTAL to power
//! up. If the XTAL does not manage to power up properly, the function will
//! loop for a long time. It is recommended that you modify this function to
//! add an appropriate timeout and error-handling procedure.
//!
//! \return None.
//
//*****************************************************************************
extern void SysCtl_selectXTALSingleEnded(void);

//*****************************************************************************
//
//! Selects the oscillator to be used for the clocking of the device.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function configures the oscillator to be used in the clocking of the
//! device. The \e oscSource parameter may take a value of
//! \b SYSCTL_OSCSRC_OSC2, \b SYSCTL_OSCSRC_XTAL, \b SYSCTL_OSCSRC_XTAL_SE, or
//! \b SYSCTL_OSCSRC_OSC1.
//!
//! \sa SysCtl_turnOnOsc()
//!
//! \return None.
//
//*****************************************************************************
extern void SysCtl_selectOscSource(uint32_t oscSource);

//*****************************************************************************
//
//! Calculates the low-speed peripheral clock frequency (LSPCLK).
//!
//! \param clockInHz is the frequency of the oscillator clock source (OSCCLK).
//!
//! This function determines the frequency of the low-speed peripheral clock
//! based on the frequency of the oscillator clock source (from \e clockInHz)
//! and the PLL and clock divider configuration registers.
//!
//! \return Returns the low-speed peripheral clock frequency.
//
//*****************************************************************************
extern uint32_t SysCtl_getLowSpeedClock(uint32_t clockInHz);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif
