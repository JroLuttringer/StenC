%{
  #include "list.h"
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
}

%type <symbol> variable
%type <string> ID
%type <value> INTEGER
%type <expr> expression statement statement_list program s assignement declaration

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
  | PRINTI '(' expression ')' ';' {
    $$.code = NULL;
    quad* q = quad_gen(Q_PRINTI, NULL, NULL, $3.result);
    $$.code = concat_quad($$.code, $3.code);
    $$.code = concat_quad($$.code, q); 
  }
  | PRINTF '(' STRING ')' ';' {
    
  }
  | IF '('boolean_expression')' '{'statement_list'}'
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
    $$.result = q->result;
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
  | INT_TYPE ID ASSIGN expression {
    symbol* s;
    if((s=lookup(tds, $2)) == NULL){
      s=add(&tds, $2);
    } else {
      fprintf(stderr, "redefinition of %s\n", $2);
      return 0;
    }
    quad* q = quad_gen(Q_ASSIGN, $4.result, NULL, s);
    $$.result = q->result;
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

boolean_expression: boolean_expression LOG_OR boolean_expression
  | boolean_expression LOG_AND boolean_expression
  | expression relop expression
  | expression LOG_EQ expression
  | expression NE expression
  | NOT boolean_expression
  | '('boolean_expression')'
  ;

relop: GT
  | LT
  | LE
  | GE
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
    printf("-E\n");
    symbol* minus_one = lookup(tds, "__negconst_1");
    if (minus_one == NULL){
      minus_one = new_integer(&tds,-1);
    }    
    symbol* s = new_temp(&tds);
    $$.result = s;
    //printf("result of E in -E is %d\n", $2.result.value);
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
  int a = 10;
  int __b = 5;
  int y = a*a + 2*++a*__b+ __b*__b;
  int x = (a+__b)*(a+__b);
  printf("%d %d %d\n", __b,x, y);
  yyparse();
  printf ("\n\n");
  printf("==== TDS ========================================================\n"); 
  print_symbol(tds);
  printf("=================================================================\n");
  fclose(fp);
  return 0;
}