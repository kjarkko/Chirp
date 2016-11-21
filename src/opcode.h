#include <stdlib.h>
#include <stdio.h>
#include "c8_sys.h"
#include "def.h"

#ifdef debug
	#define dprint(_oper_s, _opcode) printf("%s\n%4x\n",(char *)_oper_s , _opcode)
#endif

#ifndef debug
    #define dprint(a,b) ((void)0)
#endif

int opcode_execute(chipsys *sys, u16 opcode);