#include "ast.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>



int isRunning(void);
void printLineNumber(void);
int getLineNumber(void);

extern int yylex();
extern int yyparse();
extern char *yytext;
extern FILE *yyin;
extern FILE *out;
extern bool erroSemantico;


int main(int argc, char** argv){
	initMe();

	if(argc < 3){
		exit(1);	
	}
	
	if((yyin = fopen(argv[1], "r"))==0){
		exit(2);
	}

	if((out = fopen(argv[2], "w+"))==0){
		exit(1);
	}

	while(isRunning()){
		yyparse();

		if(erroSemantico == false)
			printf("Programa valido! \n");
		else{
			printf("Programa tem erros semanticos! \n");
			exit(4);
		}
	}
		
	hashPrint();
	exit(0);
}

void printLineNumber(){	
	printf("\nLinha %d :", getLineNumber());
}

