#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "def.h"
#include "c8_sys.h"
#include "io.h"

#define framerate(fr) (unsigned long)(unsigned int)(1000000 / (unsigned int)fr)

char *get_rompath(int, char const *[]);
int run_sys(struct chipsys *);

/* -r, --rom [file] load rom 
 */
int main(int argc, char const *argv[])
{
	struct chipsys sys;
	do{
		char *rom_loc = get_rompath(argc, argv);
		sys_init(&sys);
		sys_load_rom(&sys, rom_loc);
		free(rom_loc);
	}while(run_sys(&sys) == RESTART);
	return EXIT_SUCCESS;
}

int run_sys(struct chipsys *sys)
{
	int state, ret;

	while((state = cont()) == CONTINUE){
		ret = sys_emulate_cycle(sys);
		if(ret != EXIT_SUCCESS){
			sys_memdump(sys, stderr);
			state = EXIT;
		}
		screen_update(sys->screen);
		(void)usleep(framerate(60));
	}

	return state;
}

