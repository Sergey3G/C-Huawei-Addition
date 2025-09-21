#include <stdio.h>

size_t my_strlen(const char* str);
int my_puts(const char* str);
const char* my_strchr(const char* str, int ch);
char* my_strcat(char* destination, const char* source);
char* my_strncat(char* destination, const char* source, size_t n);
int my_atoi(const char* str);
char* my_fgets(char* str, unsigned int count, FILE* source);
ssize_t getline(char** lineptr, int* n, FILE* stream);

int main()
{
    char some_str[100] = "Hello, World!";
    const char* str_to_add = " Welcome to the great world of C language!";
    size_t len = my_strlen(some_str);
    printf("string length is %lu\n", len);
    my_puts(some_str);
    const char* el_num = my_strchr(some_str, 'o');
    if (el_num != NULL)
    {
        printf("first 'o' is at position %ld\n", el_num - some_str);
    }
    else
    {
        printf("character 'o' not found\n");
    }
    char* strcat_str = my_strcat(some_str, str_to_add);
    printf("strcat string is %s\n", strcat_str);

    char another_str[100] = "Hello again!";
    char* strncat_str = my_strncat(another_str, str_to_add, 7);
    printf("strncat string is %s\n", strncat_str);

    char str_for_atoi[50] = "-01213aevgajv35";
    printf("atoi function result is %d\n", my_atoi(str_for_atoi));

    char str_for_fgets[8] = " ";
    FILE* tmpf = tmpfile();
    fputs("Alan Turing", tmpf);
    fputs("Edgar Allan Poe", tmpf);
    fputs("Leo Tolstoy", tmpf);
    while (my_fgets(str_for_fgets, sizeof(str_for_fgets), tmpf) != NULL)
    {
		printf("\"%s\"", str_for_fgets);
    }

    if (feof(tmpf))
    {
		puts("End of file reached");
	}

    
    return 0;
}

size_t my_strlen(const char* str)
{
    size_t i = 0;
    for (i = 0; str[i] != '\0'; i++)
        ;
    return i;
}

int my_puts(const char* str)
{
    if (str == NULL)
    {
        return EOF;
    }
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (putchar(str[i]) == EOF) 
        {
			return EOF;
		}
    }
    if (putchar('\n') == EOF)
    {
    	return EOF;	
    }
    return 1;
}

const char* my_strchr(const char* str, int ch)
{
    if (str == NULL)
	{
    	return NULL;
    }	
    while (*str != '\0')
    {
		++str;
    	if (*str == ch)
    	{
    		return &(*str);
    	}
    }
    return NULL;
}

char* my_strcat(char* destination, const char* source)
{
    if (destination == NULL || source == NULL) 
	{
    	return destination;
    }
    char* end_of_destination = destination;
    while (*end_of_destination != '\0')
    {
        end_of_destination++;
    }
    while (*source != '\0')
    {
        *end_of_destination++ = *source++;
    }
    *end_of_destination = '\0';
    return destination;
}

char* my_strncat(char* destination, const char* source, size_t n)
{
    if (destination == NULL || source == NULL)
        return destination;

    char* dest_start = destination;

    while (*destination != '\0')
    {
        destination++;
    }

    size_t i = 0;
    while (i < n && *source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
        i++;
    }

    *destination = '\0';

    return dest_start;
}

int my_atoi(const char* str)
{
	int result = 0, sign = 1;

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

char* my_fgets(char* str, unsigned int count, FILE* stream)
{
	if (str == NULL || count < 1 || stream == NULL)
	{
		return NULL;
	}

	int ch = 0;
	size_t i = 0;

	while (i < count - 1)
	{
		ch = fgetc(stream);
		if (ch == EOF)
		{
			if (i == 0)
			{
				return NULL;
			}
			break;
		}
		str[i++] = (char)ch;
		if (ch == '\n')
		{
			break;
		}
	}

	str[i] = '\0';
	return str;	
}

/*
ssize_t getline(char** lineptr, size_t* n, FILE* stream)
{

	if (!lineptr || !n || !stream)
	{
		return -1;
	}

	const size_t start_size = 128;
	if (!(*lineptr) || *n == 0)
	{
		*lineptr = calloc(start_size, sizeof(char));
		if (!(*lineptr))
		{
			return -1;
		}
		*n = 128;
	}

	int c = 0;
	size_t pos = 0;

	while ((c = fgetc(stream)) != EOF)
	{
		if (pos + 1 >= *n)
		{
			size_t new_size = *n * 2;
			char* new_ptr = realloc(*lineptr, new_size);
			if (new_ptr = NULL)
			{
				return -1;
			}
			*lineptr = new_ptr;
			*n = new_size;
			//TODO: make till the end
		}

		if (c == '\n')
		{
			break;
		}
		
	}

	if (pos == 0 && c == EOF)
	{
		return -1;
	}

	(*lineptr)[pos] = '\0';
	return (ssize_t)pos;
}
*/
