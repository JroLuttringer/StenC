%{
  #include "include/symbol.h"
  #include "include/quad_list.h"
  #include "include/genmips.h"
  #include "include/quad.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  void yyerror( char*);
  void print_error(char*, char*);
  int yylex();
  extern FILE* yyin;
  extern int yylex_destroy(void);  

  symbol* tds = NULL;
  quad* whole_code = NULL;

  #define ERR_LENGTH 64
  #define DEBUG 1
  extern int yylineno; 

%}
%locations

%token ID DEFINE INT_TYPE STENCIL_TYPE VOID_TYPE COMMENT INTEGER PRINTI PRINTF STRING MAIN RETURN ASSIGN
%token IF ELSE WHILE DO FOR INCR DECR LOG_AND LOG_OR LOG_EQ GE LE NE GT LT NOT L
%left ',' 
%left LOG_OR
%left LOG_AND
%left LOG_EQ NE
%left GE LE GT LT
%left '+' '-'
%left '*' '/'
%right NEG NOT
%left INCR DECR 

%nonassoc IFX
%nonassoc ELSE

%union{
  char* string;
  int value;
  symbol* symbol;
  struct {
    symbol* result;
    quad* code;
  } expr;
  struct {
    symbol* offset;
    symbol* base;
    quad* code;
    int nb_dim;
  } array_access;
  struct {
    quad* code;
    int_list* list;
    int size;
  } init_list;
  struct {
    quad_list* truelist;
    quad_list* falselist;
    quad* code;
  } cond;
  struct {
    quad* code;
    symbol* sym;
    quad_list* next;
  } statement;

}

%type <symbol> ARRAY_DECLARATION
%type <string> ID STRING
%type <value> INTEGER
%type <expr> expression variable define define_list
%type <init_list> init_array inside_array
%type <array_access> array 
%type <cond> boolean_expression
%type <statement> statement statement_list program s assignement declaration COMMENT 
%%
s: 
  define_list program 
    {
      if(DEBUG) printf("Match ! \n\n");
      $$.code = NULL;
      $$.code = concat_quad($$.code, $2.code);
      whole_code = $$.code;
      return 0;
    }
  ;

define_list: 
  define define_list
    {
      //$$.code = concat_quad($1.code, $2.code);
    }
  | {}
    {
      //$$.code = NULL;
    }
  ;

define: 
  DEFINE ID INTEGER
    {
      new_define(&tds, $2, $3);
      /*
      symbol* s;
      symbol* res = new_integer(&tds, $3);

      if((s=lookup(tds, $2)) == NULL){
       if(DEBUG) printf("defining %s\n", $2);
        s=add(&tds, $2);
      } else {
        print_error("Rededefining of %s\n", $2);
        free($2);
        return 0;
      }
      quad* q = quad_gen(Q_ASSIGN, res, NULL, s);

      $$.code = NULL;
      $$.code = concat_quad($$.code, q);
      */
    }
  |DEFINE ID '-' INTEGER
    {  
      new_define(&tds, $2, -$4);
      /*    

      symbol* s;
      symbol* res = new_integer(&tds, -$4);

      if((s=lookup(tds, $2)) == NULL){
       if(DEBUG) printf("defining %s\n", $2);
        s=add(&tds, $2);
      } else {
        print_error("Rededefining of %s\n", $2);
        free($2);
        return 0;
      }
      quad* q = quad_gen(Q_ASSIGN, res, NULL, s);

      $$.code = NULL;
      $$.code = concat_quad($$.code, q);
      */
    }
  ;

program: 
  INT_TYPE MAIN '(' ')' '{' statement_list RETURN expression ';' '}'
    {
      $$.code = NULL;
      $$.code = concat_quad($$.code, $6.code);
      quad* ret = quad_gen(Q_RETURN, NULL,NULL, $8.result);
      $$.code = concat_quad($$.code, $8.code);
      $$.code = concat_quad($$.code, ret);

    }
  ;

statement_list: 
  statement_list  statement  
    { 
      if(DEBUG) printf("concat du statement \n");
      $$.next = $2.next;
      //complete_quad_list($1.next, $2);
      $$.code = NULL;
      //quad *q = quad_gen(Q_LABEL, NULL, NULL, $2);
      $$.code = concat_quad($$.code, $1.code);
      //$$.code = concat_quad($$.code, q);
      $$.code = concat_quad($$.code, $2.code);
    }
  | {}
    {
      $$.code = NULL;
    }
  ;

statement: 
  assignement ';' 
    {
      $$.code = NULL;
      $$.code = concat_quad($$.code, $1.code);
    }
  | declaration ';' 
    {
      $$.code = NULL;
      $$.code = $1.code;
    }
  | expression ';'  
    {
      $$.code = NULL;
      $$.code = concat_quad($$.code, $1.code);
    } 
  | COMMENT
    {
      $$.code = NULL;
    }
  | PRINTI '(' expression ')' ';'
    {
      $$.code = NULL;
      quad* q = quad_gen(Q_PRINTI, NULL, NULL, $3.result);
      $$.code = concat_quad($$.code, $3.code);
      $$.code = concat_quad($$.code, q); 
    }
  | PRINTF '(' STRING ')' ';' 
    {
      $$.code = NULL;
      symbol* s = new_string(&tds, $3);
      free($3);
      quad* q = quad_gen(Q_PRINTF,NULL, NULL, s);
      $$.code = concat_quad($$.code, q);    
    }   
  | boolean_expression ';' 
    {
      $$.code = $1.code;
    }
  | IF '('boolean_expression')' '{'statement_list'}' %prec IFX
    {
      symbol* true_goto= new_label(&tds);
      symbol* false_goto= new_label(&tds);
      quad* true_label = quad_gen(Q_LABEL, NULL, NULL, true_goto);
      quad* false_label = quad_gen(Q_LABEL, NULL, NULL,false_goto);
      complete_quad_list($3.truelist, true_goto);
      complete_quad_list($3.falselist, false_goto);
      $$.code = concat_quad( $3.code, true_label);
      $$.code = concat_quad( $$.code, $6.code);
      $$.code = concat_quad( $$.code, false_label);
      free_quad_list($3.truelist);
      free_quad_list($3.falselist);

    }
  | IF '('boolean_expression')' '{'statement_list'}' ELSE '{'statement_list'}' 
    {
      symbol* true_goto= new_label(&tds);
      symbol* false_goto= new_label(&tds);
      symbol* next_goto = new_label(&tds);
      complete_quad_list($3.truelist, true_goto);
      complete_quad_list($3.falselist, false_goto);
      quad* true_label = quad_gen(Q_LABEL, NULL, NULL, true_goto);
      quad* false_label = quad_gen(Q_LABEL, NULL, NULL, false_goto);
      quad* next_label=quad_gen(Q_LABEL, NULL, NULL, next_goto);
      quad* goto_next = quad_gen(Q_GOTO, NULL, NULL, next_goto );

      $$.code = concat_quad( $3.code, true_label); // goto true
      $$.code = concat_quad( $$.code, $6.code); // true code
      $$.code = concat_quad( $$.code, goto_next); // skip else
      $$.code = concat_quad( $$.code, false_label); // goto else
      $$.code = concat_quad( $$.code, $10.code); // else code
      $$.code = concat_quad( $$.code, next_label); // skip label

      free_quad_list($3.truelist);
      free_quad_list($3.falselist);

    }
   
  | WHILE '(' boolean_expression ')' '{'statement_list'}' {
      symbol* while_goto = new_label(&tds);
    	symbol* true_goto  = new_label(&tds); // pour sauter le false goto
      symbol* false_goto = new_label(&tds);
      quad* true_label = quad_gen(Q_LABEL, NULL, NULL, true_goto);
      quad* false_label = quad_gen(Q_LABEL, NULL, NULL, false_goto);
      quad* while_label=quad_gen(Q_LABEL, NULL, NULL, while_goto);
      quad* goto_while = quad_gen(Q_GOTO, NULL, NULL, while_goto);
      complete_quad_list($3.truelist, true_goto);
      complete_quad_list($3.falselist, false_goto);
      $$.code = NULL;
      $$.code = concat_quad(while_label, $3.code);
      //label while
      //boolean expression qui va a true_label ou false_label
      $$.code = concat_quad($$.code, true_label);
      //label statement list
      $$.code = concat_quad($$.code, $6.code);
      //goto while_goto
      $$.code = concat_quad($$.code, goto_while);
      //label next
			$$.code = concat_quad($$.code, false_label);   
      free_quad_list($3.truelist);
      free_quad_list($3.falselist);
  }

  | FOR '('assignement';' boolean_expression ';' expression ')' '{'statement_list'}' {
      symbol* instr_for = new_label(&tds);
      symbol* skip_for = new_label(&tds);
      symbol* begin_for = new_label(&tds);
      complete_quad_list($5.truelist, instr_for); // bool true -> instruction du for
      complete_quad_list($5.falselist, skip_for); // bool false -> sortie du for
      quad* goto_begin_for = quad_gen(Q_GOTO, NULL,NULL, begin_for);
      quad* label_begin_for = quad_gen(Q_LABEL, NULL,NULL, begin_for);
      quad* label_skip_for = quad_gen(Q_LABEL, NULL,NULL, skip_for);
      quad* label_instr = quad_gen(Q_LABEL, NULL,NULL, instr_for);
      
      
      $$.code = NULL;
      $$.code = concat_quad($$.code, $3.code); // assignement for
      $$.code = concat_quad($$.code, label_begin_for); // repere avant éval du booléen
    	$$.code = concat_quad($$.code, $5.code); // éval du booleen
      $$.code = concat_quad($$.code, label_instr);
      $$.code = concat_quad($$.code, $10.code); // instructions
      $$.code = concat_quad($$.code, $7.code); // expression
      $$.code = concat_quad($$.code, goto_begin_for); // ré évaluer booleen
      $$.code = concat_quad($$.code, label_skip_for);  // sortir du for
      free_quad_list($5.truelist);
      free_quad_list($5.falselist);
  }
  | RETURN expression ';' {
    $$.code = NULL;
    quad* ret = quad_gen(Q_RETURN, NULL,NULL, $2.result);
    $$.code = concat_quad($$.code, $2.code);
    $$.code = concat_quad($$.code, ret);

  }
  ;

assignement: 
  variable ASSIGN expression 
    {
      quad* q;
      if ($1.code == NULL) {
        q = quad_gen(Q_ASSIGN, $3.result, NULL, $1.result);
      }
      else {
        q = quad_gen(Q_SET_AV, $3.result, NULL, $1.result);
      }
      $$.code = concat_quad($1.code, $3.code);
      $$.code = concat_quad($$.code, q);
    }
  | variable ASSIGN assignement
    {
      $$.code = concat_quad($1.code, $3.code);
    }
  ;

variable: 
  ID 
    {
      symbol* s;    
      if((s=lookup(tds, $1)) == NULL){
        print_error("Unkown ID ", $1);
        free($1);
        return 0;
      }
      free($1);
      $$.code = NULL;
      $$.result = s;
    }
  | array 
    {
      symbol* four = lookup(tds, "@@const_4");
      if (four == NULL) four = new_integer(&tds, 4);
      //Pour multiplier l'offset par la taille d'un int

      symbol* id_addr = new_temp(&tds);
      quad* q1  = quad_gen(Q_LA, $1.base, NULL, id_addr);
      symbol* offset = new_temp(&tds);
      quad* q2  = quad_gen(Q_MULT, $1.offset, four, offset);
      symbol* address = new_temp(&tds);
      quad* q3   = quad_gen(Q_ADD, id_addr, offset, address);
      //on garde l'adresse car on ne sait pas si on va utiliser l'adresse
      //ou la valeure à l'adresse (gerer plus haut)
      $$.result = address;
      $$.code = NULL;
      $$.code   = concat_quad($$.code, $1.code);
      $$.code   = concat_quad($$.code, q1);
      $$.code   = concat_quad($$.code, q2);
      $$.code   = concat_quad($$.code, q3);


    }
  ;


array: ID '[' expression ']'
  { 
      $$.code = NULL;
      $$.offset = $3.result;
      $$.base = lookup(tds, $1);
      $$.nb_dim = 1;
      if ($$.base == NULL) {
        print_error("Unkown ID ", $1);
        free($1);
        return 0;
      }
      free($1);
      $$.code   = concat_quad($$.code, $3.code);
  }
  | array '[' expression ']'
  {
    $$.base = $1.base;
    $$.code = concat_quad($1.code, $3.code);
    $$.nb_dim = $1.nb_dim + 1;

    int nth_dim_size = get_nth_dim($$.nb_dim, $1.base->array.dim_list);
    if(DEBUG) printf("nth_dim size is %d\n", nth_dim_size);
    char* int_name = (char*)malloc(NAME_LENGTH);
    CHECK(int_name);
    snprintf(int_name, NAME_LENGTH, "@@const_%d", nth_dim_size); 

    symbol* dim_size = lookup(tds, int_name);
    if (dim_size == NULL) dim_size = new_integer(&tds, nth_dim_size);
    else free(int_name);

    symbol* mult = new_temp(&tds);
    symbol* add  = new_temp(&tds);
    quad* q1 = quad_gen(Q_MULT, $1.offset, dim_size, mult);
    quad* q2 = quad_gen(Q_ADD, mult, $3.result, add);
    $$.code = concat_quad($$.code, q1);  
    $$.code = concat_quad($$.code, q2);  
    $$.offset = add;
  }
  ;

declaration: 
  INT_TYPE ID 
    {
      symbol* s;
      if((s=lookup(tds, $2)) == NULL){
       if(DEBUG) printf("adding a variable\n");
        add(&tds, $2);
      } else {
        print_error("Redefinition of ", $2);
        free($2);
        return 0;
      }
      $$.code = NULL;
    }
  | INT_TYPE ID ASSIGN expression 
    {
      symbol* s;
      if((s=lookup(tds, $2)) == NULL){
       if(DEBUG) printf("declaring %s\n", $2);
        s=add(&tds, $2);
      } else {
        print_error("Redeclaration of ", $2);
        free($2);
        return 0;
      }
      quad* q = quad_gen(Q_ASSIGN, $4.result, NULL, s);

      $$.code = NULL;
      $$.code = concat_quad($$.code, $4.code);
      $$.code = concat_quad($$.code, q);
    }
  | INT_TYPE ARRAY_DECLARATION
    {
      if(DEBUG) printf("recognised int_type array_declaration\n");
      $$.code = NULL;
    }
  | INT_TYPE ARRAY_DECLARATION ASSIGN '{'init_array'}'
    {
      $$.code = NULL;
      $2->array.init_list = $5.list;
    }
  | STENCIL_TYPE ID '{' INTEGER ',' INTEGER '}' ASSIGN init_array
    {
      if(lookup(tds, $2)) {
        print_error("Redefinition of ", $2);
        free($2);
        return 0;
      }
      symbol* s = new_stencil(&tds, $2, $4);
      free($2);
      update_array(s, $6);
      s->array.size = (1+2*($4))*(1+2*($6-1));

      s->array.init_list = $9.list;
      $$.code = NULL;
    }
  ;

ARRAY_DECLARATION:
  ID '[' INTEGER ']' 
    {

      if(DEBUG) printf("Creating new array\n");
      symbol* s = lookup(tds, $1);
      if (s != NULL) 
      {
        print_error(" Redeclaration of ", $1);
        free($1);
        return 0;
      }

      s = new_array(&tds, $1, $3);
      free($1);
      $$ = s;
    }
  | ID '[' ID ']' 
    {
      symbol* define = lookup(tds, $3);
      if (define == NULL) 
      {
        printf("Error, define const %s not found\n", $3);
        free($1);
        free($3);
        return 0;
      }
      if (define->type != DEFINE_TYPE) 
      {
        printf("Error, %s not const define\n", $3);
        free($1);
        free($3);
        return 0;
      }
      if(DEBUG) printf("Creating new array\n");
      symbol* s = lookup(tds, $1);
      if (s != NULL) 
      {
        print_error(" Redeclaration of ", $1);
        free($1);
        return 0;
      }

      s = new_array(&tds, $1, define->value);
      free($1);
      free($3);
      $$ = s;
    }
  | ARRAY_DECLARATION '[' INTEGER ']' 
    {
      update_array($1, $3);
      $$ = $1;
    }
  | ARRAY_DECLARATION '[' ID ']' 
    {
      symbol* define = lookup(tds, $3);
      if (define == NULL) 
      {
        printf("Error, define const %s not found\n", $3);
        free($1);
        free($3);
        return 0;
      }
      if (define->type != DEFINE_TYPE) 
      {
        printf("Error, %s not const define\n", $3);
        free($1);
        free($3);
        return 0;
      }
      update_array($1, define->value);
      $$ = $1;
    }
  ;


init_array:  
  inside_array
    {
      $$.list = $1.list;
      $$.code = $1.code;
      $$.size = $1.size;
    }
  | init_array ',' inside_array
    {
      $$.list = concat_int_list($1.list, $3.list);
    
      $$.size = $1.size + $3.size;
      $$.code = concat_quad($1.code, $3.code);
    }
  ;


inside_array:  
  INTEGER 
    {
      $$.list = new_int_list($1);
      //create int_list
      $$.code = NULL;
      $$.size = 1;
    }
  | '-' INTEGER 
    {
     $$.list = new_int_list($2*-1);
     $$.code = NULL;
     $$.size =1;
    }
  | '{'init_array'}'
    {
      $$.list = $2.list;
      $$.code = $2.code;
      $$.size = $2.size;
    }
  ;



boolean_expression: boolean_expression LOG_OR boolean_expression 
    {
      $$.truelist = NULL;
      $$.falselist = NULL;
      symbol* label = new_label(&tds);
      complete_quad_list($1.falselist, label);
      free_quad_list($1.falselist);
      $$.truelist = concat_quad_list($1.truelist,$3.truelist);
      $$.falselist = $3.falselist;
      $$.code = NULL;
      quad* q_label = quad_gen(Q_LABEL, NULL, NULL, label);
      $$.code = concat_quad($1.code, q_label);
      $$.code = concat_quad($$.code, $3.code);
    }
  | boolean_expression LOG_AND boolean_expression
    {
      $$.truelist = NULL;
      $$.falselist = NULL;
      symbol* label = new_label(&tds);
      complete_quad_list($1.truelist, label);
      free_quad_list($1.truelist);
      $$.truelist = $3.truelist;
      $$.falselist = concat_quad_list($1.falselist,$3.falselist);    
      $$.code = NULL;
      quad* q_label = quad_gen(Q_LABEL, NULL, NULL, label);
      $$.code = concat_quad($1.code, q_label);
      $$.code = concat_quad($$.code, $3.code);
    }
  | expression LT expression 
    {
      quad* q_true = quad_gen(Q_LT, $1.result, $3.result, NULL);
      quad* q_false= quad_gen(Q_GOTO, NULL, NULL, NULL);

      $$.code = NULL;
      $$.code = concat_quad($$.code, $1.code);
      $$.code = concat_quad($$.code, $3.code);
      $$.code = concat_quad($$.code, q_true);
      $$.code = concat_quad($$.code, q_false);
      $$.truelist = new_list(q_true);
      $$.falselist = new_list(q_false);
    }
  | expression GT expression 
    {
      quad* q_true = quad_gen(Q_GT, $1.result, $3.result, NULL);
      quad* q_false= quad_gen(Q_GOTO, NULL, NULL, NULL);

      $$.code = NULL;
      $$.code = concat_quad($$.code, $1.code);
      $$.code = concat_quad($$.code, $3.code);
      $$.code = concat_quad($$.code, q_true);
      $$.code = concat_quad($$.code, q_false);
      $$.truelist = new_list(q_true);
      $$.falselist = new_list(q_false);
    }
  | expression LE expression 
    {
      quad* q_true = quad_gen(Q_LE, $1.result, $3.result, NULL);
      quad* q_false= quad_gen(Q_GOTO, NULL, NULL, NULL);

      $$.code = NULL;
      $$.code = concat_quad($$.code, $1.code);
      $$.code = concat_quad($$.code, $3.code);
      $$.code = concat_quad($$.code, q_true);
      $$.code = concat_quad($$.code, q_false);
      $$.truelist = new_list(q_true);
      $$.falselist = new_list(q_false);
    }
  | expression GE expression
    {
      quad* q_true = quad_gen(Q_GE, $1.result, $3.result, NULL);
      quad* q_false= quad_gen(Q_GOTO, NULL, NULL, NULL);

      $$.code = NULL;
      $$.code = concat_quad($$.code, $1.code);
      $$.code = concat_quad($$.code, $3.code);
      $$.code = concat_quad($$.code, q_true);
      $$.code = concat_quad($$.code, q_false);
      $$.truelist = new_list(q_true);
      $$.falselist = new_list(q_false);
    }
  | expression LOG_EQ expression
    {
      quad* q_true = quad_gen(Q_EQ, $1.result, $3.result, NULL);
      quad* q_false= quad_gen(Q_GOTO, NULL, NULL, NULL);
      $$.code = NULL;
      $$.code = concat_quad($$.code, $1.code);
      $$.code = concat_quad($$.code, $3.code);
      $$.code = concat_quad($$.code, q_true);
      $$.code = concat_quad($$.code, q_false);
      $$.truelist = new_list(q_true);
      $$.falselist = new_list(q_false);
    }
  | expression NE expression 
    {
      quad* q_true = quad_gen(Q_NE, $1.result, $3.result, NULL);
      quad* q_false= quad_gen(Q_GOTO, NULL, NULL, NULL);
      $$.code = NULL;
      $$.code = concat_quad($$.code, $1.code);
      $$.code = concat_quad($$.code, $3.code);
      $$.code = concat_quad($$.code, q_true);
      $$.code = concat_quad($$.code, q_false);
      $$.truelist = new_list(q_true);
      $$.falselist = new_list(q_false);
    }
  | NOT boolean_expression 
    {
      $$.truelist = $2.falselist;
      $$.falselist = $2.truelist;
      $$.code = $2.code;
    }
  | '('boolean_expression')' 
    {
      $$.truelist = $2.truelist;
      $$.falselist = $2.falselist;
      $$.code = $2.code;
    }
  ;

expression: 
  expression '+' expression 
    {
      $$.result = new_temp(&tds);
      $$.code = NULL;
      quad* q   = quad_gen(Q_ADD, $1.result, $3.result, $$.result);
      $$.code   = concat_quad($$.code, $1.code);
      $$.code   = concat_quad($$.code, $3.code);
      $$.code   = concat_quad($$.code, q);
    }

  | expression '-' expression
    {
      
      $$.result = new_temp(&tds);
      quad* q   = quad_gen(Q_SUB, $1.result, $3.result, $$.result);
      $$.code   = NULL;
      $$.code   = concat_quad($$.code, $1.code);
      $$.code   = concat_quad($$.code, $3.code);
      $$.code   = concat_quad($$.code, q);
    }
  | '-' expression %prec NEG
    {
     if(DEBUG) printf("-E\n");
      symbol* minus_one = lookup(tds, "@@negconst_1");
      if (minus_one == NULL){
        minus_one = new_integer(&tds,-1);
      }    
      symbol* s = new_temp(&tds);
      $$.result = s;
      quad* q = quad_gen(Q_MULT, minus_one, $2.result, $$.result);
      $$.code = NULL;
      $$.code = concat_quad($$.code, $2.code);
      $$.code = concat_quad($$.code, q);
    }
  | expression '/' expression 
    {
      $$.result = new_temp(&tds);
      quad* q   = quad_gen(Q_DIV, $1.result, $3.result, $$.result);
      $$.code = NULL;
      $$.code   = concat_quad($$.code, $1.code);
      $$.code   = concat_quad($$.code, $3.code);
      $$.code   = concat_quad($$.code, q);
    }

  | expression '*' expression 
    {
      $$.result = new_temp(&tds);
      quad* q   = quad_gen(Q_MULT, $1.result, $3.result, $$.result);
      $$.code = NULL;
      $$.code   = concat_quad($$.code, $1.code);
      $$.code   = concat_quad($$.code, $3.code);
      $$.code   = concat_quad($$.code, q);
    }
  | '('expression')'
    {
      $$.code = $2.code;
      $$.result = $2.result;
    }

  | ID INCR 
    {
      symbol* s = lookup(tds, $1);
      if(!s) {
        print_error("Unkown ID", $1);
        free($1);
        return 0;
      }
      symbol* cst_1 = lookup(tds, "@@const_1"); 
      if(!cst_1){
        cst_1 = new_integer(&tds, 1);
      }
      $$.result = s;
      quad* q = quad_gen(Q_ADD, s, cst_1, s);
      $$.code = NULL;
      $$.code = concat_quad($$.code, q);
      free($1);
    }

  | ID DECR 
    {
      symbol* s = lookup(tds, $1);
      if(!s) {
        print_error("Unkown variable used in expression ", $1);
        free($1);
        return 0;
      }
      symbol* cst_1 = lookup(tds, "@@const_1");
      if(!cst_1) {
        cst_1 = new_integer(&tds, 1);
      }
      $$.result = s;
      quad* q = quad_gen(Q_SUB, s, cst_1, s);
      $$.code = NULL;
      $$.code = concat_quad($$.code, q);
      free($1);

    }

  | variable 
    {
      //if variable is an array value
      
      if ($1.code != NULL) {
       if(DEBUG) printf("variable de type array remonte en tant qu'expression\n");
        $$.result = new_temp(&tds);
        //get address value
        quad* q = quad_gen(Q_GET_AV, $1.result, NULL, $$.result);
        $$.code = concat_quad($1.code, q);
      }
      //if variable is an id
      else {
        $$.code = $1.code;
        $$.result = $1.result;
      }      
    }

  | INTEGER 
    { 
      char tmp_name[256];
      if($1 >= 0)
        sprintf(tmp_name,"%s%d","@@const_",$1);
      else{
        sprintf(tmp_name,"%s%d","@@negconst_",$1*-1);

     if(DEBUG) printf("lookup : %s \n", tmp_name);
      }
    
      symbol* s = lookup(tds, tmp_name);
      if(s == NULL)
        s=new_integer(&tds, $1); 
      $$.result = s; 
    }
  | array '$' ID
    {
      int checkpoint = 0;
      if (DEBUG) printf("checkpoint %d \n", checkpoint++);
      $$.code = $1.code;

      //verify stencil exists
      symbol* stencil = lookup(tds, $3);
      if (stencil == NULL) {
        print_error("Unknown ID", $3);
        free($3);
        return 0;
      }
      if (stencil->type != STENCIL) {
        print_error($3, "is not a stencil");
        free($3);
        return 0;
      }
      if (DEBUG) printf("checkpoint %d \n", checkpoint++);
      int array_line_size = get_nth_dim($1.base->array.nb_dim, $1.base->array.dim_list);
      int stenc_x = get_nth_dim(1, stencil->array.dim_list);
      int min_i = -stenc_x;
      int max_i = stenc_x;
      if (DEBUG) printf("checkpoint %d \n", checkpoint++);
      int stenc_y = get_nth_dim(2, stencil->array.dim_list);
      int min_j = -(stenc_y-1);
      int max_j = stenc_y-1;
      int stenc_size = stencil->array.size;

      if (DEBUG) printf("checkpoint %d \n", checkpoint++);


      symbol* temp1 = new_temp(&tds);
      quad* q = quad_geni(Q_MULTI, $1.offset, 4, temp1);
      $$.code = concat_quad($$.code , q);
      symbol* array_base_addr = new_temp(&tds);
      q = quad_gen(Q_GET_A, $1.base, NULL, array_base_addr);
      $$.code = concat_quad($$.code, q);
      if (DEBUG) printf("checkpoint %d \n", checkpoint++);


      symbol* temp2 = new_temp(&tds);
      q = quad_gen(Q_ADD, array_base_addr, temp1, temp2);
      $$.code = concat_quad($$.code , q);

      //on a mntn l'adresse de base, il faut parcourir le stencil 
      //chercher les valeures aux addresses par rapport au stencil, les
      //multiplier par la valeure de cette variable du stencil
      //puis faire la somme de tout ça
      $$.result = new_temp(&tds);
      //assign 0 to result
      symbol* zero = lookup(tds, "@@const_0");
      if (zero == NULL) zero = new_integer(&tds, 0);
      q = quad_gen(Q_ASSIGN, zero, NULL, $$.result);
      $$.code = concat_quad($$.code, q);
      if (DEBUG) printf("checkpoint %d \n", checkpoint++);

      int decalage_j, decalage_i, decalage_total, decalage_stencil;
      symbol* array_addr_to_read = new_temp(&tds);
      symbol* array_addr_value = new_temp(&tds);
      symbol* stencil_base_addr = new_temp(&tds);
      symbol* stencil_read_addr = new_temp(&tds);
      symbol* stencil_addr_value = new_temp(&tds);
      symbol* temp_result = new_temp(&tds);
      q = quad_gen(Q_GET_A, stencil, NULL, stencil_base_addr);
      $$.code = concat_quad($$.code, q);
      if (DEBUG) printf("checkpoint %d \n", checkpoint++);

      for ( int j = min_j; j <= max_j; j++) 
      {
        //parcours de la ligne j
        decalage_j = j * array_line_size;
        printf("minj %d, j %d, max_j %d \n", min_j, j, max_j);
        if (DEBUG) printf("checkpoint %d \n", checkpoint++);
        for ( int i = min_i; i <= max_i; i++) 
        {
           printf("mini %d, i %d, max_i %d \n", min_i, i, max_i);
          decalage_i = i;
          decalage_total = (decalage_i + decalage_j) * 4;
          printf("decalage total dan array = %d\n", decalage_total);
          //calculer addresse par rapport à base et offset
          q = quad_geni(Q_ADDI, temp2, decalage_total, array_addr_to_read);
          $$.code = concat_quad($$.code, q);
          //lire valeure à cette adresse = t1
          q = quad_gen(Q_GET_AV, array_addr_to_read, NULL, array_addr_value);
          $$.code = concat_quad($$.code, q);
          //calculer l'addresse de la valeure dans le stencil
          decalage_stencil = ((j-min_j) * (1+2*stenc_x) + (i-min_i)) * 4;
          printf("decalage total dans stencil = %d\n", decalage_stencil);

          q = quad_geni(Q_ADDI, stencil_base_addr, decalage_stencil, stencil_read_addr);
          $$.code = concat_quad($$.code, q);
          //lire valeure a cette adresse = t2
          q = quad_gen(Q_GET_AV, stencil_read_addr, NULL, stencil_addr_value);
          $$.code = concat_quad($$.code, q);

          //multiplier t1 par t2 = t3
          q = quad_gen(Q_MULT, stencil_addr_value, array_addr_value, temp_result);
          $$.code = concat_quad($$.code, q);

          //ADD to result
          q = quad_gen(Q_ADD, temp_result, $$.result, $$.result);
          $$.code = concat_quad($$.code, q);

        }
      }
      if (DEBUG) printf("checkpoint %d \n", checkpoint++);



      if (DEBUG) printf("Recognised array $ ID\n");
      free($3);

    }
  ;
%%

void yyerror(char *str){
    fprintf(stderr,"[Error] line %d : %s\n",yylineno,str);
}

void print_error(char* str1, char* str2){
  char err_msg[ERR_LENGTH] = "";
  strcat(err_msg, str1);
  strcat(err_msg, str2);
  yyerror(err_msg);
}


int main(int argc, char** argv) {
  if (argc != 1){
    printf("Usage : ./bin/stenc file\n ( output in out.s )");
    return 0;
  }
  FILE* fp_in = fopen(argv[1], "r");
  yyin = fp_in;
  yyparse();
  if(DEBUG) {
    printf("==== TDS ========================================================\n"); 
    printf ("\n");
    print_symbol(tds);
    printf("=================================================================\n\n");

    printf("==== QUADS ======================================================\n"); 
    print_quads(whole_code);
    printf("=================================================================\n");
  }
  FILE* fp_out = fopen("out.s", "w");
  gen_data(fp_out, tds);
  gen_code(fp_out, whole_code);
  fclose(fp_out);
  fclose(fp_in);
  free_symbol(tds);
  free_quad(whole_code);
  


  yylex_destroy();  

  return 0;
}
