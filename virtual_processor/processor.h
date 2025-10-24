#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "stack.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct Processor
{
    Stack* stack;
    int* bytecode;
    size_t instruction_pointer;
    // massive of registers
    // RAM pushm [34]
} Processor;

typedef enum ProcessorErrors
{
    PROC_NO_ERRORS = 0,
    PROC_NULL_PTR = 1,
    PROC_INVALID_STACK = 2,
    PROC_INVALID_BYTECODE = 4,
    PROC_STACK_ERROR = 8
} ProcessorErrors;

int* read_bytecode(char* filename);
void print_bytecode(int* bytecode, size_t size);
void construct_processor(Processor* processor, Stack* stack, int* bytecode);
void destruct_processor(Processor* processor);
ProcessorErrors verify_processor(const Processor* processor);
void processor_dump(const Processor* processor);

#endif
