#include <rtthread.h>
#include <rtdef.h>

/*************************************************************************************************************/
/* test1 */
#define THREAD_STACK_SIZE   512

static rt_sem_t dynamic_sem = RT_NULL;


static rt_uint8_t thread1_stack[THREAD_STACK_SIZE];

static struct rt_thread thread1;

static void thread1_entry(void* parameter)
{
    static rt_uint8_t count = 0;
    while(1)
    {
        if(count <= 100)
        {
            count++;
        }
        else
            return;
        if(0 == (count % 10))
        {
            rt_kprintf("t1 release a dynamic semaphore.\n");
            rt_sem_release(dynamic_sem);
        }
    }
}



static rt_uint8_t thread2_stack[THREAD_STACK_SIZE];

static struct rt_thread thread2;

static void thread2_entry(void* parameter)
{
    static rt_err_t result;
    static rt_uint8_t number = 0;
    while(1)
    {
        result = rt_sem_take(dynamic_sem, RT_WAITING_FOREVER);
        if (result != RT_EOK)
        {
            rt_kprintf("t2 take a dynamic semaphore, failed.\n");
            rt_sem_delete(dynamic_sem);
            return;
        }
        else
        {
            number++;
            rt_kprintf("t2 take a dynamic semaphore. number = %d\n" ,number);
        }
    }
}

int rt_thread_sem_test_entry(void)
{
    dynamic_sem = rt_sem_create("dy_sem",0,RT_IPC_FLAG_FIFO);

    if (dynamic_sem == RT_NULL)
    {
        rt_kprintf("create dynamic semaphore failed.\n");
        return -1;
    }
    else
    {
        rt_kprintf("create done. dynamic semaphore value = 0.\n");
    }

    rt_thread_init(&thread1,"th1",thread1_entry,RT_NULL,thread1_stack,sizeof(thread1_stack),25,5);
    rt_thread_startup(&thread1);

    rt_thread_init(&thread2,"th2",thread2_entry,RT_NULL,thread2_stack,sizeof(thread2_stack),24,5);
    rt_thread_startup(&thread2);

    return 0;
}

/**********************************************************************************************/
/* test2 */
struct rt_semaphore sem_empty,sem_full;
struct rt_semaphore sem_lock;

rt_thread_t producer_tid = RT_NULL;
rt_thread_t consumer_tid = RT_NULL;

static rt_uint32_t array[5];

static rt_uint32_t set,get;


void producer_entry(void* parameter)
{
    rt_uint8_t cnt = 0;

    while(cnt < 10){

        rt_sem_take(&sem_empty,RT_WAITING_FOREVER);

        rt_sem_take(&sem_lock,RT_WAITING_FOREVER);

        array[set%5] = cnt+1;
        rt_kprintf("product generate number: %d\n\r",array[set%5]);
        set++;

        rt_sem_release(&sem_lock);

        rt_sem_release(&sem_full);

        cnt++;

        rt_thread_mdelay(10);

    }

    rt_kprintf("product exit\n\r");
}


void consumer_entry(void* parameter)
{
    rt_uint32_t sum = 0;

    while(1){

        rt_sem_take(&sem_full,RT_WAITING_FOREVER);

        rt_sem_take(&sem_lock,RT_WAITING_FOREVER);

        sum += array[get%5];
        rt_kprintf("the consumer[%d] get a number: %d\n", (get%5), array[get%5]);
        get++;

        rt_sem_release(&sem_lock);

        rt_sem_release(&sem_empty);

        if(get == 10)
            break;

        rt_thread_mdelay(50);
    }

    rt_kprintf("the consumer sum is: %d\n", sum);
    rt_kprintf("the consumer exit!\n");
}

void producer_consumer_test_entry(void)
{

    rt_sem_init(&sem_lock,"lock",1,RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_empty,"empty",5,RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_full,"full",0,RT_IPC_FLAG_FIFO);

    producer_tid = rt_thread_create("producer",producer_entry,RT_NULL,1024,5,5);

    if(producer_tid!=RT_NULL){
        rt_thread_startup(producer_tid);
    }

    consumer_tid = rt_thread_create("consumer",consumer_entry,RT_NULL,1024,7,5);

    if(consumer_tid!=RT_NULL){
        rt_thread_startup(consumer_tid);
    }

    return;
}
