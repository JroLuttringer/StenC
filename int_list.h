#ifndef __INT_LIST_H__
#define __INT_LIST_H__

#include <stdlib.h>

typedef struct int_list {
    struct int_list* next;
    int value;
} int_list;

int_list* new_int_list();
int_list* add_int_lists(int_list* l1, int_list* l2);
int get_int_list_size(int_list*);


#endif

