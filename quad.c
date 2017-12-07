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
        switch(tmp->i){
            case Q_GOTO :
                printf("GOTO\t\t");
            break;

            case Q_LABEL:
                printf("PUT_LABEL:\t");
            break;

            case Q_ADD  :
                printf("ADD\t\t");
            break;

            case Q_SUB  :
                printf("SUB\t\t");
            break;

            case Q_MULT  :
                printf("MULT\t\t");
            break;

            case Q_DIV  :
                printf("DIV\t\t");
            break;

            case Q_ASSIGN :
                printf("ASSIGN\t\t");
            break;

            case Q_PRINTI :
                printf("PRINTI\t\t");
            break;
            case Q_PRINTF :
                printf("PRINTF\t\t");
            break;

            case Q_AND :
                printf("&&\t\t");            
            break;

            case Q_OR :
                printf("||\t\t");
            break;

            case Q_LT : 
                printf("<\t\t");           
            break;

            case Q_GT: 
                printf(">\t\t");            
            break;

            case Q_LE : 
                printf("<=\t\t");            
            break;

            case Q_GE : 
                printf(">=\t\t");            
            break;

            case Q_EQ : 
                printf("==\t\t");            
            break;

            case Q_NE : 
                printf("!=\t\t");            
            break;

            case Q_NOT :
                printf("!\t\t");            
            break;
            case Q_RETURN:
                printf("RETURN\t\t");
            break;
        }

        if(!tmp->arg1){
            printf("%10s\t\t", "NULL");
        } else {
            if(tmp->arg1->is_constant){
                printf("%10d\t\t", tmp->arg1->value);
            } else {
                printf("%10s\t\t", tmp->arg1->name);
            }
        }
        if(!tmp->arg2){
            printf("%10s\t\t", "NULL");
        } else {
            if(tmp->arg2->is_constant){
                printf("%10d\t\t", tmp->arg2->value);
            } else {
                printf("%10s\t", tmp->arg2->name);
            }
        }
        if(!tmp->result){
            printf("%10s\t\t", "NULL");
        } else {
            if(tmp->result->is_constant){
                printf("%10d\t\t", tmp->result->value);
            } else {
            printf("%10s\t", tmp->result->name);
            }
        }
        printf("\n");
        tmp = tmp->next;
    }
}


