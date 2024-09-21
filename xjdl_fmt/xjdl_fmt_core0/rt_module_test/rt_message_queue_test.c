#include <rtthread.h>
#include <rtdef.h>

#define THREAD_STACK_SIZE 1024
#define THREAD_PRIOIRTY    25
#define THREAD_TIME_SLICE   5

struct rt_messagequeue test_message;
static rt_uint8_t msg_pool[2048];

static struct rt_thread mq_test_th1;
rt_uint8_t th1_stack[THREAD_STACK_SIZE];

static struct rt_thread mq_test_th2;
rt_uint8_t th2_stack[THREAD_STACK_SIZE];

void mq_thread1_entry(void* parameter)
{
    rt_uint8_t buf = 0;
    rt_uint8_t cnt = 0;
    while (1)
    {
        if (rt_mq_recv(&test_message, &buf, sizeof(buf), RT_WAITING_FOREVER) == RT_EOK)
        {
            rt_kprintf("thread1: recv msg from msg queue, the content:%c\n\r", buf);
            if (cnt == 19)
            {
                break;
            }
        }
        cnt++;
        rt_thread_mdelay(50);
    }

    rt_kprintf("thread1: detach mq \n\r");
    rt_mq_detach(&test_message);
}

void mq_thread2_entry(void* parameter)
{
    int result;
    char buf = 'A';
    rt_uint8_t cnt = 0;

    while (1){
        if (cnt == 8){
            result = rt_mq_urgent(&test_message, &buf, 1);
            if (result != RT_EOK)
            {
                rt_kprintf("rt_mq_urgent ERR\n");
            }
            else
            {
                rt_kprintf("thread2: send urgent message - %c\n\r", buf);
            }
        }
        else if (cnt>= 20){
            rt_kprintf("message queue stop send, thread2 quit\n\r");
            break;
        }
        else{
            result = rt_mq_send(&test_message, &buf, 1);
            if (result != RT_EOK)
            {
                rt_kprintf("rt_mq_send ERR\n\r");
            }
            rt_kprintf("thread2: send message - %c\n\r", buf);
        }

        buf++;
        cnt++;
        rt_thread_mdelay(5);
    }
}

void rt_message_queue_test_entry(void)
{
    rt_err_t result;
    result = rt_mq_init(&test_message,
                        "mqtest",
                        &msg_pool[0],
                        1,
                       sizeof(msg_pool),
                       RT_IPC_FLAG_FIFO);

    if (result != RT_EOK)
    {
        rt_kprintf("init message queue failed.\n");
        return;
    }

    rt_thread_init(&mq_test_th1,"mqt1",mq_thread1_entry,RT_NULL,th1_stack,sizeof(th1_stack),THREAD_PRIOIRTY,THREAD_TIME_SLICE);
    rt_thread_startup(&mq_test_th1);

    rt_thread_init(&mq_test_th2,"mqt2",mq_thread2_entry,RT_NULL,th2_stack,sizeof(th2_stack),THREAD_PRIOIRTY,THREAD_TIME_SLICE);
    rt_thread_startup(&mq_test_th2);

    return;
}


