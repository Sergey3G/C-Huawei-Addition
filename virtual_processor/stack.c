#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Errors verify_stack(Stack* stack)
{
	Errors errors = NO_ERRORS;
	if (!stack)
	{
		printf("verify_stack aborted: stack pointer is NULL!");
		errors = (Errors)(errors | DATA_NULL_PTR);
	}
	if (stack->data == NULL)
	{
		errors = (Errors)(errors | DATA_NULL_PTR);
	}
	if (stack->size > stack->capacity)
	{
		errors = (Errors)(errors | SIZE_LT_CAPACITY);
	}
	if ((int)stack->size < 0)
	{
		errors = (Errors)(errors | NEGATIVE_SIZE);
	}
	if (stack->data)
	{
		if (stack->data[0] != CANARY || stack->data[stack->capacity + 1] != CANARY)
		{
			errors = (Errors)(errors | DEAD_CANARY);
		}
	}
	return errors;
}


void stack_dump(Stack* stack)
{
	printf("\n================ STACK DUMP ================\n");

	if (!stack)
	{
		printf("Aborted: stack is null!");
		printf("============================================\n\n");
		return;
	}

	Errors err = verify_stack(stack);

	printf("Stack address: %p\n", (void*)stack);
	printf("Data pointer: %p\n", (void*)stack->data);
	printf("Size: %zu\n", stack->size);
	printf("Capacity: %zu\n", stack->capacity);
	printf("Error flags: %d (", err);

	if (err = NO_ERRORS)
	{
		printf("NO_ERRORS");
	}
	else
	{
		if (err & DATA_NULL_PTR) printf("DATA_NULL_PTR");
		if (err & SIZE_LT_CAPACITY) printf("SIZE_LT_CAPACITY");
		if (err & NEGATIVE_SIZE) printf("NEGATIVE_SIZE");
		if (err & DEAD_CANARY) printf("DEAD CANARY");
	}
	printf(")\n");

	if (err != NO_ERRORS)
	{
		printf("Stack is corrupted! Dump aborted.\n");
		printf("============================================\n\n");
		return;
	}

	printf("\n--- Memory formation ---\n");
	printf("[Left canary] = 0x%X\n", stack->data[0]);

	for (size_t i = 1; i <= stack->capacity; i++)
	{
		if (i <= stack->size)
		{
			printf(" * [%02zu] = %d (used)\n", i, stack->data[i]);
		}
		else
		{
			printf("   [%02zu] = %d (free)\n", i, stack->data[i]);
		}
	}

	printf("[Right canary] = 0x%X\n", stack->data[stack->capacity + 1]);
	printf("============================================\n\n");
}


void construct_stack(Stack* stack, size_t stk_capacity)
{
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
		return -0xDEDDED;
	}

	if (stack->size < 1)
	{
		printf("Stack is empty!\n");
		return -0xDEDDED;
	}
	data_t elem = stack->data[stack->size]; // TODO: пока сильно зависит от размеров
	stack->data[stack->size--] = 0;
	return elem;
}
