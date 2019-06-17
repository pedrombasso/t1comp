#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"
#include "y.tab.h"
#include "semantics.h"



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
			
			printf("$$$$$$$$$$$$$$$$$ SEMANTICS $$$$$$$$$$$$$$$$$$");
            semanticsCheckVariables(ast_programa);
            
         	semanticsCheckType(ast_programa);

            if(semanticFailure)
            {
                printf("Compilation failed due to semantic errors.\n");
                exit(4);
            }
            else
            	printf("No semantic errors.\n");

            // decompile(ast_programa, outfile);

           
			
		}
		else{
			printf("File does not exist!\n");
             exit(2);
        }
	}
	else {
        printf("File not informed!\nUsage: ./etapa4 input_filepath\n");
        exit(1);       	
    }
    
	
 exit(0);	
}
