#ifndef QX_DEBUG_H
#define QX_DEBUG_H

/* debug mode toggle, uncommit it for open debug mode */
// #define DEBUG

extern void __error__(const char *filename, uint32_t line);

#ifdef DEBUG
#define ASSERT(expr)                       \
    do                                     \
    {                                      \
        if (!(expr))                       \
            __error__(__FILE__, __LINE__); \
    } while ((_Bool)0)
#else
#define ASSERT(expr)
#endif

#endif
