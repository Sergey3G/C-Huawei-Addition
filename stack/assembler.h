#ifndef ASSEMBLER_H
#define ASSEMBLER_H


enum Instructions
{
    PUSH = 1,
    ADD = 2,
    SUB = 3,
    MUL = 4,
    DIV = 5,
    SQRT = 6,
    OUT = 7,
    HLT = 0
};

char* input_to_buffer(const char* input_filename);
size_t count_of_strings(const char* string);
char** create_str_array(char* buffer, size_t str_count);
int my_atoi(const char* str);
char* int_to_string(int number);
int* compile_to_bytecode(char** str_array, size_t count, size_t* instruction_counter);
void print_bytecode(int* bytecode, char* instruction, size_t count, size_t i);

#endif
