#include <stdio.h>

#include "lists.h"

void construct_list(List* list, size_t capacity)
{
    if (!list)
    {
        printf("list is null!");
        return;
    }

    data_t* data = (data_t)calloc(capacity + 1, sizeof data_t);
    if (!data)
    {
        printf("Error: memory allocation failed!\n");
        return;
    }
    data[0] = CANARY;

    size_t* next = (size_t)calloc(capacity, sizeof size_t);
    if (!next)
    {
        printf("Error: memory allocation failed!\n");
        return;
    }
    for (size_t i = 1; i < capacity; i++)
    {
        next[i] = i + 1;
    }

    size_t* prev = (size_t)calloc(capacity, sizeof size_t);
    if (!prev)
    {
        printf("Error: memory allocation failed!\n");
        return;
    }
    for (size_t i = 1; i < capacity; i++)
    {
        prev[i] = i - 1;
    }

    list->data = data;
    list->next = next;
    list->prev = prev;
}

void destruct_list(List* list)
{
    free(list->data);
    free(list->next);
    free(list->prev);
}

ListErrors verify_list(List* list)
{
    ListErrors err = NO_ERRORS;
    if (!list->data) err = (ListErrors)(err | DATA_NULL_PTR);
    if (!list->next) err = (ListErrors)(err | NEXT_NULL_PTR);
    if (!list->prev) err = (ListErrors)(err | PREV_NULL_PTR);
    if ()
    return;
}

