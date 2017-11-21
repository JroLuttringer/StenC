#include "quad.h"

quad* quad_gen(instr i, symbol* arg1, symbol* arg2, symbol* result ){
    quad* new_q = (quad*) malloc(sizeof(quad));
    new_q->i = i;
    new_q->arg1 = arg1; 
    new_q->arg2 = arg2;
    new_q->result = result;
    new_q->next = NULL;
    return new_q;
}


void quad_add(quad** head, quad* el) {
    if (*head == NULL){
        *head = el;
        return ;
    }
    quad* tmp = *head;
    while(tmp ->next != NULL){
        tmp = tmp -> next;
    }
    tmp->next = el;
    return;

}

