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
	assert(
		(state == 0 || state == 1) && 
		(x >= 0 && x < 64) && 
		(y >= 0 && y < 32)
	);
	sys->screen[y] ^= ((u64)state << x);
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

	static const u8 sprites[80] = {
		0xF0,0x90,0x90,0x90,0xF0, // 0
		0x20,0x60,0x20,0x20,0x70, // 1
		0xF0,0x10,0xF0,0x80,0xF0, // 2
		0xF0,0x10,0xF0,0x10,0xF0, // 3
		0x90,0x90,0xF0,0x10,0x10, // 4
		0xF0,0x80,0xF0,0x10,0xF0, // 5
		0xF0,0x80,0xF0,0x90,0xF0, // 6
		0xF0,0x10,0x20,0x40,0x40, // 7
		0xF0,0x90,0xF0,0x90,0xF0, // 8
		0xF0,0x90,0xF0,0x10,0xF0, // 9
		0xF0,0x90,0xF0,0x90,0x90, // A
		0xE0,0x90,0xE0,0x90,0xE0, // B
		0xF0,0x80,0x80,0x80,0xF0, // C
		0xE0,0x90,0x90,0x90,0xE0, // D
		0xF0,0x80,0xF0,0x80,0xF0, // E
		0xF0,0x80,0xF0,0x80,0x80  // F
	};
	memcpy(sys->memory, sprites, sizeof(sprites));
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

	size_t memsize = 0x1000 - 0x200;
	(void)fread(&sys->memory[0x200], sizeof(char), memsize, rom);
	
	int ret = ferror(rom);
	if(ret != EXIT_SUCCESS)
		fprintf(
			stderr,
		        "[ERROR] <sys_load_rom>"
			" error %d while reading rom: %s\n", 
			ret, filename
		);
	else if(!feof(rom))
		fprintf(
			stderr,
		        "[WARNING] <sys_load_rom>"
			" ROM too large, not fully loaded into memory: %s\n", 
		        filename
		);

	fclose(rom);
	return ret;
}

/*
 * 
 */
int sys_emulate_cycle(struct chipsys *sys)
{
	u16 opcode = sys->memory[sys->PC++];
	opcode <<= 8;
	opcode |= sys->memory[sys->PC++];

	int ret = opcode_execute(sys, opcode);

	if(ret != EXIT_SUCCESS){
		fprintf(stderr, 
			"[ERROR] <sys_emulate_cycle>"
			" opcode_execute failed: %d\n", ret);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
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
