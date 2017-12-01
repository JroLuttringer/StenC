#ifndef LQ_H
#define LQ_H

#include "quad.h"
  
typedef struct quad_list{
    quad* q;
    struct quad_list* next;
}quad_list ;


quad_list* new_list(quad*);
quad_list* add_quad_list (quad_list*, quad*);
quad_list* concat_quad_list(quad_list* , quad_list*);
void complete_quad_list(quad_list* , symbol*);
void print_quad_list(quad_list*);

#endif 
