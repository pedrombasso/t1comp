%{
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"
#include "semantics.h"

extern int yylex();
extern int yyerror(char *s);
extern FILE *yyin;
extern int getLineNumber();

AST *ast_programa = NULL;
%}

%token KW_BYTE       
%token KW_INT        
%token KW_FLOAT      
%token KW_IF         
%token KW_THEN       
%token KW_ELSE       
%token KW_LOOP       
%token KW_LEAP       
%token KW_READ       
%token KW_RETURN     
%token KW_PRINT      
%token OPERATOR_LE   
%token OPERATOR_GE   
%token OPERATOR_EQ   
%token OPERATOR_DIF  
%token OPERATOR_OR   
%token OPERATOR_AND  
%token OPERATOR_NOT  
%token TOKEN_ERROR  
%token<symbol> TK_IDENTIFIER
%token<symbol> LIT_INTEGER
%token<symbol> LIT_FLOAT
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING 

%left OPERATOR_DIF OPERATOR_NOT OPERATOR_LE OPERATOR_GE OPERATOR_EQ 
%left '<' '>'
%left OPERATOR_AND OPERATOR_OR
%left '+' '-'
%left '*' '/'
%left '(' ')'

%union {
	HASH_NODE *symbol;
    AST *ast;
}

%type<ast> programa
%type<ast> listaDec
%type<ast> declaracao
%type<ast> DecVar
%type<ast> vetorInt
%type<ast> vetorFloat
%type<ast> vetorChar
%type<ast> DecFuncao
%type<ast> listaParam
%type<ast> bloco
%type<ast> listaComandos
%type<ast> comando
%type<ast> listaElementos
%type<ast> expressao
%type<ast> listaParamExpressao




%start programa


%% 


programa: listaDec					{ast_programa = $1;}
	|								{ast_programa= NULL;}
	;

listaDec: declaracao			{ $$ = astCreate(AST_DEC, 0, $1, 0, 0, 0); }
	|declaracao listaDec		{ $$ = astCreate(AST_LIST_DEC, 0, $1, $2, 0, 0); }
	
	;

declaracao: DecFuncao				{ $$ = astCreate(AST_DEC_FUNCAO, 0, $1, 0, 0, 0); }
	| DecVar						{ $$ = astCreate(AST_DEC_VAR, 0, $1, 0, 0, 0); }
	;

DecVar: KW_INT TK_IDENTIFIER '=' LIT_INTEGER ';'	{$$ = astCreate(AST_DEC_SIMPLES, 0, astCreate_son(AST_TIPO_INT), astCreate_symbol($2),	astCreate_symbol($4), 	NULL);}
	| KW_INT TK_IDENTIFIER '=' LIT_FLOAT ';' 		{$$ = astCreate(AST_DEC_SIMPLES, 0, astCreate_son(AST_TIPO_INT), astCreate_symbol($2),	astCreate_symbol($4), 	NULL);}
	| KW_INT TK_IDENTIFIER '=' LIT_CHAR ';' 		{$$ = astCreate(AST_DEC_SIMPLES, 0, astCreate_son(AST_TIPO_INT), astCreate_symbol($2),	astCreate_symbol($4), 	NULL);}
	| KW_FLOAT TK_IDENTIFIER '=' LIT_FLOAT ';'		{$$ = astCreate(AST_DEC_SIMPLES, 0, astCreate_son(AST_TIPO_FLOAT), astCreate_symbol($2),	astCreate_symbol($4), 	NULL);}	
	| KW_FLOAT TK_IDENTIFIER '=' LIT_CHAR ';'		{$$ = astCreate(AST_DEC_SIMPLES, 0, astCreate_son(AST_TIPO_FLOAT), astCreate_symbol($2),	astCreate_symbol($4), 	NULL);}		
	| KW_FLOAT TK_IDENTIFIER '=' LIT_INTEGER ';'		{$$ = astCreate(AST_DEC_SIMPLES, 0, astCreate_son(AST_TIPO_FLOAT), astCreate_symbol($2),	astCreate_symbol($4), 	NULL);}		
	| KW_BYTE TK_IDENTIFIER '=' LIT_INTEGER ';'			{$$ = astCreate(AST_DEC_SIMPLES, 0, astCreate_son(AST_TIPO_BYTE), astCreate_symbol($2),	astCreate_symbol($4), 	NULL);}		
	| KW_BYTE TK_IDENTIFIER '=' LIT_FLOAT ';'			{$$ = astCreate(AST_DEC_SIMPLES, 0, astCreate_son(AST_TIPO_BYTE), astCreate_symbol($2),	astCreate_symbol($4), 	NULL);}		
	| KW_BYTE TK_IDENTIFIER '=' LIT_CHAR ';'			{$$ = astCreate(AST_DEC_SIMPLES, 0, astCreate_son(AST_TIPO_BYTE), astCreate_symbol($2),	astCreate_symbol($4), 	NULL);}		
	| KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ';'		{$$ = astCreate(AST_DEC_VETOR_SIMPLES, 0, astCreate_son(AST_TIPO_INT), astCreate_symbol($2),	astCreate_symbol($4), 	NULL);}
	| KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']' ';'	{$$ = astCreate(AST_DEC_VETOR_SIMPLES, 0, astCreate_son(AST_TIPO_FLOAT), astCreate_symbol($2),	astCreate_symbol($4), 	NULL);}
	| KW_BYTE TK_IDENTIFIER '[' LIT_INTEGER ']' ';'		{$$ = astCreate(AST_DEC_VETOR_SIMPLES, 0, astCreate_son(AST_TIPO_BYTE), astCreate_symbol($2),	astCreate_symbol($4), 	NULL);}


	| KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' vetorInt ';'		{$$ = astCreate(AST_DEC_VETOR_COMPLETO, 0, astCreate_son(AST_TIPO_INT), astCreate_symbol($2),	astCreate_symbol($4), 	$7);}
	| KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' vetorFloat ';'	{$$ = astCreate(AST_DEC_VETOR_COMPLETO, 0, astCreate_son(AST_TIPO_INT), astCreate_symbol($2),	astCreate_symbol($4), 	$7);}
	| KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' vetorChar ';'	{$$ = astCreate(AST_DEC_VETOR_COMPLETO, 0, astCreate_son(AST_TIPO_INT), astCreate_symbol($2),	astCreate_symbol($4), 	$7);}
	| KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' vetorInt ';'	{$$ = astCreate(AST_DEC_VETOR_COMPLETO, 0, astCreate_son(AST_TIPO_FLOAT), astCreate_symbol($2),	astCreate_symbol($4), 	$7);}
	| KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' vetorFloat ';'	{$$ = astCreate(AST_DEC_VETOR_COMPLETO, 0, astCreate_son(AST_TIPO_FLOAT), astCreate_symbol($2),	astCreate_symbol($4), 	$7);}
	| KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' vetorChar ';'	{$$ = astCreate(AST_DEC_VETOR_COMPLETO, 0, astCreate_son(AST_TIPO_FLOAT), astCreate_symbol($2),	astCreate_symbol($4), 	$7);}

	| KW_BYTE TK_IDENTIFIER '[' LIT_INTEGER ']' ':' vetorInt ';'	{$$ = astCreate(AST_DEC_VETOR_COMPLETO, 0, astCreate_son(AST_TIPO_BYTE), astCreate_symbol($2),	astCreate_symbol($4), 	$7);}
	| KW_BYTE TK_IDENTIFIER '[' LIT_INTEGER ']' ':' vetorFloat ';'	{$$ = astCreate(AST_DEC_VETOR_COMPLETO, 0, astCreate_son(AST_TIPO_BYTE), astCreate_symbol($2),	astCreate_symbol($4), 	$7);}
	| KW_BYTE TK_IDENTIFIER '[' LIT_INTEGER ']' ':' vetorChar ';'	{$$ = astCreate(AST_DEC_VETOR_COMPLETO, 0, astCreate_son(AST_TIPO_BYTE), astCreate_symbol($2),	astCreate_symbol($4), 	$7);}
	;

vetorInt: LIT_INTEGER				{$$ = astCreate(50, 0, astCreate_symbol($1), NULL,0, 0);}
	| LIT_INTEGER vetorInt 			{$$ = astCreate(50, 0, astCreate_symbol($1), $2,0, 0	);}
	;

vetorFloat: LIT_FLOAT				{$$ = astCreate(50, 0, astCreate_symbol($1), NULL,0, 0);}
	| LIT_FLOAT vetorFloat 			{$$ = astCreate(50, 0, astCreate_symbol($1), $2,0, 0	);}	
	;

vetorChar: LIT_CHAR					{$$ = astCreate(50, 0, astCreate_symbol($1), NULL,0, 0);}
	| LIT_CHAR vetorChar 			{$$ = astCreate(50, 0, astCreate_symbol($1), $2,0, 0	);}
	;


DecFuncao: 	
	KW_INT TK_IDENTIFIER '(' listaParam ')'  bloco  ';'	{$$ = astCreate(AST_FUNCAO, 0, astCreate_son(AST_TIPO_INT), astCreate_symbol($2),$4, $6	);}
	| KW_FLOAT TK_IDENTIFIER '(' listaParam ')'  bloco  ';'	{$$ = astCreate(AST_FUNCAO, 0, astCreate_son(AST_TIPO_FLOAT), astCreate_symbol($2),$4, $6	);}
	| KW_BYTE TK_IDENTIFIER '(' listaParam ')'  bloco  ';'	{$$ = astCreate(AST_FUNCAO, 0, astCreate_son(AST_TIPO_BYTE), astCreate_symbol($2),$4, $6	);}
	;

listaParam:	KW_INT TK_IDENTIFIER 	{$$ = astCreate(AST_PARAMETRO, 0, astCreate_son(AST_TIPO_INT), astCreate_symbol($2),0, 0	);}	
	| KW_FLOAT TK_IDENTIFIER		{$$ = astCreate(AST_PARAMETRO, 0, astCreate_son(AST_TIPO_FLOAT), astCreate_symbol($2),0, 0	);}
	| KW_BYTE TK_IDENTIFIER			{$$ = astCreate(AST_PARAMETRO, 0, astCreate_son(AST_TIPO_BYTE), astCreate_symbol($2),0, 0	);}
	| KW_INT TK_IDENTIFIER	',' listaParam 			{$$ = astCreate(AST_PARAMETRO, 0, astCreate_son(AST_TIPO_INT), astCreate_symbol($2), $4 , 0	);}
	| KW_FLOAT TK_IDENTIFIER	',' listaParam   	{$$ = astCreate(AST_PARAMETRO, 0, astCreate_son(AST_TIPO_FLOAT), astCreate_symbol($2),$4, 0	);}
	| KW_BYTE TK_IDENTIFIER ',' listaParam   		{$$ = astCreate(AST_PARAMETRO, 0, astCreate_son(AST_TIPO_BYTE), astCreate_symbol($2), $4, 0	);}
	| {$$ = astCreate(AST_PARAMETRO, 0, NULL, 0, 0, 0);}
	;


bloco: '{' listaComandos '}' 	{ $$ = astCreate(AST_BLOCO, 0, $2, 0, 0, 0); }	
    ;

listaComandos: comando 			{ $$ = astCreate(AST_LISTA_COMANDO, 0, $1, 0, 0, 0); }
	| listaComandos ';' comando 	{ $$ = astCreate(AST_LISTA_COMANDO, 0, $1, $3, 0, 0); }
    ;

comando: TK_IDENTIFIER '=' expressao	{$$ = astCreate(AST_CMD_ATRIB, 0, astCreate_symbol($1), $3, NULL, NULL);}
	| TK_IDENTIFIER '[' expressao ']' '=' expressao 	{$$ = astCreate(AST_CMD_ATRIB_VETOR, 0, astCreate_symbol($1), $3, $6, NULL);}
	| bloco
    | KW_READ TK_IDENTIFIER			{$$ = astCreate(AST_CMD_READ, 0, astCreate_symbol($2), 0, 0, NULL);}
	| KW_PRINT listaElementos 		{$$ = astCreate(AST_CMD_PRINT, 0, $2, 0, NULL, NULL);}
	| KW_RETURN expressao 			{$$ = astCreate(AST_CMD_RETURN, 0, $2, 0, NULL, NULL);}
    | KW_LEAP			{$$ = astCreate(AST_CMD_LEAP, 0, NULL, NULL, NULL, NULL);}
    | KW_LOOP '(' expressao ')' comando 		{$$ = astCreate(AST_CMD_LOOP, 0, $3, $5, 0, NULL);}
    | KW_IF '(' expressao ')' KW_THEN comando 		{$$ = astCreate(AST_CMD_IF, 0, $3, $6, 0, NULL);}
	| KW_IF '(' expressao ')' KW_THEN comando KW_ELSE comando 	{$$ = astCreate(AST_CMD_IF, 0, $3, $6, $8, NULL);}
	| /* Comando Vazio */	{$$ = astCreate(AST_CMD_NOP, 0, NULL, NULL, NULL, NULL);}
	;


listaElementos: expressao 		{$$ = astCreate(AST_LISTA_ELEMENTOS, 0, $1, NULL, NULL, NULL);}
	| LIT_STRING 				{$$ = astCreate(AST_LISTA_ELEMENTOS, 0, astCreate_symbol($1), NULL, NULL, NULL);}
	|  LIT_STRING ',' listaElementos 	{$$ = astCreate(AST_LISTA_ELEMENTOS, 0, astCreate_symbol($1), $3, NULL, NULL);}
	| expressao ',' listaElementos 		{$$ = astCreate(AST_LISTA_ELEMENTOS, 0, $1, $3, NULL, NULL);}
    ;


expressao: '(' expressao ')' 	{$$ = astCreate(AST_PARENTESIS, 0, $2, NULL, NULL, NULL);}
	| LIT_INTEGER		{$$ = astCreate(AST_INT, 0, astCreate_symbol($1), NULL, NULL, NULL);}
	| LIT_FLOAT			{$$ = astCreate(AST_FLOAT, 0, astCreate_symbol($1), NULL, NULL, NULL);}
	| LIT_CHAR			{$$ = astCreate(AST_BYTE, 0, astCreate_symbol($1), NULL, NULL, NULL);}
	| TK_IDENTIFIER '(' listaParamExpressao ')' 	{$$ = astCreate(AST_TK, 0, astCreate_symbol($1), $3, NULL, NULL);}
	| TK_IDENTIFIER 			{$$ = astCreate(AST_TK, 0, astCreate_symbol($1), NULL, NULL, NULL);}
	| TK_IDENTIFIER '[' expressao ']' 		{$$ = astCreate(AST_TK_VET, 0, astCreate_symbol($1), $3, NULL, NULL);}
	| expressao '+' expressao 		{$$ = astCreate(AST_CMD_ADD, 0, $1, $3, NULL, NULL);}
	| expressao '-' expressao 		{$$ = astCreate(AST_CMD_SUB, 0, $1, $3, NULL, NULL);}
	| expressao '*' expressao 		{$$ = astCreate(AST_CMD_MUL, 0, $1, $3, NULL, NULL);}
	| expressao '/' expressao       {$$ = astCreate(AST_CMD_DIV, 0, $1, $3, NULL, NULL);}
	| expressao '<' expressao       {$$ = astCreate(AST_CMD_LT, 0, $1, $3, NULL, NULL);}
	| expressao '>' expressao       {$$ = astCreate(AST_CMD_GT, 0, $1, $3, NULL, NULL);}
	| expressao OPERATOR_AND expressao {$$ = astCreate(AST_CMD_AND, 0, $1, $3, NULL, NULL);}
	| expressao OPERATOR_OR expressao {$$ = astCreate(AST_CMD_OR, 0, $1, $3, NULL, NULL);}
	| expressao OPERATOR_NOT expressao {$$ = astCreate(AST_CMD_NOT, 0, $1, $3, NULL, NULL);}
	| expressao OPERATOR_LE expressao {$$ = astCreate(AST_CMD_LE, 0, $1, $3, NULL, NULL);}
	| expressao OPERATOR_GE expressao {$$ = astCreate(AST_CMD_GE, 0, $1, $3, NULL, NULL);}
	| expressao OPERATOR_EQ expressao {$$ = astCreate(AST_CMD_EQ, 0, $1, $3, NULL, NULL);}
	| expressao OPERATOR_DIF expressao {$$ = astCreate(AST_CMD_DIF, 0, $1, $3, NULL, NULL);}
	| OPERATOR_NOT expressao  {$$ = astCreate(AST_CMD_OP_NOT, 0, $2, 0, NULL, NULL);}
	;

listaParamExpressao: expressao  		{$$ = astCreate(AST_LISTA_PARAM_EXP, 0, $1, NULL, NULL, NULL);}
	| expressao ',' listaParamExpressao		{$$ = astCreate(AST_LISTA_PARAM_EXP, 0, $1, $3, NULL, NULL);}
	| /* Nada */  		{$$ = astCreate(AST_CMD_NOP, 0, NULL, NULL, NULL, NULL);}
	;



%%

int yyerror(char *s){
	fprintf(stderr, "Erro na linha %d: %s\n", getLineNumber(), s);
	exit(3);
}
