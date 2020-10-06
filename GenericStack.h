#ifdef GENERIC_STACK_TYPE

#ifndef GS_MAX_DUMP
#define GS_MAX_DUMP 20
#endif
//TODO: if not define GS_MAX_DUMP

//(*0+)
#define STR(X) #X
#define MACRO_TO_STR(MACRO) STR(MACRO)
//(*0-)

//TODO:while not delete cause attempt to pragma
//(*1++)
//#if MACRO_TO_STR(GENERIC_STACK_TYPE) == "double"
/*#ifndef COMPILE_GENERIC_double
#define COMPILE_GENERIC_double 1
#elif GENERIC_STACK_TYPE == TYPE_I
#ifndef COMPILE_GENERIC_int
#define COMPILE_GENERIC_int 1*/
//(*1+-)


//TODO:pragma omega_macro:OwO
/*        (*2++)
#if !defined(MACRO_1) || !defined(MACRO_2)
#if !defined(MACRO_1)
#define MACRO_1 1
#elif !defined(MACRO_2)
#define MACRO_2 1
#endif
*/ //     (*2+-)

#define GLUE_SECRET(A, B) A##B
#define GLUE(A, B) GLUE_SECRET(A, B) 

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

//+++++###############################[struct define]######################################################
#define generic_stack(T) GLUE(generic_stack_, T)

static 
struct generic_stack(GENERIC_STACK_TYPE)
{
    size_t size;
    size_t capasity;//capacity   :|   ... do it later
    GENERIC_STACK_TYPE *ptr;
};

typedef struct generic_stack(GENERIC_STACK_TYPE) generic_stack(GENERIC_STACK_TYPE);
//-----###############################[struct define]######################################################

//+++++###############################[REAL STATIC FUNC]######################################################
//TODO:pragma

//-----###############################[REAL STATIC FUNC]######################################################

//+++++###############################[NEW]######################################################
#define new_generic_stack(T) GLUE(new_generic_stack_, T)

static
generic_stack(GENERIC_STACK_TYPE) new_generic_stack(GENERIC_STACK_TYPE) (size_t capacity)
{
    #ifdef CAPACITY_IS_POW2
    size_t capacity_0 = capacity;
    size_t capacity_pow2 = 1;
    for (int i = 0; i < sizeof(capacity) * CHAR_BIT; i++) {
        if (!capacity) { break; }
        capacity >>= 1;
        capacity_pow2 <<= 1;
    }
    if (capacity_0 && (capacity_pow2 >> 1) == capacity_0) { capacity_pow2 >>= 1; }
    capacity = capacity_pow2;
    #endif
    generic_stack(GENERIC_STACK_TYPE) stack = {0,};
    if (!capacity) capacity = 1;
    stack.ptr = calloc(capacity, sizeof(GENERIC_STACK_TYPE));
    if (!stack.ptr) {
        //TODO!use error param
        exit(1);
    }
    stack.capasity = capacity;
    return stack;
}

#define new_empty_generic_stack(T) GLUE(new_empty_generic_stack_, T)

static
generic_stack(GENERIC_STACK_TYPE) new_empty_generic_stack(GENERIC_STACK_TYPE) ()
{
    enum { DEFAULT_CAPACITY = 0x10};
    return new_generic_stack(GENERIC_STACK_TYPE)(DEFAULT_CAPACITY);
}
//-----###############################[NEW]######################################################

//+++++###############################[IS_VALID]#################################################
#define generic_stack_is_valid(T) GLUE(generic_stack_is_valid_, T)

#ifndef GS_ENUM_VALIDATE
#define GS_ENUM_VALIDATE
typedef enum GENERIC_STACK_ENUM_VALIDATE
{
    GS_VALID,
    GS_NOT_VALID_PTR,
    GS_ERROR_SIZE,
}GENERIC_STACK_ENUM_VALIDATE;
#endif

static
GENERIC_STACK_ENUM_VALIDATE generic_stack_is_valid(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self)
{
    if (!self->ptr) {
        return GS_NOT_VALID_PTR;
    }
    if (self->capasity < self->size) {
        return GS_ERROR_SIZE;
    }
    return GS_VALID;
}
//-----###############################[IS_VALID]#################################################

//+++++###############################[DUMP/LOG]#################################################
#define generic_stack_dump(T) GLUE(generic_stack_dump_, T)

#define generic_stack_get_elem_dump(T) GLUE(T, _gs_elem_dump)
#define generic_stack_elem_dump(T) GLUE(T, _gs_elem_dump)

#define __GS_ONE_ELEM_DUMP(self, GS_TYPE, X_file, X_ind)       \
fprintf(X_file, "    [%u] {", X_ind);                          \
generic_stack_elem_dump(GS_TYPE)(X_file, self->ptr[X_ind]);    \
fprintf(X_file, "}\n");

static
void generic_stack_dump(GENERIC_STACK_TYPE)(const generic_stack(GENERIC_STACK_TYPE) *self, FILE *generic_stack_log_file, size_t max)
{
    if (!generic_stack_log_file) {
        generic_stack_log_file = fopen("generic_stack_log.log", "a");
        if (!generic_stack_log_file) { return; }
    }
    fprintf(generic_stack_log_file, "  [%p] generic_stack(%s):\n", self, MACRO_TO_STR(GENERIC_STACK_TYPE));
    if (!self) { goto GS_DUMP_CLOSE_RETURN; }
    fprintf(generic_stack_log_file, "    size:%u  capasity:%u  ptr:[%p]:\n", self->size, self->capasity, self->ptr);
    if (!self->ptr) { goto GS_DUMP_CLOSE_RETURN; }
    #ifdef ELEM_DUMPABLE
    fprintf(generic_stack_log_file, "    {\n");
    if (max != 0 && max < self->capasity + 2) {
        size_t to = max / 2;
        if (to > self->size) {
            to = self->size;
        }
        for (size_t ind = 0; ind < to; ind++) {
            __GS_ONE_ELEM_DUMP(self, GENERIC_STACK_TYPE, generic_stack_log_file, ind);
        }
        if (to * 2 < self->size) {
            fprintf(generic_stack_log_file, "    ...\n");
        }
        size_t from = self->size - to; //can overflow but it doesn't matter cause next if
        if (self->size < to) {
            from = to + 1;
        }
        for (size_t ind = from; ind < self->size; ind++) {
            __GS_ONE_ELEM_DUMP(self, GENERIC_STACK_TYPE, generic_stack_log_file, ind);
        }

        if (self->size + 1 < self->capasity) {
            __GS_ONE_ELEM_DUMP(self, GENERIC_STACK_TYPE, generic_stack_log_file, self->size + 1);
            if (self->size + 3 < self->capasity) {
                fprintf(generic_stack_log_file, "    ...\n");
            }
            if (self->size + 2 < self->capasity) {
                __GS_ONE_ELEM_DUMP(self, GENERIC_STACK_TYPE, generic_stack_log_file, self->capasity - 1);
            }
        }

    } else {
        for (size_t ind = 0; ind < self->capasity; ind++) {
            __GS_ONE_ELEM_DUMP(self, GENERIC_STACK_TYPE, generic_stack_log_file, ind);
        }
    }
    fprintf(generic_stack_log_file, "    }\n");
    #else
    fprintf(generic_stack_log_file, "    no func for dump elem\n");
    #endif

GS_DUMP_CLOSE_RETURN:
    fclose(generic_stack_log_file);
}

#define GENERIC_STACK_LOG(GS_TYPE, self, max)                                        \
{                                                                                    \
    FILE *generic_stack_log_file = fopen("generic_stack_log.log", "a");              \
    if (generic_stack_log_file) {                                                    \
    fprintf(generic_stack_log_file, "%s: %s+%u:\n", __FILE__, __FUNCTION__, __LINE__);  \
    generic_stack_dump(GS_TYPE)(self, generic_stack_log_file, max);                  \
    }                                                                                \
}

#define GENERIC_STACK_AUTO_VALIDATE(GS_TYPE, self, max)    \
if (generic_stack_is_valid(GS_TYPE)(self) != GS_VALID) {   \
GENERIC_STACK_LOG(GS_TYPE, self, max);                     \
assert(!"check log file");                                 \
}

#define __GENERIC_STACK_AUTO_VALIDATE(self) GENERIC_STACK_AUTO_VALIDATE(GENERIC_STACK_TYPE, self, GS_MAX_DUMP)

//-----###############################[DUMP/LOG]#################################################


//+++++###############################[FREE]#####################################################
#define free_generic_stack(T) GLUE(free_generic_stack_, T)

static
void free_generic_stack(GENERIC_STACK_TYPE) (generic_stack(GENERIC_STACK_TYPE) *self)
{
    __GENERIC_STACK_AUTO_VALIDATE(self);
    free(self->ptr);
    self->size = ~0;
    self->capasity = 0;
    self->ptr = NULL;
}
//-----###############################[FREE]#####################################################

//+++++###############################[PUSH&POP]#################################################
#define generic_stack_push(T) GLUE(generic_stack_push_, T)
//TODO:pragma generic_stack__

static
void generic_stack_push(GENERIC_STACK_TYPE) (generic_stack(GENERIC_STACK_TYPE) *self, GENERIC_STACK_TYPE elem)
{
    __GENERIC_STACK_AUTO_VALIDATE(self);
    if (self->size == self->capasity) {
        void *temp_ptr = realloc(self->ptr, self->capasity * 2);
        if (!temp_ptr) {
            //TODO!use error param
            exit(1);
        }
        self->ptr = temp_ptr;
        self->capasity *= 2;
    }
    self->ptr[self->size++] = elem;
    __GENERIC_STACK_AUTO_VALIDATE(self);
}



#define generic_stack_pop(T) GLUE(generic_stack_pop_, T)
//TODO:pragma generic_stack__pop

static
GENERIC_STACK_TYPE generic_stack_pop(GENERIC_STACK_TYPE) (generic_stack(GENERIC_STACK_TYPE) *self)
{
    __GENERIC_STACK_AUTO_VALIDATE(self);
    if (self->size == 0) {
        //TODO!use error param
        exit(1);
    } 
    return self->ptr[self->size--];
    __GENERIC_STACK_AUTO_VALIDATE(self);
}
//-----###############################[PUSH&POP]#################################################


//+++++###############################[TOP]#################################################
#define generic_stack_top(T) GLUE(generic_stack_top_, T)
//TODO:pragma generic_stack__

static
GENERIC_STACK_TYPE generic_stack_top(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self)
{
    __GENERIC_STACK_AUTO_VALIDATE(self);
    if (self->size == 0) {
        //TODO!use error param
        exit(1);
    }
    return self->ptr[self->size];
    __GENERIC_STACK_AUTO_VALIDATE(self);
}
//-----###############################[TOP]#################################################

//+++++###############################[EMPTY]#################################################
#define generic_stack_empty(T) GLUE(generic_stack_empty_, T)
//TODO:pragma generic_stack__

static
bool generic_stack_empty(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self)
{
    __GENERIC_STACK_AUTO_VALIDATE(self);
    return self->size == 0;
    __GENERIC_STACK_AUTO_VALIDATE(self);
}
//-----###############################[EMPTY]#################################################

//+++++###############################[SWAP]#################################################
#define generic_stack_swap(T) GLUE(generic_stack_swap_, T)
//TODO:pragma generic_stack__

static
void generic_stack_swap(GENERIC_STACK_TYPE) (generic_stack(GENERIC_STACK_TYPE) *self, generic_stack(GENERIC_STACK_TYPE) *other)
{
    __GENERIC_STACK_AUTO_VALIDATE(self);
    __GENERIC_STACK_AUTO_VALIDATE(other);

    if (self == other) {
        return;
    }

    size_t size = self->size;
    size_t capacity = self->capasity;
    GENERIC_STACK_TYPE *ptr = self->ptr;

    self->size = other->size;
    self->capasity = other->capasity;
    self->ptr = other->ptr;

    other->size = size;
    other->capasity = capacity;
    other->ptr = ptr;

    __GENERIC_STACK_AUTO_VALIDATE(other);
    __GENERIC_STACK_AUTO_VALIDATE(self);
}
//-----###############################[SWAP]#################################################

//+++++###############################[COMPARE]##############################################
#ifdef COMPARABLE
typedef int (*comparator)(GENERIC_STACK_TYPE a, GENERIC_STACK_TYPE b);

#define generic_stack_get_comparator(T) GLUE(T, _gs_comparator)

#define generic_stack_compare(T) GLUE(generic_stack_compare_, T)

static
int generic_stack_compare(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self, const generic_stack(GENERIC_STACK_TYPE) *other)
{
    __GENERIC_STACK_AUTO_VALIDATE(self);
    __GENERIC_STACK_AUTO_VALIDATE(other);
    if (self == other) {
        return 0;
    }
    static comparator cmpr = generic_stack_get_comparator(GENERIC_STACK_TYPE);//TODO

    size_t to = (self->size <= other->size) ? self->size : other->size;
    for (size_t i = 0; i < to; i++) {
        int x = cmpr(self->ptr[i], other->ptr[i]);
        if (!x) return x;
    }

    if (self->size == other->size) {
        return 0;
    } else
    if (self->size < other->size) {
        return 1;
    } else {
        return -1;
    }

}

#define generic_stack_equal(T) GLUE(generic_stack_equal_, T)

static 
bool  generic_stack_equal(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self, const generic_stack(GENERIC_STACK_TYPE) *other)
{ return generic_stack_compare(GENERIC_STACK_TYPE)(self, other) == 0; }


#define generic_stack_not_equal(T) GLUE(generic_stack_not_equal_, T)

static
bool  generic_stack_not_equal(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self, const generic_stack(GENERIC_STACK_TYPE) *other)
{return generic_stack_compare(GENERIC_STACK_TYPE)(self, other) != 0;}


#define generic_stack_less(T) GLUE(generic_stack_less_, T)

static
bool  generic_stack_less(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self, const generic_stack(GENERIC_STACK_TYPE) *other)
{return generic_stack_compare(GENERIC_STACK_TYPE)(self, other) < 0;}


#define generic_stack_less_eq(T) GLUE(generic_stack_less_eq_, T)

static
bool  generic_stack_less_eq(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self, const generic_stack(GENERIC_STACK_TYPE) *other)
{return generic_stack_compare(GENERIC_STACK_TYPE)(self, other) <= 0;}


#define generic_stack_more(T) GLUE(generic_stack_more_, T)

static
bool  generic_stack_more(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self, const generic_stack(GENERIC_STACK_TYPE) *other)
{return generic_stack_compare(GENERIC_STACK_TYPE)(self, other) > 0;}


#define generic_stack_more_eq(T) GLUE(generic_stack_more_eq_, T)

static
bool  generic_stack_more_eq(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self, const generic_stack(GENERIC_STACK_TYPE) *other)
{return generic_stack_compare(GENERIC_STACK_TYPE)(self, other) >= 0;}
#endif
//-----###############################[COMPARE]##############################################


//#endif //!(*2--)

/**/
//(*1+-)
//#endif
/*#endif
#endif*/
//(*1--)
/**/

#endif

//(*1xx) - after special pragma
