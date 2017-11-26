#ifndef QD_H
#define QD_H

#include <stdlib.h>
#include "list.h"
enum op {
    Q_ADD, Q_SUB, Q_MULT, Q_DIV, Q_ASSIGN, Q_PRINTI
};

typedef enum op op;
typedef struct quad quad;
typedef struct quad {
    op i;
    symbol* arg1;
    symbol* arg2;
    symbol* result;
    struct quad* next;
} quad;

quad* quad_gen(op , symbol* , symbol* , symbol* );

void quad_add(quad**, quad*);
quad* concat_quad(quad*,quad*);
void print_quads(quad* head);



#endif 
