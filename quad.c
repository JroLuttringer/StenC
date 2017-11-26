#include "quad.h"

quad* quad_gen(op i, symbol* arg1, symbol* arg2, symbol* result ){
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

quad* concat_quad(quad* q1, quad* q2){
    if(!q1) return q2; 
    if(!q2) return q1;

    quad* tmp = NULL;
    tmp = q1;
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = q2;
    return q1;
}

void print_quads(quad* head){
    quad* tmp = head;
    if( tmp == NULL) return;
    while(tmp){

        if(tmp->i == Q_ADD) {
            printf("ADD\t\t");
        } 
        if(tmp->i == Q_SUB) {
            printf("SUB\t\t");
        } 
        if(tmp->i == Q_MULT) {
            printf("MULT\t\t");
        } 
        if(tmp->i == Q_DIV) {
            printf("DIV\t\t");
        } 
        if(tmp->i == Q_ASSIGN){
            printf("ASSIGN\t\t");
        }
        if(tmp->i == Q_PRINTI){
            printf("PRINTI");
        }
        if(tmp->arg1 == NULL){
            printf("\t\t%s",tmp->result->name);
            tmp = tmp -> next;
            continue;
        }
        if(tmp -> arg1 -> is_constant){
            printf("%d\t\t", tmp->arg1->value);
        } else {
            printf("%s\t\t", tmp -> arg1-> name);
        } 
        if(tmp -> arg2 != NULL ){       
            if(tmp -> arg2 -> is_constant){
                printf("%d\t\t", tmp->arg2->value);
            } else {
                printf("%s\t\t", tmp -> arg2-> name);
            }
        } else {printf("\t\t");}
        if(tmp -> result -> is_constant){
            printf("%d\t\t", tmp->result->value);
        } else {
            printf("%s\t\t", tmp -> result-> name);
        }

        printf("\n");
        tmp = tmp->next;
    }
}

