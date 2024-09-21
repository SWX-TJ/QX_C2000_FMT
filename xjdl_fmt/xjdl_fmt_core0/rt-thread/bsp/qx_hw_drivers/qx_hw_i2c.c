#include "board_config.h"
#include "qx_hw_i2c.h"
#include "i2c_config.h"
#include "sysctl.h"
#include "interrupt.h"
#include "pmbus.h"
#include "gpio.h"
#include "cpu_port.h"
#include <rtdevice.h>
#include "device.h"


void I2cSetFrequency(volatile struct I2C_REGS * address, uint32_t frequency)
{
    if(frequency <= I2CFREQ_NORMAL)
    {
        address->IC_CON.bit.SPEED = 0x01;
        address->IC_SS_SCL_HCNT.all = (uint16_t)(SystemCoreClock / frequency / 2 - 1);
        address->IC_SS_SCL_LCNT.all = (uint16_t)(SystemCoreClock / frequency / 2 - 1);
    }
    else if(frequency <= I2CFREQ_RAPID)
    {
        address->IC_CON.bit.SPEED = 0x02;
        address->IC_FS_SCL_HCNT.all = (uint16_t)(SystemCoreClock / frequency / 2);
        address->IC_FS_SCL_LCNT.all = (uint16_t)(SystemCoreClock / frequency / 2);
    }
    else if(frequency <= I2CFREQ_HIGHSPEED)
    {
        //address->IC_CON.bit.SPEED = 0x03;
    }
    else
    {

    }
}

rt_ssize_t qx_master_xfer(struct rt_i2c_bus_device *bus,struct rt_i2c_msg msgs[],rt_uint32_t num)
{
    rt_int32_t i, ret;
    struct rt_i2c_msg *msg = RT_NULL;
    struct qx_i2c_t *i2c_obj;
    struct rt_completion *completion;

    if(!num){
       return 0;
    }

    i2c_obj = rt_container_of(bus, struct qx_i2c_t, i2c_bus);
    completion = &(i2c_obj->completion);

    for(rt_uint32_t i = 0;i < num;i++){
        msg = &msgs[i];

        /* master read */
        if(msg->flags == RT_I2C_RD){

        }
        /* master write */
        else if(msg->flags == RT_I2C_WR){

        }

    }

    return ret;
}

//rt_ssize_t qx_slave_xfer(struct rt_i2c_bus_device *bus,struct rt_i2c_msg msgs[],rt_uint32_t num)
//{
//
//}
//
//rt_err_t qx_i2c_bus_control(struct rt_i2c_bus_device *bus,int cmd,void *args)
//{
//
//}

const struct rt_i2c_bus_device_ops qx_i2c_ops =
{
    .master_xfer =  qx_master_xfer,
    .slave_xfer = RT_NULL,
    .i2c_bus_control =  RT_NULL,
};

static struct qx_i2c_board_config i2c_board_config[] =
{
#if defined(BOARD_CFG_I2CA)
        I2CA_CONFIG,
#endif

#if defined(BOARD_CFG_PMBUS_I2CB)

#endif
};

static struct i2c_parameter_config i2c_parameter[] =
{
#if defined(BOARD_CFG_I2CA)
        I2CA_PARAMETER_CONFIG,
#endif

#if defined(BOARD_CFG_PMBUS_I2CB)

#endif

};

static struct qx_i2c_t qx_i2c_obj[sizeof(i2c_board_config)/sizeof(struct qx_i2c_board_config)] = {0};


static void qx_enable_i2c_clockgate(volatile struct I2C_REGS* ins)
{
    if(ins == &I2caRegs){
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
    }else if(ins == (volatile struct I2C_REGS*)&PmbusaRegs){
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PMBUSA);
    }

    return;
}


static rt_err_t qx_i2c_gpio_config(struct qx_i2c_board_config* cfg)
{
    GPIO_PinMux scl_pin_mux,sda_pin_mux;

    if(cfg->instance == &I2caRegs){
        switch(cfg->sda_pin_num){
            case 0: sda_pin_mux = GPIO_0_I2CA_SDA; break;
            case 10: sda_pin_mux = GPIO_10_I2CA_SDA; break;
            case 26: sda_pin_mux = GPIO_26_I2CA_SDA; break;
            case 32: sda_pin_mux = GPIO_32_I2CA_SDA; break;
            case 35: sda_pin_mux = GPIO_35_I2CA_SDA; break;
            default: sda_pin_mux = 0xffUL; break;
        }

        switch(cfg->scl_pin_num){
            case 1: scl_pin_mux = GPIO_1_I2CA_SCL; break;
            case 8: scl_pin_mux = GPIO_8_I2CA_SCL; break;
            case 27: scl_pin_mux = GPIO_27_I2CA_SCL; break;
            case 33: scl_pin_mux = GPIO_33_I2CA_SCL; break;
            case 37: scl_pin_mux = GPIO_37_I2CA_SCL; break;
            case 41: scl_pin_mux = GPIO_41_I2CA_SCL; break;
            default: scl_pin_mux = 0xffUL; break;
        }
    }else if(cfg->instance == (volatile struct I2C_REGS*)&PmbusaRegs){
        switch(cfg->sda_pin_num){
            case 2: sda_pin_mux = GPIO_2_PMBUSA_SDA; break;
            case 14: sda_pin_mux = GPIO_14_PMBUSA_SDA; break;
            case 17: sda_pin_mux = GPIO_17_PMBUSA_SDA; break;
            case 25: sda_pin_mux = GPIO_25_PMBUSA_SDA; break;
            case 34: sda_pin_mux = GPIO_34_PMBUSA_SDA; break;
            case 40: sda_pin_mux = GPIO_40_PMBUSA_SDA; break;
            default: sda_pin_mux = 0xffUL; break;
        }

        switch(cfg->scl_pin_num){
            case 3: scl_pin_mux = GPIO_3_PMBUSA_SCL; break;
            case 15: scl_pin_mux = GPIO_15_PMBUSA_SCL; break;
            case 17: scl_pin_mux = GPIO_16_PMBUSA_SCL; break;
            case 24: scl_pin_mux = GPIO_24_PMBUSA_SCL; break;
            case 35: scl_pin_mux = GPIO_35_PMBUSA_SCL; break;
            default: scl_pin_mux = 0xffUL; break;
        }
    }

    if(sda_pin_mux == 0xffUL || scl_pin_mux == 0xffUL){
        return -RT_ERROR;
    }else{
        GPIO_Config(cfg->scl_pin_num,scl_pin_mux,GPIO_DIR_MODE_OUT,GPIO_PIN_TYPE_OD | GPIO_PIN_TYPE_PULLUP,GPIO_QUAL_SYNC);
        GPIO_Config(cfg->sda_pin_num,sda_pin_mux,GPIO_DIR_MODE_OUT,GPIO_PIN_TYPE_OD | GPIO_PIN_TYPE_PULLUP,GPIO_QUAL_SYNC);
    }

    return RT_EOK;
}

static void qx_i2c_parameter_config(struct qx_i2c_t* current_i2c)
{
    volatile struct I2C_REGS* ins = current_i2c->board_config->instance;

    struct i2c_parameter_config* para = current_i2c->parameter_config;


    /* first disable i2c module */
    I2cPeripheralEnable(ins,I2CDISABLE);

    I2cSetFrequency(ins,para->speed);

    if(para->mode == I2C_MATER_MODE){
        I2cSetRole(ins,I2CROLE_MASTER);
        I2cEnableRestart(ins,I2CENABLE);
    }else if(para->mode == I2C_SLAVE_MODE){
        I2cSetRole(ins,I2CROLE_SLAVE);
    }

    if(para->address_mode == I2C_7BIT){
        I2cSetAddrBitWide(ins,I2CBITWIDE_7);
    }else if(para->address_mode == I2C_10BIT){
        I2cSetAddrBitWide(ins,I2CBITWIDE_10);
    }

    I2CSetSelfId(ins,para->slave_address);

    I2CSetDestId(ins,para->master_address);

    /* disable all interrupt */
    I2cInterruptInitial(ins);

    /* open needed interrupt */
    I2CEnableInterrupt(ins,I2CINTERRUPT_RXFULL,I2CENABLE);

    I2cPeripheralEnable(ins,I2CENABLE);

    if(ins == &I2caRegs){
        Interrupt_enable(INT_I2CA);
    }else if(ins == (volatile struct I2C_REGS*)&PmbusaRegs){
        Interrupt_enable(INT_PMBUSA);
    }
}

static rt_err_t qx_i2c_config(struct rt_i2c_bus_device *bus)
{
    rt_err_t rst = RT_EOK;

    struct qx_i2c_t* current_i2c = rt_container_of(bus, struct qx_i2c_t, i2c_bus);

    struct qx_i2c_board_config* board_cfg = current_i2c->board_config;

    struct i2c_parameter_config* parameter = current_i2c->parameter_config;

    qx_enable_i2c_clockgate(board_cfg->instance);

    rst = qx_i2c_gpio_config(board_cfg);

    qx_i2c_parameter_config(current_i2c);

    return rst;
}

rt_err_t rt_hw_i2c_init(void)
{
    rt_err_t rst = RT_EOK;
    rt_uint32_t obj_num = sizeof(qx_i2c_obj)/sizeof(struct qx_i2c_t);

    for(rt_uint32_t i = 0; i < obj_num; i++){
        qx_i2c_obj[i].board_config = &i2c_board_config[i];
        qx_i2c_obj[i].parameter_config = &i2c_parameter[i];
        qx_i2c_obj[i].i2c_bus.ops = &qx_i2c_ops;
        qx_i2c_obj[i].i2c_bus.timeout = i2c_board_config[i].timeout;

        rt_completion_init(&qx_i2c_obj[i].completion);

        qx_i2c_config(&qx_i2c_obj[i].i2c_bus);

        rst = rt_i2c_bus_device_register(&qx_i2c_obj[i].i2c_bus, qx_i2c_obj[i].board_config->name);
    }
    return rst;
}

#if defined(BOARD_CFG_I2CA)
__interrupt void i2ca_isr(void)
{

}
#endif

#if defined(BOARD_CFG_PMBUS_I2CB)
__interrupt void pmbus_isr(void)
{

}
#endif
