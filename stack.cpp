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

    MakeHash (stk);

    StackValidator(stk);

    return 0;
}

int StackDestroy (Stack *stk)
{
    StackValidator(stk);

    stk->size       = 0;
    stk->capacity   = 0;

    stk->data = (elem_t*) ((char*) stk->data - sizeof (canary_t));
    free (stk->data);   

    return 0;
}

int StackPush (Stack *stk, elem_t value)
{
    StackValidator (stk);

    if (stk->size == stk->capacity) StackResize (stk, increase);

    stk->data[stk->size] = value;
    stk->size++;

    MakeHash (stk);

    return 0;
}

int StackPop (Stack *stk, elem_t *ret_value)
{
    StackValidator (stk);

    assert (ret_value != NULL);

    if (stk->size == 0) return 0; //TODO return value is same for good and bad situation

    *ret_value = stk->data[stk->size];
    stk->data[stk->size] = 0;
    stk->size--;

    if (stk->capacity >= 2 * MUL_DIV_COEF * stk->size) StackResize (stk, decrease);

    MakeHash (stk);

    return 0;
}

void StackResize (Stack *stk, IncreaseDecreaseMode mode)
{
    if (mode == increase) 
    {
        stk->capacity *= MUL_DIV_COEF;                  //increase
    }
    else 
    {
        stk->capacity /= MUL_DIV_COEF;                  //decrease
    }
    
    CanaryPtrMoving (stk);
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

void CanaryPtrMoving (Stack *stk)
{
    *(stk->canary_right_arr_ptr) = 0;

    stk->data = (elem_t*) ((char*) stk->data - sizeof (canary_t));
    stk->data = (elem_t*) realloc (stk->data, stk->capacity * sizeof (elem_t) + 2 * sizeof (canary_t));

    stk->canary_left_arr_ptr = (canary_t*) stk->data;
    *(stk->canary_left_arr_ptr) = stk->canary_reference;

    stk->canary_right_arr_ptr = (canary_t*) ((char*) stk->data + sizeof (canary_t) + stk->capacity * sizeof (elem_t));
    *(stk->canary_right_arr_ptr) = stk->canary_reference;
    
    stk->data = (elem_t*) ((char*) stk->data + sizeof (canary_t));
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


unsigned int HashFAQ6 (const char* str, int size)
{

    unsigned int hash = 0;

    for (; size > 0; str++)
    {
        hash += (unsigned char)(*str);
        hash += (hash << 10);
        hash ^= (hash >> 6);

        size--;
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    
    return hash;
}

unsigned int HashOfStack (Stack *stk)
{
    char* h_stk_ptr = (char*) stk;
    return HashFAQ6(h_stk_ptr, sizeof (*(stk)));
}

unsigned int HashOfData (Stack *stk)
{
    char* h_data_ptr = (char*) ((canary_t*) stk->data - 1);
    return HashFAQ6(h_data_ptr, stk->capacity * sizeof (elem_t) + 2 * sizeof (canary_t));
}

void MakeHash (Stack *stk)
{
   stk->hash_stk    = HashOfStack (stk);
   stk->hash_data   = HashOfData (stk);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int StackValidator (Stack *stk)
{
    int magic_error_number = 0;

    if (stk == NULL)                                               magic_error_number += error_stack_ptr;
    if (stk->data == NULL)                                         magic_error_number += error_array_ptr;
    if (stk->size <= 0)                                            magic_error_number += error_stack_size;
    if (stk->capacity <= 0)                                        magic_error_number += error_stack_capacity;

    if (stk->hash_stk  != HashOfStack (stk) && 
       (stk->hash_data != HashOfData (stk)))                       magic_error_number += hash_error_stack_data;
    if (stk->hash_stk  != HashOfStack (stk))                       magic_error_number += hash_error_stack;
    if (stk->hash_data != HashOfData (stk))                        magic_error_number += hash_error_data;

    if (stk->canary_left   != stk->canary_reference)               magic_error_number += left_stack_canary_dead;
    if (stk->canary_right  != stk->canary_reference)               magic_error_number += right_stack_canary_dead;
    if (*(stk->canary_left_arr_ptr)    != stk->canary_reference)   magic_error_number += left_arr_canary_dead;
    if (*(stk->canary_right_arr_ptr)   != stk->canary_reference)   magic_error_number += right_arr_canary_dead;

    printf ("//////////////////////////\n"
            "Stack validation code: %d\n"
            "//////////////////////////\n", magic_error_number);

    return magic_error_number;
}
