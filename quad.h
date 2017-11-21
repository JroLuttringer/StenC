#ifndef QD_H
#define QD_H

#include <stdlib.h>
#include "list.h"
enum en_inst {
    addi, soustr, multi, divi 
};

typedef enum en_inst instr;

typedef struct quad {
    instr i;
    symbol* arg1;
    symbol* arg2;
    symbol* result;
    struct quad* next;
} quad;

quad* quad_gen( instr i, symbol* arg1, symbol* arg2, symbol* result; );

void quad_add(quad** head, quad* el);

#endif 
