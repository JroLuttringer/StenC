#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NAME_LENGTH 43

struct symbol {
    bool is_constant;
    char* name;
    int value;
    struct symbol* next;
};
typedef struct symbol symbol;

symbol* new_temp(symbol** , int);
symbol* lookup(symbol*, char*);
void print_symbol(symbol*);
symbol* add(symbol** head, char* name);
#endif
