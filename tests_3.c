#include "tests_3.h"

int test_3()
{
    generic_stack(uint) *gs_u = new_generic_stack_ptr(uint)(3);
    GENERIC_STACK_LOG(uint, gs_u, 10, "[capacity == 4]");
    if (gs_u->capacity != 4) {
        printf("error capacity!");
        exit(1);
    }
    generic_stack_push(uint)(gs_u, 1);
    generic_stack_push(uint)(gs_u, 2);
    generic_stack_push(uint)(gs_u, 3);
    generic_stack_push(uint)(gs_u, 4);
    generic_stack_push(uint)(gs_u, 5);
    generic_stack_push(uint)(gs_u, 6);
    GENERIC_STACK_LOG(uint, gs_u, 10, "[capacity == 8]");
    if (gs_u->capacity != 8) {
        printf("error capacity!");
        exit(1);
    }
    generic_stack_set_capacity(uint)(gs_u, 12);
    GENERIC_STACK_LOG(uint, gs_u, 10, "[capacity == 16]");
    if (gs_u->capacity != 16) {
        printf("error capacity!");
        exit(1);
    }

    if (generic_stack_pop(uint)(gs_u) != 6) {
        printf("error in pop!");
        exit(1);
    }
    generic_stack_squeeze_capacity(uint)(gs_u);
    GENERIC_STACK_LOG(uint, gs_u, 10, "[capacity == 8]");
    if (gs_u->capacity != 8) {
        printf("error capacity!");
        exit(1);
    }

    generic_stack_set_capacity(uint)(gs_u, 3); // be careful with it
    GENERIC_STACK_LOG(uint, gs_u, 10, "[capacity == 4]");
    if (generic_stack_pop(uint)(gs_u) != 3) {
        printf("error in pop!");
        exit(1);
    }

    generic_stack_set_capacity(uint)(gs_u, 0); 
    GENERIC_STACK_LOG(uint, gs_u, 10, "[ptr == NULL]");
    if (gs_u->ptr != NULL) {
        printf("error in set capacity!");
        exit(1);
    }
    generic_stack_push(uint)(gs_u, 1);
    generic_stack_push(uint)(gs_u, 2);
    GENERIC_STACK_LOG(uint, gs_u, 10, "[capacity == 2]");
    if (generic_stack_pop(uint)(gs_u) != 2) {
        printf("error in pop!");
        exit(1);
    }

    free_generic_stack(uint)(gs_u);
    return 0;
}