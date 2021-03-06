#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "c8_sys.h"
#include "def.h"
#include "opcode.h"
#include "io.h"

int opcode_execute(struct chipsys *sys, u16 opcode)
{
	// pointers to registers Vx and Vy
	u8 *const vxp = &sys->V[(opcode >> 8) & 0x000F],
	   *const vyp = &sys->V[(opcode >> 4) & 0x000F];

	// uses the address of label extension
	static const void * const jump0x8[16] = { // opcodes 0x8nnn
		&&op80,&&op81,&&op82,&&op83,&&op84,&&op85,&&op86,&&op87,
		&&op88,&&op89,&&op8A,&&op8B,&&op8C,&&op8D,&&op8E,&&op8F
	}, * const jump[16] = {
		&&op0,&&op1,&&op2,&&op3,&&op4,&&op5,&&op6,&&op7,
		&&op8,&&op9,&&opA,&&opB,&&opC,&&opD,&&opE,&&opF					
	};
	
	goto *jump[opcode >> 12];

op0:	if(opcode == 0x00E0){
		(void)memset(sys->screen, 0, sizeof(u64) * 32);
	}else if(opcode == 0x00E0){ // ?????????
		assert(sys->SP > 0);
		sys->PC = sys->stack[--sys->SP];
	}else{
		goto unknown_opcode;
	}
	return EXIT_SUCCESS;

op1:	sys->PC = opcode & 0x0FFF;
	return EXIT_SUCCESS;

op2:	sys->stack[sys->SP++] = sys->PC;
	sys->PC = opcode & 0x0FFF;
	return EXIT_SUCCESS;

op3:	if(*vxp == (opcode & 0x00FF))
		sys->PC += 2;
	return EXIT_SUCCESS;

op4:	if(*vxp == (opcode & 0x00FF))
		sys->PC += 2;
	return EXIT_SUCCESS;

op5:	if(opcode & 0x000F) 
		goto unknown_opcode;
	if(*vyp == *vxp)
		sys->PC += 2;
	return EXIT_SUCCESS;

op6:	*vxp = opcode & 0x00FF;
	return EXIT_SUCCESS;

op7:	*vxp += opcode & 0x00FF;
	return EXIT_SUCCESS;

op8:;	goto *jump0x8[opcode & 0x000F];

	op80:	*vxp = *vyp;
		return EXIT_SUCCESS;
	
	op81:	*vxp |= *vyp;
		return EXIT_SUCCESS;
	
	op82:	*vxp &= *vyp;
		return EXIT_SUCCESS;
	
	op83:	*vxp ^= *vyp;
		return EXIT_SUCCESS;
	
	op84:	sys->V[0xF] = ((UINT8_MAX - *vxp) < *vyp);
		*vxp += *vyp;
		return EXIT_SUCCESS;
	
	op85: 	sys->V[0xF] = *vyp < *vxp;
		*vxp -= *vyp;
		return EXIT_SUCCESS;
	
	op86:	*vxp >>= *vyp; 
		return EXIT_SUCCESS;
	
	op87:	sys->V[0xF] = *vyp > *vxp;
		*vxp = *vyp - *vxp;
		return EXIT_SUCCESS;
	
	op88:	goto unknown_opcode;
	op89:	goto unknown_opcode;
	op8A:	goto unknown_opcode;
	op8B:	goto unknown_opcode;
	op8C:	goto unknown_opcode;
	op8D:	goto unknown_opcode;

	op8E:	*vxp <<= *vyp;
		return EXIT_SUCCESS;

	op8F:	goto unknown_opcode;

op9:	if(opcode & 0x000F)
		goto unknown_opcode;
	if(*vxp != *vyp)
		sys->PC += 2;
	return EXIT_SUCCESS;

opA:;	// TODO
	
opB:	assert((opcode & 0x0FFF) + sys->V[0] < 4094);
	sys->PC = (opcode & 0x0FFF) + sys->V[0];
	return EXIT_SUCCESS;

opC:	*vxp = (rand() % 256) & (u8)opcode;
	return EXIT_SUCCESS;

opD:;	int x = *vxp % 64;
	u64 erased = 0;
	int nib = opcode & 0x000F;
	while(nib--){
		u64 *rowptr = &sys->screen[(nib + *vyp) % 32]; 
		u64 shifted = ((u64)sys->memory[sys->I + nib] >> (64 - x)) | // TODO: check overflow
		              ((u64)sys->memory[sys->I + nib] << x); // bug?
		erased |= *rowptr & shifted;
		*rowptr ^= shifted;
	}
	sys->V[0xF] = erased ? 1:0;
	return EXIT_SUCCESS;
	
opE:	switch(opcode & 0x00FF){ // TODO: make this or the keyboard less dumb
	case 0x9E:
		for(int i = 0; i < 16; i++)
			if(sys->key[i] == *vxp)
				sys->PC += 2;
		return EXIT_SUCCESS;
	case 0xA1:
		for(int i = 0; i < 16; i++)
			if(sys->key[i] == *vxp)
				return EXIT_SUCCESS;
		sys->PC += 2;
		return EXIT_SUCCESS;
	default:
		goto unknown_opcode;
	};
	
opF:	switch(opcode & 0x00FF){
	case 0x07: 
		*vxp = sys->delay_timer;
		break;
	case 0x0A: 
		*vxp = wkeypress(sys->key);
		break;
	case 0x15: 
		sys->delay_timer = *vxp;
		break;
	case 0x18: 
		sys->sound_timer = *vxp;
		break;
	case 0x1E: 
		sys->I += *vxp;
		break;
	case 0x29: 
		sys->I = hexsprite_address[*vxp % 16];
		break;
	case 0x33:
		sys->memory[sys->I  ] = (*vxp / 100) % 10;
		sys->memory[sys->I+1] = (*vxp / 10 ) % 10;
		sys->memory[sys->I+2] = (*vxp / 1  ) % 10;
		break;
	case 0x55:
		memcpy(&sys->memory[sys->I], sys->V, (opcode >> 8) & 0x000F);
		break;
	case 0x65:
		memcpy(sys->V, &sys->memory[sys->I], (opcode >> 8) & 0x000F);
		break;
	default: 
		goto unknown_opcode;
	}
	return EXIT_SUCCESS;

unknown_opcode:
	fprintf(stderr, "[ERROR] <opcode_execute> Unknown opcode: %4x\n", opcode);
	return EXIT_FAILURE;
}
