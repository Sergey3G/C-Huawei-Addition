#include <stdio.h>

#include "processor.h"
#include "stack.h"

int* read_bytecode(char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        printf("Error: cannot open file %s!\n", filename);
        return NULL;
    }

    size_t size = 0;
    size_t read_size = fread();

    int* bytecode = (int*)calloc();
}
