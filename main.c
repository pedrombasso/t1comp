#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "hash.h"

extern int running;
extern int lineNumber;
int yylex();
extern char* yytext;
extern FILE *yyin;

int isRunning(void);
int getLineNumber(void);
void initMe(void);

int main (int argc, char **argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "Call: ./a.out filename\n");
		exit(1);
	}
	if((yyin = fopen(argv [1], "r")) == 0)
	{
		fprintf(stderr, "Cannot open file\n");
		exit(2);
	}
	initMe();
	int tok = 0;
	while (running)
	{
		tok = yylex();
		if(!isRunning) break;
		
		fprintf(stdout, "%s: ", yytext);
		switch(tok)
		{
			case KW_BYTE: fprintf(stdout, "KW_BYTE \n"); break;
			case KW_INT: fprintf(stdout, "KW_INT \n"); break;
			case KW_FLOAT: fprintf(stdout, "KW_FLOAT \n"); break;
			case KW_IF: fprintf(stdout, "KW_IF \n" ); break;
			case KW_THEN: fprintf(stdout, "KW_THEN \n"); break;	
			case KW_ELSE: fprintf(stdout, "KW_ELSE \n"); break;
			case KW_LOOP: fprintf(stdout, "KW_LOOP \n"); break;
			case KW_LEAP: fprintf(stdout, "KW_LEAP \n"); break;
			case OPERATOR_OR: fprintf(stdout, "OPERATOR_OR \n"); break;	
			case OPERATOR_AND: fprintf(stdout, "OPERATOR_AND \n"); break;
			case OPERATOR_NOT: fprintf(stdout, "OPERATOR_NOT \n"); break;
			case KW_READ: fprintf(stdout, "KW_READ \n"); break;
			case KW_PRINT: fprintf(stdout, "KW_PRINT \n"); break;
			case KW_RETURN: fprintf(stdout, "KW_RETURN \n"); break;
			case OPERATOR_LE: fprintf(stdout, "OPERATOR_LE \n"); break;
			case OPERATOR_GE: fprintf(stdout, "OPERATOR_GE \n"); break;
			case OPERATOR_EQ: fprintf(stdout, "OPERATOR_EQ \n"); break;	
			case OPERATOR_DIF: fprintf(stdout, "OPERATOR_DIF \n"); break;	
			case TOKEN_ERROR: fprintf(stdout, "TOKEN_ERROR \n"); break;
			case TK_IDENTIFIER: fprintf(stdout, "TK_IDENTIFIER \n"); break;
			case LIT_INTEGER: fprintf(stdout, "LIT_INTEGER \n"); break;
			case LIT_FLOAT: fprintf(stdout, "LIT_FLOAT \n"); break;
			case LIT_CHAR: fprintf(stdout, "LIT_CHAR \n"); break;
			case LIT_STRING: fprintf(stdout, "LIT_STRING \n"); break;
			default: fprintf(stdout, "DEFAULT: %d \n", tok); break;
		}
	}
hashPrint();
}
	
