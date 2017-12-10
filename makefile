CC = gcc
LEX = lex
YACC = yacc -d 
CFLAGS = -O2 -Wall
LDFLAGS = -ly -lfl -Iinclude # Linux: -lfl / OSX: -ll
EXEC = stenc
SRC = src/quad.c src/symbol.c src/genmips.c src/quad_list.c src/int_list.c
OBJ = $(SRC:.c=.o)

all: $(OBJ) y.tab.c lex.yy.c
	$(CC) -g -o $(EXEC) $^ $(LDFLAGS)
	mv $(EXEC) bin/
	mv src/*.o obj/
	
y.tab.c: $(EXEC).y
	$(YACC) $(EXEC).y


lex.yy.c: $(EXEC).l
	$(LEX) $(EXEC).l


%.o: %.c
	$(CC) -g -o $@ -c $< $(CFLAGS)
	
		


clean:
	rm bin/$(EXEC) obj/*.o y.tab.c y.tab.h lex.yy.c
