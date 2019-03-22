%{
	#include "tokens.h"
	#include "hash.c"
	
	int Running = 1;
	int LineNumber = 1;
%}

%x COMMENT

%%

"if"			{return KW_IF;}
"int"			{return KW_INT;}
[0-9]+			{hashInsert(0 , yytext); return LIT_INTEGER;}
[A-Za-z]+		{hashInsert(0 , yytext); return TK_IDENTIFIER;}
[-+*/();.<>=]	{return yytext[0];}
"]"				{return yytext[0];}
"["				{return yytext[0];}
"\n"				{++LineNumber;}
[\t]		
"//".*		
"/*"			{BEGIN(COMMENT);}


<COMMENT>"*/"	{BEGIN(INITIAL);}
<COMMENT>.
<COMMENT>"\n"	{++LineNumber;}

%%


int yywrap()
{
	Running = 0;
	return 1;
}
