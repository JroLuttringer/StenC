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
%right '=' '{' '!' 
%left INCR DECR '+' '-' '*' '/' LOG_AND LOG_EQ GE LE NE LOG_OR GT LT 

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
statement: line ';'
  | PRINTI '(' variable ')' ';' 
  | PRINTF '(' STRING ')' ';'
  | IF '('boolean_expression')' '{'statement_list'}'
  | IF '('boolean_expression')' '{'statement_list'}' ELSE '{'statement_list'}'
  | WHILE '(' boolean_expression ')' '{'statement_list'}'
  | FOR '('assignement';' boolean_expression ';' assignement ')' '{'statement_list'}'
  | RETURN INTEGER ';'
  ;

line: assignement
  | definition
  ;

assignement: variable '=' expression
  | variable '=' assignement
  | ID INCR 
  | ID DECR 
  ;
definition: INT_TYPE ID '=' expression
  | INT_TYPE ID dimensions '=' '{'int_list'}'
  ;


variable: ID dimensions;
dimensions: %empty
  | dimensions '['expression']'
  ;

int_list: INTEGER
  | int_list ',' INTEGER
    ;

boolean_expression: expression LOG_EQ expression
  | expression GE expression
  | expression GT expression
  | expression LE expression
  | expression LT expression
  | expression NE expression
  | boolean_expression LOG_AND boolean_expression
  | boolean_expression LOG_OR boolean_expression
  | NOT boolean_expression
  | '('boolean_expression')'
  ;

expression: '-' expression
  | expression '+' expression
  | expression '-' expression
  | expression '/' expression
  | expression '*' expression
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