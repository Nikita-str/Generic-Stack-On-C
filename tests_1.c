#include "tests_1.h"

int double_gs_comparator(double a, double b)
{
    //EPS
    if (a < b)return 1;
    if (a > b)return -1;
    return 0;
}

void double_gs_elem_dump(FILE *file, double x)
{
    fprintf(file, " %lf ", x);
}

int int_gs_comparator(int a, int b)
{
    //EPS
    if (a < b)return 1;
    if (a > b)return -1;
    return 0;
}
void int_gs_elem_dump(FILE *file, int x)
{
    fprintf(file, " %d ", x);
}

int test_1()
{
    unsigned char data_for_hash[12] = {0x12, 0x11, 0xA1, 0xAC, 0xBC, 0x3D, 0x7F, 0xFF, 0x13, 0x31, 0xA1, 0xAC};
    hash_t hash = 0;
    hash = gs_mem_hash_add(hash, data_for_hash, 0, 2);
    hash = gs_mem_hash_add(hash, data_for_hash, 2, 4);
    hash = gs_mem_hash_add(hash, data_for_hash, 4, 6);
    hash = gs_mem_hash_add(hash, data_for_hash, 6, 8);
    #define TOTO 12
    #if TOTO > 8
    hash = gs_mem_hash_add(hash, data_for_hash, 8, 10);
    #endif
    #if TOTO > 10
    hash = gs_mem_hash_add(hash, data_for_hash, 10, 12);
    #endif
    #if TOTO == 10
    hash_t hash_8 = gs_get_mem_hash(data_for_hash, 0, 10);
    #elif TOTO == 12
    hash_t hash_8 = gs_get_mem_hash(data_for_hash, 0, 12);
    #else
    hash_t hash_8 = gs_get_mem_hash(data_for_hash, 0, 8);
    #endif
    if (hash != hash_8) {
        printf("ERROR IN HASH FUNCTION\n");
        exit(1);
    }
    
    generic_stack_double *zd = new_generic_stack_ptr(double)(5);
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
    generic_stack_double *zd2 = new_generic_stack_ptr_double(77);
    generic_stack(double) zd3 = new_generic_stack_double(77);
    generic_stack_make_valid_canary(double)(&zd3);
    generic_stack(int) zi = new_generic_stack_int(7);
    generic_stack(int) zi2 = new_generic_stack_int(17);

    generic_stack_empty(double)(zd);

    printf("%d\n", generic_stack_compare(double)(zd, zd2));
    printf("%d\n", generic_stack_compare(double)(zd, &zd3));
    printf("%d\n", generic_stack_compare(int)(&zi, &zi2));

    generic_stack_double *gs_d_4 = new_generic_stack_ptr_double(0);
    generic_stack_push(double)(gs_d_4, 10);
    generic_stack_pop(double)(gs_d_4);
    generic_stack_push(double)(gs_d_4, 9);
    generic_stack_push(double)(gs_d_4, 8);

    generic_stack(double) *zd_p = zd;

    GENERIC_STACK_LOG(double, zd_p, 20, "");
    GENERIC_STACK_LOG(int, (&zi), 20, "{JUST CHECK}");

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
    generic_stack_pop(int)(gs_i);
    free_generic_stack(int)(gs_i);

    return 0;
}