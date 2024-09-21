#include <rtthread.h>
#include <rtdef.h>

/*****************************************************************************************************************/
/*
 * test1 variable protected by mutex
 */
#define THREAD_STACK_SIZE   1024
#define THREAD_PRIORITY     8
#define THREAD_TIME_SLICE   5

static rt_mutex_t dynamic_mutex = RT_NULL;

static rt_uint8_t number1,number2;

static struct rt_thread mutex_th1;
static struct rt_thread mutex_th2;

static rt_uint8_t mutex_th1_stack[THREAD_STACK_SIZE];
static rt_uint8_t mutex_th2_stack[THREAD_STACK_SIZE];

void mutex_th1_entry(void* parameter)
{
    while(1)
    {
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
        number1++;
        rt_thread_mdelay(10);
        number2++;
        rt_mutex_release(dynamic_mutex);
        if(number1>=50)
            return;
    }
}

void mutex_th2_entry(void* parameter)
{
    while(1)
    {
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
        if(number1 != number2)
        {
            rt_kprintf("not protect.number1 = %d, mumber2 = %d \n",number1 ,number2);
        }
        else
        {
            rt_kprintf("mutex protect ,number1 = mumber2 is %d\n",number1);
        }
        number1++;
        number2++;
        rt_mutex_release(dynamic_mutex);
        if(number1>=50)
            return;
    }
}

void mutex_test_entry(void)
{
    dynamic_mutex = rt_mutex_create("dynamic",RT_IPC_FLAG_FIFO);

    if(dynamic_mutex==RT_NULL){
        rt_kprintf("create dynamic mutex failed.\n");
        return;
    }

    rt_thread_init(&mutex_th1,"mutex1",mutex_th1_entry,RT_NULL,mutex_th1_stack,sizeof(mutex_th1_stack),THREAD_PRIORITY,THREAD_TIME_SLICE);
    rt_thread_startup(&mutex_th1);
    rt_thread_init(&mutex_th2,"mutex2",mutex_th2_entry,RT_NULL,mutex_th2_stack,sizeof(mutex_th2_stack),THREAD_PRIORITY,THREAD_TIME_SLICE);
    rt_thread_startup(&mutex_th2);

    return;
}
/*****************************************************************************************************************/
/*
 * test2
 */

static rt_thread_t mutex_tid1 = RT_NULL;
static rt_thread_t mutex_tid2 = RT_NULL;
static rt_thread_t mutex_tid3 = RT_NULL;

static rt_mutex_t test2_mutex = RT_NULL;

void mutex_tid1_entry(void* parameter)
{
    rt_thread_mdelay(100);

    if(mutex_tid2->current_priority != mutex_tid3->current_priority){
        rt_kprintf("the priority of thread2 is: %d\n", mutex_tid2->current_priority);
        rt_kprintf("the priority of thread3 is: %d\n", mutex_tid3->current_priority);
        rt_kprintf("test failed.\n");
    }else{
        rt_kprintf("the priority of thread2 is: %d\n", mutex_tid2->current_priority);
        rt_kprintf("the priority of thread3 is: %d\n", mutex_tid2->current_priority);
        rt_kprintf("test OK.\n");
    }

    return;
}

void mutex_tid2_entry(void* parameter)
{
    rt_err_t res;

    rt_kprintf("the priority of thread2 is: %d\n", mutex_tid2->current_priority);

    rt_thread_mdelay(50);

    res = rt_mutex_take(test2_mutex, RT_WAITING_FOREVER);
    if (res == RT_EOK)
    {
        rt_mutex_release(test2_mutex);
    }

}

void mutex_tid3_entry(void* parameter)
{
    rt_tick_t tick;
    rt_err_t res;

    rt_kprintf("the priority of thread3 is: %d\n", mutex_tid3->current_priority);

    res = rt_mutex_take(test2_mutex, RT_WAITING_FOREVER);
    if (res != RT_EOK)
    {
        rt_kprintf("thread3 take a mutex, failed.\n");
    }

    tick = rt_tick_get();
    while (rt_tick_get() - tick < (RT_TICK_PER_SECOND / 2)) ;

    rt_mutex_release(test2_mutex);

    return;
}

void mutex_priority_test_entry(void)
{
    test2_mutex = rt_mutex_create("test2",RT_IPC_FLAG_FIFO);

    if (test2_mutex == RT_NULL)
    {
        rt_kprintf("create test2 mutex failed.\n");
        return;
    }

    mutex_tid1 = rt_thread_create("tid1",mutex_tid1_entry,RT_NULL,THREAD_STACK_SIZE,THREAD_PRIORITY-1,THREAD_TIME_SLICE);

    if(mutex_tid1 != RT_NULL){
        rt_thread_startup(mutex_tid1);
    }

    mutex_tid2 = rt_thread_create("tid2",mutex_tid2_entry,RT_NULL,THREAD_STACK_SIZE,THREAD_PRIORITY,THREAD_TIME_SLICE);

    if(mutex_tid2 != RT_NULL){
        rt_thread_startup(mutex_tid2);
    }

    mutex_tid3 = rt_thread_create("tid3",mutex_tid3_entry,RT_NULL,THREAD_STACK_SIZE,THREAD_PRIORITY+1,THREAD_TIME_SLICE);

    if(mutex_tid3 != RT_NULL){
        rt_thread_startup(mutex_tid3);
    }

    return;
}


