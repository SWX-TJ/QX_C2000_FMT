#ifndef SERIAL_CONFIG_H
#define SERIAL_CONFIG_H

#include <board_config.h>


#if defined(BOARD_CFG_SCIA)
#ifndef SCIA_CONFIG
#define SCIA_CONFIG                                                 \
    {                                                               \
        .name = "SCIA",                                             \
        .number = &SciaRegs,                                        \
        .intr_type = INT_SCIA,                                      \
        .rx_pin_num = 25,                                           \
        .tx_pin_num = 24,                                           \
    }
#endif /* SCIA_CONFIG */
#endif

#if defined(BOARD_CFG_SCIB)
#ifndef SCIB_CONFIG
#define SCIB_CONFIG                                                 \
    {                                                               \
        .name = "SCIB",                                             \
        .instance = &ScibRegs,                                      \
        .intr_type = INT_SCIB,                                      \
        .rx_pin_num = 13,                                           \
        .tx_pin_num = 12,                                           \
    }
#endif /* SCIA_CONFIG */
#endif

#if defined (BOARD_SERIALA_RX_USING_DMA)
#ifndef SERIAL_A_DMA_CFG
#define SERIAL_A_DMA_CFG                        \
{                                               \
    .srcAddr  =  0,                              \
    .destAddr =  0,                              \
    .blockSize = 0,                              \
    .srcWidth = DMA_TRANS_WIDTH_8,               \
    .destWidth = DMA_TRANS_WIDTH_8,              \
    .srcMsize = DMA_MSIZE_1,                     \
    .destMsize = DMA_MSIZE_1,                    \
    .TT_FC = DMA_P2M_DMA,                        \
    .srcHSInterface = DMA_TRIGGER_SCIBRX,        \
    .destHSInterface = DMA_TRIGGER_MEM,          \
    .srcHSType = DMA_HS_HARDWARE,                \
    .destHSType = DMA_HS_HARDWARE,               \
}
#endif

#ifndef SERIAL_A_RX_DMA_CHANNEL_CFG
#define SERIAL_A_RX_DMA_CHANNEL_CFG              1
#endif

#endif


#if defined (BOARD_SERIALA_TX_USING_DMA)
#ifndef SERIAL_A_TX_DMA_CFG
#define SERIAL_A_TX_DMA_CFG                     \
{                                               \
    .srcAddr  =                                 \
    .destAddr =                                 \
    .blockSize =                                \
    .srcWidth =                                 \
    .destWidth =                                \
    .srcMsize =                                 \
    .destMsize =                                \
    .TT_FC =                                    \
    .srcHSInterface =                           \
    .destHSInterface =                          \
    .srcHSType =                                \
    .destHSType =                               \
}
#endif
#endif

#if defined (BOARD_SERIALB_RX_USING_DMA)
#ifndef SERIAL_B_RX_DMA_PARAM_CFG
#define SERIAL_B_RX_DMA_PARAM_CFG                \
{                                                \
    .srcAddr  =  0,                              \
    .destAddr =  0,                              \
    .blockSize = 7,                              \
    .srcWidth = DMA_TRANS_WIDTH_8,               \
    .destWidth = DMA_TRANS_WIDTH_8,              \
    .srcMsize = DMA_MSIZE_1,                     \
    .destMsize = DMA_MSIZE_1,                    \
    .TT_FC = DMA_P2M_DMA,                        \
    .srcHSInterface = DMA_TRIGGER_SCIBRX,        \
    .destHSInterface = DMA_TRIGGER_MEM,          \
    .srcHSType = DMA_HS_HARDWARE,                \
    .destHSType = DMA_HS_HARDWARE,               \
}
#endif

#ifndef SERIAL_B_RX_DMA_CHANNEL_CFG
#define SERIAL_B_RX_DMA_CHANNEL_CFG              2
#endif

#endif

#if defined (BOARD_SERIALB_TX_USING_DMA)
#ifndef SERIAL_B_TX_DMA_PARAM_CFG
#define SERIAL_B_TX_DMA_PARAM_CFG                \
{                                                \
    .srcAddr  =  0,                              \
    .destAddr =  0,                              \
    .blockSize = 0,                              \
    .srcWidth = DMA_TRANS_WIDTH_8,               \
    .destWidth = DMA_TRANS_WIDTH_8,              \
    .srcMsize = DMA_MSIZE_1,                     \
    .destMsize = DMA_MSIZE_1,                    \
    .TT_FC = DMA_M2P_DMA,                        \
    .srcHSInterface = DMA_TRIGGER_MEM,           \
    .destHSInterface = DMA_TRIGGER_SCIBTX,       \
    .srcHSType = DMA_HS_HARDWARE,                \
    .destHSType = DMA_HS_HARDWARE,               \
}
#endif

#ifndef SERIAL_B_TX_DMA_CHANNEL_CFG
#define SERIAL_B_TX_DMA_CHANNEL_CFG              3
#endif

#endif

#endif

