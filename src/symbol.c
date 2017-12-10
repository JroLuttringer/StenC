#include "../include/symbol.h"
static int nb ;


void free_symbol(symbol* s){
    symbol* tmp;
    while (s != NULL){
        tmp = s;
        s = s->next;
        if(tmp){
            if(tmp->name)free(tmp->name);
            if(tmp->type == STRING_TYPE) free(tmp->string);
            if(tmp->type == ARRAY || tmp->type == STENCIL) free_int_list(tmp->array.dim_list);
            if((tmp->type == ARRAY || tmp->type == STENCIL))
            {
               if (tmp->array.init_list != NULL)  free_int_list(tmp->array.init_list);
            }
            free(tmp);
        }
    }
}


symbol* new_temp(symbol** head){
    symbol* s = (symbol*)malloc(sizeof(symbol));
    CHECK(s != NULL);

    s->type=CONSTANT;
    s->is_constant=false;
    s->value = 0; 
    s->name = (char*)malloc(NAME_LENGTH);
    CHECK(s->name != NULL);

    snprintf(s->name, NAME_LENGTH, "@@temp_%d", nb++); 
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
    CHECK(s != NULL);

    s->is_constant=false;
    s->type = ARRAY;
    s->name = (char*)malloc(NAME_LENGTH);
    CHECK(s->name != NULL);

    snprintf(s->name, NAME_LENGTH, id, nb++); 
    s->next = NULL;
    s->array.size = taille_dim;
    s->array.nb_dim = 1;
   // printf("taille dim : %d\n", taille_dim);
    s->array.dim_list = new_int_list(taille_dim);
    s->array.init_list = NULL;

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


symbol* new_stencil(symbol** head, char* id, int taille_dim){
    symbol* s = (symbol*)malloc(sizeof(symbol));
    CHECK(s != NULL);

    s->is_constant=false;
    s->type = STENCIL;
    s->name = (char*)malloc(NAME_LENGTH);
    CHECK(s->name);

    snprintf(s->name, NAME_LENGTH, id, nb++); 
    s->next = NULL;
    s->array.size = taille_dim;
    s->array.nb_dim = 1;
    s->array.dim_list = new_int_list(taille_dim);
    s->array.init_list = NULL;

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
    // int_list* tmp = array_to_update->array.dim_list;
   // printf("taille dim : %d\n", new_dim_size);
    array_to_update->array.size *= new_dim_size;
    // while(tmp != NULL){
    //     tmp->value *= new_dim_size;
    //     tmp = tmp->next;
    // }
    array_to_update->array.dim_list = add_int_to_list(array_to_update->array.dim_list,new_dim_size);
    array_to_update->array.nb_dim++;
    return array_to_update;
}



symbol* new_integer(symbol** head, int value){
    symbol* s = (symbol*)malloc(sizeof(symbol));
    CHECK(s);

    s->type = CONSTANT;
    s->is_constant=true;
    s->value = value;
    s->name = (char*)malloc(NAME_LENGTH);
    CHECK(s->name);

    if(value >=0)
        snprintf(s->name, NAME_LENGTH, "@@const_%d", value); 
    else
        snprintf(s->name, NAME_LENGTH, "@@negconst_%d", value*-1); 
  
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

symbol* new_define(symbol** head, char* name, int value){
    symbol* s = (symbol*)malloc(sizeof(symbol));
    CHECK(s);

    s->type = DEFINE_TYPE;
    s->is_constant=true;
    s->value = value;
    s->name = (char*)malloc(NAME_LENGTH);
    CHECK(s->name);

    snprintf(s->name, NAME_LENGTH, name, nb++); 
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
    CHECK(s);
    s->is_constant=false;
    s->value = 0;
    s->type = LABEL;
    s->name = (char*)malloc(NAME_LENGTH);
    CHECK(s->name);
    snprintf(s->name, NAME_LENGTH, "@@label_%d", nb++);
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
   // printf("creating new string %s\n", val);
    symbol* s = (symbol*)malloc(sizeof(symbol));
    CHECK(s);
    s->is_constant=false;
    s->type = STRING_TYPE;
    int l = strlen(val)+1;
    s->string = (char*)malloc(l);
    CHECK(s->string);
    strncpy(s->string, val, l);
    s->name = (char*)malloc(NAME_LENGTH);
    CHECK(s->name);
    snprintf(s->name, NAME_LENGTH, "@@string_%d", nb++);
    s->next = NULL;
    symbol* tmp = *head;
    if(tmp == NULL) *head = s;
    else {
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = s;
    }
  ///  printf("created new string %s\n", s->string);
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
    CHECK(new_s);
    new_s->type = VARIABLE;
    new_s->is_constant = false;
    new_s->name = name;
    new_s->next = NULL; 
    new_s->value = 0;
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
    if (strstr(tmp->name, "@@string")) 
    printf("%s\t\t%s\t\t(isconstant : %d)\n", tmp->name, tmp->string, tmp->is_constant);
        else
    printf("%s\t\t%d\t\t(isconstant : %d)\n", tmp->name, tmp->value, tmp->is_constant);
    tmp = tmp->next;
  }
  printf("\n");
}


sym_list* new_sym_list(symbol* s){
    sym_list* n = malloc(sizeof(sym_list));
    CHECK(n);
    n->next = NULL;
    n->sym = s;
    return n;
}

sym_list* concat_sym_list(sym_list* l1, sym_list* l2){
    if(!l1) return l2;
    if(!l2) return l1;
    sym_list* tmp = l1;
    CHECK(tmp);
    while(tmp->next)  tmp = tmp->next;
    tmp->next = l2;
    return l1;
}

symbol* get_nth_sym(int sym_nb, sym_list* l) {
   // printf("getting %d sym\n", sym_nb);
    int i;
    for (  i = 0; i < sym_nb && l!=NULL; i++) l = l->next;
   // printf("getting %d sym %d i\n", sym_nb, i);
  //  printf("got it ! \n");
   // if(!(l)) printf("But it's null :/\n");
    if(!l || i<sym_nb-1) {printf("Error in array declaration/access\n"); exit(-1);}
    return l->sym;
}

void free_sym_list(sym_list* sl){
    if(!sl) return;
    sym_list* tmp = sl;
    while(sl){
        tmp = sl;
        sl = sl->next;
      //  if(tmp->q)free_quad(tmp->q);
        free(tmp);
    }
}