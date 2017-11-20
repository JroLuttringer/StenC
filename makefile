CC = gcc
LEX = lex
YACC = bison -d
CFLAGS = -O2 -Wall -Wconflicts-sr 
LDFLAGS = -ly -lfl  # Linux: -lfl / OSX: -ll
EXEC = stenc
SRC = 
OBJ = $(SRC:.c=.o)

all: $(OBJ) stenc.tab.c lex.yy.c
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

stenc.tab.c: $(EXEC).y
	$(YACC) $(EXEC).y

lex.yy.c: $(EXEC).l
	$(LEX) $(EXEC).l

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm $(EXEC) *.o stenc.tab.c stenc.tab.h lex.yy.c
