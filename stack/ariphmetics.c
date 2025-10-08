#include <stdio.h>
#include <math.h>

#include "ariphmetics.h"

Errors stack_add(Stack* stack)
{
    push_stack(stack, pop_stack(stack) + pop_stack(stack));
}

Errors stack_sub(Stack* stack)
{
    push_stack(stack, pop_stack(stack) - pop_stack(stack));
}

Errors stack_mul(Stack* stack)
{
    push_stack(stack, pop_stack(stack) * pop_stack(stack));
}

Errors stack_div(Stack* stack)
{
    push_stack(stack, pop_stack(stack) / pop_stack(stack));
}
/*
Errors stack_sqrt(Stack* stack)
{
    push_stack(stack, sqrt(pop_stack(stack)));
}
*/
