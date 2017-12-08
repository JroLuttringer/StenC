#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "int_list.h"

#define NAME_LENGTH 43

enum type_enum{
    LABEL, CONSTANT, STRING_TYPE, ARRAY, VARIABLE 
};
typedef enum type_enum type_enum;

typedef struct array {
    int nb_dim;
    int_list* dim_list;
} array_struct;

struct symbol {
    type_enum type;  
    bool is_constant;
    char* name;
    union {
    	int value;
        char* string;
        array_struct array;
    };
    struct symbol* next;
};
typedef struct symbol symbol;
symbol* new_label(symbol** );
symbol* new_string(symbol** , char*);
symbol* new_temp(symbol**);
symbol* new_array(symbol**,char*,int);
symbol* update_array(symbol* array_to_update, int new_dim_size);
symbol* new_integer(symbol** , int );
symbol* lookup(symbol*, char*);
void print_symbol(symbol*);
symbol* add(symbol**, char* );
#endif
