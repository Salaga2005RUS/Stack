#include <stdio.h>

#include "stack.h"

int main ()
{
    Stack stack {};
    elem_t x = 0;
    StackInit(&stack, CAPACITY_0);

    for (int i = 0; i < 20; i++)
    {
        StackPush(&stack, 5*i); // TODO Rename iteration variable
        printf ("Stack element - %d, Stack Size - %d, Stack Capacity - %d\n\n", stack.data[stack.size - 1], stack.size, stack.capacity);
    } // TODO Make dump function with use of __FILE__, __LINE__, PRETTY_FUNCTION

    for (int i = 20; i > 1; i--)
    {
        StackPop(&stack, &x);
        // printf ("Stack element - %d, Stack Size - %d, Stack Capacity - %d\n\n", stack.data[stack.size - 1], stack.size, stack.capacity);
        printf ("[%d] %d/%d\n", stack.data[stack.size - 1], stack.size, stack.capacity);
        // printf ("Empty Stack");
    }

    StackDestroy(&stack);

    return 0;
}