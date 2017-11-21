#include "list_quad.h"

list_quad* new_list(quad* q){
    list_quad* lq = malloc(sizeof(list_quad));
    lq -> q = q;
    lq -> next = NULL;
    return lq;
}

void concat(list_quad** l1, list_quad* l2){
    if(*l1  == NULL){
        *l1 = l2;
        return;
    }
    if(l2 == NULL){
        return;
    }
    list_quad* tmp = *l1;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp -> next = l2;
}


void complete(list_quad* lq, symbol* nextquad){
    if(lq == NULL) return;
    list_quad* tmp = lq;
    while(tmp != NULL){
        tmp -> q -> result = nextquad;
        tmp = tmp -> next;
    }
}
