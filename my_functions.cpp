#include <stdio.h>

size_t my_strlen(const char* str);
int my_puts(const char* str);
const char* my_strchr(const char* str, int ch);
char* my_strcat(char* destination, const char* source);
char* my_strncat(char* destination, const char* source, size_t n);

int main()
{
    char some_str[100] = "Hello, World!";
    const char* str_to_add = " Welcome to the great world of C language!";
    size_t len = my_strlen(some_str);
    printf("string length is %u\n", len);
    my_puts(some_str);
    const char* el_num = my_strchr(some_str, 'o');
    if (el_num != NULL)
    {
        printf("first 'o' is at position %d\n", el_num - some_str);
    }
    else
    {
        printf("character 'o' not found\n");
    }
    char* strcat_str = my_strcat(some_str, str_to_add);
    printf("strcat string is %s\n", strcat_str);

    // Для демонстрации my_strncat создадим новый буфер
    char another_str[100] = "Hello again!";
    char* strncat_str = my_strncat(another_str, str_to_add, 7);
    printf("strncat string is %s\n", strncat_str);

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
        if (putchar(str[i]) == EOF) return EOF; // Добавлена проверка ошибок вывода
    }
    if (putchar('\n') == EOF) return EOF;
    return 1;
}

const char* my_strchr(const char* str, int ch)
{
    if (str == NULL) return NULL;
    for (size_t i = 0; ; ++i)
    {
        if (str[i] == ch)
            return &str[i];
        if (str[i] == '\0') break; // Прерываем цикл при достижении конца строки
    }
    return NULL;
}

char* my_strcat(char* destination, const char* source)
{
    if (destination == NULL || source == NULL) return destination; // Проверка на NULL
    char* end_of_destination = destination;
    while (*end_of_destination != '\0')
    {
        end_of_destination++;
    }
    while (*source != '\0')
    {
        *end_of_destination++ = *source++; // Более компактная запись
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

}

