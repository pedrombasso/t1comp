
etapa1: main.o lex.yy.o 
	gcc lex.yy.o main.o  -o etapa1 
main.o: main.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	lex scanner.l 
clean:
	rm *.o etapa1
