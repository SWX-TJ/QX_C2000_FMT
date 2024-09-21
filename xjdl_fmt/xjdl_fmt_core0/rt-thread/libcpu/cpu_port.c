#include <rthw.h>
#include <rtconfig.h>
#include <rtthread.h>

#include "device.h"
#include "interrupt.h"

volatile rt_ubase_t rt_from_thread = 0;
volatile rt_ubase_t rt_to_thread = 0;
volatile rt_uint32_t rt_thread_switch_interrupt_flag = 0;
//volatile rt_uint32_t rt_hw_context_switch_flag = 0;

uint32_t SystemCoreClock = 0;

#if defined(DEV_ENV_FPGA)

#else

#define USE_PLL

#endif

void SystemCoreClockUpdate(void)
{
#ifdef USE_PLL
    Device_init();
#else
    SysCtl_setPLLSysClk(0);
    SysCtl_setLowSpeedClock(0);
#endif
}

void get_system_core_clock_value(void)
{
	SystemCoreClock = SysCtl_getClock(DEVICE_OSCSRC_FREQ);
}

struct rt_hw_stack_frame
{
     /* 32 x 32-bit general purpose registers
     * GR0  ~ GR15: caller saved registers
     * GR16 ~ GR29: callee saved registers
     * G30: stack pointer
     * G31: link register (return address)
     */
    rt_ubase_t GR0;
    rt_ubase_t GR1;
    rt_ubase_t GR2;
    rt_ubase_t GR3;
    rt_ubase_t GR4;
    rt_ubase_t GR5;
    rt_ubase_t GR6;
    rt_ubase_t GR7;
    rt_ubase_t GR8;
    rt_ubase_t GR9;
    rt_ubase_t GR10;
    rt_ubase_t GR11;
    rt_ubase_t GR12;
    rt_ubase_t GR13;
    rt_ubase_t GR14;
    rt_ubase_t GR15;
    rt_ubase_t GR16;
    rt_ubase_t GR17;
    rt_ubase_t GR18;
    rt_ubase_t GR19;
    rt_ubase_t GR20;
    rt_ubase_t GR21;
    rt_ubase_t GR22;
    rt_ubase_t GR23;
    rt_ubase_t GR24;
    rt_ubase_t GR25;
    rt_ubase_t GR26;
    rt_ubase_t GR27;
    rt_ubase_t GR28;
    rt_ubase_t GR29;
    rt_ubase_t GR30;
    rt_ubase_t GR31;

    /* 1 x 32-bit control register */
    rt_ubase_t CR;

    /* 1 x 32-bit interrupt return address register */
    rt_ubase_t IRA;
};

rt_uint8_t* rt_hw_stack_init(void* tentry,
                             void* parameter,
                             rt_uint8_t* stack_addr,
                             void* texit) {
    struct rt_hw_stack_frame* frame;
    rt_uint8_t* stk;
    int i;

    /* align the incoming stack pointer to 16-byte boundary */
    stk = stack_addr + sizeof(rt_ubase_t);
    stk = (rt_uint8_t*)RT_ALIGN_DOWN((rt_ubase_t)stk, 8);
    /* reserve space to hold the entire struct rt_hw_stack_frame */
    stk -= sizeof(struct rt_hw_stack_frame);

    frame = (struct rt_hw_stack_frame*)stk;
    for (i = 0; i < sizeof(struct rt_hw_stack_frame) / sizeof(rt_ubase_t); i++) {
        ((rt_ubase_t*)frame)[i] = 0xdeadbeef;
    }


    /* GR4~GR7 are used to transmit parameter */
    frame->GR4 = (rt_ubase_t)parameter;

    frame->GR30 = (rt_ubase_t)stk;

    frame->GR31 = (rt_ubase_t)texit;

    frame->CR = 0;

    frame->IRA = (rt_ubase_t)tentry;

    return stk;
}

rt_uint32_t get_rt_thread_switch_interrupt_flag_addr() {
    return (rt_uint32_t)(&rt_thread_switch_interrupt_flag);
}

rt_uint32_t get_rt_from_thread_addr() {
    return (rt_uint32_t)(&rt_from_thread);
}

rt_uint32_t get_rt_to_thread_addr() {
    return (rt_uint32_t)(&rt_to_thread);
}

void trigger_rt_thread_intr(void)
{
    ERAD_enableModules(ERAD_INST_COUNTER1);
}

#if 0
void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to) {
    if (rt_thread_switch_interrupt_flag == 0)
        rt_from_thread = from;

    rt_to_thread = to;
    rt_thread_switch_interrupt_flag = 1;
    trigger_rt_thread_intr();
    return;
}

void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to) {
    if (rt_thread_switch_interrupt_flag == 0)
        rt_from_thread = from;

    rt_to_thread = to;
    rt_thread_switch_interrupt_flag = 1;
    trigger_rt_thread_intr();
    return;
}
#endif


void erad_sec_config(u32 base, ERAD_Counter_Input_Event event,
    ERAD_Counter_Event_Mode event_mode, u32 ref, bool rst_on_match, bool en_int, bool en_stop)
{
    ERAD_clearCounterEvent(base);
    ERAD_clearCounterOverflow(base);
    ERAD_resetCounter(ERAD_getCounterInstance(base));
    ERAD_Counter_Config counter_params;
    counter_params.event        = event;
    counter_params.event_mode   = event_mode;
    counter_params.reference    = ref;
    counter_params.rst_on_match = rst_on_match;
    counter_params.enable_int   = en_int;
    counter_params.enable_stop  = en_stop;
    ERAD_configCounterInCountingMode(base, counter_params);
}

void erad_cmt_mode_init(void)
{
	Interrupt_enable(INT_RTOS);

	erad_sec_config(
        ERAD_COUNTER1_BASE, ERAD_EVENT_NO_EVENT, ERAD_COUNTER_MODE_ACTIVE, 1, 1, 1, 0);
}


void init_intr_vec_table(void)
{
    extern u32 _CORE0_IRAM_START;
//    extern u32 _CORE1_IRAM_START;
    CpuSysRegs.CPU0EXPSTART.bit.EXPSTART = ((int)(&_CORE0_IRAM_START) >> 15) & 7;
//    CpuSysRegs.CPU1EXPSTART.bit.EXPSTART = ((int)(&_CORE1_IRAM_START) >> 15) & 7;
}

void qx_timer_confing(rt_uint32_t base, rt_uint32_t period, rt_uint16_t prescaler, rt_uint8_t int_flag)
{
    CPUTimer_stopTimer(base);
    CPUTimer_setPeriod(base, period);
    CPUTimer_setPreScaler(base, prescaler);

    if (int_flag)
    {
        if (base == CPUTIMER0_BASE)
            Interrupt_enable(INT_TIMER0);
        else if (base == CPUTIMER1_BASE)
            Interrupt_enable(INT_TIMER1);
        else
            Interrupt_enable(INT_TIMER2);
        CPUTimer_enableInterrupt(base);
    }
    else
    {
        if (base == CPUTIMER0_BASE)
            Interrupt_disable(INT_TIMER0);
        else if (base == CPUTIMER1_BASE)
            Interrupt_disable(INT_TIMER1);
        else
            Interrupt_disable(INT_TIMER2);
        CPUTimer_disableInterrupt(base);
    }
}

void rt_thread_system_tick_init(rt_uint32_t tick)
{
	SystemCoreClock = SysCtl_getClock(DEVICE_OSCSRC_FREQ);

	qx_timer_confing(CPUTIMER0_BASE, SystemCoreClock/tick, 0, 1);

	/* use lowest priority intr as soft intr */
//	qx_timer_confing(CPUTIMER1_BASE, SystemCoreClock-1, 0, 1);

	CPUTimer_startTimer(CPUTIMER0_BASE);
}

__interrupt void rt_thread_tick_intr(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();

    u32 val = CpuTimer0Regs.EOI;
}

void rt_hw_console_output(const char *str)
{
    while (*str)
    {
        while (!ScibRegs.LSR.bit.THRE)
            ;
        ScibRegs.THR = *str;
        while (!ScibRegs.LSR.bit.TEMT)
            ;
        str++;
    }
}

#define SYS_CLOCK_SOURCE        (DEVICE_OSCSRC_FREQ)
#define BAUDRATE_VALUE          (115200U)
#define BAUDRATE_CONFIG_INT     (SYS_CLOCK_SOURCE/(BAUDRATE_VALUE*16U))
#define BAUDRATE_CONFIG_FRI     ((SYS_CLOCK_SOURCE - \
                                    (BAUDRATE_CONFIG_INT*BAUDRATE_VALUE*16U))/BAUDRATE_VALUE)

void scib_hw_init(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIB);

    SCI_setConfig(&ScibRegs, BAUDRATE_CONFIG_INT, BAUDRATE_CONFIG_FRI,\
            SCI_DATA_8BITS, SCI_STOP_BIT_1, SCI_PARITY_NONE);

    SCI_enableFIFO(&ScibRegs);

    GPIO_Config(56, GPIO_56_SCIB_TX, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_Config(57, GPIO_57_SCIB_RX, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
}
