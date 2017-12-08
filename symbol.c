#include "symbol.h"
static int nb ;

symbol* new_temp(symbol** head){
    symbol* s = (symbol*)malloc(sizeof(symbol));
    s->type=CONSTANT;
    s->is_constant=false;
    s->value = 0; 
    s->name = (char*)malloc(NAME_LENGTH);
    snprintf(s->name, NAME_LENGTH, "__temp_%d", nb++); 
    s->next = NULL;


    symbol* tmp = *head;
    if(tmp == NULL) *head = s;
    else {
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = s;
    }
    return s;
}

symbol* new_array(symbol** head, char* id, int taille_dim){
    symbol* s = (symbol*)malloc(sizeof(symbol));
    s->is_constant=false;
    s->type = ARRAY;
    s->name = (char*)malloc(NAME_LENGTH);
    snprintf(s->name, NAME_LENGTH, id, nb++); 
    s->next = NULL;
    s->array.nb_dim = 1;
    s->array.dim_list = new_int_list();
    s->array.dim_list = add_int_to_list(s->array.dim_list,taille_dim);

    symbol* tmp = *head;
    if(tmp == NULL) *head = s;
    else {
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = s;
    }

    return s;
}

symbol* update_array(symbol* array_to_update, int new_dim_size){
    int_list* tmp = array_to_update->array.dim_list;
    while(tmp != NULL){
        tmp->value *= new_dim_size;
        tmp = tmp->next;
    }
    array_to_update->array.dim_list = add_int_to_list(array_to_update->array.dim_list,new_dim_size);
    array_to_update->array.nb_dim++;
    return array_to_update;
}



symbol* new_integer(symbol** head, int value){
    symbol* s = (symbol*)malloc(sizeof(symbol));
    s->type = VARIABLE;
    s->is_constant=true;
    s->value = value;
    s->name = (char*)malloc(NAME_LENGTH);
    if(value >=0)
        snprintf(s->name, NAME_LENGTH, "__const_%d", value); 
    else
        snprintf(s->name, NAME_LENGTH, "__negconst_%d", value*-1); 
  
    s->next = NULL;
    symbol* tmp = *head;
    if(tmp == NULL) *head = s;
    else {
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = s;
    }
    return s;
}



symbol* new_label(symbol** head){
    symbol* s = (symbol*)malloc(sizeof(symbol));
    s->is_constant=false;
    s->value = 0;
    s->type = LABEL;
    s->name = (char*)malloc(NAME_LENGTH);
    snprintf(s->name, NAME_LENGTH, "__label_%d", nb++);
    s->next = NULL;
    symbol* tmp = *head;
    if(tmp == NULL) *head = s;
    else {
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = s;
    }
    return s;
}

symbol* new_string(symbol** head, char* val){
    printf("creating new string %s\n", val);
    symbol* s = (symbol*)malloc(sizeof(symbol));
    s->is_constant=false;
    s->type = STRING_TYPE;
    int l = strlen(val);
    s->string = (char*)malloc(l);
    strncpy(s->string, val, l);
    s->name = (char*)malloc(NAME_LENGTH);
    snprintf(s->name, NAME_LENGTH, "__string_%d", nb++);
    s->next = NULL;
    symbol* tmp = *head;
    if(tmp == NULL) *head = s;
    else {
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = s;
    }
    printf("created new string %s\n", s->string);
    return s;
}




symbol* lookup(symbol* head, char* name){
    symbol* tmp = head;
    while(tmp != NULL && strcmp(tmp->name, name)){
            tmp = tmp -> next;   
    }
    return tmp;
}



symbol* add(symbol** head, char* name){
    symbol* new_s = malloc(sizeof(symbol));
    new_s->is_constant = false;
    new_s->name = name;
    new_s->next = NULL; 
    symbol* tmp = *head;
    if(tmp == NULL) *head = new_s;
    else {
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = new_s;
    }
    return new_s;
}



void print_symbol(symbol* head){
  symbol* tmp = head;
  while(tmp != NULL ){
    if (strstr(tmp->name, "__string")) 
    printf("%s\t\t%s\t\t(isconstant : %d)\n", tmp->name, tmp->string, tmp->is_constant);
        else
    printf("%s\t\t%d\t\t(isconstant : %d)\n", tmp->name, tmp->value, tmp->is_constant);
    tmp = tmp->next;
  }
  printf("\n");
}


