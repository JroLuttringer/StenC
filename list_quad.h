#ifndef LQ_H
#define LQ_H

#include "quad.h"

typedef struct list_quad{
    quad* q;
    struct list_quad* next;
} list_quad ;


list_quad* new_list(quad*);
void concat(list_quad** , list_quad*);
void complete(list_quad* , symbol*);

#endif 
