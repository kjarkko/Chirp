//#include <gtk/gtk.h>
#include "def.h"
#include "c8_sys.h"

#ifndef IO_H
#define IO_H

    u8 wkeypress(u8 *accepted);
    void terminal_print_screen(uint64_t screen[]);
    /*
    gtkApplication *screen_init();
    void screen_update(chipsys *sys, gtkApplication *screen);
    void screen_close(gtkApplication *screen);
    */
    
#endif
