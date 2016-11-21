#include <stdlib.h>
#include <stdio.h>
#include "c8_sys.h"
#include "opcode.h"


inline void sys_init(chipsys *sys)
{
	memset(sys, 0, sizeof(c8sys));
}

int sys_load_rom(chipsys *sys, char *filename)
{
	FILE *rom = fopen(filename "r");
	if(!rom){
		printf("[ERROR] - Could not open rom: %s\n", filename);
		return EXIT_FAILURE;
	}

	//load rom into system memory

	fclose(rom);
	return EXIT_SUCCESS;
}

void sys_emulate_cycle(chipsys *sys)
{
	u16 opcode = sys->memory[sys->PC] << 8 | sys->memory[sys->PC + 1];

}
