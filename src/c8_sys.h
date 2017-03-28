#include <stdio.h>
#include <stdbool.h>
#include "def.h"

#ifndef C8_SYS_H
#define C8_SYS_H
 
	/* TODO
	 * this table contains the addresses
	 * of the sprites of different hex values (0x0 - 0xF)
	 */
	extern const u16 hexsprite_address[16];

	struct chipsys {
		u8 V[16];
		u16 I:12;
		u16 PC:12;
		// first *unused* address in the stack
		u8 SP:4; 
		u16 stack[16];
		u8 memory[4096];
		
		u64 screen[32];
		u8 key[16];
		u8 delay_timer;
		u8 sound_timer;
	};


	void sys_clone(struct chipsys *src, struct chipsys *dst);
	bool sys_equ(struct chipsys *s1, struct chipsys *s2);

	/* screen format:
	 * ( 0, 0)       (63, 0)
	 * 
	 * ( 0,31)       (63,31)
	 */
	void screen_xor_pixel(struct chipsys *sys, int x, int y, bool state);
	int screen_get_pixel(struct chipsys *sys, int x, int y);

	void sys_init(struct chipsys *sys);
	int sys_load_rom(struct chipsys *sys, const char *filename);
	int sys_emulate_cycle(struct chipsys *sys);
	void sys_memdump(struct chipsys *sys, FILE *write_to);

#endif
