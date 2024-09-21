#include <rtdevice.h>

#include "gpio.h"
#include "qx_hw_gpio.h"

#if defined(RT_USING_PIN)
GPIO_PinNum qx_get_pin_index(rt_base_t user_pin_number)
{
    GPIO_PinNum index;

    for(index = 0;index < (GPIO_PIN_59+1);index++){
        if(index == user_pin_number){
            return index;
        }
    }

    return UNKNOW_PIN_NUMBER;
}

GPIO_PinMux qx_get_pin_mux(GPIO_PinNum pin_index)
{
    if(pin_index < GPIO_PIN_16){
        return (QX_GPIO_MUX_REG_VALUE_BASE1+pin_index*0x200UL);
    }else if(pin_index < GPIO_PIN_32){
        return (QX_GPIO_MUX_REG_VALUE_BASE2+(pin_index-GPIO_PIN_16)*0x200UL);
    }else if(pin_index < GPIO_PIN_48){
        return (QX_GPIO_MUX_REG_VALUE_BASE3+(pin_index-GPIO_PIN_32)*0x200UL);
    }
    else if(pin_index <= GPIO_PIN_59){
        return (QX_GPIO_MUX_REG_VALUE_BASE4+(pin_index-GPIO_PIN_48)*0x200UL);
    }

    return (GPIO_PinMux)0xffUL;
}

static void qx_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    GPIO_PinNum pin_convert = 0;

    pin_convert = qx_get_pin_index(pin);

    if(pin_convert == UNKNOW_PIN_NUMBER){
        return;
    }

    GPIO_writePin(pin_convert,value);
}

static rt_ssize_t qx_pin_read(struct rt_device* device,rt_base_t pin)
{
    GPIO_PinNum pin_convert = 0;
    rt_ssize_t rst = 0;

    pin_convert = qx_get_pin_index(pin);

    if(pin_convert == UNKNOW_PIN_NUMBER){
        return UNKNOW_PIN_NUMBER;
    }

    rst = GPIO_readPin(pin_convert);
    return rst;
}

static void qx_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_PinNum pin_convert = 0;

    pin_convert = qx_get_pin_index(pin);

    if(pin_convert == UNKNOW_PIN_NUMBER){
        return;
    }

    GPIO_PinMux pin_mux_reg_value = qx_get_pin_mux(pin_convert);

    if(pin_mux_reg_value == UNKNOW_PIN_MUX_VALUE){
        return;
    }

    GPIO_PinType pin_type = 0;
    GPIO_Direction pin_dir = 0;
//    GPIO_QualificationMode pin_qa_mode = GPIO_QUAL_SYNC;

    switch(mode){
        case PIN_MODE_OUTPUT: pin_type = GPIO_PIN_TYPE_STD; pin_dir = GPIO_DIR_MODE_OUT; break;
        case PIN_MODE_INPUT:  pin_type = GPIO_PIN_TYPE_STD; pin_dir = GPIO_DIR_MODE_IN; break;
        case PIN_MODE_INPUT_PULLUP: pin_type = GPIO_PIN_TYPE_PULLUP; pin_dir = GPIO_DIR_MODE_IN; break;
        case PIN_MODE_INPUT_PULLDOWN: pin_type = GPIO_PIN_TYPE_STD; pin_dir = GPIO_DIR_MODE_IN; break;
        case PIN_MODE_OUTPUT_OD:pin_type = GPIO_PIN_TYPE_OD; pin_dir = GPIO_DIR_MODE_OUT; break;
        default: break;
    }

    GPIO_Config(pin_convert,pin_mux_reg_value,pin_dir,pin_type,GPIO_QUAL_SYNC);
}


enum {
    PIN_IRQ_SLOT_1 = 0,
    PIN_IRQ_SLOT_2,
    PIN_IRQ_SLOT_3,
    PIN_IRQ_SLOT_4,
    PIN_IRQ_SLOT_5,
};


static struct rt_pin_irq_hdr pin_irq_hdr_array[] = {
        {-1,0,RT_NULL,RT_NULL},
        {-1,0,RT_NULL,RT_NULL},
        {-1,0,RT_NULL,RT_NULL},
        {-1,0,RT_NULL,RT_NULL},
        {-1,0,RT_NULL,RT_NULL},
};


static rt_uint32_t get_irq_array_empty_slot(void)
{
   for(rt_uint32_t i = 0; i < (sizeof(pin_irq_hdr_array)/sizeof(struct rt_pin_irq_hdr)); i++){
       if(pin_irq_hdr_array[i].pin == -1){
           return i;
       }
   }
   return NO_SLOT_IN_PIN_IRQ_ARRAY;
}


static rt_uint32_t get_irq_array_slot_index(rt_base_t pin)
{
    for(rt_uint32_t i = 0; i < (sizeof(pin_irq_hdr_array)/sizeof(struct rt_pin_irq_hdr)); i++){
        if(pin_irq_hdr_array[i].pin == pin){
            return i;
        }
    }
    return NO_SUITABLE_SLOT_IN_ARRAY;
}


rt_err_t qx_pin_attach_irq(struct rt_device *device, rt_base_t pin, rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level = 0;

    GPIO_PinNum pin_index = qx_get_pin_index(pin);

    if(pin_index == UNKNOW_PIN_NUMBER){
        return RT_ERROR;
    }

    rt_uint32_t slot = get_irq_array_empty_slot();

    if(slot == NO_SLOT_IN_PIN_IRQ_ARRAY){
        return RT_ERROR;
    }

    level = rt_hw_interrupt_disable();

    pin_irq_hdr_array[slot].pin = pin;
    pin_irq_hdr_array[slot].mode = mode;
    pin_irq_hdr_array[slot].hdr = hdr;
    pin_irq_hdr_array[slot].args = args;

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t qx_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{

    GPIO_PinNum pin_index = qx_get_pin_index(pin);

    if(pin_index == UNKNOW_PIN_NUMBER){
        return RT_ERROR;
    }

    rt_uint32_t detach_index = get_irq_array_slot_index(pin);

    if(detach_index == NO_SLOT_IN_PIN_IRQ_ARRAY){
        return RT_ERROR;
    }

    rt_base_t level = rt_hw_interrupt_disable();

    pin_irq_hdr_array[detach_index].pin = -1;
    pin_irq_hdr_array[detach_index].mode = 0;
    pin_irq_hdr_array[detach_index].hdr = RT_NULL;
    pin_irq_hdr_array[detach_index].args = RT_NULL;

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t qx_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{

    GPIO_PinNum pin_index = qx_get_pin_index(pin);

    if(pin_index == UNKNOW_PIN_NUMBER){
        return RT_ERROR;
    }

    rt_uint32_t array_index = get_irq_array_slot_index(pin);

    if(array_index == NO_SUITABLE_SLOT_IN_ARRAY){
       return RT_ERROR;
    }

    INTERRUPT_Type pin_irq = 0;

    switch(array_index){
        case 0: pin_irq = INT_XINT1; break;
        case 1: pin_irq = INT_XINT2; break;
        case 2: pin_irq = INT_XINT3; break;
        case 3: pin_irq = INT_XINT4; break;
        case 4: pin_irq = INT_XINT5; break;
        default: break;
    }

    if(enabled == PIN_IRQ_ENABLE){
        GPIO_IntType type = 0;
        switch(pin_irq_hdr_array[array_index].mode){
            case PIN_IRQ_MODE_RISING: type = GPIO_INT_TYPE_RISING_EDGE; break;
            case PIN_IRQ_MODE_FALLING: type = GPIO_INT_TYPE_FALLING_EDGE; break;
            case PIN_IRQ_MODE_RISING_FALLING: type = GPIO_INT_TYPE_BOTH_EDGES; break;
            default: break;
        }
        GPIO_setInterruptType(array_index,type);
        GPIO_setInterruptPin(pin_index,array_index);
        GPIO_enableInterrupt(array_index);
        Interrupt_enable(pin_irq);

    }else if(enabled == PIN_IRQ_DISABLE){
        GPIO_disableInterrupt(array_index);
        Interrupt_disable(pin_irq);
    }

    return RT_EOK;
}

static const struct rt_pin_ops qx_pin_ops = {
        .pin_mode = qx_pin_mode,
        .pin_write = qx_pin_write,
        .pin_read = qx_pin_read,
        .pin_attach_irq = qx_pin_attach_irq,
        .pin_detach_irq = qx_pin_detach_irq,
        .pin_irq_enable = qx_pin_irq_enable,
//        .pin_get = qx_pin_get,
};

int rt_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &qx_pin_ops, RT_NULL);
}
#endif
/**********************************************************************************************************/
#if defined(RT_USING_PIN)
/* irq routines */
__interrupt void xint1_isr(void)
{
    rt_interrupt_enter();

    if(pin_irq_hdr_array[PIN_IRQ_SLOT_1].hdr != RT_NULL){
        pin_irq_hdr_array[PIN_IRQ_SLOT_1].hdr(pin_irq_hdr_array[PIN_IRQ_SLOT_1].args);
    }

    rt_interrupt_leave();
}

__interrupt void xint2_isr(void)
{
    rt_interrupt_enter();

    if(pin_irq_hdr_array[PIN_IRQ_SLOT_2].hdr != RT_NULL){
        pin_irq_hdr_array[PIN_IRQ_SLOT_2].hdr(pin_irq_hdr_array[PIN_IRQ_SLOT_2].args);
    }

    rt_interrupt_leave();
}

__interrupt void xint3_isr(void)
{
    rt_interrupt_enter();

    if(pin_irq_hdr_array[PIN_IRQ_SLOT_3].hdr != RT_NULL){
        pin_irq_hdr_array[PIN_IRQ_SLOT_3].hdr(pin_irq_hdr_array[PIN_IRQ_SLOT_3].args);
    }

    rt_interrupt_leave();
}

__interrupt void xint4_isr(void)
{
    rt_interrupt_enter();

    if(pin_irq_hdr_array[PIN_IRQ_SLOT_4].hdr != RT_NULL){
        pin_irq_hdr_array[PIN_IRQ_SLOT_4].hdr(pin_irq_hdr_array[PIN_IRQ_SLOT_4].args);
    }

    rt_interrupt_leave();
}

__interrupt void xint5_isr(void)
{
    rt_interrupt_enter();

    if(pin_irq_hdr_array[PIN_IRQ_SLOT_5].hdr != RT_NULL){
        pin_irq_hdr_array[PIN_IRQ_SLOT_5].hdr(pin_irq_hdr_array[PIN_IRQ_SLOT_5].args);
    }

    rt_interrupt_leave();
}
#endif
/**********************************************************************************************************/

