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
    union {
    	int value;
    	char* string;
    };
    //int value;
    struct symbol* next;
};
typedef struct symbol symbol;
symbol* new_label(symbol** );
symbol* new_string(symbol** , char*);
symbol* new_temp(symbol**);
symbol* new_integer(symbol** , int );
symbol* lookup(symbol*, char*);
void print_symbol(symbol*);
symbol* add(symbol**, char* );
#endif
