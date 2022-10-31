TARGET = a.out
OBJECT = lex.yy.o symboltable.o 
CC = g++
LEX = flex
LIBS = -ll 

a.out: lex.yy.c
	$(CC) lex.yy.c $(LIBS)

lex.yy.c: test.l
	$(LEX) test.l

clean:
	rm -f $(TARGET) $(OBJECT) 

