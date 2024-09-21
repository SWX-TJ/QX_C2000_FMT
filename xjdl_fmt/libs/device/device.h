#ifndef QX_DEVICE_H
#define QX_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "driverlib.h"

//
// SYSCTL
//
#define SYSCTL_FMULT_NONE SYSCTL_IDIV(1)

//*****************************************************************************
//
// Defines related to clock configuration
//
//*****************************************************************************
//
// 10MHz~16Mhz XTAL
//
#if defined(DEV_ENV_FPGA)
#define DEVICE_OSCSRC_FREQ          10000000UL

#define IMULT_VAL                   40 // WARNNING: IMULT_VAL must >= 40 & <=63
#define ODIV_VAL                    4  // WARNNING: ODIV_VAL  must >=  0 & <=15
#define LSPCLK_PRESCALE             SYSCTL_LSPCLK_PRESCALE_1
#else
#define DEVICE_OSCSRC_FREQ          16000000UL

#define IMULT_VAL                   40 // WARNNING: IMULT_VAL must >= 40 & <=63
#define ODIV_VAL                    2  // WARNNING: ODIV_VAL  must >=  0 & <=15
#define LSPCLK_PRESCALE             SYSCTL_LSPCLK_PRESCALE_1
#endif

// Define to pass to SysCtl_setClock(). Will configure the clock as follows:
// PLLSYSCLK = (XTAL/OSC1/OSC2 CLK) * IMULT_VAL / IDIV / ODIV_VAL / SYSDIV
//
#define DEVICE_SETCLOCK_CFG         (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(IMULT_VAL) | SYSCTL_IDIV(1) | \
                                     SYSCTL_ODIV(ODIV_VAL) | SYSCTL_SYSDIV(1) | SYSCTL_PLL_ENABLE)


// SYSCLK frequency based on the above DEVICE_SETCLOCK_CFG. Update the
// code below if a different clock configuration is used!
//
#define DEVICE_SYSCLK_FREQ          (((DEVICE_OSCSRC_FREQ * IMULT_VAL / 1) / ODIV_VAL) / 1)

//
// LSPCLK frequency based on the above DEVICE_SYSCLK_FREQ and LSPCLK_PRESCALE
//
#define LSPCLK_PRESCALE_VAL         ((LSPCLK_PRESCALE == SYSCTL_LSPCLK_PRESCALE_1) ? 1 : (LSPCLK_PRESCALE * 2))
#define DEVICE_LSPCLK_FREQ          (DEVICE_SYSCLK_FREQ / LSPCLK_PRESCALE_VAL)

//*****************************************************************************
//
// Macro to call SysCtl_delay() to achieve a delay in microseconds. The macro
// will convert the desired delay in microseconds to the count value expected
// by the function. \b x is the number of microseconds to delay.
//
// The loop in qx_precise_delay takes 8 cycles per iteration plus 8 cycles of
// overhead (5 cycles of passing argument and executing call, and 3 cycles of
// function return).
//
//*****************************************************************************
#define DEVICE_DELAY_US(x) qx_precise_delay(((((long double)(x)) / (1000000.0L /  \
                                  (long double)DEVICE_SYSCLK_FREQ)) - 8.0L) / 8.0L)

//*****************************************************************************
//  Defines for setting FSI clock speeds in normal FSI mode (SPI_MODE == 0)
//*****************************************************************************
//
//  TXCLKIN = INPUT_CLOCK / PRESCALE_VAL
//  TXCLK (in FSI mode) = TXCLKIN / 2
//  TXCLK (in SPI mode) = TXCLKIN
//
//  Below assumes INPUT_CLOCK == 200 MHz (PLLRAWCLK, SEL_PLLCLK == 1)
//
#define FSI_PRESCALE_50MHZ          2U
#define FSI_PRESCALE_25MHZ          4U
#define FSI_PRESCALE_10MHZ          10U
#define FSI_PRESCALE_5MHZ           20U


extern void Device_init(void);
extern void SysCtl_enablePeripheralAll(void);
extern bool Device_verifyXTAL(float freq);
extern void Device_initGPIO(void);
extern void __error__(const char *filename, uint32_t line);

#ifdef __cplusplus
}
#endif

#endif
