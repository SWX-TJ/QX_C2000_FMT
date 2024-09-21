#ifndef QX_HW_SERIAL_H
#define QX_HW_SERIAL_H

#include <rtthread.h>
#include <rtdevice.h>
#include "serial.h"
#include <sci.h>
#include <interrupt.h>
#include "dma.h"


typedef struct{
    DMA_ConfigParams* dma_param;
    rt_uint8_t channel;
}qx_dma_config_t;

struct qx_serial_board_config {
    const char* name;
    volatile struct SCI_REGS *instance;
    INTERRUPT_Type intr_type;
    rt_uint32_t rx_pin_num;
    rt_uint32_t tx_pin_num;
#if defined(RT_SERIAL_USING_DMA)
    DMA_ConfigParams* serial_rx_dma;
    DMA_ConfigParams* serial_tx_dma;
    rt_uint8_t rx_channel;
    rt_uint8_t tx_channel;
#endif
};

struct qx_serial_t{
    struct qx_serial_board_config* board_config;
    rt_uint16_t serial_dma_flag;
    struct rt_serial_device serial_arch;
};

extern rt_err_t rt_hw_serial_init(void);

#endif
