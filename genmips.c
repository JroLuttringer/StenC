#include "genmips.h"


void gen_data(FILE* mips_file, symbol* tds){
  fprintf(mips_file,".data\n");
  symbol* tmp = tds;
  while(tmp){
      fprintf(mips_file, "%s:\t.word %d\n", tmp->name, tmp->value);
      tmp = tmp->next;
    }
    fprintf(mips_file, "%s:\t.asciiz %s\n", "ERRDIVZERO", "Error : division by zero\n");
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
            fprintf(mips_file, "\tlw %s, %s\n","$a0", tmp->result->name);
            fprintf(mips_file, "\tli $v0, 4\n");
            fprintf(mips_file, "\tsyscall\n");
            break;

            default: 
            break;
      }
    } else if(tmp->arg1 != NULL && tmp->arg2 == NULL) {
      switch(tmp -> i){
        case Q_ASSIGN:
          fprintf(mips_file, "\tlw $t0, %s\n", tmp->arg1->name);
          fprintf(mips_file, "\tsw $t0, %s\n", tmp->result->name);
        break;
        default : break;
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
        default:
        break;
      }
      //TODO : if null , statement inutile ????
      if(tmp->result != NULL)
        fprintf(mips_file, "\tsw %s, %s\n",  "$t2", tmp->result->name);
    }
    tmp = tmp->next;
  }
  fprintf(mips_file, "jr $ra");
}
