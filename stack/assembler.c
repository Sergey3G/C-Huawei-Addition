#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* input_to_buffer(const char* input_filename);
size_t count_of_strings(const char* string);
char** create_str_array(char* buffer, size_t str_count);
// int output_to_file(const char* filename, char** str_array, int count);
char** turn_into_byte(char** str_array, size_t count, size_t* bytecode_size);
int my_atoi(const char* str);
char* int_to_string(int number);
int bytecode_output(const char* filename, char** bytecode, size_t count);
void free_bytecode(char** bytecode, size_t size);

int main()
{
    char* buffer = input_to_buffer("instructions.txt");
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
    size_t bytecode_size = 0;
    char** bytecode = turn_into_byte(str_array, strings_count, &bytecode_size);
    if (!bytecode)
    {
        free_bytecode(bytecode, bytecode_size);
        return 1;
    }
    bytecode_output("byte_code.txt", bytecode, bytecode_size);
    free_bytecode(bytecode, bytecode_size);
    free(str_array);
    free(buffer);

    return 0;
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

/*
int output_to_file(const char* filename, char** str_array, int count)
{
    FILE* file = fopen(filename, "w");
    if (!file)
    {
        printf("Error: cannot open file %s\n", filename);
        return 1;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s\n", str_array[i]);
    }

    fclose(file);
    return 0;
}
*/

char** turn_into_byte(char** str_array, size_t count, size_t* bytecode_size)
{
    char** bytecode = (char**)calloc(count * 2, sizeof(char*));
    if (!bytecode)
    {
        printf("Error: memory allocation failed!");
        return NULL;
    }

    size_t bytecode_index = 0;

    for (size_t i = 0; i < count; i++)
    {
        char* instruction = str_array[i];

        if (!instruction || strlen(instruction) == 0)
        {
            continue;
        }

        while (isspace(*instruction))
        {
            instruction++;
        }

        if (strncmp(instruction, "PUSH", 4) == 0)
        {
            bytecode[bytecode_index++] = strdup("1");

            int number = my_atoi(instruction + 4);
            char* arg_str = int_to_string(number);
            if (arg_str)
            {
                bytecode[bytecode_index++] = arg_str;
            }
        }
        else if (strcmp(instruction, "ADD") == 0)
        {
            bytecode[bytecode_index++] = strdup("2");
        }
        else if (strcmp(instruction, "SUB") == 0)
        {
            bytecode[bytecode_index++] = strdup("3");
        }
        else if (strcmp(instruction, "SUB") == 0)
        {
            bytecode[bytecode_index++] = strdup("4");
        }
        else if (strcmp(instruction, "MUL") == 0)
        {
            bytecode[bytecode_index++] = strdup("5");
        }
        else if (strcmp(instruction, "DIV") == 0)
        {
            bytecode[bytecode_index++] = strdup("6");
        }
        else if (strcmp(instruction, "SQRT") == 0)
        {
            bytecode[bytecode_index++] = strdup("7");
        }
        else if (strcmp(instruction, "OUT") == 0)
        {
            bytecode[bytecode_index++] = strdup("8");
        }
        else if (strcmp(instruction, "HLT") == 0)
        {
            bytecode[bytecode_index++] = strdup("0");
        }
    }
    *bytecode_size = bytecode_index;
    return bytecode;
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

int bytecode_output(const char* filename, char** bytecode, size_t count)
{
    FILE* file = fopen(filename, "w");
    if (!file)
    {
        printf("Error: memory allocation failed!");
        return 1;
    }

    for (size_t i = 0; i < count; i++)
    {
        fprintf(file, "%s\n", bytecode[i]);
    }
    return 0;
}

void free_bytecode(char** bytecode, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        free(bytecode[i]);
    }
    free(bytecode);
}
