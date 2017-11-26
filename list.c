#include "list.h"

symbol* new_temp(symbol** head){
    static int nb ;
    symbol* s = (symbol*)malloc(sizeof(symbol));
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


symbol* new_integer(symbol** head, int value){
    symbol* s = (symbol*)malloc(sizeof(symbol));
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
    printf("%s\t\t%d\t\t(isconstant : %d)\n", tmp->name, tmp->value, tmp->is_constant);
    tmp = tmp->next;
  }
  printf("\n");
}


