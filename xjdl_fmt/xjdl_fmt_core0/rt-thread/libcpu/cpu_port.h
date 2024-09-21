#ifndef CPU_PORT_H
#define CPU_PORT_H

#include "device.h"
#include "rttypes.h"

void SystemCoreClockUpdate(void);
void rt_thread_system_tick_init(rt_uint32_t tick);
void erad_cmt_mode_init(void);
void init_intr_vec_table(void);
extern void StdOutInit(volatile struct SCI_REGS *sci, int baudrate, uint32_t pin, GPIO_PinMux pin_mux);
extern void scib_hw_init(void);
extern rt_base_t rt_hw_interrupt_disable(void);
extern void rt_hw_interrupt_enable(rt_base_t level);
extern uint32_t SystemCoreClock;


extern void test_loacation(void);
#endif


