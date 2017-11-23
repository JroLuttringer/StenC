%{
  #include "list.h"
  #include "quad.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  void yyerror( char*);
  int yylex();
  extern FILE* yyin;
  symbol* tds = NULL;

%}

%token ID INT_TYPE VOID_TYPE COMMENT INTEGER PRINTI PRINTF STRING MAIN RETURN
%token IF ELSE WHILE DO FOR INCR DECR LOG_AND LOG_OR LOG_EQ GE LE NE GT LT NOT
%left INCR DECR ',' '-' '*' '/' '+' LOG_AND NE GE LE GT LT LOG_OR
%right ASSIGN NOT

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
%type <expr> expression statement statement_list program s assignement

%%
s: program {
  printf("Match ! \n\n");

   $$.code = NULL;
   $$.code = concat_quad($$.code, $1.code);
   printf("==== QUADS ======================================================\n"); 
   print_quads($$.code);
   printf("=================================================================\n\n");
   return 0;
}
;
program: INT_TYPE MAIN '(' ')' '{' statement_list RETURN expression ';' '}' {
  $$.code = NULL;
  $$.code = concat_quad($$.code, $6.code);
}
;
statement_list: statement_list statement  { 
    $$.code = NULL;
    $$.code = concat_quad($$.code, $1.code);
    $$.code = concat_quad($$.code, $2.code);
  }
  | %empty {
    $$.code = NULL;
  }
  ;
statement: assignement ';' {
  $$.code = NULL;
  $$.code = concat_quad($$.code, $1.code);
}
  | declaration ';'
  | expression ';'  {
    $$.code = NULL;
    $$.code = concat_quad($$.code, $1.code);
  } 
  | COMMENT
  | PRINTI '(' variable ')' ';' 
  | PRINTF '(' STRING ')' ';'
  | IF '('boolean_expression')' '{'statement_list'}'
  | IF '('boolean_expression')' '{'statement_list'}' ELSE '{'statement_list'}'
  | WHILE '(' boolean_expression ')' '{'statement_list'}'
  | FOR '('assignement';' boolean_expression ';' expression ')' '{'statement_list'}'
  | RETURN expression ';'
  ;

assignement: variable ASSIGN expression {
  quad* q = quad_gen(Q_ASSIGN, $3.result, NULL, $1);
  $$.result = q->result;
  $$.code = NULL;
  $$.code = concat_quad($$.code, $3.code);
  $$.code = concat_quad($$.code, q);
}
  | variable ASSIGN assignement
  ;

variable: ID {
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

declaration: INT_TYPE ID {
  symbol* s;
  if((s=lookup(tds, $2)) == NULL){
    add(&tds, $2);
  } else {
    fprintf(stderr, "redefinition of %s\n", $2);
    return 0;
  }
}
  | INT_TYPE ID ASSIGN expression
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
  | expression
  ;

relop: GT
  | LT
  | LE
  | GE
  ;

expression: '-' expression {}
  | expression '+' expression {
    $$.result = new_temp(&tds);
 $$.code = NULL;
    quad* q   = quad_gen(Q_ADD, $1.result, $3.result, $$.result);
    $$.code   = concat_quad($$.code, $1.code);
    $$.code   = concat_quad($$.code, $3.code);
       // print_quads(q);

    $$.code   = concat_quad($$.code, q);
    
    //print_quads($$.code);

  }
  | expression '-' expression{
    $$.result = new_temp(&tds);
    quad* q   = quad_gen(Q_SUB, $1.result, $3.result, $$.result);
 $$.code = NULL;
    $$.code   = concat_quad($$.code, $1.code);
    $$.code   = concat_quad($$.code, $3.code);
    $$.code   = concat_quad($$.code, q);
  }
  | expression '/' expression {
    $$.result = new_temp(&tds);
    quad* q   = quad_gen(Q_DIV, $1.result, $3.result, $$.result);
 $$.code = NULL;
    $$.code   = concat_quad($$.code, $1.code);
    $$.code   = concat_quad($$.code, $3.code);
    $$.code   = concat_quad($$.code, q);
  }
  | expression '*' expression {
    $$.result = new_temp(&tds);
    quad* q   = quad_gen(Q_MULT, $1.result, $3.result, $$.result);
 $$.code = NULL;
    $$.code   = concat_quad($$.code, $1.code);
    $$.code   = concat_quad($$.code, $3.code);
    $$.code   = concat_quad($$.code, q);
  }
  | ID INCR {
     $$.result = new_temp(&tds);
     symbol* s = lookup(tds, $1);
     if(!s) {
	fprintf(stderr, "unknown variable %s used in arith. expr\n", $1);
        return 0;
     }
     
     symbol* cst_1 = lookup(tds, "@@const_1");
     if(!cst_1){
 	cst_1 = new_integer(&tds, 1);
     }
     quad* q = quad_gen(Q_ADD, s, cst_1, $$.result);
     $$.code = NULL;
	$$.code = concat_quad($$.code,q);
   }
    

  | ID DECR {
     $$.result = new_temp(&tds);
     symbol* s = lookup(tds, $1);
     if(!s) {
	fprintf(stderr, "unknown variable %s used in arith. expr\n", $1);
        return 0;
     }
     
     symbol* cst_1 = lookup(tds, "@@const_1");
     if(!cst_1){
 	cst_1 = new_integer(&tds, 1);
     }
     quad* q = quad_gen(Q_SUB, s, cst_1, $$.result);

     $$.code = NULL;
	$$.code = concat_quad($$.code,q);
  }
 

  | variable 
    {
      symbol* s;
      if(!(s=lookup(tds, $1->name))) {
        fprintf(stderr, "unknown variable %s used in arithmetic expression", $1->name);
        return 0;
      } else {
        $$.result = s;
      }
    }
  | INTEGER { 
    char tmp_name[256];
    sprintf(tmp_name,"%s%d","@@const_",$1);
    symbol* s = lookup(tds, tmp_name);
    if(s == NULL)
      s=new_integer(&tds, $1); 
    $$.result = s; 
  }

  ;
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
