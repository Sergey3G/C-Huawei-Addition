#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

char* file_to_buffer(const char* filename);
int count_of_strings(const char* string);
struct String* create_str_array(char* buffer);
int bubble_sort(struct String* array, int array_len);
int reverse_bubble_sort(struct String* array, int array_len);
int output_to_file(const char* filename, struct String* lines, int count);
int strcmp_from_end(const char* string_1, const char* string_2);

struct String
{
	char* ptr;
	size_t len;
};

int main(const int argc, const char* const argv[]) // TODO: divide into files
{
    char* buffer = file_to_buffer("onegin_input.txt");
    if (!buffer) 
    {
        return 1;
    }

    int strings_num = count_of_strings(buffer);
    printf("count of strings is %d\n", strings_num);

    struct String* lines = create_str_array(buffer);
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
		else if (strncmp(argv[1], "--reverse", 9) == 0) // TODO: qsort mode 
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
	// TODO: assert
    struct stat st; // TODO: enum error
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

    while ((check = strchr(check, '\n')) != NULL)  // TODO: /n/n/n
    {
        count++;
        check++;
    }

    return count + 1;
}

/*
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
*/

int bubble_sort(struct String* array, int array_len)
{
    for (int i = 0; i < array_len - 1; i++) 
    {
        for (int j = 0; j < array_len - i - 1; j++) 
        {
            if (strcmp(array[j].ptr, array[j + 1].ptr) > 0) 
            {
                struct String tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
    return 0;
}

int reverse_bubble_sort(struct String* array, int array_len) // TODO: size_t
{
    for (int i = 0; i < array_len - 1; i++) 
    {
        for (int j = 0; j < array_len - i - 1; j++) 
        {
            if (strcmp_from_end(array[j].ptr, array[j + 1].ptr) > 0) 
            {
                struct String tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
    return 0;
}

int output_to_file(const char* filename, struct String* lines, int count)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) 
    {
        printf("Error: cannot open file %s\n", filename);
        return 1;
    }

    for (int i = 0; i < count; i++) 
    {
        fprintf(file, "%s\n", lines[i].ptr);
    }

    fclose(file);
    return 0;
}

int strcmp_from_end(const char* string_1, const char* string_2)
{
	int i = strlen(string_1) - 1; // TODO: это будет слишком часто вызываться
	int j = strlen(string_2) - 1;

	for (int i = strlen(string_1) - 1, j = strlen(string_2) - 1; i >= 0 &&
		j >= 0; i--, j--)
	{
		if (string_1[i] != string_2[j])
		{
			return string_1[i] - string_2[j];
		}
	}

	return i - j;
}


struct String* create_str_array(char* buffer) // TODO: omit struct
{
	int str_count = count_of_strings(buffer);
	struct String* array = (struct String*)calloc(str_count, sizeof(struct String));
	
	if (array == NULL)
	{
		printf("Error: memory allocation failed");
	}

	struct String* current = array;
	current->ptr = buffer;
	current->len = strlen(buffer);
	current++;

	char* check = strchr(buffer, '\n');

	while (check != NULL && current < array + str_count)
	{
		*check = '\0';
		current->ptr = check + 1;
		current->len = strlen(current->ptr);
		current++;
		check = strchr(check + 1, '\n'); // TODO: maybe count length of strings in another way
	}

	return array;
}



