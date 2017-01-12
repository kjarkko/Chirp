#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "c8_sys.h"
#include "io.h"

#define framerate(fr) (unsigned long)(unsigned int)(1000000 / (unsigned int)fr)

char const *get_rompath(int, char const *[]);

/* -r, --rom [file] load rom 
 */
int main(int argc, char const *argv[])
{
	char const *rom_loc = get_rompath(argc, argv);
	
	struct chipsys sys;
	sys_init(&sys);
	sys_load_rom(&sys, rom_loc);

	while(cont()){
		sys_emulate_cycle(&sys);
		screen_update(sys.screen);
		usleep(framerate(60));
	}

	return EXIT_SUCCESS;
}

char const *get_rompath(int argc, char const *argv[])
{
	for(int i = 1; i < argc; i++){
		if(strcmp("-r", argv[i]) == 0){
			if(i + 1 < argc){
				return argv[i+1];
			}else{
				printf("flag '-r' used but no path specified");
			}
		}
	}

	printf("Enter location of ROM to load: ");
	char loc[256];
	fgets(loc, sizeof(loc), stdin);
	size_t len = strlen(loc);
	if(len > 0)
		loc[len-1] = '\0'; // overwrite \n with \0
	char *ret = malloc(sizeof(char) * (len+1));
	memcpy(ret, loc, sizeof(char) * len+1);
	return ret;
}

