#ifndef QX_MEMMAP_H
#define QX_MEMMAP_H

/* memery map for peripheral */
#define SRAM_DATA_BASE    0x00000000U
#define IPC_CPU0_MEM_BASE 0x00100000U
#define IPC_CPU1_MEM_BASE 0x00101000U
#define SRAM_INST_BASE    0x00200000U
#define SRAM_BOOT_BASE    0x00280000U

#define PIECTRL_BASE       0x007F0100U
#define DEBUG_BASE         0x007F0200U
#define CPUTIMER0_BASE     0x007F0300U
#define CPUTIMER1_BASE     0x007F0314U
#define CPUTIMER2_BASE     0x007F0328U
#define CPUTIMERSYS_BASE   0x007F03A0U
#define CPUTIMER0LC2_BASE  0x007F03B0U
#define CPUTIMER1LC2_BASE  0x007F03B4U
#define CPUTIMER2LC2_BASE  0x007F03B8U
#define CR_BASE            0x007F0400U
#define GR_BASE            0x007F0500U
#define MOB_BASE           0x007F0600U
#define EXP_BASE           0x007F0700U
#define WD_BASE            0x007F0800U
#define IPC_REG_BASE       0x007F0900U
#define IPC_CMD_BASE       0x007F0A00U
#define VCU_BASE           0x007F0B00U
#define TRACE_BUFFER_BASE  0x007F0C00U
#define WATCH_POINT_BASE   0x007F0D00U
#define ECC_BASE           0x007F0E00U
#define ERAD_GLOBAL_BASE   0x007F0F00U
#define ERAD_HWBP1_BASE    0x007F1000U
#define ERAD_HWBP2_BASE    0x007F1100U
#define ERAD_HWBP3_BASE    0x007F1200U
#define ERAD_HWBP4_BASE    0x007F1300U
#define ERAD_HWBP5_BASE    0x007F1400U
#define ERAD_HWBP6_BASE    0x007F1500U
#define ERAD_HWBP7_BASE    0x007F1600U
#define ERAD_HWBP8_BASE    0x007F1700U
#define ERAD_COUNTER1_BASE 0x007F1800U
#define ERAD_COUNTER2_BASE 0x007F1900U
#define ERAD_COUNTER3_BASE 0x007F1A00U
#define ERAD_COUNTER4_BASE 0x007F1B00U
#define CLKCFG_BASE        0x01000000U
#define CPUSYS_BASE        0x01001000U
#define DEVCFG_BASE        0x01001000U
#define XINT_BASE          0x010011B0U
#define NMI_BASE           0x01001200U
#define DCC0_BASE          0x01002000U
#define GPIOCTRL_BASE      0x01003000U
#define GPIODATA_BASE      0x01004000U
#define INPUTXBAR_BASE     0x01005000U
#define EPWMXBAR_BASE      0x01006000U
#define OUTPUTXBAR_BASE    0x01007000U
#define XBAR_BASE          0x01008000U
#define DMA_BASE           0x01009000U
#define DMA_CH1_BASE       0x01009100U
#define DMA_CH2_BASE       0x01009200U
#define DMA_CH3_BASE       0x01009300U
#define DMA_CH4_BASE       0x01009400U
#define DMA_CH5_BASE       0x01009500U
#define DMA_CH6_BASE       0x01009600U
#define ANALOGSUBSYS_BASE  0x0100A000U
#define ADCA_BASE          0x0100B000U
#define ADCARESULT_BASE    0x0100B100U
#define ADCB_BASE          0x0100B200U
#define ADCBRESULT_BASE    0x0100B300U
#define ADCC_BASE          0x0100B400U
#define ADCCRESULT_BASE    0x0100B500U
#define PGA1_BASE          0x0100C000U
#define PGA2_BASE          0x0100C020U
#define PGA3_BASE          0x0100C040U
#define PGA4_BASE          0x0100C060U
#define PGA5_BASE          0x0100C080U
#define PGA6_BASE          0x0100C0A0U
#define PGA7_BASE          0x0100C0C0U
#define DACA_BASE          0x0100D000U
#define DACB_BASE          0x0100D040U
#define CMPSS1_BASE        0x0100E000U
#define CMPSS2_BASE        0x0100E100U
#define CMPSS3_BASE        0x0100E200U
#define CMPSS4_BASE        0x0100E300U
#define CMPSS5_BASE        0x0100E400U
#define CMPSS6_BASE        0x0100E500U
#define CMPSS7_BASE        0x0100E600U
#define SDFM1_BASE         0x0100F000U
#define ECAP1_BASE         0x01010000U
#define ECAP2_BASE         0x01010080U
#define ECAP3_BASE         0x01010100U
#define ECAP4_BASE         0x01010180U
#define ECAP5_BASE         0x01010200U
#define ECAP6_BASE         0x01010280U
#define ECAP7_BASE         0x01010300U
#define HRCAP6_BASE        0x010102C0U
#define HRCAP7_BASE        0x01010340U
#define SYNCSOC_BASE       0x01010380U
#define SFO_BASE           0x01010400U
#define SFOHHR_BASE        0x01010480U
#define EPWM9_BASE         0x01010600U
#define EPWM10_BASE        0x01010800U
#define EPWM11_BASE        0x01010A00U
#define EPWM12_BASE        0x01010C00U
#define EPWM1_BASE         0x01011000U
#define EPWM2_BASE         0x01011200U
#define EPWM3_BASE         0x01011400U
#define EPWM4_BASE         0x01011600U
#define EPWM5_BASE         0x01011800U
#define EPWM6_BASE         0x01011A00U
#define EPWM7_BASE         0x01011C00U
#define EPWM8_BASE         0x01011E00U
#define EQEP1_BASE         0x01012000U
#define EQEP2_BASE         0x01012800U
#define SPIA_MASTER_BASE   0x01013000U
#define SPIA_SLAVE_BASE    0x01013400U
#define SPIA_SEL_BASE      0x01013800U
#define SPIB_MASTER_BASE   0x01014000U
#define SPIB_SLAVE_BASE    0x01014400U
#define SPIB_SEL_BASE      0x01014800U
#define SCIA_BASE          0x01015000U
#define SCIB_BASE          0x01016000U
#define I2CA_BASE          0x01017000U
#define PMBUSA_BASE        0x01018000U
#define LIN_BASE           0x01019000U
#define FSITXA_BASE        0x0101A000U
#define FSIRXA_BASE        0x0101B000U
#define REGFILE_BASE       0x0101C000U
#define CANA_BASE          0x01020000U
#define CANB_BASE          0x01030000U
#define CANFDA_BASE        0x01052000U
#define CANFDB_BASE        0x01053000U
#define HR_ADCA_BASE       0x01054000U
#define HR_ADCB_BASE       0x01054400U
#define HR_ADCC_BASE       0x01054800U
#define XINTF_BASE         0x20000000U
#define FLASH0CTRL_BASE    0x01040000U

#define FLASH0DATA_BASE 0x30000000U
#define FLASH0OTP1_BASE 0x30100000U
#define FLASH0OTP2_BASE 0x30101000U

#endif
