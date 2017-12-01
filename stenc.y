%{
  #include "list.h"
  #include "quad_list.h"
  #include "genmips.h"
  #include "quad.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  void yyerror( char*);
  int yylex();
  extern FILE* yyin;
  symbol* tds = NULL;

%}

%token ID INT_TYPE VOID_TYPE COMMENT INTEGER PRINTI PRINTF STRING MAIN RETURN ASSIGN
%token IF ELSE WHILE DO FOR INCR DECR LOG_AND LOG_OR LOG_EQ GE LE NE GT LT NOT
%left ','  
%left LOG_OR
%left LOG_AND
%left LOG_EQ NE
%left GE LE GT LT
%left '+' '-'
%left '*' '/'
%right NEG NOT
%left INCR DECR 

%union{
  char* string;
  int value;
  symbol* symbol;
  struct {
    symbol* result;
    quad* code;
  } expr;
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

%type <symbol> variable tag
%type <string> ID STRING COMMENT
%type <value> INTEGER
%type <expr> expression 
%type <cond> boolean_expression
%type <statement> statement statement_list program s assignement declaration 
%%
s: program 
{
  printf("Match ! \n\n");
  $$.code = NULL;
  $$.code = concat_quad($$.code, $1.code);
  printf("==== QUADS ======================================================\n"); 
  print_quads($$.code);
  printf("=================================================================\n\n");
  FILE* fp = fopen("simple_arithm.asm", "w");
  gen_data(fp, tds);
  gen_code(fp, $$.code);
  fclose(fp);


  return 0;
};

program: INT_TYPE MAIN '(' ')' '{' statement_list RETURN expression ';' '}'
{
  $$.code = NULL;
  $$.code = concat_quad($$.code, $6.code);
};

statement_list: 
  statement_list statement  
    { 
      $$.code = NULL;
      $$.code = concat_quad($$.code, $1.code);
      $$.code = concat_quad($$.code, $2.code);
    }
  | %empty
    {
      $$.code = NULL;
    };

statement: 
  assignement ';' 
    {
      $$.code = NULL;
      $$.code = concat_quad($$.code, $1.code);
    }
  | declaration ';'
  | expression ';'  
    {
      $$.code = NULL;
      $$.code = concat_quad($$.code, $1.code);
    } 
  | COMMENT
  | PRINTI '(' expression ')' ';'
    {
      $$.code = NULL;
      quad* q = quad_gen(Q_PRINTI, NULL, NULL, $3.result);
      $$.code = concat_quad($$.code, $3.code);
      $$.code = concat_quad($$.code, q); 
    }
  | PRINTF '(' STRING ')' ';' 
    {
     /* $$.code = NULL;
      symbol* s = new_temp(&tds,$3)
      quad* q = quad_gen(Q_PRINTF,NULL, NULL, s);
      $$.code = concat_quad($$.code, q);    */
    }   
  | boolean_expression ';' 
    {
      $$.code = $1.code;
    }
  | IF '('boolean_expression')' tag '{'statement_list'}'
    {
      complete_quad_list($3.truelist, $5);
      $$.next = concat_quad_list($3.falselist, $7.next);
    }
  | IF '('boolean_expression')' '{'statement_list'}' ELSE '{'statement_list'}'
  | WHILE '(' boolean_expression ')' '{'statement_list'}'
  | FOR '('assignement';' boolean_expression ';' expression ')' '{'statement_list'}'
  | RETURN expression ';'
  ;

assignement: 
  variable ASSIGN expression 
    {
      symbol* s = lookup(tds, $1->name);
      if(s == NULL) {
        fprintf(stderr, "Unknown variable %s in assignement\n", $1->name);
        return 0;
      }
      quad* q = quad_gen(Q_ASSIGN, $3.result, NULL, s);
     // $$.result = q->result;
      $$.code = NULL;
      $$.code = concat_quad($$.code, $3.code);
      $$.code = concat_quad($$.code, q);
    }
  | variable ASSIGN assignement
  ;

variable: 
  ID 
    {
      symbol* s;    
      if((s=lookup(tds, $1)) == NULL){
        fprintf(stderr, "unknown variable %s", $1);
        return 0;
      }
      $$ = NULL;
      $$ = s;
    }
  | array ']'
  ;

array: ID '[' expression 
  | array ']' '[' expression
  ;

declaration: 
  INT_TYPE ID 
    {
      symbol* s;
      if((s=lookup(tds, $2)) == NULL){
        add(&tds, $2);
      } else {
        fprintf(stderr, "redefinition of %s\n", $2);
        return 0;
      }
    }
  | INT_TYPE ID ASSIGN expression 
    {
      symbol* s;
      if((s=lookup(tds, $2)) == NULL){
        s=add(&tds, $2);
      } else {
        fprintf(stderr, "redefinition of %s\n", $2);
        return 0;
      }
      quad* q = quad_gen(Q_ASSIGN, $4.result, NULL, s);
     // $$.result = q->result;
      $$.code = NULL;
      $$.code = concat_quad($$.code, $4.code);
      $$.code = concat_quad($$.code, q);
    }
  | INT_TYPE array']'
  | INT_TYPE array']' ASSIGN '{'init_array'}'
  ;

/* array init :  inside array or multiple arrays */

init_array:  inside_array
  | init_array ',' inside_array
  ;

/* inside an array : arithmetic expression or another array */

inside_array:  expression 
  | '{'init_array'}'
  ;

boolean_expression: boolean_expression LOG_OR tag boolean_expression 
  {
      $$.truelist = NULL;
      $$.falselist = NULL;
      complete_quad_list($1.falselist, $3);
      $$.truelist = concat_quad_list($1.truelist,$4.truelist);
      $$.falselist = $4.falselist;
      $$.code = NULL;
      quad* q_label = quad_gen(Q_LABEL, NULL, NULL, $3);
      $$.code = concat_quad($1.code, q_label);
      $$.code = concat_quad($$.code, $4.code);
  }
  | boolean_expression LOG_AND tag boolean_expression
    {
      $$.truelist = NULL;
      $$.falselist = NULL;
      complete_quad_list($1.truelist, $3);
      $$.truelist = $4.truelist;
      $$.falselist = concat_quad_list($1.falselist,$4.falselist);    
      $$.code = NULL;
      quad* q_label = quad_gen(Q_LABEL, NULL, NULL, $3);
      $$.code = concat_quad($1.code, q_label);
      $$.code = concat_quad($$.code, $4.code);
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

tag: %empty {
  $$ = new_label(&tds);
}

//relop: GT
//  | LT
//  | LE
//  | GE
//  ;
//
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
      printf("-E\n");
      symbol* minus_one = lookup(tds, "__negconst_1");
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
        fprintf(stderr, "unknown variable %s used in arith. expr\n", $1);
        return 0;
      }
      symbol* cst_1 = lookup(tds, "__const_1"); //TODO @
      if(!cst_1){
        cst_1 = new_integer(&tds, 1);
      }
      $$.result = s;
      quad* q = quad_gen(Q_ADD, s, cst_1, s);
      $$.code = NULL;
      $$.code = concat_quad($$.code, q);
    }

  | ID DECR 
    {
      symbol* s = lookup(tds, $1);
      if(!s) {
        fprintf(stderr, "unknown variable %s used in arith. expr\n", $1);
        return 0;
      }
      symbol* cst_1 = lookup(tds, "__const_1");
      if(!cst_1){
        cst_1 = new_integer(&tds, 1);
      }
      $$.result = s;
      quad* q = quad_gen(Q_SUB, s, cst_1, s);
      $$.code = NULL;
      $$.code = concat_quad($$.code, q);

    }

  | variable 
    {
      symbol* s;
      if(!(s=lookup(tds, $1->name))) {
        fprintf(stderr, "unknown variable %s used in arithmetic expression", $1->name);
        return 0;
      }
      $$.result = s;
    }

  | INTEGER 
    { 
      char tmp_name[256];
      if($1 >= 0)
        sprintf(tmp_name,"%s%d","__const_",$1);
      else{
        sprintf(tmp_name,"%s%d","__negconst_",$1*-1);
        printf("lookup : %s \n", tmp_name);
      }
    
      symbol* s = lookup(tds, tmp_name);
      if(s == NULL)
        s=new_integer(&tds, $1); 
      $$.result = s; 
    };
%%

void yyerror (char *s) {
    fprintf(stderr, "[Yacc] error: %s\n", s);
}

int main(int argc, char** argv) {
  FILE* fp = fopen("simple_arithm.c", "r");
  yyin = fp;
  yyparse();
  printf ("\n\n");
  printf("==== TDS ========================================================\n"); 
  print_symbol(tds);
  printf("=================================================================\n");
  fclose(fp);
  return 0;
}