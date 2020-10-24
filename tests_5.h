//check canary for data with using ptr
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>

#include "GenericStackSetEmptyConfig.h"
#include "GenericStackConfigEnum.h"

#define GENERIC_STACK_POSTFIX t5

#define GENERIC_STACK_TYPE int32_t
#define CANARY_FOR_DATA 
#define CANARY_FD_USE_PTR
#include "GenericStack.h"
#undef GENERIC_STACK_TYPE

extern int test_2();