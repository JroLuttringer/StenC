#ifndef __INT_LIST_H__
#define __INT_LIST_H__

#include <stdlib.h>

typedef struct int_list {
    struct int_list* next;
    int value;
} int_list;


int_list* new_int_list(int );
int_list* add_int_lists(int_list* l1, int_list* l2);
int get_int_list_size(int_list*);
int get_nth_dim(int, int_list*);
int_list* add_int_to_list(int_list* l, int n);
int_list* concat_int_list(int_list*, int_list*);
void free_int_list(int_list*);

#endif

