#include "c8_sys.h"
#include "def.h"
#include "opcode.h"

int opcode_execute(struct chipsys *sys, u16 opcode)
{
	/*
	static void *jump[] = {
		&&op0,&&op1,&&op2,&&op3,&&op4,&&op5,&&op6,&&op7,
		&&op8,&&op9,&&opA,&&opB,&&opC,&&opD,&&opE,&&opF,						
	};
	goto *jump[opcode >> 12];
	*/
	goto *((void*[16]){
			&&op0,&&op1,&&op2,&&op3,
			&&op4,&&op5,&&op6,&&op7,
			&&op8,&&op9,&&opA,&&opB,
			&&opC,&&opD,&&opE,&&opF
		})[opcode >> 12];

op0:if(opcode == 0x00E0){
		memset(sys->screen, 0, sizeof(uint64_t) * 32);
	}else if(opcode == 0x00E0){
		assert(sys->SP > 0);
		sys->PC = sys->stack[--sys->SP];
	}else{
		goto unknown;
	}
	return EXIT_SUCCESS;
op1:sys->PC = opcode & 0x0FFF;
	return EXIT_SUCCESS;
op2:sys->stack[sys->SP++] = sys->PC;
	sys->PC = opcode & 0x0FFF;
	return EXIT_SUCCESS;
op3:if(sys->V[(opcode >> 8) & 0x000F] == (opcode & 0x00FF))
		sys->PC += 2;
	return EXIT_SUCCESS;
op4:if(sys->V[(opcode >> 8) & 0x000F] == (opcode & 0x00FF))
		sys->PC += 2;
	return EXIT_SUCCESS;
op5:if(opcode & 0x000F) // last 4 bits must be 0
		goto unknown;
	if(sys->V[(opcode >> 4) & 0x000F] == sys->V[(opcode >> 8) & 0x000F])
		sys->PC += 2;
	return EXIT_SUCCESS;
op6:sys->V[(opcode >> 8) & 0x000F] = opcode & 0x00FF;
	return EXIT_SUCCESS;
op7:sys->V[(opcode >> 8) & 0x000F] += opcode & 0x00FF;
	return EXIT_SUCCESS;
op8:goto *((void*[16]){
			&&op80,&&op81,&&op82,&&op83,
			&&op84,&&op85,&&op86,&&op87,
			&&op88,&&op89,&&op8A,&&op8B,
			&&op8C,&&op8D,&&op8E,&&op8F
		})[opcode & 0x000F];
	op80:sys->V[(opcode >> 8) & 0x000F] = sys->V[(opcode >> 4) & 0x000F];
		return EXIT_SUCCESS;
	op81:sys->V[(opcode >> 8) & 0x000F] |= sys->V[(opcode >> 4) & 0x000F];
		return EXIT_SUCCESS;
	op82:sys->V[(opcode >> 8) & 0x000F] &= sys->V[(opcode >> 4) & 0x000F];
		return EXIT_SUCCESS;
	op83:sys->V[(opcode >> 8) & 0x000F] ^= sys->V[(opcode >> 4) & 0x000F];
		return EXIT_SUCCESS;
	op84: // check for integer overflow
		sys->V[(opcode >> 8) & 0x000F] += sys->V[(opcode >> 4) & 0x000F];
		return EXIT_SUCCESS;
	op85: // check for integer underflow
		sys->V[(opcode >> 8) & 0x000F] -= sys->V[(opcode >> 4) & 0x000F];
		return EXIT_SUCCESS;
	op86: // second register used or const one?
		sys->V[(opcode >> 8) & 0x000F] >>= sys->V[(opcode >> 4) & 0x000F]; 
		return EXIT_SUCCESS;
	op87: // check for integer underflow
		sys->V[(opcode >> 8) & 0x000F] = 	sys->V[(opcode >> 4) & 0x000F] - 
											sys->V[(opcode >> 8) & 0x000F];
		return EXIT_SUCCESS;
	op88:goto unknown;
	op89:goto unknown;
	op8A:goto unknown;
	op8B:goto unknown;
	op8C:goto unknown;
	op8D:goto unknown;
	op8E: // second register used or const one?
		sys->V[(opcode >> 8) & 0x000F] <<= sys->V[(opcode >> 4) & 0x000F];
		return EXIT_SUCCESS;;
	op8F:goto unknown;
op9:if(opcode & 0x000F) // last 4 bits must be 0
		goto unknown;
	if(sys->V[(opcode >> 8) & 0x000F] != sys->V[(opcode >> 4) & 0x000F])
		sys->PC += 2;
	return EXIT_SUCCESS;

opA:;
	
opB:sys->PC = (opcode & 0x0FFF) + sys->V[0];
	assert(sys->PC < 4096);
	return EXIT_SUCCESS;
opC:sys->V[(opcode >> 8) & 0x000F] = (rand() % 256) & (u8)opcode;
	return EXIT_SUCCESS;

opD:;
	
opE:;
	
opF:;
	u16 *reg = &sys->V[(opcode >> 8) & 0x000F];
	switch(opcode & 0x00FF){
		case 0x07: *reg = sys->delay_timer;
			break;
		case 0x0A: // get key and store in reg
			break;
		case 0x15: sys->delay_timer = *reg; // overflow?
			break;
		case 0x18: sys->sound_timer = *reg; // overflow?
			break;
		case 0x1E: sys->I += *reg;
			break;
		case 0x29: // sprite
			break;
		case 0x33: // asd
			break;
		case 0x55:
			break;
		case 0x65:
			break;
		default: goto unknown;
	}
	return EXIT_SUCCESS;

unknown:
	printf("[ERROR] <opcode_execute> Unknown opcode: %4x", opcode);
	return EXIT_FAILURE;
}
