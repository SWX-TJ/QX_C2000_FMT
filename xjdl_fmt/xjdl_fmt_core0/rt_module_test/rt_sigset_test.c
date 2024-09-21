#include <rtthread.h>
#include <rtdef.h>

#define THREAD_STACK_SIZE 1024
#define THREAD_PRIOIRTY   25
#define THREAD_TIMESLICE   5


rt_thread_t sigset_th1 = RT_NULL;


void thread1_signal_handler(int sig)
{
    rt_kprintf("thread1 received signal %d\n", sig);
}


void sigset_test_thread1_entry(void* parameter)
{
    int cnt = 0;


}
