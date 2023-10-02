#ifndef STACK_H
#define STACK_H

#define MUL_DIV_COEF 2
#define CAPACITY_0 5

typedef int elem_t;
typedef unsigned long long canary_t;

typedef struct
{
    canary_t     canary_left;
    unsigned int hash_stk;
    unsigned int hash_data;
    elem_t       size;
    elem_t       capacity;
    canary_t     canary_reference;   
    canary_t*    canary_left_arr_ptr;
    elem_t*      data; 
    canary_t*    canary_right_arr_ptr;
    canary_t     canary_right;   
} Stack;

enum IncreaseDecreaseMode 
{
    increase = 1,
    decrease = -1
};

enum StackErrorCode
{
    clear_stack             = 1,
    error_stack_ptr         = 2,
    error_array_ptr         = 4,
    error_stack_size        = 8,
    error_stack_capacity    = 16,
    hash_error_stack_data   = 32,
    hash_error_stack        = 64,
    hash_error_data         = 128,
    left_stack_canary_dead  = 256,
    right_stack_canary_dead = 512,
    left_arr_canary_dead    = 1024,
    right_arr_canary_dead   = 2048
};

int StackInit       (Stack *stk, elem_t capacity_0);
int StackDestroy    (Stack *stk);

int StackPush       (Stack *stk, elem_t value);
int StackPop        (Stack *stk, elem_t *ret_value);

void StackResize    (Stack *stk, enum IncreaseDecreaseMode);

int StackValidator  (Stack *stk);

canary_t GenerateCanary ();

void CreateDataArray    (Stack *stk);

void CanaryPtrMoving    (Stack *stk);

unsigned int HashFAQ6   (const char* str, int size);

unsigned int HashOfData     (Stack *stk);
unsigned int HashOfStack    (Stack *stk);

void MakeHash (Stack *stk);

#endif