#ifndef QX_HW_I2C_H
#define QX_HW_I2C_H
#include <rtdevice.h>
#include "q28004x_i2c.h"
#include "interrupt.h"

struct qx_i2c_board_config{
    const char* name;
    volatile struct I2C_REGS* instance;
    INTERRUPT_Type intr_type;
    rt_uint32_t scl_pin_num;
    rt_uint32_t sda_pin_num;
    rt_uint32_t timeout;
};

struct i2c_parameter_config{
    rt_uint8_t mode;
    rt_uint32_t speed;
    rt_uint8_t address_mode;
    rt_uint16_t master_address;
    rt_uint16_t slave_address;
};

struct qx_i2c_t{
    struct qx_i2c_board_config* board_config;
    struct i2c_parameter_config* parameter_config;
    struct rt_i2c_bus_device    i2c_bus;
    rt_uint8_t                  i2c_dma_flag;
    struct rt_completion completion;
};

/******************************************************/
#define I2C_MATER_MODE      0x01
#define I2C_SLAVE_MODE      0x02

#define I2C_7BIT            0x01
#define I2C_8BIT            0x02
#define I2C_10BIT           0x03

#endif
