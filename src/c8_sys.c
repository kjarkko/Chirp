#include "c8_sys.h"

inline void sys_init(chipsys *sys)
{
	(void)memset(sys, 0, sizeof(chipsys));
}

/* Load the rom located in <filename>
 */
int sys_load_rom(chipsys *sys, char *filename)
{
	FILE *rom = fopen(filename, "r");
	if(!rom){
		printf("[ERROR] <sys_load_rom> Could not open rom: %s\n", filename);
		return EXIT_FAILURE;
	}

	//load rom into system memory
	unsigned int addr = 0x0200;
	int byte;
	while(1){
		byte = fgetc(rom);
		if(byte == EOF)
			break;
		else if(addr == 0xFFF){
			printf("[ERROR] <sys_load_rom> rom too large, cannot load into memory: %s\n", filename);
			return EXIT_FAILURE;
		}
		++addr;
		sys->memory[addr] = (u8)byte;
	}

	fclose(rom);
	return EXIT_SUCCESS;
}

void sys_emulate_cycle(chipsys *sys)
{
	u16 opcode = sys->memory[sys->PC] << 8 | sys->memory[sys->PC + 1];
	sys->PC += 2;

	int ret = opcode_execute(sys, opcode);
	if(ret == EXIT_FAILURE){
		printf("[ERROR] <sys_emulate_cycle> opcode_execute failed\n");
		exit(EXIT_FAILURE);
	}
}


