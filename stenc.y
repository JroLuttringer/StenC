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
%type <string> ID STRING
%type <value> INTEGER
%type <expr> expression 
%type <cond> boolean_expression
%type <statement> statement statement_list program s assignement declaration COMMENT 
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
  statement_list  statement  
    { 
      printf("concat du statement \n");
      $$.next = $2.next;
      //complete_quad_list($1.next, $2);
      $$.code = NULL;
      //quad *q = quad_gen(Q_LABEL, NULL, NULL, $2);
      $$.code = concat_quad($$.code, $1.code);
      //$$.code = concat_quad($$.code, q);
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
    {
      //$$.code = NULL;
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
      printf("test\n");
      printf("saw printf %s\n", $3);
      symbol* s = new_string(&tds, $3);
      quad* q = quad_gen(Q_PRINTF,NULL, NULL, s);
      $$.code = concat_quad($$.code, q);    
    }   
  | boolean_expression ';' 
    {
        printf("buginator boolean_expr ;\n");
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
      
  }
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
        printf("adding a variable\n");
        add(&tds, $2);
      } else {
        fprintf(stderr, "redefinition of %s\n", $2);
        return 0;
      }
      $$.code = NULL;
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
        printf("dans le gt de expr\n");
      quad* q_true = quad_gen(Q_GT, $1.result, $3.result, NULL);
      quad* q_false= quad_gen(Q_GOTO, NULL, NULL, NULL);

      $$.code = NULL;
      $$.code = concat_quad($$.code, $1.code);
      $$.code = concat_quad($$.code, $3.code);
      $$.code = concat_quad($$.code, q_true);
      $$.code = concat_quad($$.code, q_false);
      $$.truelist = new_list(q_true);
      $$.falselist = new_list(q_false);
     printf("check err seg\n");
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
   printf("Je créé le tag\n");
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
