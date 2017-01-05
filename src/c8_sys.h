#include "def.h"

#ifndef C8_SYS_H
#define C8_SYS_H

	struct chipsys {
		uint64_t screen[32];
		u8 key[16];
		u8 delay_timer;
		u8 sound_timer;

		u8 V[16];
		u16 I:12;
		u16 PC:12;
		// first *unused* address in the stack
		u8 SP:4; 
		u16 stack[16];
		u8 memory[4096];
	};

	/* screen format:
	 * ( 0, 0)       (63, 0)
	 * 
	 * ( 0,31)       (63,31)
	 */
	void screen_xor_pixel(struct chipsys *sys, int x, int y, bool state);
	int screen_get_pixel(struct chipsys *sys, int x, int y);

	void sys_init(struct chipsys *sys);
	int sys_load_rom(struct chipsys *sys, const char *filename);
	void sys_emulate_cycle(struct chipsys *sys);
	void sys_memdump(struct chipsys *sys, FILE *write_to);

#endif
