#include "c8_sys.h"
#include "def.h"
#include "opcode.h"

// names from http://www.badlogicgames.com/wordpress/?p=3564
static inline void sysc	(chipsys *sys, u16 opcode)
{
	(void)sys;
	dprint("sysc", opcode);
	printf("system calls not supported, opcode: %4x", opcode);
}
static inline void clear	(chipsys *sys, u16 opcode)
{
	(void)opcode;
	dprint("clear", opcode);
	memset(sys->screen, 0, 64 * sizeof(uint64_t));
	//memset(sys->screen, 0, 2048 * sizeof(int));
}
static inline void ret		(chipsys *sys, u16 opcode)
{
	(void)opcode;
	dprint("ret", opcode);
	sys->PC = sys->stack[sys->SP--];
}
static inline void jmp		(chipsys *sys, u16 opcode)
{
	dprint("jmp", opcode);
	sys->PC = opcode & 0x0FFF;
}
static inline void call	(chipsys *sys, u16 opcode)
{
	dprint("call", opcode);
	sys->stack[++sys->SP] = sys->PC;
	sys->PC = opcode & 0x0FFF;
}
static inline void seq		(chipsys *sys, u16 opcode)
{
	dprint("seq", opcode);
	if(sys->V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
		sys->PC += 2;
}
static inline void sneq	(chipsys *sys, u16 opcode)
{
	dprint("sneq", opcode);
	if(sys->V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
		sys->PC += 2;
}
static inline void seqr	(chipsys *sys, u16 opcode)
{
	dprint("seqr", opcode);
	//if(sys->V[(opcode & 0x0F00) >> 8] == sys->V[(opcode & 0x00F0) >> 4])
	if(sys->V[(opcode & 0x0F00) >> 4] == sys->V[(opcode & 0x00F0)])
		sys->PC += 2;
}
static inline void set		(chipsys *sys, u16 opcode)
{
	dprint("set", opcode);
	int reg = (opcode & 0x0F00) >> 8,
		val = opcode & 0x00FF;
	sys->V[reg] = (u16)val;
}
static inline void add		(chipsys *sys, u16 opcode)
{
	dprint("add", opcode);
	int reg = (opcode & 0x0F00) >> 8,
		val = opcode & 0x00FF;
		sys->V[reg] = (u16)val;
}
static inline void setr	(chipsys *sys, u16 opcode)
{
	dprint("setr", opcode);
	int r1 = (opcode & 0x0F00) >> 8, 
		r2 = (opcode & 0x00F0) >> 4;
	sys->V[r1] = sys->V[r2];
}
static inline void or		(chipsys *sys, u16 opcode)
{
	dprint("or", opcode);
	int r1 = (opcode & 0x0F00) >> 8, 
		r2 = (opcode & 0x00F0) >> 4;
	sys->V[r1] = sys->V[r1] | sys->V[r2];
}
static inline void and		(chipsys *sys, u16 opcode)
{
	dprint("and", opcode);
	int r1 = (opcode & 0x0F00) >> 8, 
		r2 = (opcode & 0x00F0) >> 4;
	sys->V[r1] = sys->V[r1] & sys->V[r2];
}
static inline void xor		(chipsys *sys, u16 opcode)
{
	dprint("xor", opcode);
	int r1 = (opcode & 0x0F00) >> 8, 
		r2 = (opcode & 0x00F0) >> 4;
	sys->V[r1] = sys->V[r1] ^ sys->V[r2];
}
static inline void addr	(chipsys *sys, u16 opcode)
{
	dprint("addr", opcode);
	int r1 = (opcode & 0x0F00) >> 8, 
		r2 = (opcode & 0x00F0) >> 4;
	if(sys->V[r1] > 0xFFFF - sys->V[r2]) // overflow check
		sys->V[0xF] = 1;							// set VF to 1 ??
	else
		sys->V[0xF] = 0;
	sys->V[r1] += sys->V[r2];
}
static inline void subr	(chipsys *sys, u16 opcode)
{
	dprint("subr", opcode);
	int r1 = (opcode & 0x0F00) >> 8, 
		r2 = (opcode & 0x00F0) >> 4;
	if(sys->V[r1] < sys->V[r2])
		sys->V[0xF] = 1;							// set VF to 1 ??
	else
		sys->V[0xF] = 0;
	sys->V[r1] -= sys->V[r2];
}
static inline void shr		(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("shr", opcode);
}
static inline void subb	(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("subb", opcode);
}
static inline void shl		(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("shl", opcode);
}
static inline void sneqr	(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("sneqr", opcode);
}
static inline void seti	(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("seti", opcode);
}
static inline void jmpv0	(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("jmpv0", opcode);
}
static inline void rnd	(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("rnd", opcode);
}
static inline void draw	(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("draw", opcode);
}
static inline void skey	(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("skey", opcode);
}
static inline void snkey	(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("snkey", opcode);
}
static inline void getdelay(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("getdelay", opcode);
}
static inline void waitkey	(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("waitkey", opcode);
}
static inline void setdelay(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("setdelay", opcode);
}
static inline void setsound(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("setsound", opcode);
}
static inline void addi	(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("addi", opcode);
}
static inline void spritei	(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("spritei", opcode);
}
static inline void bcd		(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("bcd", opcode);
}
static inline void push	(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("push", opcode);
}
static inline void pop(chipsys *sys, u16 opcode)
{
	(void)sys;
	(void)opcode;
	dprint("pop", opcode);
}

int opcode_execute(chipsys *sys, u16 opcode)
{
	#ifdef CHECK_BOUNDS
		assert(sys->PC < 4096);
	#endif

	switch(opcode >> 12){ // 0xNXYZ => 0xN
		case(0x0):
			if(opcode == 0x00E0)
				clear(sys, opcode);
			else if(opcode == 0x00EE)
				ret(sys, opcode);
			else
				sysc(sys, opcode);
			break;
		case(0x1):
			jmp(sys, opcode);
			break;
		case(0x2):
			call(sys, opcode);
			break;
		case(0x3):
			seq(sys, opcode);
			break;
		case(0x4):
			sneq(sys, opcode);
			break;
		case(0x5):
			seqr(sys, opcode);
			break;
		case(0x6):
			set(sys, opcode);
			break;
		case(0x7):
			add(sys, opcode);
			break;
		case(0x8): // -----TODO-----
			switch(opcode & 0x000F){
				case(0x0):
					setr(sys, opcode);
					break;
				case(0x1):
					or(sys, opcode);
					break;
				case(0x2):
					and(sys, opcode);
					break;
				case(0x3):
					xor(sys, opcode);
					break;
				case(0x4):
					addr(sys, opcode);
					break;
				case(0x5):
					subr(sys, opcode);
					break;
				case(0x6):
					shr(sys, opcode);
					break;
				case(0x7):
					subb(sys, opcode);
					break;
				case(0xE):
					shl(sys, opcode);
					break;
			}
			break;
		case(0x9):
			sneqr(sys, opcode);
			break;
		case(0xA):
			seti(sys, opcode);
			break;
		case(0xB):
			jmpv0(sys, opcode);
			break;
		case(0xC):
			rnd(sys, opcode);
			break;
		case(0xD):
			draw(sys, opcode);
			break;
		case(0xE):
			if((opcode & 0x00FF) == 0x009E)
				skey(sys, opcode);
			else if((opcode & 0x00FF) == 0x00A1)
				snkey(sys, opcode);
			else
				goto unknown_op;
			break;
		case(0xF):
			switch(opcode & 0x00FF){
				case(0x07):
					getdelay(sys, opcode);
					break;
				case(0x0A):
					waitkey(sys, opcode);
					break;
				case(0x15):
					setdelay(sys, opcode);
					break;
				case(0x18):
					setsound(sys, opcode);
					break;
				case(0x1E):
					addi(sys, opcode);
					break;
				case(0x29):
					seti(sys, opcode);
					break;
				case(0x33):
					bcd(sys, opcode);
					break;
				case(0x55):
					push(sys, opcode);
					break;
				case(0x65):
					pop(sys, opcode);
					break;
				default: goto unknown_op;
			}
			break;
	}

	#ifdef CHECK_BOUNDS
		assert(sys->PC < 4096);
	#endif

	return EXIT_SUCCESS;

	unknown_op: printf("[ERROR] <opcode_execute> Unknown opcode: %4x", opcode);
	return EXIT_FAILURE;
}
