#include "def.h"
#include "c8_sys.h"
 
#ifndef IO_H
#define IO_H

	char *get_rompath();

	/* determines whether the program should continue normally,
	 * halt or restart (load new rom etc)
	 * 0 = continue normally
	 * 1 = restart
	 * 2 = exit
	 */
	int cont(void); 
	u8 wkeypress(u8 *accepted);
	bool ispressed(u8 key);

	int screen_init(void);
	int screen_update(u64 screen[32]);
	int screen_close(void);
#endif
