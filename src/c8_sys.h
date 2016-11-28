#include "def.h"

#ifndef C8_SYS_H
#define C8_SYS_H
	typedef struct {
		u8 memory[4096];
		u16 PC;
		u16 stack[16];
		u16 SP;

		u16 V[16];
		u16 I;

		uint64_t screen[32];
		u8 key[16];
		u8 delay_timer;
		u8 sound_timer;
	} chipsys;

	/* screen format:
	* ( 0, 0)       (63, 0)
	* 
	* ( 0,31)       (63,31)
	*/
	void screen_xor_pixel(chipsys *sys, int x, int y, int on_off);
	int screen_get_pixel(chipsys *sys, int x, int y);

	void sys_init(chipsys *sys);
	int sys_load_rom(chipsys *sys, char *filename);
	void sys_emulate_cycle(chipsys *sys);
	void sys_memdump(chipsys *sys, FILE *write_to);

#endif
