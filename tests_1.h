#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "GenericStackConfigEnum.h" //optional for #define GS_CONFIG GS_CF_CMP | GS_CF_EDUMP

extern int double_gs_comparator(double a, double b);
extern void double_gs_elem_dump(FILE *file, double x);
extern int int_gs_comparator(int a, int b);
extern void int_gs_elem_dump(FILE *file, int x);

//#define/undef CAPACITY_IS_POW2
//#define/undef NOT_REAL_EMPTY_STACK 0x10

#define GENERIC_STACK_TYPE double
#define ELEM_DUMPABLE
#define COMPARABLE
#define CANARY_FS_USE_PTR
#define GS_CONFIG 0b11110000
#include "GenericStack.h"
#undef GENERIC_STACK_TYPE 

#define GENERIC_STACK_TYPE int
#undef CANARY_FS_USE_PTR
#undef ELEM_DUMPABLE
#include "GenericStack.h"
#undef GENERIC_STACK_TYPE 

extern int test_1();