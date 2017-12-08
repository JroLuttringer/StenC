#include "genmips.h"


void gen_data(FILE* mips_file, symbol* tds){
  fprintf(mips_file,".data\n");
  symbol* tmp = tds;
  int size = 0;
  while(tmp){
      switch(tmp->type){
        case LABEL:
          break;
        case STRING_TYPE:
          fprintf(mips_file, "%s:\t.asciiz %s\n", tmp->name, tmp->string);
          break;
        case ARRAY:
          size = tmp->array.dim_list->value;
          printf("Size of array is %d\n", size);
          fprintf(mips_file, "%s:\t.word", tmp->name);
          for (int i = 0; i < size; i++) fprintf(mips_file, " 0");
          fprintf(mips_file, "\n");
          break;
        case CONSTANT:
        case VARIABLE:
          fprintf(mips_file, "%s:\t.word %d\n", tmp->name, tmp->value);
          break;
        default:
          printf("Error gen_data\n");
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
          printf("jro a oublié comme un gogol\n");
          break;
      }
    } else if(tmp->arg1 != NULL && tmp->arg2 == NULL) {
      switch(tmp -> i){
        case Q_ASSIGN:
          fprintf(mips_file, "\tlw $t0, %s\n", tmp->arg1->name);
          fprintf(mips_file, "\tsw $t0, %s\n", tmp->result->name);
        break;
        default :
            printf("jro a oublié comme un gogol\n");
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
            printf("jro a oublié comme un gogol\n");
        break;
      }
      //TODO : if null , statement inutile ????
      if(tmp->i == Q_ADD || tmp->i == Q_SUB || tmp->i == Q_MULT || tmp->i == Q_DIV )
        fprintf(mips_file, "\tsw %s, %s\n",  "$t2", tmp->result->name);
    }
    tmp = tmp->next;
  }
}
