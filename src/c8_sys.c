#include "opcode.h"
#include "def.h"
#include "c8_sys.h"

/*
 * 
 */
void screen_xor_pixel(struct chipsys *sys, int x, int y, int state)
{
	assert(state == 0 || state == 1);
	assert(x >= 0 && x < 64);
	assert(y >= 0 && y < 32);
	sys->screen[y] ^= ((uint64_t)state << x);
}

/*
 * 
 */
int screen_get_pixel(struct chipsys *sys, int x, int y)
{
	return (int)(sys->screen[y] & (1 << x));
}

/*
 * 
 */
void sys_init(struct chipsys *sys)
{
	(void)memset(sys, 0, sizeof(struct chipsys));
	sys->PC = 0x0200;
}

/* 
 * Load the rom located in <filename>
 */
int sys_load_rom(struct chipsys *sys, const char *filename)
{
	FILE *rom = fopen(filename, "r");
	if(!rom){
		printf("[ERROR] <sys_load_rom> Could not open rom: %s\n", filename);
		return EXIT_FAILURE;
	}

	//load rom into system memory
	unsigned int addr = 0x0200;
	int byte;
	while((byte = fgetc(rom)) != EOF){
		if(addr == 0x1000){
			printf("[ERROR] <sys_load_rom> rom too large, cannot load into memory: %s\n", filename);
			fclose(rom);
			return EXIT_FAILURE;
		}

		sys->memory[addr++] = (u8)byte;
	}

	fclose(rom);
	return EXIT_SUCCESS;
}

/*
 * 
 */
void sys_emulate_cycle(struct chipsys *sys)
{
	u16 opcode = sys->memory[sys->PC] << 8;
	++sys->PC;
	opcode |= sys->memory[sys->PC];
	++sys->PC;

	int ret = opcode_execute(sys, opcode);

	if(ret == EXIT_FAILURE){
		printf("[ERROR] <sys_emulate_cycle> opcode_execute failed\n");
		exit(EXIT_FAILURE);
	}
}

/*
 * 
 */
void sys_memdump(struct chipsys *sys, FILE *write_to)
{
	fputs("\nREGISTERS:\n", write_to);
	fprintf(write_to, "I  [%04x]\n", sys->I);
	for(int i = 0; i < 16; i++)
		fprintf(write_to, "%02d [%04x]\n", i, sys->V[i]);

	fprintf(write_to, "\nSTACK:\nSP - %04x\n",sys->SP);
	for(int i = 0; i < 16; i++)
		fprintf(write_to, "%02d [%04x]\n", i, sys->stack[i]);

	fprintf(write_to, "\nMEMORY:\nPC - %04x\n", sys->PC);
	for(int i = 0; i < 4096;){
		fprintf(write_to, "%03x - %03x:   ", i, i + 15);
		do{
			fprintf(write_to, "%02x  ", sys->memory[i]);
			++i;
		}while(i % 16 != 0);
		fprintf(write_to, "\n");
	}
}
