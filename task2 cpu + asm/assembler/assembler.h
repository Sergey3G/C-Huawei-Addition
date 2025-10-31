#ifndef ASSEMBLER_H
#define ASSEMBLER_H

char* input_to_buffer(const char* input_filename);
size_t count_of_strings(const char* string);
char** create_str_array(char* buffer, size_t str_count);
int my_atoi(const char* str);
int* compile_to_bytecode(char** str_array, size_t count);
void print_bytecode(int* bytecode, char* instruction, size_t count, size_t i);

#endif
