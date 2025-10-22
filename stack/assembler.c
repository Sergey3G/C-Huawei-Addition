#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

    size_t instruction_counter = 0;
    int* bytecode = compile_to_bytecode(str_array, strings_count, &instruction_counter);
    if (!bytecode)
    {
        for (size_t i = 0; i < strings_count; i++)
        {
            free(str_array[i]);
        }
        free(str_array);
        return 1;
    }

    for (size_t i = 0; i < strings_count - 1; i++)
    {
        printf("instructions[%ld]: %s\n", i + 1, str_array[i]);
    }
    printf("-----------------------------\n");
    for (size_t i = 0; i < instruction_counter; i++)
    {
        printf("bytecode[%ld] = %d\n", i, bytecode[i]);
    }

    FILE* output_file = fopen("byte_code.bin", "wb");
    if (!output_file)
    {
        printf("Error: cannot open file byte_code.bin!");
        return 1;
    }

    size_t wrote_count = fwrite(bytecode, sizeof(int), instruction_counter, output_file);
    if (wrote_count != instruction_counter)
    {
        printf("Error: cannot correctly read file content!");
        return 1;
    }
}

char* input_to_buffer(const char* input_filename)
{
    struct stat st;
    if (stat(input_filename, &st) != 0)
    {
        perror("stat failed!");
        return NULL;
    }

    size_t file_size = (size_t)st.st_size;
    FILE* input_file = fopen(input_filename, "r");
    if (!input_file)
    {
        printf("Error: cannot open file: %s!\n", input_filename);
        return NULL;
    }

    char* buffer = (char*)calloc(file_size + 1, sizeof(char));
    if (!buffer)
    {
        printf("Error: memory allocation failed!");
        fclose(input_file);
        return NULL;
    }

    size_t read_size = fread(buffer, sizeof(char), file_size, input_file);
    fclose(input_file);
    if (read_size != file_size)
    {
        printf("Error: cannot read file content!\n");
        free(buffer);
        return NULL;
    }
    buffer[file_size] = '\0';
    return buffer;
}

size_t count_of_strings(const char* string)
{
    if (!string)
    {
        printf("Error: string is nullptr!");
        return 0;
    }
    size_t count = 0;
    const char* check = string;

    while ((check = strchr(check, '\n')) != NULL)
    {
        count++;
        check++;
    }

    return count + 1;
}

char** create_str_array(char* buffer, size_t str_count)
{
    char** array = (char**)calloc(str_count, sizeof(char*));

    if (!array)
    {
        printf("Error: memory allocation failed!");
        return NULL;
    }

    char** current = array;
    *current++ = buffer;
    char* check = strchr(buffer, '\n');

    while (check != NULL && current < array + str_count)
    {
        *check = '\0';
        *current = check + 1;
        current++;
        check = strchr(check + 1, '\n');
    }

    return array;
}

int my_atoi(const char* str)
{
	int result = 0, sign = 1;

    while (*str == ' ' || *str == '\t')
    {
        str++;
    }

	if (*str == '+')
	{
		str++;
	}
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}

	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}

	return sign * result;
}

char* int_to_string(int number)
{
    size_t len = (size_t)snprintf(NULL, 0, "%d", number);
    char* str = (char*)malloc(len + 1);

    if (str)
    {
        snprintf(str, len + 1, "%d", number);
    }
    return str;
}

int* compile_to_bytecode(char** str_array, size_t count, size_t* instruction_counter)
{
    int* bytecode = (int*)calloc(count * 2, sizeof(int));
    if (!bytecode)
    {
        printf("Error: memory allocation failed!");
        return NULL;
    }

    int* start_bytecode = bytecode;

    for (size_t i = 0; i < count; i++)
    {
        if (strncmp(str_array[i], "PUSH", 4) == 0)
        {
            char* start_instruction = str_array[i];
            *start_bytecode = PUSH;
            start_instruction += 4;
            start_bytecode++;

            *start_bytecode = my_atoi(start_instruction);
            start_bytecode++;
            print_bytecode(bytecode, start_instruction, count, i);
            *instruction_counter += 2;
        }
        else if (strcmp(str_array[i], "ADD") == 0)
        {
            *start_bytecode = ADD;
            start_bytecode++;
            print_bytecode(bytecode, str_array[i], count, i);
            *instruction_counter += 1;
        }
        else if (strcmp(str_array[i], "SUB") == 0)
        {
            *start_bytecode = SUB;
            start_bytecode++;
            print_bytecode(bytecode, str_array[i], count, i);
            *instruction_counter += 1;
        }
        else if (strcmp(str_array[i], "MUL") == 0)
        {
            *start_bytecode = MUL;
            start_bytecode++;
            print_bytecode(bytecode, str_array[i], count, i);
            *instruction_counter += 1;
        }
        else if (strcmp(str_array[i], "DIV") == 0)
        {
            *start_bytecode = DIV;
            start_bytecode++;
            print_bytecode(bytecode, str_array[i], count, i);
            *instruction_counter += 1;
        }
        else if (strcmp(str_array[i], "SQRT") == 0)
        {
            *start_bytecode = SQRT;
            start_bytecode++;
            print_bytecode(bytecode, str_array[i], count, i);
            *instruction_counter += 1;
        }
        else if (strcmp(str_array[i], "OUT") == 0)
        {
            *start_bytecode = OUT;
            start_bytecode++;
            print_bytecode(bytecode, str_array[i], count, i);
            *instruction_counter += 1;
        }
        else if (strcmp(str_array[i], "HLT") == 0)
        {
            *start_bytecode = HLT;
            start_bytecode++;
            print_bytecode(bytecode, str_array[i], count, i);
            *instruction_counter += 1;
        }
    }

    return bytecode;
}

void print_bytecode(int* bytecode, char* instruction, size_t count, size_t i)
{
    printf("Read instruction number %ld: %s\n", i + 1, instruction);
    printf("-----------------------------\n");
    for (size_t j = 0; j < 2 * count; j++)
    {
        printf("bytecode[%ld] = %d\n", j, bytecode[j]);
    }
    printf("-----------------------------\n");
    return;
}

