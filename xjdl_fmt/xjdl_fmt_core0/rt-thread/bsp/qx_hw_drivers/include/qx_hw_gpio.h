#ifndef QX_HW_GPIO_H
#define QX_HW_GPIO_H

#define QX_GPIO_MUX_REG_VALUE_BASE1      0x000C0000UL
#define QX_GPIO_MUX_REG_VALUE_BASE2      0x00100000UL
#define QX_GPIO_MUX_REG_VALUE_BASE3      0x005C0000UL
#define QX_GPIO_MUX_REG_VALUE_BASE4      0x00600000UL

#define UNKNOW_PIN_NUMBER               0xFFUL
#define UNKNOW_PIN_MUX_VALUE            0xFFUL
#define NO_SLOT_IN_PIN_IRQ_ARRAY        0xFFUL
#define NO_SUITABLE_SLOT_IN_ARRAY       0xFFUL

extern int rt_hw_pin_init(void);

#endif
