#ifdef GENERIC_STACK_TYPE

/****
{NOTE:0} 
  don't override NULL it's not funny at all cause its original definition depends on [compiler/<stddef.h> handler]
{NOTE:1}
  if something start with __ it mean: "not use it please". so ponder do you really want use it. 
  if something went wrong after use __%func_name% you deserve it.

{NR:0}
  macros
  CANARY_FS_USE_PTR : NOT RECOMEND ! by cause possibility reallocation dat struct
                        if you use it you should guarantee that there not be mem realloc of generic_stack(corresp. type)
                        OR 
                        use generic_stack_make_valid_canary(corresp. type) after struct mem reallocation
                    AND
                        use only 'new_generic_stack_ptr'
                        OR
                        call 'generic_stack_make_valid_canary' after 'new_generic_stack'

****/

//TODO:ADD:CHANGE CAPACITY

//++++++++##########################[PARANOIC:UNDEFINE]###################

//q.v. {NOTE:0}

#ifdef if
#undef if 
#endif

#ifdef for
#undef for
#endif

#ifdef break
#undef break
#endif

#ifdef while
#undef while
#endif

#ifdef case
#undef case
#endif

#ifdef return
#undef return
#endif

#ifdef size_t
#undef size_t
#endif

#ifdef caanry_t
#undef canary_t
#endif
//---------##########################[PARANOIC:UNDEFINE]###################

#ifdef CANARY_FOR_STRUCT
#define LEFT_CANARY  0xCD9E5AB7E6DAB69AULL //last bit:0
#define RIGHT_CANARY 0xA96BAD6E7BA5E9DCULL //last bit:0
#define SPECIAL_BAD_CANARY 0x59351A1BADCA1497ULL //last bit:1
#endif

#ifndef GS_MAX_DUMP
#define GS_MAX_DUMP 20
#endif

//(*0+)
#define STR(X) #X
#define MACRO_TO_STR(MACRO) STR(MACRO)
//(*0-)

#define GLUE_SECRET(A, B) A##B
#define GLUE(A, B) GLUE_SECRET(A, B) 

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

//+++++###############################[struct define]######################################################
#define generic_stack(T) GLUE(generic_stack_, T)

#ifndef GENERIC_STACK_CANARY_TYPE_PSOTFIX_0xBc4feJ
#define GENERIC_STACK_CANARY_TYPE_PSOTFIX_0xBc4feJ
typedef unsigned long long canary_t;
#endif

static 
struct generic_stack(GENERIC_STACK_TYPE)
{
    #ifdef CANARY_FOR_STRUCT
    canary_t left_canary;
    //canary_t left_sweet_wine_from_some_islands; one of definitions of the word canary: "canary is a sweet wine from the Canary Islands, similar to Madeira."
    #endif
    size_t size;
    size_t capañity;
    GENERIC_STACK_TYPE *ptr;
    #ifdef CANARY_FOR_STRUCT
    canary_t right_canary;
    #endif
};

typedef struct generic_stack(GENERIC_STACK_TYPE) generic_stack(GENERIC_STACK_TYPE);
//-----###############################[struct define]######################################################

//+++++###############################[REAL STATIC FUNC]######################################################
//TODO:pragma
#ifndef GENERIC_STACK_LOG_PSOTFIX_0xEF542EH4
#define GENERIC_STACK_LOG_PSOTFIX_0xEF542EH4
static const GS_LOG_FNAME = "generic_stack_log.log";

bool CLEAR_LOG_FILE = false;

static FILE *generic_stack_log_fopen(const char *name)
{
    if(CLEAR_LOG_FILE)return fopen(name, "a");
    CLEAR_LOG_FILE = true;
    return fopen(name, "w");
}
#endif
//-----###############################[REAL STATIC FUNC]######################################################

//+++++###############################[NEW]######################################################

//++ define func name:

#if defined(CANARY_FOR_STRUCT) && defined(CANARY_FS_USE_PTR)
#define generic_stack_make_valid_canary(T) GLUE(generic_stack_make_valid_canary_, T)
static void generic_stack_make_valid_canary(GENERIC_STACK_TYPE) (generic_stack(GENERIC_STACK_TYPE) *self);
#endif
//--

#define new_generic_stack(T) GLUE(new_generic_stack_, T)
#define new_generic_stack_ptr(T) GLUE(new_generic_stack_ptr_, T)
#define __generic_stack_calloc(T) GLUE(__generic_stack_calloc_, T)

static 
GENERIC_STACK_TYPE *__generic_stack_calloc(GENERIC_STACK_TYPE) (size_t capacity)
{
    GENERIC_STACK_TYPE *ptr = NULL;
    if (capacity) {
        #ifdef CANARY_FOR_DATA
        size_t needable_byte = sizeof(GENERIC_STACK_TYPE) * capacity + sizeof(canary_t) * 2;
        void *data_ptr = calloc(capacity, needable_byte);
        if (!data_ptr) { exit(1); }
        ((canary_t *)data_ptr)[0] = LEFT_CANARY;
        ptr = (GENERIC_STACK_TYPE *)((char *)data_ptr + sizeof(canary_t));
        ((canary_t *)(ptr + capacity))[0] = RIGHT_CANARY;
        #else
        ptr = calloc(capacity, sizeof(GENERIC_STACK_TYPE));
        if (!ptr) { exit(1); }
        #endif
    }
    return ptr;
}

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

    stack.ptr = __generic_stack_calloc(GENERIC_STACK_TYPE)(capacity);

    #ifdef CANARY_FOR_STRUCT
    #ifdef CANARY_FS_USE_PTR //NOT RECOMEND ! by cause possibility reallocation dat struct q.v. {NR:0}
    stack.left_canary = LEFT_CANARY ^ (canary_t)&stack;
    stack.right_canary = RIGHT_CANARY ^ (canary_t)&stack;
    #else
    stack.left_canary  = LEFT_CANARY;
    stack.right_canary = RIGHT_CANARY;
    #endif
    #endif

    if (!stack.ptr) {
        //TODO!use error param
        exit(1);
    }
    stack.capañity = capacity;
    return stack;
}

static
generic_stack(GENERIC_STACK_TYPE) *new_generic_stack_ptr(GENERIC_STACK_TYPE) (size_t capacity)
{
    generic_stack(GENERIC_STACK_TYPE) *self = calloc(1, sizeof(*self));
    *self = new_generic_stack(GENERIC_STACK_TYPE)(capacity);
    #if defined(CANARY_FOR_STRUCT) && defined(CANARY_FS_USE_PTR)
    generic_stack_make_valid_canary(GENERIC_STACK_TYPE)(self);
    #endif
    return self;
}

#define new_empty_generic_stack(T) GLUE(new_empty_generic_stack_, T)

static
generic_stack(GENERIC_STACK_TYPE) new_empty_generic_stack(GENERIC_STACK_TYPE) ()
{
    enum 
    {
        DEFAULT_CAPACITY = 
        #ifdef NOT_REAL_EMPTY_STACK
        NOT_REAL_EMPTY_STACK
        #else
        0x0
        #endif
    };
    return new_generic_stack(GENERIC_STACK_TYPE)(DEFAULT_CAPACITY);
}
//-----###############################[NEW]######################################################

//+++++###############################[IS_VALID]#################################################
#define generic_stack_is_valid(T) GLUE(generic_stack_is_valid_, T)
#define __generic_stack_valid_canary(T) GLUE(__generic_stack_valid_canary_, T)
#ifdef CANARY_FOR_DATA
#define __generic_stack_valid_data_canary(T) GLUE(__generic_stack_valid_data_canary_, T)
#endif
#if defined(CANARY_FOR_STRUCT) && defined(CANARY_FS_USE_PTR)
#define generic_stack_make_valid_canary(T) GLUE(generic_stack_make_valid_canary_, T)
#endif
#ifndef GS_ENUM_VALIDATE
#define GS_ENUM_VALIDATE
typedef enum GENERIC_STACK_ENUM_VALIDATE
{//TODO:paranoic undefine
    GS_VALID,
    GS_NOT_VALID_PTR,
    GS_ERROR_SIZE,
    GS_NOT_VALID_STRUCT,
    //canary:
    GS_LEFT_CANARY_DELIBERATELY_NOT_VALID,
    GS_RIGHT_CANARY_DELIBERATELY_NOT_VALID,
    GS_LR_CANARY_DELIBERATELY_NOT_VALID,
    GS_LEFT_CANARY_NOT_VALID,
    GS_RIGHT_CANARY_NOT_VALID,
    GS_LR_CANARY_NOT_VALID,
    //data canary:
    GS_LEFT_DATA_CANARY_DELIBERATELY_NOT_VALID,
    GS_RIGHT_DATA_CANARY_DELIBERATELY_NOT_VALID,
    GS_LR_DATA_CANARY_DELIBERATELY_NOT_VALID,
    GS_LEFT_DATA_CANARY_NOT_VALID,
    GS_RIGHT_DATA_CANARY_NOT_VALID,
    GS_LR_DATA_CANARY_NOT_VALID,
}GENERIC_STACK_ENUM_VALIDATE;
#endif

//#pragma OwO real static next line
static
GENERIC_STACK_ENUM_VALIDATE __generic_stack_valid_canary(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self)
{
    //switch not can be turn into function by cause in statement 'case x:' x need be const      :|
    //and macro will only worsen readability 

    //not need if it real private     but it don't         :|
    if (!self) { 
        return GS_NOT_VALID_STRUCT;
    }

    #ifdef CANARY_FOR_STRUCT
    int canary_valid = 0b11;

    //this is separate case cause it's suspicious:
    canary_valid ^= ((self->left_canary != SPECIAL_BAD_CANARY)) + ((self->right_canary != SPECIAL_BAD_CANARY) << 1);
    switch (canary_valid) {
    case 0b01:return GS_LEFT_CANARY_DELIBERATELY_NOT_VALID;
    case 0b10:return GS_RIGHT_CANARY_DELIBERATELY_NOT_VALID;
    case 0b11:return GS_LR_CANARY_DELIBERATELY_NOT_VALID;
    default:break;
    }

    canary_valid = 0b11;
    #ifdef CANARY_FS_USE_PTR
    canary_valid ^= ((self->left_canary ^ (canary_t)self) == LEFT_CANARY) + (((self->right_canary ^ (canary_t)self) == RIGHT_CANARY) << 1);
    #else
    canary_valid ^= ((self->left_canary == LEFT_CANARY)) + ((self->right_canary == RIGHT_CANARY) << 1);
    #endif
    switch (canary_valid) {
    case 0b01:return GS_LEFT_CANARY_NOT_VALID;
    case 0b10:return GS_RIGHT_CANARY_NOT_VALID;
    case 0b11:return GS_LR_CANARY_NOT_VALID;
    default:break;
    }
    #endif

    return GS_VALID;
}

#ifdef CANARY_FOR_DATA
static
GENERIC_STACK_ENUM_VALIDATE __generic_stack_valid_data_canary(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self)
{
    //not need if it real private     but it don't         :|
    if (!self) {
        return GS_NOT_VALID_STRUCT;
    }

    int canary_valid = 0b11;

    canary_t left_canary = ((canary_t *) self->ptr)[-1];
    canary_t right_canary = ((canary_t *) (self->ptr + self->capañity))[0];
    

    //this is separate case cause it's suspicious:
    canary_valid ^= ((left_canary != SPECIAL_BAD_CANARY)) + ((right_canary != SPECIAL_BAD_CANARY) << 1);
    switch (canary_valid) {
    case 0b01:return GS_LEFT_DATA_CANARY_DELIBERATELY_NOT_VALID;
    case 0b10:return GS_RIGHT_DATA_CANARY_DELIBERATELY_NOT_VALID;
    case 0b11:return GS_LR_DATA_CANARY_DELIBERATELY_NOT_VALID;
    default:break;
    }
    canary_valid = 0b11;

    canary_valid ^= (left_canary  == LEFT_CANARY) + ((right_canary == RIGHT_CANARY) << 1);
    switch (canary_valid) {
    case 0b01:return GS_LEFT_DATA_CANARY_NOT_VALID;
    case 0b10:return GS_RIGHT_DATA_CANARY_NOT_VALID;
    case 0b11:return GS_LR_DATA_CANARY_NOT_VALID;
    default:break;
    }

    return GS_VALID;
}
#endif

static
GENERIC_STACK_ENUM_VALIDATE generic_stack_is_valid(GENERIC_STACK_TYPE) (const generic_stack(GENERIC_STACK_TYPE) *self)
{
    if (!self) {
        return GS_NOT_VALID_STRUCT;
    }

    bool is_empty_struct = (self->capañity == 0) && (self->size == 0) && (self->ptr == NULL);

    if (!is_empty_struct) {
        if (!self->ptr) {
            return GS_NOT_VALID_PTR;
        }
        if (self->capañity < self->size) {
            return GS_ERROR_SIZE;
        }
    }

    GENERIC_STACK_ENUM_VALIDATE valid_canary = GS_VALID;
    valid_canary = __generic_stack_valid_canary(GENERIC_STACK_TYPE)(self);
    if (valid_canary != GS_VALID) return valid_canary;

    #ifdef CANARY_FOR_DATA
    GENERIC_STACK_ENUM_VALIDATE valid_data_canary = GS_VALID;
    valid_data_canary = __generic_stack_valid_data_canary(GENERIC_STACK_TYPE)(self);
    if (valid_data_canary != GS_VALID) return valid_data_canary;
    #endif

    return GS_VALID;
}

#if defined(CANARY_FOR_STRUCT) && defined(CANARY_FS_USE_PTR)
static
void generic_stack_make_valid_canary(GENERIC_STACK_TYPE) (generic_stack(GENERIC_STACK_TYPE) *self)
{
    self->left_canary = LEFT_CANARY ^ (canary_t)self;
    self->right_canary = RIGHT_CANARY ^ (canary_t)self;
}
#endif
//-----###############################[IS_VALID]#################################################

//+++++###############################[DUMP/LOG]#################################################
#define generic_stack_dump(T) GLUE(generic_stack_dump_, T)

#define generic_stack_get_elem_dump(T) GLUE(T, _gs_elem_dump)
#define generic_stack_elem_dump(T) GLUE(T, _gs_elem_dump)

//TODO:'\t'
#define __GS_ONE_ELEM_DUMP(self, GS_TYPE, X_file, X_ind)       \
fprintf(X_file, "    [%u] {", X_ind);                          \
generic_stack_elem_dump(GS_TYPE)(X_file, self->ptr[X_ind]);    \
fprintf(X_file, "}\n");

static
void generic_stack_dump(GENERIC_STACK_TYPE)(const generic_stack(GENERIC_STACK_TYPE) *self, FILE *generic_stack_log_file, size_t max)
{
    if (!generic_stack_log_file) {
        generic_stack_log_file = generic_stack_log_fopen(GS_LOG_FNAME);
        if (!generic_stack_log_file) { return; }
    }
    fprintf(generic_stack_log_file, "  [%p] generic_stack(%s):\n", self, MACRO_TO_STR(GENERIC_STACK_TYPE));
    if (!self) { goto GS_DUMP_CLOSE_RETURN; }
    fprintf(generic_stack_log_file, "    size:%u  capañity:%u  ptr:[%p]:\n", self->size, self->capañity, self->ptr);
    #ifdef CANARY_FOR_STRUCT
    GENERIC_STACK_ENUM_VALIDATE valid_canary = GS_VALID;
    valid_canary = __generic_stack_valid_canary(GENERIC_STACK_TYPE)(self);
    switch (valid_canary) {
    case GS_LEFT_CANARY_DELIBERATELY_NOT_VALID:
        fprintf(generic_stack_log_file, "    for struct: only left canary deliberately not valid\n    it is suspicious\n");
        break;
    case GS_RIGHT_CANARY_DELIBERATELY_NOT_VALID:
        fprintf(generic_stack_log_file, "    for struct: only right canary deliberately not valid\n    it is suspicious\n");
        break;
    case GS_LR_CANARY_DELIBERATELY_NOT_VALID:
        fprintf(generic_stack_log_file, "    for struct: left and right canary deliberately not valid\n");
        break;
    case GS_LEFT_CANARY_NOT_VALID:
        fprintf(generic_stack_log_file, "    for struct: only left canary not valid => data may not be valid\n");
        break;
    case GS_RIGHT_CANARY_NOT_VALID:
        fprintf(generic_stack_log_file, "    for struct: only right canary not valid => data may not be valid\n");
        break;
    case GS_LR_CANARY_NOT_VALID:
        fprintf(generic_stack_log_file, "    for struct: left and right canary not valid => data may not be valid\n");
        break;
    case GS_VALID:
        fprintf(generic_stack_log_file, "    struct canaries is valid\n");
        break;
    default:fprintf(generic_stack_log_file, "    for struct: something really strange happened\n    function %s not valid ! IMPORTANT\n", 
                                            MACRO_TO_STR(generic_stack_valid_canary(GENERIC_STACK_TYPE)));
    }
    #endif

    if (!self->ptr) { goto GS_DUMP_CLOSE_RETURN; }
    #ifdef CANARY_FOR_DATA
    GENERIC_STACK_ENUM_VALIDATE valid_data_canary = GS_VALID;
    valid_data_canary = __generic_stack_valid_data_canary(GENERIC_STACK_TYPE)(self);
    switch (valid_data_canary) {
    case GS_LEFT_DATA_CANARY_DELIBERATELY_NOT_VALID:
        fprintf(generic_stack_log_file, "    for data: only left canary deliberately not valid\n    it is suspicious\n");
        break;
    case GS_RIGHT_DATA_CANARY_DELIBERATELY_NOT_VALID:
        fprintf(generic_stack_log_file, "    for data: only right canary deliberately not valid\n    it is suspicious\n");
        break;
    case GS_LR_DATA_CANARY_DELIBERATELY_NOT_VALID:
        fprintf(generic_stack_log_file, "    for data: left and right canary deliberately not valid\n");
        break;
    case GS_LEFT_DATA_CANARY_NOT_VALID:
        fprintf(generic_stack_log_file, "    for data: only left canary not valid => data may not be valid\n");
        break;
    case GS_RIGHT_DATA_CANARY_NOT_VALID:
        fprintf(generic_stack_log_file, "    for data: only right canary not valid => data may not be valid\n");
        break;
    case GS_LR_DATA_CANARY_NOT_VALID:
        fprintf(generic_stack_log_file, "    for data: left and right canary not valid => data may not be valid\n");
        break;
    case GS_VALID: 
        fprintf(generic_stack_log_file, "    data canaries is valid\n");
        break;
    default:fprintf(generic_stack_log_file, "    for data: something really strange happened\n    function %s not valid ! IMPORTANT\n",
        MACRO_TO_STR(generic_stack_valid_canary(GENERIC_STACK_TYPE)));
    }
    #endif

    bool valid_size = self->size <= self->capañity;
    if (!valid_size) {
        fprintf(generic_stack_log_file, "    capacity < size ! struct not valid\n");
    }

    #ifdef ELEM_DUMPABLE
    fprintf(generic_stack_log_file, "    {\n");
    if (max != 0 && max < self->capañity + 2 && valid_size) {
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

        if (self->size + 1 < self->capañity) {
            __GS_ONE_ELEM_DUMP(self, GENERIC_STACK_TYPE, generic_stack_log_file, self->size + 1);
            if (self->size + 3 < self->capañity) {
                fprintf(generic_stack_log_file, "    ...\n");
            }
            if (self->size + 2 < self->capañity) {
                __GS_ONE_ELEM_DUMP(self, GENERIC_STACK_TYPE, generic_stack_log_file, self->capañity - 1);
            }
        }

    } else {
        for (size_t ind = 0; ind < self->capañity; ind++) {
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
    FILE *generic_stack_log_file = generic_stack_log_fopen(GS_LOG_FNAME);            \
    if (generic_stack_log_file) {                                                    \
    fprintf(generic_stack_log_file, "%s: %s+%u:\n", __FILE__, __FUNCTION__, __LINE__);  \
    generic_stack_dump(GS_TYPE)(self, generic_stack_log_file, max);                  \
    }                                                                                \
}

#define GENERIC_STACK_AUTO_VALIDATE(GS_TYPE, self, max) \
if (generic_stack_is_valid(GS_TYPE)(self) != GS_VALID) {   \
GENERIC_STACK_LOG(GS_TYPE, self, max);                     \
assert(!"check log file");                                 \
}//TODO:if!assert (get generic_stack_is_valid
//return ret_value ;                after assert i.e. it was shifted here from line afeter assert and before }                         \

#define __GENERIC_STACK_AUTO_VALIDATE(self, ret_value) GENERIC_STACK_AUTO_VALIDATE(GENERIC_STACK_TYPE, self, GS_MAX_DUMP)
#define __GENERIC_STACK_AUTO_VALIDATE_VOIDF(self) GENERIC_STACK_AUTO_VALIDATE(GENERIC_STACK_TYPE, self, GS_MAX_DUMP)

//-----###############################[DUMP/LOG]#################################################


//+++++###############################[FREE]#####################################################
#define free_generic_stack(T) GLUE(free_generic_stack_, T)

static
void free_generic_stack(GENERIC_STACK_TYPE) (generic_stack(GENERIC_STACK_TYPE) *self)
{
    __GENERIC_STACK_AUTO_VALIDATE_VOIDF(self);
    free(self->ptr);

    //TODO:ADD #ifdef ?WITH_BREAK_STRUCT? FOR SPEED UP:
    self->size = ~0 ^ 0xA35;
    self->capañity = 0x55;
    self->ptr = NULL; //TODO:paranoic:check:NULL
    #ifdef CANARY_FOR_STRUCT
    self->left_canary = SPECIAL_BAD_CANARY;
    self->right_canary = SPECIAL_BAD_CANARY;
    #endif
}
//-----###############################[FREE]#####################################################

//+++++###############################[PUSH&POP]#################################################
#define generic_stack_push(T) GLUE(generic_stack_push_, T)
//TODO:pragma generic_stack__

static
void generic_stack_push(GENERIC_STACK_TYPE) (generic_stack(GENERIC_STACK_TYPE) *self, GENERIC_STACK_TYPE elem)
{
    __GENERIC_STACK_AUTO_VALIDATE_VOIDF(self);

    if (self->size == self->capañity) {

        size_t new_capacity = self->capañity ? self->capañity * 2 : 1;

        if (new_capacity == 1) {
            self->ptr = __generic_stack_calloc(GENERIC_STACK_TYPE)(new_capacity);
        } else {
            void *temp_ptr = NULL;

            #ifdef CANARY_FOR_DATA
            size_t needable_byte = sizeof(GENERIC_STACK_TYPE) * new_capacity + sizeof(canary_t) * 2;
            temp_ptr = realloc(((canary_t *)self->ptr) - 1, needable_byte);
            #else
            void *temp_ptr = realloc(self->ptr, sizeof(GENERIC_STACK_TYPE) * new_capacity);
            #endif

            if (!temp_ptr) { exit(1); }//TODO!use error param

            #ifdef CANARY_FOR_DATA
            ((canary_t *)temp_ptr)[0] = LEFT_CANARY;
            self->ptr = (GENERIC_STACK_TYPE *)((char *)temp_ptr + sizeof(canary_t));
            ((canary_t *)(self->ptr + new_capacity))[0] = RIGHT_CANARY;
            #else
            self->ptr = temp_ptr;
            #endif

            self->capañity = new_capacity;
        }
    }
    self->ptr[self->size++] = elem;
    __GENERIC_STACK_AUTO_VALIDATE_VOIDF(self);
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
    size_t capacity = self->capañity;
    GENERIC_STACK_TYPE *ptr = self->ptr;
    #if defined(CANARY_FOR_STRUCT) && defined(CANARY_FS_USE_PTR)
    canary_t left_canary = self->left_canary;
    canary_t right_canary = self->right_canary;
    #endif

    self->size = other->size;
    self->capañity = other->capañity;
    self->ptr = other->ptr;
    #if defined(CANARY_FOR_STRUCT) && defined(CANARY_FS_USE_PTR)
    self->left_canary = other->left_canary;
    self->right_canary = other->right_canary;
    #endif

    other->size = size;
    other->capañity = capacity;
    other->ptr = ptr;
    #if defined(CANARY_FOR_STRUCT) && defined(CANARY_FS_USE_PTR)
    other->left_canary = left_canary;
    other->right_canary = right_canary;
    #endif

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

//+++++################################[UNDEFS]#############################################

#ifdef CANARY_FOR_STRUCT
#undef LEFT_CANARY  
#undef RIGHT_CANARY
#endif

//-----################################[UNDEFS]#############################################

#endif

