#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

struct Stack
{
	data_t* data;
	size_t size;
	size_t capacity;
};

enum Errors
{
	NO_ERRORS = 0,
	SIZE_LT_CAPACITY = 1,
	DATA_NULL_PTR = 2,
	NEGATIVE_SIZE = 4
};

void construct_stack(Stack* stack, size_t stk_capacity);
void destruct_stack(Stack* stack);
void push_stack(Stack* stack, data_t value);
data_t pop_stack(Stack* stack);
Errors verify_stack(Stack* stack);
void stack_dump(Stack* stack);

int main()
{
	Stack stack = {};
	construct_stack(&stack, 10);

	for (size_t i = 0; i < 6; i++)
	{
		push_stack(&stack, i + 1);
	}

	stack_dump(&stack);

	return 0;
}


Errors verify_stack(Stack* stack)
{
	Errors errors = NO_ERRORS;
	if (stack->data == NULL) errors = (Errors)(errors | DATA_NULL_PTR);
	if (stack->size > stack->capacity) errors = (Errors)(errors | SIZE_LT_CAPACITY);
	if (stack->size < 0) errors = (Errors)(errors | DATA_NULL_PTR);

	if (errors & DATA_NULL_PTR) printf("Error: incorrect data pointer");
	if (errors & SIZE_LT_CAPACITY) printf("Error: size is larger than capacity");
	if (errors & NEGATIVE_SIZE) printf("Error: negative size");

	return errors;
}


void stack_dump(Stack* stack)
{
	Errors verify = verify_stack(stack);
	if (verify != NO_ERRORS)
	{
		printf("Stack is corrupted, error code is %d\n", verify);
		return;
	}

	for (size_t i = 0; i < stack->capacity; i++)
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
	stack->data = (data_t*)calloc(stk_capacity + 1, sizeof(data_t));
	stack->capacity = stk_capacity;
	stack->size = 0;
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
	stack->data[stack->size++] = value;
}

data_t pop_stack(Stack* stack)
{
	data_t elem = stack->data[stack->size - 1];
	stack->data[stack->size - 1] = 0;
	return elem;
}
