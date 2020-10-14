#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "GenericStackSetEmptyConfig.h"

#define GENERIC_STACK_POSTFIX t4


typedef struct point
{
    int x;
    int y;
}point;

extern void point_t4_gs_elem_dump(FILE *file, point x);

#define GENERIC_STACK_TYPE point
#define CAPACITY_IS_POW2
#define HASH_DATA
#define ELEM_DUMPABLE
#define CANARY_FOR_STRUCT
#define GS_WITH_ERROR_VALIDATE
#include "GenericStack.h"
#undef GENERIC_STACK_TYPE 

extern int test_4();