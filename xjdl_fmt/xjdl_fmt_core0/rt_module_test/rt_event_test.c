#include <rtthread.h>
#include <rtdef.h>

#define THREAD_PRIORITY   8
#define THREAD_STACK_SIZE   1024
#define THREAD_TIME_SLICE   5

#define FLAG3  (1UL<<3)
#define FLAG5  (1UL<<5)

static struct rt_event test_event;

static rt_uint8_t th1_stack[THREAD_STACK_SIZE];

static struct rt_thread event_th1;

static rt_uint8_t th2_stack[THREAD_STACK_SIZE];
static struct rt_thread event_th2;

void thread1_rec_event_entry(void* parameter)
{
    rt_uint32_t event_value;

    if (rt_event_recv(&test_event, (FLAG3 | FLAG5),
            RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
            RT_WAITING_FOREVER, &event_value) == RT_EOK)
    {
        rt_kprintf("thread1: OR recv event 0x%x\n", event_value);
    }

    rt_kprintf("thread1: delay 1s to prepare the second event\n");
    rt_thread_mdelay(1000);

    if (rt_event_recv(&test_event, (FLAG3 | FLAG5),
            RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
            RT_WAITING_FOREVER, &event_value) == RT_EOK)
    {
        rt_kprintf("thread1: AND recv event 0x%x\n", event_value);
    }

    rt_kprintf("thread1 leave.\n");

}

void thread2_send_event_entry(void* parameter)
{
    rt_kprintf("thread2: send event3\n");
    rt_event_send(&test_event, FLAG3);
    rt_thread_mdelay(200);

    rt_kprintf("thread2: send event5\n");
    rt_event_send(&test_event, FLAG5);
    rt_thread_mdelay(200);

    rt_kprintf("thread2: send event3\n");
    rt_event_send(&test_event, FLAG3);
    rt_kprintf("thread2 leave.\n");
}


void rt_event_test_entry(void)
{
    rt_err_t res;

    res = rt_event_init(&test_event,"tstEve",RT_IPC_FLAG_FIFO);

    if(res != RT_EOK){
        rt_kprintf("init event failed.\n");
        return;
    }

    rt_thread_init(&event_th1,
                    "event_th1",
                    thread1_rec_event_entry,
                    RT_NULL,
                    th1_stack,
                    sizeof(th1_stack),
                    THREAD_PRIORITY - 1, THREAD_TIME_SLICE);

    rt_thread_startup(&event_th1);

    rt_thread_init(&event_th2,
                    "event_th2",
                    thread2_send_event_entry,
                    RT_NULL,
                    th2_stack,
                    sizeof(th2_stack),
                    THREAD_PRIORITY, THREAD_TIME_SLICE);

    rt_thread_startup(&event_th2);

    return;
}



