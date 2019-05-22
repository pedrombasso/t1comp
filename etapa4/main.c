#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"
#include "y.tab.h"



FILE *yyin;
void initMe(void);
int yyparse (void);
int getLineNumber(void);
void show();
extern AST *ast_programa;
FILE* outfile;

int main(int argc, char* argv[]){
	
	if (argc > 2 && (yyin = fopen(argv[1], "r")) && (outfile = fopen(argv[2], "w"))){
        initMe();
		if(yyparse() == 0){
			printf("Sucess, this is a program!\nLines: %d\n", getLineNumber());
			hashPrint();
			astPrint(ast_programa,0);
			decompile(ast_programa, outfile);
            exit(0);
			
		}
    }
    
	exit(3);
}
