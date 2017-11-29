#include "quad_list.h"

quad_list* new_list(quad* q){
    quad_list* lq = malloc(sizeof(quad_list));
    lq -> q = q;
    lq -> next = NULL;
    return lq;
}

quad_list* add_quad_list(quad_list* ql, quad* q){
    quad_list* new_ql = malloc(sizeof(quad_list));
    new_ql->q = q;
    new_ql->next = NULL;
    if(!ql){
        return new_ql;
    }

    quad_list* tmp = ql;
    while(tmp -> next != NULL){
        tmp=tmp->next;
    }
    tmp->next = new_ql;
    return ql;
}


quad_list* concat_quad_list(quad_list* l1, quad_list* l2){
    if(l1  == NULL){
        return l2;
    }
    if(l2 == NULL){
        return l1;
    }

    quad_list* tmp = l1;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp -> next = l2;
    return l1;
}


quad_list* complete_quad_list(quad_list* lq, symbol* nextquad){
    if(lq == NULL) return lq;
    quad_list* tmp = lq;
    while(tmp != NULL){
        tmp -> q -> result = nextquad;
        tmp = tmp -> next;
    }
    return lq;
}

void print_quad_list(quad_list* ql){
    if(ql == NULL){
        return;
    }


}

