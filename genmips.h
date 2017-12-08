#ifndef __GENMIPS_H__
#define __GENMIPS_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "symbol.h"
#include "quad.h"


void gen_data(FILE*, symbol* );
void gen_interrupt(FILE*);
void gen_code(FILE*, quad* );


#endif