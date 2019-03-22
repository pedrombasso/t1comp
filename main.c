#include <stdio.h>
#include <stdlib.h>

extern int Running;
extern int LineNumber;
extern int yylex();
extern FILE *yyin;
#include "tokens.h"
#include "hash.h"
//#include "lex.yy.h"
int main(int argc, char **argv)
{	
	if (argc < 2)
	{
		fprintf(stderr, "Call: ./a.out fileName\n");
		exit(1);
	}
	if ((yyin = fopen(argv[1], "r")) == 0)
	{
		fprintf(stderr, "Cannot open file \"%s\"\n",argv[1] );
		exit(2);
	}
	
	hashInit();
	int tok = 0;
	
	while(Running)
	{
		tok = yylex();
		if(!Running) break;
		switch(tok)
		{
			case KW_IF: fprintf(stdout, "KW_IF "); break;
			case KW_INT: fprintf(stdout, "KW_INT "); break;
			case LIT_INTEGER: fprintf(stdout, "LIT_INTEGER "); break;
			case TK_IDENTIFIER: fprintf(stdout, "IDENTIFIER "); break;
			default: fprintf(stdout, "TOKEN<%c> at line %d",tok,LineNumber );
		
		}
	}
	hashPrint();
	exit(0);

}