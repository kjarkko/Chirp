#include "def.h"

typedef struct {
	u8 memory[4096];
	u16 PC;
	u8 stack[16];
	u16 SP;

	u16 V[16];
	u16 I;

	u8 screen[64 * 32];
	u8 key[16];
	u8 delay_timer;
	u8 sound_timer;
} chipsys;

inline void sys_init(chipsys *sys);
int sys_load_rom(chipsys *sys, char *filename);
void sys_emulate_cycle(chipsys *sys);