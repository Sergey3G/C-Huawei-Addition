#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct Processor
{
    Stack* stack;
    int* bytecode;
    size_t instruction_pointer;
    // massive of registers
    // RAM pushm [34]
} Processor;

int* read_bytecode(char* filename);

#endif
