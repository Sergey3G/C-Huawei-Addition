#ifndef LISTS_H
#define LISTS_H

#include "listerrors.h"

#define CANARY 0xDEDDED

typedef int data_t;

typedef struct List
{
   data_t* data;
   size_t* next;
   size_t* prev;
   size_t head;
   size_t tail;
} List;

void construct_list(List* list, size_t capacity);
void destruct_list(List* list);
ListErrors verify_list(List* list);
// void list_insert(List* list, data_t elem);
// void list_remove(List* list, size_t pos);

#endif
