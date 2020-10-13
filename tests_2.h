#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "GenericStackConfigEnum.h" //optional for #define GS_CONFIG GS_CF_CMP | GS_CF_EDUMP

#define GENERIC_STACK_POSTFIX t2

extern void double_t2_gs_elem_dump(FILE *file, double x);
extern void int_t2_gs_elem_dump(FILE *file, int x);

#define GENERIC_STACK_TYPE double
#define ELEM_DUMPABLE
#define CANARY_FS_USE_PTR
#define GS_CONFIG 0b11000000
#include "GenericStack.h"
#undef GENERIC_STACK_TYPE 

#define GENERIC_STACK_TYPE int
#undef CANARY_FS_USE_PTR
#include "GenericStack.h"
#undef GENERIC_STACK_TYPE 

extern int test_2();