#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

int StackInit (Stack *stk, elem_t capacity_0)
{
    stk->size = 0;
    stk->capacity = capacity_0;
    stk->data = (elem_t *) calloc (stk->capacity, sizeof (elem_t));

    StackOK (stk);

    return 0;
}

int StackDestroy (Stack *stk)
{
    StackOK (stk);

    stk->size = 0;
    stk->capacity = 0;
    free (stk->data);   

    return 0;
}

int StackPush (Stack *stk, elem_t value)
{
    StackOK (stk);

    if (stk->size == stk->capacity) StackResize (stk, increase);
    stk->data[stk->size] = value;
    stk->size++;

    return 0;
}

int StackPop (Stack *stk, elem_t *ret_value)
{
    StackOK (stk);
    assert (ret_value != NULL);

    if (stk->size == 0) return 0;
    *ret_value = stk->data[stk->size];
    stk->data[stk->size] = 0;
    stk->size--;
    if (stk->capacity >= 2 * MUL_DIV_COEF * stk->size) StackResize (stk, decrease);

    return 0;
}

void StackResize (Stack *stk, IncreaseDecreaseMode mode)
{
    if (mode == increase) stk->capacity *= MUL_DIV_COEF;
    else stk->capacity /= MUL_DIV_COEF;
    stk->data = (elem_t *) realloc (stk->data, stk->capacity * sizeof (elem_t));
}

void StackOK (Stack *stk)
{
    assert (stk != NULL);
    assert (stk->data != NULL);
    assert (stk->size >= 0);
    assert (stk->capacity >= 0);
}