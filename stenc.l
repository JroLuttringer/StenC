%{
  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
  #include "list.h"
  #include "quad.h"
  #include "quad_list.h"
  #include "y.tab.h"
  #include "y.tab.h"

%}


id    [_a-zA-Z][_a-zA-Z0-9]*
int 0|([1-9][0-9]*)
comment ("/*"([^*]|(\*+[^*/]))*"*"+"/")|("//"[^\n]*\n)
string  \".*\"

%%

"int"    { return INT_TYPE; }
"if"     { return IF; }
"for"    { return FOR;}
"else"   { return ELSE; }
"do"     { return DO; }
"void"   { return VOID_TYPE; }
"while"  { return WHILE; }
"main"   { return MAIN;}
"return" { return RETURN;}
"++"     { return INCR;}
"--"     { return DECR;}
"&&"     { return LOG_AND;}
"||"     { return LOG_OR;}
"=="     { return LOG_EQ;}
">="     { return GE;}
"<="     { return LE;}
">"      { return GT;}
"<"      { return LT;}
"!="     { return NE;}
";"      { return yytext[0];}
"="      { return ASSIGN;}
"{"      { return yytext[0];}
"}"      { return yytext[0];}
","      { return yytext[0];}
"("      { return yytext[0];}
")"      { return yytext[0];}
"["      { return yytext[0];}
"]"      { return yytext[0];}
"!"      { return NOT;}
"-"      { return yytext[0];}
"+"      { return yytext[0];}
"*"      { return yytext[0];}
"/"      { return yytext[0];}
"printi" { return PRINTI;}
"printf" { return PRINTF;}
{id} { yylval.string = strdup(yytext);return ID;}
{int}  { yylval.value = atoi(yytext);return INTEGER;}
{comment}  { return COMMENT;}
{string}  { yylval.string = strdup(yytext); return STRING;}

[ \t\n]  { }
. {}

%%