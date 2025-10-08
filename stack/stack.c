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
		errors = (Errors)(errors | NEGATIVE_SIZE);
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

	for (size_t i = 1; i <= stack->capacity; i++)
	{
		if (i <= stack->size)
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
{ // TODO: проверять, что ne null
	if (!stack)
	{
		printf("Stack is null!");
		return;
	}
	stack->data = (data_t*)calloc(stk_capacity + 2, sizeof(data_t));
	if (!stack->data)
	{
		printf("Error: memory allocation failed!\n");
		return;
	}
	stack->capacity = stk_capacity;
	stack->size = 0;
	stack->data[0] = CANARY;
	stack->data[stack->capacity + 1] = CANARY;
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
	if (!stack)
	{
		printf("Stack is null!");
		return;
	}
	if (stack->size >= stack->capacity)
	{
		size_t old_capacity = stack->capacity;
		stack->capacity *= 2;

		stack->data = (data_t*)realloc(stack->data, (stack->capacity + 2) * sizeof(data_t));
		if (!stack->data)
		{
			printf("Error: memory allocation failed!");
			return;
		}

		for (size_t i = old_capacity + 2; i < stack->capacity + 2; i++)
		{
			stack->data[i] = 0;
		} // fill_stack (form, to, element)

		stack->data[stack->capacity + 1] = CANARY;
	}
	stack->data[++stack->size] = value;
}

data_t pop_stack(Stack* stack)
{
	if (!stack)
	{
		printf("Stack is null!\n");
		return -0xDEADBABE;
	}

	if (stack->size < 1)
	{
		printf("Stack is empty!\n");
		return -0xDEADBABE;
	}
	data_t elem = stack->data[stack->size]; // TODO: пока сильно зависит от размеров
	stack->data[stack->size--] = 0;
	return elem;
}
