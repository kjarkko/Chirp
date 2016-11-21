#include "opcode.h"

// names from http://www.badlogicgames.com/wordpress/?p=3564
inline void sysc	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void clear	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void ret		(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void jmp		(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void call	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void seq		(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void sneq	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void seqr	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void set		(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void add		(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void setr	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);

}
inline void or		(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void and		(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void xor		(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void addr	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void sub		(chipsys *sys, u16 opcode) // TODO ?????????
{
	dprint("sysc", opcode);
}
inline void shr		(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void subb	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void shl		(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void sneqr	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void seti	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void jmpv0	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void rnd	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void draw	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void skey	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void snkey	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void getdelay(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void waitkey	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void setdelay(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void setsound(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void addi	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void spritei	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void bcd		(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void push	(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}
inline void pop		(chipsys *sys, u16 opcode)
{
	dprint("sysc", opcode);
}

int opcode_execute(chipsys *sys, u16 opcode)
{
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

	return EXIT_SUCCESS;

	unknown_op: printf("[ERROR] - Unknown opcode: %4x", opcode);
	return EXIT_FAILURE;
}
