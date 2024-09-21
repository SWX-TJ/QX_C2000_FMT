#include <rtthread.h>
#include <rtdevice.h>
#include "cpu_port.h"


#define TEST_SERIAL_NAME    "SCIB"
#define TEST_MSG_POOL_SIZE  256
char msg_pool[TEST_MSG_POOL_SIZE];

struct rx_msg{
    rt_device_t dev;
    rt_size_t size;
};


rt_device_t serial_test;

struct rt_messagequeue rx_mq;

static rt_err_t serial_send_what_had_received(rt_device_t dev, rt_size_t size)
{
    struct rx_msg msg;
    rt_err_t result;
    msg.dev = dev;
    msg.size = size;
    result = rt_mq_send(&rx_mq, &msg, sizeof(msg));
    if (result == -RT_EFULL)
    {
        rt_kprintf("message queue full！\n");
    }
    return result;
}

static void serial_test_entry(void* para)
{
    struct rx_msg msg;
    rt_err_t result;
    rt_uint32_t rx_length;
    static char rx_buffer[RT_SERIAL_RB_BUFSZ + 1];
    while (1)
    {
        rt_memset(&msg, 0, sizeof(msg));
        result = rt_mq_recv(&rx_mq, &msg, sizeof(msg), RT_WAITING_FOREVER);
        if (result != 0)
        {
            rx_length = rt_device_read(msg.dev, 0, rx_buffer, msg.size);
            rx_buffer[rx_length] = '\0';
            rx_buffer[rx_length+1] = '\n';
            rt_device_write(serial_test, 0, rx_buffer, rx_length);
        }
    }
}

int serial_dma_sample(int argc, char *argv[])
{
    rt_err_t rst = RT_EOK;

    char serial_name[RT_NAME_MAX];

    char test_str[] = "serial dma sample!\n\r";

    if(argc == 2){
        rt_strncpy(serial_name, argv[1], RT_NAME_MAX);
    }else{
        rt_strncpy(serial_name, TEST_SERIAL_NAME, RT_NAME_MAX);
    }

    serial_test = rt_device_find(serial_name);

    if(!serial_test){
        rt_kprintf("test_serial open fail!\n\r");
        return RT_ERROR;
    }

    /* buffer of serial receive */
    rt_mq_init(&rx_mq, "mq_test",
               msg_pool,
               sizeof(struct rx_msg),
               sizeof(msg_pool),
               RT_IPC_FLAG_FIFO);

    rt_device_open(serial_test, RT_DEVICE_FLAG_DMA_TX | RT_DEVICE_FLAG_DMA_RX);

    rt_device_set_rx_indicate(serial_test, serial_send_what_had_received);

    rt_device_write(serial_test, 0, test_str, (sizeof(test_str) - 1));

    rt_thread_t thread = rt_thread_create("serial_test", serial_test_entry, RT_NULL,
                                           1024, 10, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rst = RT_ERROR;
    }
    return rst;
}
