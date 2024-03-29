#include "../include/genmips.h"


void change_symbol_table(symbol* tds){
  symbol* tmp = tds;
  char *c;
  while(tmp){
    if( (c=strstr(tmp->name, "@@")) ){
      *c='_';
      *(c+1)='_';
    } else{
      char* new_name = realloc(tmp->name,strlen(tmp->name)+3);
      if(!new_name){printf("problem while generating code \n"); exit(-1);}
      tmp->name = new_name;
      strcat(tmp->name, "__\0");
    }
    tmp=tmp->next;
  }
}


void gen_data(FILE* mips_file, symbol* tds){
  change_symbol_table(tds);
  fprintf(mips_file,".data\n");
  symbol* tmp = tds;
  int size = 0;
  int i;
  while(tmp){
      switch(tmp->type){
        case LABEL:
          break;
        case STRING_TYPE:
          fprintf(mips_file, "%s:\t.asciiz %s\n", tmp->name, tmp->string);
          break;
        case ARRAY:
        case STENCIL:
          if (tmp->array.init_list != NULL)
          {
            size = tmp->array.size; 
            fprintf(mips_file, "%s:\t.word", tmp->name);
            for (i = 0; i < size; i++) 
            {
              fprintf(mips_file, " %d", get_nth_dim((i+1), tmp->array.init_list));
            }
            fprintf(mips_file, "\n");
          }
          else
          {
            size = tmp->array.size * 4;
            fprintf(mips_file, "%s:\t.space %d\n", tmp->name, size);
          }
          break;
        case CONSTANT:
        case VARIABLE:
        case DEFINE_TYPE:
          fprintf(mips_file, "%s:\t.word %d\n", tmp->name, tmp->value);
          break;
        default:
          fprintf(stderr,"Error while generating mips : data type unknown\n");
          return ;
          break;
      }
      tmp = tmp->next;
    }
    gen_interrupt(mips_file);
}

void gen_interrupt(FILE* mips_file){
  fprintf(mips_file, "%s:\t.asciiz %s\n", "ERRDIVZERO", "\"Error : division by zero\"\n");
}

void gen_code(FILE* mips_file, quad* code){
  quad* tmp = code;
  fprintf(mips_file, ".text\nmain:\n");
  while(tmp){
    if(tmp->arg1 == NULL && tmp->arg2 == NULL){
      switch(tmp->i){ // TODO : FACTORISER
        case Q_PRINTI:
          fprintf(mips_file, "\tlw %s, %s\n", "$a0",tmp->result->name);
          fprintf(mips_file, "\tli $v0, 1\n");
          fprintf(mips_file, "\tsyscall\n");
          break;
        case Q_PRINTF:
          fprintf(mips_file, "\tla %s, %s\n","$a0", tmp->result->name);
          fprintf(mips_file, "\tli $v0, 4\n");
          fprintf(mips_file, "\tsyscall\n");
          break;
        case Q_GOTO:
          fprintf(mips_file, "\tj %s\n", tmp->result->name);
          break;
        case Q_LABEL:
          fprintf(mips_file, "\t%s:\n", tmp->result->name);
          break;
        case Q_RETURN:
          fprintf(mips_file, "\tlw $v0, %s\n", tmp ->result->name);
          fprintf(mips_file, "\tjr $ra\n");
          break;   

        default: 
            printf("Type unknown\n");
          break;
      }
    } else if(tmp->arg1 != NULL && tmp->arg2 == NULL) {
      switch(tmp -> i){
        case Q_ASSIGN:
          fprintf(mips_file, "\tlw $t0, %s\n", tmp->arg1->name);
          fprintf(mips_file, "\tsw $t0, %s\n", tmp->result->name);
        break;
        case Q_LA:
          fprintf(mips_file, "\tla $t0, %s\n", tmp->arg1->name);
          fprintf(mips_file, "\tsw $t0, %s\n", tmp->result->name);          

          break;
        case Q_GET_A:
          fprintf(mips_file, "\tla $t0, %s\n", tmp->arg1->name);
          fprintf(mips_file, "\tsw $t0, %s\n", tmp->result->name);
          break;
        case Q_GET_AV:
          fprintf(mips_file, "\tlw $t0, %s\n", tmp->arg1->name);
          fprintf(mips_file, "\tlw $t1, ($t0)\n");
          fprintf(mips_file, "\tsw $t1, %s\n", tmp->result->name);         

          break;
        case Q_SET_AV:
          fprintf(mips_file, "\tlw $t0, %s\n", tmp->arg1->name);
          fprintf(mips_file, "\tlw $t1, %s\n", tmp->result->name);
          fprintf(mips_file, "\tsw $t0, ($t1)\n");          

        break;
        case Q_ADDI:
          fprintf(mips_file, "\tlw %s, %s\n", "$t0",tmp->arg1->name);
          fprintf(mips_file, "\taddi $t2,$t0,%d\n", tmp->argi2);
          fprintf(mips_file, "\tsw %s, %s\n",  "$t2", tmp->result->name);
          break;
        case Q_MULTI:
          fprintf(mips_file, "\tlw %s, %s\n", "$t0",tmp->arg1->name);
          fprintf(mips_file, "\tmul $t2,$t0,%d\n", tmp->argi2);
          fprintf(mips_file, "\tsw %s, %s\n",  "$t2", tmp->result->name);
          break;
        default :
            printf("Type unknown\n");
            break;
      }
    } else if (tmp->arg1 != NULL && tmp->arg2 != NULL){
      fprintf(mips_file, "\tlw %s, %s\n", "$t0",tmp->arg1->name);
      fprintf(mips_file, "\tlw %s, %s\n", "$t1",tmp->arg2->name);
      switch(tmp-> i){
        case Q_ADD:
          fprintf(mips_file, "\taddu $t2,$t0,$t1\n");
        break;
        case Q_SUB:
          fprintf(mips_file, "\tsubu $t2,$t0,$t1\n");
        break;
        case Q_MULT:
          fprintf(mips_file, "\tmul $t2,$t0,$t1\n");
        break;
        case Q_DIV:
          fprintf(mips_file, "\tdiv $t2,$t0,$t1\n");
        break;
        case Q_GT:
          fprintf(mips_file, "\tbgt $t0, $t1, %s\n", tmp->result->name);
          break;
        case Q_GE:
          fprintf(mips_file, "\tbge $t0, $t1, %s\n", tmp->result->name);
          break;
        case Q_LT:
          fprintf(mips_file, "\tblt $t0, $t1, %s\n", tmp->result->name);
          break;
        case Q_LE:
          fprintf(mips_file, "\tble $t0, $t1, %s\n", tmp->result->name);
          break;
        case Q_EQ:
          fprintf(mips_file, "\tbeq $t0, $t1, %s\n", tmp->result->name);
          break;
        case Q_NE:
          fprintf(mips_file, "\tbne $t0, $t1, %s\n", tmp->result->name);
          break;


        default:
            printf("Type unknown\n");
        break;
      }
      if(tmp->i == Q_ADD || tmp->i == Q_SUB || tmp->i == Q_MULT || tmp->i == Q_DIV )
        fprintf(mips_file, "\tsw %s, %s\n",  "$t2", tmp->result->name);
    }
    tmp = tmp->next;
  }
}
