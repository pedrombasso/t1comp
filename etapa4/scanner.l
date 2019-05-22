
%{
#include "hash.h"
#include "ast.h"
#include "y.tab.h"
  

int lineNumber = 1;
int running = 1; 

%}


%x BLOCK_COMMENT 

%%
"byte"				        { return KW_BYTE; }
"int"				        { return KW_INT; }
"float"				        { return KW_FLOAT; }
"if"				        { return KW_IF; }
"then"				        { return KW_THEN; }
"else"				        { return KW_ELSE; }
"loop"				        { return KW_LOOP; }
"leap"				        { return KW_LEAP; }
"read"				        { return KW_READ; }
"print"			        	{ return KW_PRINT; }
"return"        			{ return KW_RETURN; }
"<="			        	{ return OPERATOR_LE; }
">="        				{ return OPERATOR_GE; }
"=="	        			{ return OPERATOR_EQ; }
"!="		        		{ return OPERATOR_DIF; }
"or"		        		{ return OPERATOR_OR; }
"and"		        		{ return OPERATOR_AND; }
"not"		        		{ return OPERATOR_NOT; }
" "
""
"\t"
"\n"				        { lineNumber++; }
[,;!@:()+-/}{*/<>=&$#]		{ return yytext[0]; }
"["					        { return yytext[0]; }
"]"					        { return yytext[0]; }
([a-z0-9]|_)+			    { yylval.symbol = hashInsert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER; }
[OIHGFEDCBA]+			    { yylval.symbol = hashInsert(LIT_INTEGER, yytext); return LIT_INTEGER; }
[OIHGFEDCBA]+"."[OIHGFEDCBA]+		{ yylval.symbol = hashInsert(LIT_FLOAT, yytext); return LIT_FLOAT; }		
['].[']				        { yylval.symbol = hashInsert(LIT_CHAR, yytext); return LIT_CHAR; }
\"(\\.|[^\\"])*\"			{ yylval.symbol = hashInsert(LIT_STRING, yytext); return LIT_STRING; }
"ZZ".*				
"XXX"			            { BEGIN(BLOCK_COMMENT); }
<BLOCK_COMMENT>"XXX"	    { BEGIN(INITIAL); }
<BLOCK_COMMENT>.
<BLOCK_COMMENT>"\n"		    { lineNumber++; }
.				            { return TOKEN_ERROR; }

%%

int yywrap()
{
	running = 0;
	return 1;
}

int getLineNumber(void)
{
	return lineNumber;
}

int isRunning(void)
{
	return running;
}

void initMe(void)
{
	hashInit();
}



