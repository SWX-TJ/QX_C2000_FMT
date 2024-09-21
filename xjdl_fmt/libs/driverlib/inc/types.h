#ifndef QX_TYPES_H
#define QX_TYPES_H

//*****************************************************************************
// Macros for hardware access
//*****************************************************************************

#define HWREG(x)  (*((volatile uint32_t *)(x)))
#define HWREGH(x) (*((volatile uint16_t *)(x)))
#define HWREGB(x) (*((volatile uint8_t *)(x)))
/* #define HWREG_BP(x) __byte_peripheral_32((uint32_t *)(x)) */

//*****************************************************************************
// SUCCESS and FAILURE for API return value
//*****************************************************************************
#define STATUS_S_SUCCESS (0)
#define STATUS_E_FAILURE (-1)

//*****************************************************************************
// Definition of 8 bit types for USB Driver code to maintain portability
// between byte and word addressable cores of C2000 Devices.
//*****************************************************************************
// typedef uint16_t uint8_t;
// typedef int16_t int8_t;

//****************************************************************************
// For checking NULL pointers
//****************************************************************************
#ifndef NULL
#define NULL ((void *)0x0)
#endif

//*****************************************************************************
// Extern compiler intrinsic prototypes. See compiler User's Guide for details.
// These are provided to satisfy static analysis tools. The #ifndef is required
// because the '&' is for a C++-style reference, and although it is the correct
// prototype, it will not build in C code.
//*****************************************************************************
// #if (defined(__TMS320C28XX__) || defined(__TMS320C28XX_CLA__))
// #else
// extern int16_t &__byte(int16_t *array, uint16_t byte_index);
// extern uint32_t &__byte_peripheral_32(uint32_t *x);
// #endif

// C++ Bool Compatibility
#if defined(__cplusplus)
typedef bool _Bool;
#endif

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

typedef float float32_t;

typedef volatile uint8_t vu8;
typedef volatile uint16_t vu16;
typedef volatile uint32_t vu32;
typedef volatile uint64_t vu64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

/* simulation of __byte() Intrinsic, refer to SPRU514Z, table 7-6 */
static inline uint16_t __byte(int16_t * array, uint16_t byte_index) {
    return ((uint8_t *)array)[byte_index];
}

#endif
