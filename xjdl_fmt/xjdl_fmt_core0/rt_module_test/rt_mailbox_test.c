#include <rtthread.h>
#include <rtdef.h>

#define THREAD_STACK_SIZE   1024
#define THREAD_PRIORITY     8
#define THREAD_TIME_SLICE   5

static struct rt_mailbox test_mailbox;

static rt_uint8_t mailbox_pool[128];

static char message1[] = "I'm a mail!";

static char message2[] = "this is another mail!";

static char message3[] = "over";

static rt_uint8_t th1_stack[THREAD_STACK_SIZE];

static struct rt_thread mail_th1;

static rt_uint8_t th2_stack[THREAD_STACK_SIZE];

static struct rt_thread mail_th2;

void mail_rec_th1_entry(void* parameter)
{
    char *str;
    while (1)
    {
        rt_kprintf("thread1: try to recv a mail\n");
        if (rt_mb_recv(&test_mailbox, (unsigned long *)&str, RT_WAITING_FOREVER) == RT_EOK)
        {
            rt_kprintf("thread1: get a mail from mailbox, the content:%s\n", str);
            if (str == message3)
            break;

            rt_thread_mdelay(100);
            }
    }

    rt_mb_detach(&test_mailbox);
}

void mail_send_th2_entry(void* parameter)
{
    rt_uint8_t count;
    count = 0;
    while (count < 10)
    {
        count ++;
        if (count & 0x1)
        {
            rt_mb_send(&test_mailbox, (rt_uint32_t)&message1);
        }
        else
        {
            rt_mb_send(&test_mailbox, (rt_uint32_t)&message2);
        }
        rt_thread_mdelay(200);
    }

    rt_mb_send(&test_mailbox, (rt_uint32_t)&message3);
}

void rt_mailbox_test_entry(void)
{
    rt_err_t res;

    res = rt_mb_init(&test_mailbox,"test_mb",mailbox_pool,(sizeof(mailbox_pool)/4),RT_IPC_FLAG_FIFO);

    if(res!=RT_EOK){
        rt_kprintf("init mailbox failed.\n");
        return;
    }

    rt_thread_init(&mail_th1,
                    "thread1",
                    mail_rec_th1_entry,
                    RT_NULL,
                    th1_stack,
                    sizeof(th1_stack),
                    THREAD_PRIORITY, THREAD_TIME_SLICE);
    rt_thread_startup(&mail_th1);

    rt_thread_init(&mail_th2,
                    "thread2",
                    mail_send_th2_entry,
                    RT_NULL,
                    th2_stack,
                    sizeof(th2_stack),
                    THREAD_PRIORITY, THREAD_TIME_SLICE);
    rt_thread_startup(&mail_th2);

    return;
}
