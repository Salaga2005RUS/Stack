#ifndef STACK_H
#define STACK_H

#define MUL_DIV_COEF 2
#define CAPACITY_0 5

typedef int elem_t;
typedef unsigned long long canary_t;

typedef struct
{
    canary_t    canary_left;
    elem_t      size;
    elem_t      capacity;
    canary_t    canary_reference;   
    canary_t*   canary_left_arr_ptr;
    elem_t*     data; 
    canary_t*   canary_right_arr_ptr;
    canary_t    canary_right;   
} Stack;

enum IncreaseDecreaseMode 
{
    increase = 1,
    decrease = -1
};

enum CanaryErrorCode
{
    left_stack_canary_dead  = -1,
    right_stack_canary_dead = 1,
    left_arr_canary_dead    = 2,
    right_arr_canary_dead   = -2,
    canary_alive            = 0
};

enum StackErrorCode
{
    clear_stack             = 0,
    error_stack_ptr         = 1,
    error_array_ptr         = 2,
    error_stack_size        = 3,
    error_stack_capacity    = 4
};

int StackInit       (Stack *stk, elem_t capacity_0);
int StackDestroy    (Stack *stk);

int StackPush   (Stack *stk, elem_t value);
int StackPop    (Stack *stk, elem_t *ret_value);

void StackResize (Stack *stk, enum IncreaseDecreaseMode);

StackErrorCode StackOK (Stack *stk);

canary_t GenerateCanary ();
CanaryErrorCode CanaryChecking (Stack *stk);

void CreateDataArray (Stack *stk);

void CanaryPtrMoving (Stack *stk);


#endif