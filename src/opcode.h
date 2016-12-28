#include "c8_sys.h"

#ifndef OPCODE_H
#define OPCODE_H

    #ifdef debug
        #define dprint(_oper_s, _opcode) printf("%s\n%4x\n",(char *)_oper_s , _opcode)
    #else
        #define dprint(a,b) ((void)0)
    #endif

    int opcode_execute(struct chipsys *sys, u16 opcode);
    
#endif
