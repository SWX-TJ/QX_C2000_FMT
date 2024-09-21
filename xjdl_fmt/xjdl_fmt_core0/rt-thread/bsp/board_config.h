#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H
#include <rtthread.h>

/****************************************************************************************************/
/* group of scib configs */
#define BOARD_CFG_SCIB
#if defined(RT_SERIAL_USING_DMA)
#define BOARD_SERIALB_RX_USING_DMA
#define BOARD_SERIALB_TX_USING_DMA
#endif
/****************************************************************************************************/

/* group of i2ca configs */
#define BOARD_CFG_I2CA

#endif
