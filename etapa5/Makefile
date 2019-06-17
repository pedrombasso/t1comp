
etapa4: y.tab.o lex.yy.o hash.o ast.o semantic.o main.o 
	gcc -o etapa4 lex.yy.o y.tab.o hash.o ast.o semantic.o main.o -Wall
main.o: main.c
	gcc -c main.c -Wall
semantic.o: semantic.c
	gcc -c semantic.c -Wall
ast.o:	ast.c
	gcc -c ast.c -Wall
hash.o: hash.c
	gcc -c hash.c -Wall
y.tab.o: y.tab.c
	gcc -c y.tab.c -Wall
y.tab.c: parser.y
	bison -y -d -v parser.y
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l 
clean:
	rm *.o lex.yy.c lex.yy.h y.tab.c y.tab.h y.output etapa4 
