#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "GenericStackSetEmptyConfig.h"

#define GENERIC_STACK_POSTFIX t3

typedef unsigned int uint;
#define GENERIC_STACK_TYPE uint
#define CAPACITY_IS_POW2
//#define WITHOUT_AUTO_CHECK_VALID
#include "GenericStack.h"
#undef GENERIC_STACK_TYPE 

extern int test_3();