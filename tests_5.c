#include "tests_5.h"

int test_5()
{
    generic_stack(int32_t) gs = new_generic_stack(int32_t)(3);
    for (int i = -7; i <= 37; i++) { 
        //actually the whole test happens here, when we realloc ptr(during push), 
        //                if canary stay valid(it check automaticaly) then all ok
        generic_stack_push(int32_t)(&gs, i);
    }
    for (int i = 37; i >= -7; i--) {
        int32_t z = 99;
        if (i != (z = generic_stack_pop(int32_t)(&gs))) {
            printf("! something went wrong:  %d != %d\n", i, z); 
        }
    }

    GENERIC_STACK_LOG(int32_t, &gs, 10, "[-___-]");
    free_generic_stack(int32_t)(&gs);

    printf("OK : TEST 5\n");
    return 0;
}