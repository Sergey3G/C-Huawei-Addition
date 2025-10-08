#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* input_to_buffer(const char* input_filename);
size_t count_of_strings(const char* string);
char** create_str_array(char* buffer, size_t str_count);
int my_atoi(const char* str);
char* int_to_string(int number);
int compile_to_bytecode(char** str_array, size_t count, const char* filename);

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
    compile_to_bytecode(str_array, strings_count, "byte_code.txt");

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

int compile_to_bytecode(char** str_array, size_t count, const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (!file)
    {
        printf("Error: cannot read file %s!\n", filename);
        return 1;
    }

    int error_flag = 0;

    for (size_t i = 0; i < count; i++)
    {
        char* instruction = str_array[i];
        if (!instruction || !*instruction)
        {
            continue;
        }

        while (isspace(*instruction))
        {
            instruction++;
        }

        if (strncmp(instruction, "PUSH", 4) == 0)
        {
            fprintf(file, "1\n");

            int number = my_atoi(instruction + 4);
            fprintf(file, "%d\n", number);
        }
        else if (strcmp(instruction, "ADD") == 0)
        {
            fprintf(file, "2\n");
        }
        else if (strcmp(instruction, "SUB") == 0)
        {
            fprintf(file, "3\n");
        }
        else if (strcmp(instruction, "SUB") == 0)
        {
            fprintf(file, "4\n");
        }
        else if (strcmp(instruction, "MUL") == 0)
        {
            fprintf(file, "5\n");
        }
        else if (strcmp(instruction, "DIV") == 0)
        {
            fprintf(file, "6\n");
        }
        else if (strcmp(instruction, "SQRT") == 0)
        {
            fprintf(file, "7\n");
        }
        else if (strcmp(instruction, "OUT") == 0)
        {
            fprintf(file, "8\n");
        }
        else if (strcmp(instruction, "HLT") == 0)
        {
            fprintf(file, "0");
        }
        else
        {
            printf("You have grammatic error on line %lu!\n", i + 1);
            error_flag = 1;
            break;
        }
    }

    fclose(file);

    if (error_flag == 1)
    {
        file = fopen(filename, "w");
        if (!file)
        {
            printf("Error: cannot clear %s content!\n", filename);
            return 1;
        }
        fclose(file);
        return 1;
    }
    return 0;
}
