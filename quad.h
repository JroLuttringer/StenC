#ifndef QD_H
#define QD_H

#include <stdlib.h>
#include "list.h"


enum op {
    Q_ADD, Q_SUB, Q_MULT, Q_DIV, Q_ASSIGN, Q_PRINTI,
    Q_OR, Q_AND, Q_LT, Q_GT, Q_LE, Q_GE, Q_EQ, Q_NE, Q_NOT,
    Q_GOTO, Q_LABEL, Q_PRINTF, Q_RETURN
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
