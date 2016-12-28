#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifndef DEF_H
#define DEF_H

    #ifdef DEBUG
        #include <assert.h>
    #else
        #define assert(ignore) ((void)0)
    #endif

    typedef uint8_t u8;
    typedef uint16_t u16;

#endif
