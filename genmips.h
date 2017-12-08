#ifndef __GENMIPS_H__
#define __GENMIPS_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "symbol.h"
#include "quad.h"

void gen_code(FILE*, quad* );
void gen_data(FILE*, symbol* );


#endif