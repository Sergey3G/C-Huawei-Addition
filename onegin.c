#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

char* file_to_buffer(const char* filename);
int count_of_strings(const char* string);
char** create_ptr_array(char* buffer);
int bubble_sort(char** array, int array_len);
int reverse_bubble_sort(char** array, int array_len);
int output_to_file(const char* filename, char** lines, int count);
int strcmp_from_end(const char* string_1, const char* string_2);

struct String
{
	char* ptr;
	int len;
};

int main(const int argc, char** const argv)
{
    char* buffer = file_to_buffer("onegin_input.txt");
    if (!buffer) 
    {
        return 1;
    }

    int strings_num = count_of_strings(buffer);
    printf("count of strings is %d\n", strings_num);

    char** lines = create_ptr_array(buffer);
    if (!lines) 
    {
        free(buffer);
        return 1;
    }

	if (argc > 1)
	{
		if (strncmp(argv[1], "--direct", 8) == 0)
		{
			bubble_sort(lines, strings_num);
		}
		else if (strncmp(argv[1], "--reverse", 9) == 0)
		{
			reverse_bubble_sort(lines, strings_num);
		}	
	}
    
    output_to_file("onegin_output.txt", lines, strings_num);

    free(lines);
    free(buffer);

    return 0;
}

char* file_to_buffer(const char* filename)
{
    struct stat st;
    if (stat(filename, &st) != 0) 
    {
        perror("stat failed");
        return NULL;
    }

    size_t file_size = st.st_size;
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("Error: cannot open file %s\n", filename);
        return NULL;
    }

    char* buffer = (char*)calloc(file_size + 1, sizeof(char));
    if (buffer == NULL) 
    {
        printf("Error: memory allocation failed!\n");
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(buffer, sizeof(char), file_size, file);
    fclose(file);
    if (read_size != file_size) 
    {
        printf("Error: cannot read file content!\n");
        free(buffer);
        return NULL;
    }

    buffer[file_size] = '\0';
    return buffer;			
}

int count_of_strings(const char* string)
{
    int count = 0;
    const char* check = string;

    while ((check = strchr(check, '\n')) != NULL) 
    {
        count++;
        check++;
    }

    return count + 1;
}

char** create_ptr_array(char* buffer)
{
    int str_count = count_of_strings(buffer);
    char** array = (char**)calloc(str_count, sizeof(char*));

    if (array == NULL) 
    {
        printf("Error: memory allocation failed\n");
        return NULL;
    }

    char** current = array;
    *current++ = buffer;
    char* check = strchr(buffer, '\n');

    while (check != NULL && current < array + str_count) 
    {
        *check = '\0';               
        *current++ = check + 1;
        check = strchr(check + 1, '\n');
    }

    return array;
}

int bubble_sort(char** array, int array_len)
{
    for (int i = 0; i < array_len - 1; i++) 
    {
        for (int j = 0; j < array_len - i - 1; j++) 
        {
            if (strcmp(array[j], array[j + 1]) > 0) 
            {
                char* tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
    return 0;
}

int reverse_bubble_sort(char** array, int array_len)
{
    for (int i = 0; i < array_len - 1; i++) 
    {
        for (int j = 0; j < array_len - i - 1; j++) 
        {
            if (strcmp_from_end(array[j], array[j + 1]) > 0) 
            {
                char* tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
    return 0;
}

int output_to_file(const char* filename, char** lines, int count)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: cannot open file %s\n", filename);
        return 1;
    }

    for (int i = 0; i < count; i++) 
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);
    return 0;
}

int strcmp_from_end(const char* string_1, const char* string_2)
{
	int i = strlen(string_1) - 1;
	int j = strlen(string_2) - 1;

	while (i >= 0 && j >= 0)
	{
		if (string_1[i] != string_2[j])
		{
			return (unsigned char)string_1[i] - (unsigned char)string_2[j];
		}
		i--;
		j--;
	}

	return (i - j);
}



