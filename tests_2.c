#include "tests_2.h"


void double_t2_gs_elem_dump(FILE *file, double x)
{
    fprintf(file, " %lf ", x * 4);
}

void int_t2_gs_elem_dump(FILE *file, int x)
{
    fprintf(file, " %d ", x / 2);
}

int test_2()
{
    generic_stack_double_t2 *zd = new_generic_stack_ptr(double)(5);
    generic_stack_push(double)(zd, 13);
    generic_stack_push(double)(zd, 12.0);
    generic_stack_push(double)(zd, 11);
    generic_stack_push(double)(zd, 10);
    generic_stack_pop(double)(zd);
    generic_stack_pop(double)(zd);
    //zd->size++;//crash by hash
    generic_stack_push(double)(zd, 10);
    generic_stack_push(double)(zd, 10);
    generic_stack_push(double)(zd, 9);
    generic_stack_pop(double)(zd);
    generic_stack_push(double)(zd, 8);
    generic_stack_push(double)(zd, 7);
    generic_stack_push(double)(zd, 6);
    generic_stack_push(double)(zd, 5.32);
    generic_stack_pop(double)(zd);
    generic_stack_push(double)(zd, 5.30);
    generic_stack_push(double)(zd, 5.27);
    generic_stack_push(double)(zd, 5.21);
    generic_stack_push(double)(zd, 11.21);
    generic_stack_push(double)(zd, 13.212);
    generic_stack_double_t2 *zd2 = new_generic_stack_ptr(double)(77);
    generic_stack(double) zd3 = new_generic_stack_double_t2(77);
    generic_stack(int) zi = new_generic_stack_int_t2(7);
    generic_stack(int) zi2 = new_generic_stack(int)(17);

    generic_stack_empty(double)(zd);

    generic_stack_double_t2 *gs_d_4 = new_generic_stack_ptr_double_t2(0);
    generic_stack_push(double)(gs_d_4, 10);
    generic_stack_pop(double)(gs_d_4);
    generic_stack_push(double)(gs_d_4, 9);
    generic_stack_push(double)(gs_d_4, 8);

    generic_stack(double) *zd_p = zd;

    GENERIC_STACK_LOG(double, zd_p, 20, "");
    GENERIC_STACK_LOG(int, (&zi), 20, "{JUST CHECK:T2}");

    #ifdef GENERIC_STACK_LOG_PSOTFIX_0xEF542EH4
    printf("%lf\n", generic_stack_pop(double)(gs_d_4));
    #endif

    free_generic_stack(double)(zd);
    free_generic_stack(double)(zd2);
    free_generic_stack(double)(&zd3);
    free_generic_stack(double)(gs_d_4);
    free_generic_stack(int)(&zi);
    free_generic_stack(int)(&zi2);

    generic_stack(int) *gs_i = new_generic_stack_ptr(int)(0);
    for (int i = 0; i < 25; i++) {
        generic_stack_push(int)(gs_i, i * 4);
    }    
    GENERIC_STACK_LOG(int, gs_i, -1, "");
    for (int i = 24; i >= 5; i--) {
        if (i * 4 != generic_stack_pop(int)(gs_i)) {
            printf("WRONG VALUE\n");
            exit(1);
        }
    }
    GENERIC_STACK_LOG(int, gs_i, -1, "");
    free_generic_stack(int)(gs_i);

    return 0;
}