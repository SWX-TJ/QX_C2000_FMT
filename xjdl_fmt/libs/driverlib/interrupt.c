#include "driverlib.h"

//*****************************************************************************
// Interrupt_initModule
//*****************************************************************************
void Interrupt_initModule(void)
{
    DINT;

    PieCtrlRegs.PIEIER1.all  = 0;
    PieCtrlRegs.PIEIER2.all  = 0;
    PieCtrlRegs.PIEIER3.all  = 0;
    PieCtrlRegs.PIEIER4.all  = 0;
    PieCtrlRegs.PIEIER5.all  = 0;
    PieCtrlRegs.PIEIER6.all  = 0;
    PieCtrlRegs.PIEIER7.all  = 0;
    PieCtrlRegs.PIEIER8.all  = 0;
    PieCtrlRegs.PIEIER9.all  = 0;
    PieCtrlRegs.PIEIER10.all = 0;
    PieCtrlRegs.PIEIER11.all = 0;
    PieCtrlRegs.PIEIER12.all = 0;

    PieCtrlRegs.IER.all = 0;

    EINT;
}

//*****************************************************************************
// Interrupt_enable
//*****************************************************************************
void Interrupt_enable(INTERRUPT_Type interruptNumber)
{
    int intGroup;
    int groupMask;

    intGroup  = ((interruptNumber & 0xFF00) >> 8) - 1;
    groupMask = 1 << intGroup;

    if (intGroup <= 12)
        HWREGH(((int)&PieCtrlRegs.PIEIER1 + (intGroup * 4)))
            |= (1 << ((interruptNumber & 0xFF) - 1));

    PieCtrlRegs.IER.all |= (1 << intGroup);
}

//*****************************************************************************
// Interrupt_disable
//*****************************************************************************
void Interrupt_disable(INTERRUPT_Type interruptNumber)
{
    int intGroup;
    int groupMask;

    intGroup  = ((interruptNumber & 0xFF00) >> 8) - 1;
    groupMask = 1 << intGroup;

    if (intGroup <= 12)
        HWREGH(((int)&PieCtrlRegs.PIEIER1 + (intGroup * 4)))
            &= ~(1 << ((interruptNumber & 0xFF) - 1));
    else
        PieCtrlRegs.IER.all &= ~(1 << intGroup);
}
