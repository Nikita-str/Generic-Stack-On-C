#include "tests_4.h"

void point_t4_gs_elem_dump(FILE *file, point e)
{
    fprintf(file, " x: %d;  y: %d;  ", e.x, e.y);
}

int test_4()
{
    GENERIC_STACK_ENUM_VALIDATE gs_error = 0;
    generic_stack(point) *gs_0 = new_generic_stack_ptr(point)(4, &gs_error);
    generic_stack_push(point)(gs_0, (point){12, 11}, &gs_error);
    if (gs_error != GS_VALID) {
        printf("! something wrong with gs_error: %d\n", gs_error);
        exit(1);
    }
    canary_t lcanary = gs_0->left_canary;
    gs_0->left_canary = 111;
    generic_stack_push(point)(gs_0, (point) { 11, 10 }, &gs_error);
    if (gs_error != GS_LEFT_CANARY_NOT_VALID) {
        printf("! something wrong with STRUCT CANARY VALIDATION gs_error: %d\n", gs_error);
        exit(1);
    }
    gs_0->left_canary = lcanary;
    generic_stack_push(point)(gs_0, (point) { 11, 10 }, &gs_error);
    if (gs_error != GS_VALID) {
        printf("! something wrong with gs_error: %d\n", gs_error);
        exit(1);
    }
    generic_stack_push(point)(gs_0, (point) { 10, 9 }, &gs_error);
    generic_stack_push(point)(gs_0, (point) { 9, 8 }, &gs_error);
    int save_y = gs_0->ptr[1].y;
    gs_0->ptr[1].y = 54;
    generic_stack_push(point)(gs_0, (point) { 8, 7 }, &gs_error);
    if (gs_error != GS_DATA_HASH_NOT_VALID) {
        printf("! something wrong with DATA_HASH VALIDATION gs_error: %d\n", gs_error);
        exit(1);
    }
    gs_0->ptr[1].y = save_y;
    generic_stack_push(point)(gs_0, (point) { 8, 7 }, &gs_error);
    GENERIC_STACK_LOG(point, gs_0, 10, "[CHECK:point]");

    free_generic_stack(point)(gs_0, &gs_error);
    return 0;
}
