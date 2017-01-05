#include <check.h>
#include <stdbool.h>
#include "../src/c8_sys.h"

START_TEST(mocktest)
{
        struct chipsys sys;
        struct chipsys cmp;
        sys_init(&sys);
        sys_init(&cmp);
        // sys setup
        chipsys_clone(&sys, &cmp);
        sys_emulate_cycle(&sys);
        // change cmp to desired state
        ck_assert(chipsys_equ(&sys, &cmp));
}
END_TEST


