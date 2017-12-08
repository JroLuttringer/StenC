#include "int_list.h"

int_list* new_int_list(){
    int_list* n = malloc(sizeof(int_list));
    n->next = NULL;
    n->value = 0;
    return n;
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
