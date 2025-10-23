#include <stdio.h>
#include <stdlib.h>

#include "processor.h"

int* read_bytecode(char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        printf("Error: cannot open file %s!\n", filename);
        return NULL;
    }

    size_t size = 0;
    fread(&size, sizeof(int), 1, file);

    rewind(file);

    int* bytecode = (int*)calloc(size + 1, sizeof(int));
    if (!bytecode)
    {
        printf("Error: memory allocation failed!");
        return NULL;
    }

    size_t read_size = fread(bytecode, sizeof(int), size + 1, file);
    if (read_size != size + 1)
    {
        printf("Error: cannot read file content correctly!");
    }

    fclose(file);
    return bytecode;
}

void print_bytecode(int* bytecode, size_t size)
{
    if (!bytecode)
    {
        printf("Error: bytecode is null!\n");
        return;
    }

    printf("\n========= BYTECODE =========\n");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d\n", bytecode[i]);
    }
    printf("============================\n");
}

void construct_processor(Processor* processor, Stack* stack, int* bytecode)
{
    if (!processor)
    {
        printf("Error: processor is null!");
        return;
    }

    if (!stack)
    {
        printf("Error: stack is null!");
        return;
    }

    if (!bytecode)
    {
        printf("Error: bytecode is null!");
        return;
    }

    processor->stack = stack;
    processor->bytecode = bytecode;
    processor->instruction_pointer = 0;
}

void destruct_processor(Processor* processor)
{
    if (processor->stack)
    {
        destruct_stack(processor->stack);
        free(processor->stack);
        processor->stack = NULL;
    }
    if (processor->bytecode)
    {
        free(processor->bytecode);
        processor->bytecode = NULL;
    }
    processor->instruction_pointer = 0;
}

ProcessorErrors verify_processor(const Processor* processor)
{
    ProcessorErrors err = PROC_NO_ERRORS;

    if (!processor)
    {
        err = (ProcessorErrors)(err | PROC_NULL_PTR);
    }

    if (!processor->stack)
    {
        err = (ProcessorErrors)(err | PROC_INVALID_STACK);
    }

    if (!processor->bytecode)
    {
        err = (ProcessorErrors)(err | PROC_INVALID_BYTECODE);
    }

    if (processor->stack && verify_stack(processor->stack) != NO_ERRORS)
    {
        err = (ProcessorErrors)(err | PROC_STACK_ERROR);
    }
}

void processor_dump(const Processor* processor)
{
    printf("\n================ PROCESSOR DUMP ================\n");

    if (!processor)
    {
        printf("Aborted: processor is null!\n");
        printf("\n================================================\n");
        return;
    }

    ProcessorErrors err = verify_processor(processor);

    printf("Processor address: %p\n", (void*)processor);
    printf("Stack address: %p\n", (void*)processor->stack);
    printf("Bytecode address: %p\n", (void*)processor->bytecode);
    printf("Instruction pointer: %ld", processor->instruction_pointer);
    printf("Error flags: %d (", err);

    if (err != PROC_NO_ERRORS)
    {
        printf("Processor corrupted! Attempting stack dump...\n");
        if (processor->stack)
        {
            stack_dump(processor->stack);
        }
        printf("================================================\n\n");
        return;
    }

    printf("\n--- Stack state ---\n");
    stack_dump(processor->stack);

    printf("\n--- Bytecode preview ---\n");
    for (int i = 0; i < max(processor->bytecode[0], 10) && processor->bytecode && processor->bytecode[i] != 0; i++)
    {
        printf("[%02d] = %d\n", i, processor->bytecode[i]);
    }
}
