
void opcode_execute(c8sys *sys, u16 opcode)
{

}

// 0x7XKK
/*----------*/

/* Clear the display
 */
void cls_f(c8sys *sys, u16 opcode)
{

}

/* Return from subroutine
 */
void ret_f(c8sys *sys, u16 opcode)
{
	sys->pc = sys->stack[sys->sp--];
}

/* Jump
 */
void jp_f(c8sys *sys, u16 opcode)
{
	sys->pc = 0x0FFF & opcode;
}

/* Call subroutine
 */
void call_f(c8sys *sys, u16 opcode)
{

}

//----
/* Skip next instruction
 *  0x3XKK - VX == KK
 *  0x5xy0 - VX == VY
 */
void se_f(c8sys *sys, u16 opcode)
{

}

//----
/* Skip next instruction, not equal
 *  0x4XKK - VX != KK
 */
void sne_f(c8sys *sys, u16 opcode)
{

}

//----
/* Load value
 *  6XKK - VX = KK
 *  8XY0 - VX = VY
 */
void ld_f(c8sys *sys, u16 opcode)
{

}

//----
/*
 */
void add_f(c8sys *sys, u16 opcode)
{

}

void or_f(c8sys *sys, u16 opcode)
{

}

void and_f(c8sys *sys, u16 opcode)
{

}

void xor_f(c8sys *sys, u16 opcode)
{

}

void sub_f(c8sys *sys, u16 opcode)
{

}

void shr_f(c8sys *sys, u16 opcode)
{

}

void subn_f(c8sys *sys, u16 opcode)
{

}

void shl_f(c8sys *sys, u16 opcode)
{

}

void rnd_f(c8sys *sys, u16 opcode)
{

}

void drw_f(c8sys *sys, u16 opcode)
{

}

void skp_f(c8sys *sys, u16 opcode)
{

}

void sknp_f(c8sys *sys, u16 opcode)
{

}

