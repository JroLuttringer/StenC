%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  void yyerror( char*);
  int yylex();
  extern FILE* yyin;
%}

%token ID INT_TYPE VOID_TYPE COMMENT INTEGER PRINTI PRINTF STRING MAIN RETURN
%token IF ELSE WHILE DO FOR INCR DECR LOG_AND LOG_OR LOG_EQ GE LE NE GT LT NOT
%right ASSIGN 
%left INCR DECR '+' '-' '*' '/' NOT LOG_AND LOG_EQ GE LE NE LOG_OR GT LT 

// TODO : assignement -> assignement list 
// FOR sans accolades ?
// left & right
//empty
%%
s: program { printf("Match ! \n"); return 0;} ;
program: INT_TYPE MAIN '(' ')' '{' statement_list '}' ;
statement_list: statement statement_list
  | %empty
  ;
statement: assignement ';'
  | declaration ';'
  | expression;
  | PRINTI '(' variable ')' ';' 
  | PRINTF '(' STRING ')' ';'
  | IF '('boolean_expression')' '{'statement_list'}'
  | IF '('boolean_expression')' '{'statement_list'}' ELSE '{'statement_list'}'
  | WHILE '(' boolean_expression ')' '{'statement_list'}'
  | FOR '('assignement';' boolean_expression ';' expression ')' '{'statement_list'}'
  | RETURN INTEGER ';'
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
  | INT_TYPE array']' ASSIGN '{'int_list'}'
  ;

int_list: expression
  | int_list ',' expression
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
  | expression '/' expression
  | expression '*' expression
  | ID INCR
  | ID DECR  
  | variable
  | INTEGER 

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