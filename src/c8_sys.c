#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "opcode.h"
#include "def.h"
#include "c8_sys.h"
 
const u16 hexsprite_address[16] = {
	00,05,10,15,
	20,25,30,35,
	40,45,50,55,
	60,65,70,75
};

void sys_clone(struct chipsys *src, struct chipsys *dst)
{
	memcpy(dst,src,sizeof(struct chipsys));
}

bool sys_equ(struct chipsys *s1, struct chipsys *s2)
{
        return memcmp(s1,s2,sizeof(struct chipsys)) == 0;
}

/*
 * 
 */
void screen_xor_pixel(struct chipsys *sys, int x, int y, bool state)
{
	(void)assert((state == 0 || state == 1) && 
		(x >= 0 && x < 64) && 
		(y >= 0 && y < 32));
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

	/* add sprites for hexdec chars
	 * TODO: create a char[] with these values and copy it 
	 * into the system  memory, add entire alphabet?
	 */
	u8 *addr = sys->memory;
	// 0
	*addr++ = 0xF0;
	*addr++ = 0x90;
	*addr++ = 0x90;
	*addr++ = 0x90;
	*addr++ = 0xF0;
	// 1
	*addr++ = 0x20;
	*addr++ = 0x60;
	*addr++ = 0x20;
	*addr++ = 0x20;
	*addr++ = 0x70;
	// 2
	*addr++ = 0xF0;
	*addr++ = 0x10;
	*addr++ = 0xF0;
	*addr++ = 0x80;
	*addr++ = 0xF0;
	// 3
	*addr++ = 0xF0;
	*addr++ = 0x10;
	*addr++ = 0xF0;
	*addr++ = 0x10;
	*addr++ = 0xF0;
	// 4
	*addr++ = 0x90;
	*addr++ = 0x90;
	*addr++ = 0xF0;
	*addr++ = 0x10;
	*addr++ = 0x10;
	// 5
	*addr++ = 0xF0;
	*addr++ = 0x80;
	*addr++ = 0xF0;
	*addr++ = 0x10;
	*addr++ = 0xF0;
	// 6
	*addr++ = 0xF0;
	*addr++ = 0x80;
	*addr++ = 0xF0;
	*addr++ = 0x90;
	*addr++ = 0xF0;
	// 7
	*addr++ = 0xF0;
	*addr++ = 0x10;
	*addr++ = 0x20;
	*addr++ = 0x40;
	*addr++ = 0x40;
	// 8
	*addr++ = 0xF0;
	*addr++ = 0x90;
	*addr++ = 0xF0;
	*addr++ = 0x90;
	*addr++ = 0xF0;
	// 9
	*addr++ = 0xF0;
	*addr++ = 0x90;
	*addr++ = 0xF0;
	*addr++ = 0x10;
	*addr++ = 0xF0;
	// A
	*addr++ = 0xF0;
	*addr++ = 0x90;
	*addr++ = 0xF0;
	*addr++ = 0x90;
	*addr++ = 0x90;
	// B
	*addr++ = 0xE0;
	*addr++ = 0x90;
	*addr++ = 0xE0;
	*addr++ = 0x90;
	*addr++ = 0xE0;
	// C
	*addr++ = 0xF0;
	*addr++ = 0x80;
	*addr++ = 0x80;
	*addr++ = 0x80;
	*addr++ = 0xF0;
	// D
	*addr++ = 0xE0;
	*addr++ = 0x90;
	*addr++ = 0x90;
	*addr++ = 0x90;
	*addr++ = 0xE0;
	// E
	*addr++ = 0xF0;
	*addr++ = 0x80;
	*addr++ = 0xF0;
	*addr++ = 0x80;
	*addr++ = 0xF0;
	// F
	*addr++ = 0xF0;
	*addr++ = 0x80;
	*addr++ = 0xF0;
	*addr++ = 0x80;
	*addr++ = 0x80;
}

/* 
 * Load the rom located in <filename>
 */
int sys_load_rom(struct chipsys *sys, const char *filename)
{
	FILE *rom = fopen(filename, "r");
	if(!rom){
		fprintf(stderr,
			"[ERROR] <sys_load_rom> Could not open rom: %s\n", 
			filename);
		return EXIT_FAILURE;
	}

	//load rom into system memory
	unsigned int addr = 0x0200;
	int byte;
	while((byte = fgetc(rom)) != EOF){
		if(addr == 0x1000){
			fprintf(stderr,
				"[ERROR] <sys_load_rom> rom too large, cannot load into memory: %s\n",
				filename);
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
	u16 opcode = sys->memory[sys->PC++];
	opcode <<= 8;
	opcode |= sys->memory[sys->PC++];

	int status = opcode_execute(sys, opcode);

	if(status != EXIT_SUCCESS){
		fputs("[ERROR] <sys_emulate_cycle> opcode_execute failed\n",
			stderr);
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
