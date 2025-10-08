#include <stdio.h>

#include "stack.h"
#include "ariphmetics.h"

int main()
{
	Stack stack = {};
	construct_stack(&stack, 10);

	pop_stack(&stack);

    stack_dump(&stack);

	destruct_stack(&stack);

	return 0;
}
