#ifndef STACK_H
#define STACK_H

#define MUL_DIV_COEF 2
#define CAPACITY_0 5

typedef int elem_t;

typedef struct
{
    elem_t *data;
    elem_t size;
    elem_t capacity;
} Stack;

enum IncreaseDecreaseMode 
{
    increase = 1,
    decrease = -1
};

int StackInit (Stack *stk, elem_t capacity_0);
int StackDestroy (Stack *stk);
int StackPush (Stack *stk, elem_t value);
int StackPop (Stack *stk, elem_t *ret_value);
void StackResize (Stack *stk, enum IncreaseDecreaseMode);
void StackOK (Stack *stk);


#endif