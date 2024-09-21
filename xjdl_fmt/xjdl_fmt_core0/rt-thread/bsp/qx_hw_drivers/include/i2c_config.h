#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H

#include "board_config.h"
#include "qx_hw_i2c.h"

#if defined(BOARD_CFG_I2CA)
#ifndef I2CA_CONFIG
#define I2CA_CONFIG                     \
    {                                   \
        .name = "I2CA",                 \
        .instance = &I2caRegs,          \
        .intr_type = INT_I2CA,          \
        .scl_pin_num = 0,               \
        .sda_pin_num = 1,               \
    }
#endif
#endif

#if defined(BOARD_CFG_I2CA)
#ifndef I2CA_PARAMETER_CONFIG
#define I2CA_PARAMETER_CONFIG           \
        {                               \
            .mode = I2C_MATER_MODE,     \
            .speed = 100000UL,          \
            .address_mode = I2C_7BIT,   \
            .master_address = 0x00,     \
            .slave_address = 0x5A,      \
        }
#endif
#endif



#endif
