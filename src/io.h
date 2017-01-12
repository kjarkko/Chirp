#include "def.h"
#include "c8_sys.h"
 
#ifndef IO_H
#define IO_H
 
    /* determines whether the program should halt due to user input,
     * for example esc key has been pressed
     */
	int cont(void); 
	u8 wkeypress(u8 *accepted);
	bool ispressed(u8 key);

	int screen_init(void);
	int screen_update(uint64_t screen[32]);
	int screen_close(void);
    
#endif
