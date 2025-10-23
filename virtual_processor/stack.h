#ifndef STACK_H
#define STACK_H

#define CANARY 0xDEDDED

typedef int data_t;

typedef struct Stack
{
	data_t* data;
	size_t size;
	size_t capacity;
} Stack;

typedef enum Errors
{
	NO_ERRORS = 0,
	SIZE_LT_CAPACITY = 1,
	DATA_NULL_PTR = 2,
	NEGATIVE_SIZE = 4,
	DEAD_CANARY = 8
} Errors;

void construct_stack(Stack* stack, size_t stk_capacity);
void destruct_stack(Stack* stack);
void push_stack(Stack* stack, data_t value);
data_t pop_stack(Stack* stack);
Errors verify_stack(Stack* stack);
void stack_dump(Stack* stack);

#endif
