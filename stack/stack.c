#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Errors verify_stack(Stack* stack)
{
	Errors errors = NO_ERRORS;
	if (stack->data == NULL)
		errors = (Errors)(errors | DATA_NULL_PTR);
	if (stack->size > stack->capacity)
		errors = (Errors)(errors | SIZE_LT_CAPACITY);
	if (stack->size < 0)
		errors = (Errors)(errors | DATA_NULL_PTR);
	if (stack->data[0] != CANARY || stack->data[stack->capacity + 1] != CANARY)
		errors = (Errors)(errors | DEAD_CANARY);

	if (errors & DATA_NULL_PTR)
		printf("Error: incorrect data pointer!");
	if (errors & SIZE_LT_CAPACITY)
		printf("Error: size is larger than capacity!");
	if (errors & NEGATIVE_SIZE)
		printf("Error: negative size!");
	if (errors & DEAD_CANARY)
		printf("Your stack was attacked, canary defence was defeated!");

	return errors;
}


void stack_dump(Stack* stack)
{
	Errors verify = verify_stack(stack);
	if (verify != NO_ERRORS)
	{
		printf("Stack is corrupted, error code is %d\n", verify);
		if (verify & DEAD_CANARY)
		{
			destruct_stack(stack);
		}
		return;
	}

	for (size_t i = 1; i < stack->capacity; i++)
	{
		if (i < stack->size)
		{
			printf("stack[%ld] = %d is filled\n", i, stack->data[i]);
		}
		else
		{
			printf("stack[%ld] = %d is empty\n", i, stack->data[i]);
		}
	}
}


void construct_stack(Stack* stack, size_t stk_capacity)
{
	stack->data = (data_t*)calloc(stk_capacity + 2, sizeof(data_t));
	stack->capacity = stk_capacity;
	stack->size = 0;
	stack->data[0] = 0xDEADBABE;
	stack->data[stack->capacity + 1] = 0xDEADBABE;
}

void destruct_stack(Stack* stack)
{
	free(stack->data);
	stack->data = NULL;
	stack->size = 0;
	stack->capacity = 0;
}

void push_stack(Stack* stack, data_t value)
{
	stack->data[++stack->size] = value;
}

data_t pop_stack(Stack* stack)
{
	data_t elem = stack->data[stack->size];
	stack->data[stack->size--] = 0;
	return elem;
}
