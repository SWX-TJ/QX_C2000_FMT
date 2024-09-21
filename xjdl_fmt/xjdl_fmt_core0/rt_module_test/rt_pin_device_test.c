#include <rtthread.h>
#include <rtdevice.h>
#if defined(RT_USING_PIN)

#define TEST_PIN_NUM  14

void pin_sample(void)
{
    rt_pin_mode(TEST_PIN_NUM,PIN_MODE_OUTPUT);
    rt_pin_write(TEST_PIN_NUM,0);
}

void pin_change_output_value(rt_uint32_t count)
{
    rt_pin_write(TEST_PIN_NUM,count%2);
}

void pin_isr_callback(void* arg)
{
    if(arg == RT_NULL){
        rt_kprintf("xint1 call back\n\r");
    }
}

void pin_irq_sample(void)
{
    rt_err_t rst = 0;

    rt_pin_mode(TEST_PIN_NUM,PIN_MODE_INPUT);

    rst = rt_pin_attach_irq(TEST_PIN_NUM,PIN_IRQ_MODE_RISING,pin_isr_callback,RT_NULL);

    if(rst != RT_EOK){
        rt_kprintf("pin irq attach error\n");
        return;
    }

    rst = rt_pin_irq_enable(TEST_PIN_NUM,PIN_IRQ_ENABLE);

    if(rst != RT_EOK){
        rt_kprintf("pin irq enable error\n");
        return;
    }

}
#endif
