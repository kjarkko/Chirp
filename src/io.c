#include <stdlib.h>
#include "io.h"

u8 wkeypress(u8 accepted[16])
{
    (void)accepted;
    exit(-1);
}

/*
 * 
 */
void terminal_print_screen(uint64_t screen[])
{
    for(int i = 0; i < 32; i++){
        for(int j = 0; j < 64; j++){
            putc(
                (screen[i] & (1 << j)) ? '#' : '.',
                stdout
            );
        }
        putc('\n', stdout);
    }
}
/*
gtkApplication *screen_init()
{

}

void screen_update(chipsys *sys, gtkApplication *screen)
{
    
}

void screen_close(gtkApplication *screen)
{

}
*/
