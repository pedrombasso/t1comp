etapa3: lex.yy.o main.o hash.o y.tab.o ast.o 
	gcc -o etapa3 lex.yy.o main.o hash.o ast.o  y.tab.o

ast.o : ast.c
	gcc -c ast.c

main.o: main.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
lex.yy.o: parser.y scanner.l
	yacc -d -v parser.y
	lex --header-file=lex.yy.h scanner.l 
	gcc -c lex.yy.c y.tab.c
clean:
	rm -f *.o lex.yy.* y.tab.*  etapa3 y.output
