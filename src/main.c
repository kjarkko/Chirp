#include <string.h>
#include "def.h"
#include "c8_sys.h"
#include "io.h"

char *get_rom(void);

/* -r [file] load rom
 */
int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	char *rom_loc = get_rom();
	
	chipsys sys;
	sys_init(&sys);
	sys_load_rom(&sys, rom_loc);



	while(0){
		sys_emulate_cycle(&sys);
	}
	
	sys_memdump(&sys, stdout);

	return EXIT_SUCCESS;
}

char *get_rom(void)
{
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

