#include "int_list.h"

int_list* new_int_list(int k){
    int_list* n = malloc(sizeof(int_list));
    n->next = NULL;
    n->value = k;
    return n;
}

void free_int_list(int_list* l){
    int_list* tmp;
    while (l != NULL)
    {
        tmp = l;
        l = l->next;
        free(tmp);
    }
}

int_list* add_int_lists(int_list* l1, int_list* l2)	{
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;
    
    int_list* tmp = l1;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = l2;
    return l1;

}

int_list* add_int_to_list(int_list* l, int n){
    int_list* new = malloc(sizeof(int_list));
    new->value = n;
    new->next = NULL;
    if(l == NULL) return new;
    int_list* tmp = l;
    while(tmp->next)  tmp = tmp ->next;
    tmp->next = new;
    return l;
}

int_list* concat_int_list(int_list* l1, int_list* l2){

    while(l1->next)  l1 = l1->next;
    l1->next = l2;
    return l1;
}

int get_nth_dim(int dim, int_list* l) {
    for ( int i = 1; i < dim; i++) l = l->next;
    return l->value;
}

int get_int_list_size(int_list* l){
    int size = 0;
    int_list* tmp = l;
    while(tmp != NULL)
	{
        size++;
        tmp = tmp->next;
    }
    return size;
}
