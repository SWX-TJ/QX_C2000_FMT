#include "device.h"
#include "driverlib.h"

void Device_init(void)
{
    SysCtl_setClock(DEVICE_SETCLOCK_CFG);
    SysCtl_setLowSpeedClock(LSPCLK_PRESCALE);

    if (SysCtl_getClock(DEVICE_OSCSRC_FREQ) >= 120000000)
        Flash_setClkDiv(4); // flash max support 133Mhz clock

    // SysCtl_enablePeripheralAll();
}

void SysCtl_enablePeripheralAll(void)
{
    // ADC max support 48Mhz clock
    AdcaRegs.ADCCTL.bit.PRESCALE    = ADC_CLK_DIV_6_0;
    AdcbRegs.ADCCTL.bit.PRESCALE    = ADC_CLK_DIV_6_0;
    AdccRegs.ADCCTL.bit.PRESCALE    = ADC_CLK_DIV_6_0;
    HrAdcaRegs.adcctl2.bit.prescale = ADC_CLK_DIV_6_0;
    HrAdcbRegs.adcctl2.bit.prescale = ADC_CLK_DIV_6_0;
    HrAdccRegs.adcctl2.bit.prescale = ADC_CLK_DIV_6_0;

    // DAC max support 5Mhz clock
    DacaRegs.DACCTL.bit.PRESCALE             = 50;
    DacbRegs.DACCTL.bit.PRESCALE             = 50;
    Cmpss1Regs.COMPDACHCTL.bit.DACH_PRESCALE = 50;
    Cmpss1Regs.COMPDACLCTL.bit.DACH_PRESCALE = 50;
    Cmpss2Regs.COMPDACHCTL.bit.DACH_PRESCALE = 50;
    Cmpss2Regs.COMPDACLCTL.bit.DACH_PRESCALE = 50;
    Cmpss3Regs.COMPDACHCTL.bit.DACH_PRESCALE = 50;
    Cmpss3Regs.COMPDACLCTL.bit.DACH_PRESCALE = 50;
    Cmpss4Regs.COMPDACHCTL.bit.DACH_PRESCALE = 50;
    Cmpss4Regs.COMPDACLCTL.bit.DACH_PRESCALE = 50;
    Cmpss5Regs.COMPDACHCTL.bit.DACH_PRESCALE = 50;
    Cmpss5Regs.COMPDACLCTL.bit.DACH_PRESCALE = 50;
    Cmpss6Regs.COMPDACHCTL.bit.DACH_PRESCALE = 50;
    Cmpss6Regs.COMPDACLCTL.bit.DACH_PRESCALE = 50;
    Cmpss7Regs.COMPDACHCTL.bit.DACH_PRESCALE = 50;
    Cmpss7Regs.COMPDACLCTL.bit.DACH_PRESCALE = 50;

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM8);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM9);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM10);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM11);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM12);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SD1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PMBUSA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA_HR);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB_HR);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCC_HR);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_LINA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_XINTF);
}

void Device_initGPIO(void)
{
    //
    // Disable pin locks.
    //
    GPIO_unlockPortConfig(GPIO_PORT_A, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_B, 0xFFFFFFFF);
}

bool Device_verifyXTAL(float freq)
{
    // Use DCC to verify the XTAL frequency using INTOSC2 as reference clock
    // Turn on XTAL and wait for it to power up using X1CNT
    SysCtl_turnOnOsc(SYSCTL_OSCSRC_XTAL);
    SysCtl_clearExternalOscCounterValue();
    while (SysCtl_getExternalOscCounterValue() != SYSCTL_X1CNT_X1CNT_M)
        ;

    // Enable DCC0 clock
    // SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC0);

    // Insert atleast 5 cycles delay after enabling the peripheral clock
    // asm(" RPT #5 || NOP");

    // Configures XTAL as CLKSRC0 and INTOSC2 as CLKSRC1
    // Fclk0 = XTAL frequency (input parameter)
    // Fclk1 = INTOSC2 frequency = 10MHz
    // Configuring DCC error tolerance of +/-1%
    // INTOSC2 can have a variance in frequency of +/-10%
    // Assuming PLL is not already configured, SysClk freq = 10MHz
    // Note : Update the tolerance and INTOSC2 frequency variance as necessary.
    return (DCC_verifyClockFrequency(
        DCC0_BASE, DCC_COUNT1SRC_INTOSC2, 10.0F, DCC_COUNT0SRC_XTAL, freq, 1.0F, 10.0F, 10.0F));
}

void __error__(const char *filename, uint32_t line)
{
    // printf("assert error at %s:%d\n", filename, line);
    ESTOP0;
}
