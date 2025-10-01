#include <stdio.h>

#include "stack.h"
#include "ariphmetics.h"

int main()
{
	Stack stack = {};
	construct_stack(&stack, 10);

	for (size_t i = 0; i < stack.capacity; i++)
	{
		push_stack(&stack, i);
		printf("Iteration number: %ld:\n", i);
		stack_dump(&stack);
	}

	return 0;
}
