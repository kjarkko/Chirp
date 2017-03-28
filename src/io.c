#include <stdlib.h>
#include <string.h>
//#include <gtk-3.0/gtk/gtk.h>
#include "io.h"

char *get_rompath()
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


int cont(void)
{
	return 0;
}

u8 wkeypress(u8 *accepted){
        return 0;
}

bool ispressed(u8 key)
{
	return false;
}

int screen_init(void)
{
	return EXIT_FAILURE;
}

int screen_update(u64 screen[32])
{
	return EXIT_FAILURE;
}

int screen_close(void)
{
	return EXIT_FAILURE;
}

