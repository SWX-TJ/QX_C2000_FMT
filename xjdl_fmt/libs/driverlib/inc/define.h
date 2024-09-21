#ifndef QX_DEFINE_H
#define QX_DEFINE_H

#ifdef __cplusplus
extern "C" {
#endif

/* #include <stdint.h> */
#include <stdbool.h>

#include "types.h"
#include "cpu.h"
#include "memmap.h"
#include "debug.h"


#define VERSION_NUMBER 010000U

#define USE_ALWAYS_INLINE // use always inline toogle

#ifndef USE_ALWAYS_INLINE
#define STATIC_INLINE static inline
#else
#define STATIC_INLINE __attribute__((always_inline)) static inline
#endif

#define STATIC_ALWAYS_INLINE __attribute__((always_inline)) static inline

STATIC_INLINE uint32_t Version_getLibVersion(void)
{
    return (VERSION_NUMBER);
}

#ifdef __cplusplus
}
#endif

#endif
