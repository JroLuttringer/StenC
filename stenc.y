%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "quad.h"
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
}

%type <symbol*> expression
%type <string> variable
%type <string> ID
%type <int> INTEGER

%%
s: program { printf("Match ! \n"); return 0;} ;
program: INT_TYPE MAIN '(' ')' '{' statement_list '}' ;
statement_list: statement statement_list
  | %empty
  ;
statement: assignement ';'
  | declaration ';'
  | expression ';'
  | PRINTI '(' variable ')' ';' 
  | PRINTF '(' STRING ')' ';'
  | IF '('boolean_expression')' '{'statement_list'}'
  | IF '('boolean_expression')' '{'statement_list'}' ELSE '{'statement_list'}'
  | WHILE '(' boolean_expression ')' '{'statement_list'}'
  | FOR '('assignement';' boolean_expression ';' expression ')' '{'statement_list'}'
  | RETURN expression ';'
  ;

assignement: variable ASSIGN expression
  | variable ASSIGN assignement
  ;

variable: ID ;
  | array ']'
  ;

array: ID '[' expression 
  | array ']' '[' expression
  ;

declaration: INT_TYPE ID
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

expression: '-' expression
  | expression '+' expression
  | expression '-' expression
  | expression '/' expression {
    symbol* tmp = new_temp()
  }
  | expression '*' expression
  | ID INCR {
    symbol *tmp;
    if(! (tmp=lookup(ds, $1)){
      tmp->value++;
    } else {
      fprintf(stderr, "id++ with unknown id \n");
    }
  }  

  | ID DECR {
      symbol *tmp;
      if(! (tmp=lookup(tds, $1))){
        tmp->value--;
      } else {
        fprintf(stderr, "id++ with unknown id \n");
      }
    }  

  | variable 
    {
      if(!lookup(tds, $1)) 
        add(&tds, $1);
    }
  | INTEGER { new_temp(&tds, $1) }

  ;
%%

void yyerror (char *s) {
    fprintf(stderr, "[Yacc] error: %s\n", s);
}

int main(int argc, char** argv) {
  FILE* fp = fopen("C_simple.c", "r");
  yyin = fp;
  yyparse();
  fclose(fp);
  return 0;
}