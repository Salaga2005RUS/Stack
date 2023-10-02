#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "stack.h"

int StackInit (Stack *stk, elem_t capacity_0)
{
    stk->size       = 0;
    stk->capacity   = capacity_0; //TODO rename

    stk->canary_left = stk->canary_right = stk->canary_reference = GenerateCanary();

    CreateDataArray (stk);

    #ifdef _DEBUG
    printf ("StackInit error code: %d\n", StackOK (stk));
    #endif

    return 0;
}

int StackDestroy (Stack *stk)
{
    printf ("StackDestroy error code: %d\n", StackOK (stk)); //TODO debug flag

    stk->size       = 0;
    stk->capacity   = 0;

    stk->data = (elem_t*) ((char*) stk->data - sizeof (canary_t));
    free (stk->data);   

    return 0;
}

int StackPush (Stack *stk, elem_t value)
{
    printf ("StackPush error code: %d\n", StackOK (stk)); //TODO 

    if (stk->size == stk->capacity) StackResize (stk, increase);

    stk->data[stk->size] = value;
    stk->size++;

    return 0;
}

int StackPop (Stack *stk, elem_t *ret_value)
{
    printf ("StackPop error code: %d\n", StackOK (stk)); //TODO
    assert (ret_value != NULL);

    if (stk->size == 0) return 0; //TODO return value is same for good and bad situation

    *ret_value = stk->data[stk->size];
    stk->data[stk->size] = 0;
    stk->size--;

    if (stk->capacity >= 2 * MUL_DIV_COEF * stk->size) StackResize (stk, decrease);

    return 0;
}

void StackResize (Stack *stk, IncreaseDecreaseMode mode)
{
    if (mode == increase) 
    {
        stk->capacity *= MUL_DIV_COEF; //increase
    }
    else 
    {
        stk->capacity /= MUL_DIV_COEF;                  //decrease
    }

    CanaryPtrMoving (stk);
}

StackErrorCode StackOK (Stack *stk)
{
    if      (stk == NULL)           return error_stack_ptr;
    else if (stk->data == NULL)     return error_array_ptr;
    else if (stk->size <= 0)        return error_stack_size;
    else if (stk->capacity <= 0)    return error_stack_capacity;
    else                            return clear_stack;
}

canary_t GenerateCanary ()
{
    srand(time(NULL));

    canary_t ret_value;

    for (int i = 0; i < sizeof (canary_t); i++)
    {
        ((char*)(&ret_value))[i] = rand () % 256;
    }

    return ret_value;
}

CanaryErrorCode CanaryChecking (Stack *stk)
{
    if      (stk->canary_left   != stk->canary_reference)               return left_stack_canary_dead;
    else if (stk->canary_right  != stk->canary_reference)               return right_stack_canary_dead;
    else if (*(stk->canary_left_arr_ptr)    != stk->canary_reference)   return left_arr_canary_dead;
    else if (*(stk->canary_right_arr_ptr)   != stk->canary_reference)   return right_arr_canary_dead;
    else                                                                return canary_alive;
}

void CreateDataArray (Stack *stk)
{
    int stack_byte_size = 1; //TODO stack byte size
    stk->data = (elem_t *) calloc (1, stk->capacity * sizeof (elem_t) + 2 * sizeof (canary_t));

    stk->canary_left_arr_ptr = (canary_t*) stk->data;
    *(stk->canary_left_arr_ptr) = stk->canary_reference;

    stk->canary_right_arr_ptr = (canary_t*) ((char*) stk->data + sizeof (canary_t) + stk->capacity * sizeof (elem_t));
    *(stk->canary_right_arr_ptr) = stk->canary_reference;

    stk->data = (elem_t*) ((char*) stk->data + sizeof (canary_t));
}

void CanaryPtrMoving (Stack *stk) //TODO rename or 
{
    //TODO stack_byte size
    *(stk->canary_right_arr_ptr) = 0;

    stk->data = (elem_t*) ((char*) stk->data - sizeof (canary_t));
    stk->data = (elem_t*) realloc (stk->data, stk->capacity * sizeof (elem_t) + 2 * sizeof (canary_t));

    stk->canary_left_arr_ptr = (canary_t*) stk->data;
    *(stk->canary_left_arr_ptr) = stk->canary_reference;

    stk->canary_right_arr_ptr = (canary_t*) ((char*) stk->data + sizeof (canary_t) + stk->capacity * sizeof (elem_t));
    *(stk->canary_right_arr_ptr) = stk->canary_reference;
    
    stk->data = (elem_t*) ((char*) stk->data + sizeof (canary_t));
}
