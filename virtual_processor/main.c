#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "ariphmetics.h"
#include "processor.h"

int main()
{
	int* bytecode = read_bytecode("byte_code.bin");
	if (!bytecode)
	{
		return 1;
	}
	print_bytecode(bytecode, bytecode[0] + 1);
	free(bytecode);
	return 0;
}
