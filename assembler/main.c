#include <stdio.h>
#include <stdlib.h>

#include "assembler.h"

int main()
{
    char* buffer = input_to_buffer("instructions.asm");
    if (!buffer)
    {
        return 1;
    }

    size_t strings_count = count_of_strings(buffer);
    char** str_array = create_str_array(buffer, strings_count);
    if (!str_array)
    {
        free(buffer);
        return 1;
    }

    int* bytecode = compile_to_bytecode(str_array, strings_count);
    if (!bytecode)
    {
        free(str_array);
        return 1;
    }

    for (size_t i = 0; i < strings_count - 1; i++)
    {
        printf("instructions[%ld]: %s\n", i + 1, str_array[i]);
    }
    printf("------------------------------\n");
    for (size_t i = 0; i < (size_t)bytecode[0] + 1; i++)
    {
        printf("bytecode[%ld] = %d\n", i, bytecode[i]);
    }

    FILE* output_file = fopen("../virtual_processor/byte_code.bin", "wb");
    if (!output_file)
    {
        printf("Error: cannot open file byte_code.bin!");
        return 1;
    }

    size_t wrote_count = fwrite(bytecode, sizeof(int), (size_t)bytecode[0] + 1, output_file);
    if (wrote_count != (size_t)bytecode[0] + 1)
    {
        printf("Error: cannot correctly write into file!");
        return 1;
    }

    fclose(output_file);
    free(buffer);
    free(str_array);
    free(bytecode);

    return 0;
}
