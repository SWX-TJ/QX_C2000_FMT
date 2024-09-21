#include <rtthread.h>
#include <rtdef.h>
#include <rtdevice.h>


rt_uint32_t test_cnt = 0;
rt_uint32_t test_cnt1 = 0;
rt_uint32_t test_cnt2 = 0;
rt_uint32_t test_cnt3 = 0;
rt_thread_t th1_ptr = RT_NULL;
rt_thread_t th2_ptr = RT_NULL;
rt_thread_t th3_ptr = RT_NULL;


void th2_entry(void* parameter)
{
    while(1){
        rt_kprintf("th2");
        rt_thread_mdelay(2000);
    }
}

rt_ssize_t led_flip = 0;

void th1_entry(void* parameter)
{
    while(1){
        rt_kprintf("th1\n\r");
        if(!led_flip){
            led_flip++;
        }else{
            led_flip = 0;
        }
        rt_pin_write(59,led_flip);
        rt_thread_mdelay(1000);
    }
}

void th3_entry(void* parameter)
{
    rt_uint32_t para = *((rt_uint32_t*)parameter);
    if(para == 0x55){
        for(rt_uint8_t i = 0;i < 3;i++){
            rt_kprintf("th3_cnt: %d\n\r", i);
        }
    }
}

rt_uint32_t* th3_key;

void rt_thread_test_entry(void)
{
    *th3_key = 0x55;

    rt_pin_mode(59,PIN_MODE_OUTPUT);

    th1_ptr = rt_thread_create("TH1",th1_entry,RT_NULL,1024,10,10);
    th2_ptr = rt_thread_create("TH2",th2_entry,RT_NULL,1024,10,10);
    th3_ptr = rt_thread_create("TH3",th3_entry,(void*)th3_key,1024,7,10);

    if(th1_ptr!=RT_NULL)
        rt_thread_startup(th1_ptr);

    if(th2_ptr!=RT_NULL)
        rt_thread_startup(th2_ptr);

    if(th3_ptr!=RT_NULL)
        rt_thread_startup(th3_ptr);



}
