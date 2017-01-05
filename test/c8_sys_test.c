#include <stdlib.h>
#include <stdbool.h>
#include <check.h>
#include "../src/c8_sys.h"


/*
 *
 */
START_TEST(sys_load_rom_test)
{
        const char *rompath;
        struct chipsys sys, cmp;
        
        // empty rom
        rompath = "testrom_empty";
        sys_init(&sys);
        sys_init(&cmp);
        ck_assert(sys_load_rom(&sys, rompath) == EXIT_SUCCESS);
        ck_assert(sys_equ(&sys, &cmp) == true);

        // writes single byte 0x81
        rompath = "testrom_single_0x81";
        sys_init(&sys);
        sys_init(&cmp);
        ck_assert(sys_load_rom(&sys, rompath) == EXIT_SUCCESS);
        cmp.memory[0x200] = 0x81;
        ck_assert(sys_equ(&sys, &cmp) == true);
        
        // fills the memory with byte 0xFF
        rompath = "testrom_full_0xFF";
        sys_init(&sys);
        sys_init(&cmp);
        ck_assert(sys_load_rom(&sys, rompath) == EXIT_SUCCESS);
        memset(&cmp.memory[0x200], 0xFF, 0x1000 - 0x200); // size off-by-one?
        ck_assert(sys_equ(&sys, &cmp) == true);

        // oversized rom
        rompath = "testrom_too_large";
        sys_init(&sys);
        sys_init(&cmp);
        ck_assert(sys_load_rom(&sys, rompath) != EXIT_SUCCESS);
}
END_TEST
