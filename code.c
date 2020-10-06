#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

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

#define GENERIC_STACK_TYPE double
//#define/undef CAPACITY_IS_POW2
//#define/undef COMPARABLE
//#define/undef ELEM_DUMPABLE
#define ELEM_DUMPABLE
#define COMPARABLE
#include "GenericStack.h"
#undef GENERIC_STACK_TYPE 

#define GENERIC_STACK_TYPE int
//#define/undef CAPACITY_IS_POW2
//#define/undef COMPARABLE
#undef ELEM_DUMPABLE
#define COMPARABLE
#include "GenericStack.h"
#undef GENERIC_STACK_TYPE 
/*/
#define GENERIC_STACK_TYPE double
#include "GenericStack.h"
#undef GENERIC_STACK_TYPE 
/**/
#pragma omega_macro:OwO version 0 { delete "static" level:now } & define unique \
    zz
#pragma omega_macro:OwO !delete what:next_line


//TODO:add validate func; add dump func; add error param (used for release)
int main()
{
    generic_stack_double zd = new_generic_stack_double(5);
    generic_stack_push(double)(&zd, 13);
    generic_stack_push(double)(&zd, 12.0);
    generic_stack_push(double)(&zd, 11);
    generic_stack_push(double)(&zd, 10);
    generic_stack_push(double)(&zd, 9);
    generic_stack_push(double)(&zd, 8);
    generic_stack_push(double)(&zd, 7);
    generic_stack_double zd2 = new_generic_stack_double(77);
    generic_stack(int) zi = new_generic_stack_int(7);
    generic_stack(int) zi2 = new_generic_stack_int(17);

    generic_stack_empty(double)(&zd);//but we can calculate (double) on compile time! so use ?pragma?  \
                                       but declaration depends on lang so not pragma, but one abstract \
                                       lang next level that will be translated to .c

    printf("%d\n",generic_stack_compare(double)(&zd, &zd2));
    printf("%d\n",generic_stack_compare(int)(&zi, &zi2));

    generic_stack(double) *zd_p = &zd;

    //#define ELEM_DUMPABLE

    GENERIC_STACK_LOG(double, zd_p, 20);//hmm.. weird 12.4908... 

    return 0;
}