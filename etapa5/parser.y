%{
#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"
extern int getLineNumber();

void yyerror(char *msg);
int yylex();

FILE *out = NULL;
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
%token <symbol> TK_IDENTIFIER
%token <symbol> LIT_INTEGER
%token <symbol> LIT_FLOAT  
%token <symbol> LIT_CHAR 
%token <symbol> LIT_STRING
%token TOKEN_ERROR

%union{
    struct hashnode *symbol;
    struct astnode *ast;
}

%left OPERATOR_OR
%left OPERATOR_AND
%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF OPERATOR_NOT '<' '>'
%left '+' '-'
%left '*' '/'
%left '(' ')'

%type <ast> programa 
%type <ast> listaDec 
%type <ast> dec 
%type <ast> listaParam 
%type <ast> param 
%type <ast> paramFinal 
%type <ast> bloco 
%type <ast> listaComandos 
%type <ast> comando 
%type <ast> comandoFinal 
%type <ast> expressao 
%type <ast> listaParamExpressao 
%type <ast> listaParamExpressaoFinal 
%type <ast> valor 
%type <ast> listaValor 




%type <ast> atrib
%%

programa    : listaDec                                                       {$$ = $1;astPrint($1, 0); decompile($1, out); checarDeclaracao($1); checarNaoDeclarado(); checarOperandos($1);}
            ;

listaDec     : dec listaDec                                                   {$$ = astCreate(AST_LIST_DEC, 0, $1, $2, 0, 0);}
            |                                                               {$$ = 0;}
            ;

dec         : KW_BYTE TK_IDENTIFIER '=' valor                             ';' {$$ = astCreate(AST_DEC_VAR, $2, astCreate(AST_TIPO_BYTE, 0, 0, 0, 0, 0), $4, 0, 0);}
            | KW_BYTE TK_IDENTIFIER '[' LIT_INTEGER ']'                 ';' {$$ = astCreate(AST_DEC_VETOR, $2, astCreate(AST_TIPO_BYTE, 0, 0, 0, 0, 0), astCreate(AST_LIT_INTEGER, $4, 0, 0, 0, 0), 0, 0);}
            | KW_BYTE TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listaValor     ';' {$$ = astCreate(AST_DEC_VETOR_COMPLETO, $2, astCreate(AST_TIPO_BYTE, 0, 0, 0, 0, 0), astCreate(AST_LIT_INTEGER, $4, 0, 0, 0, 0), $7, 0);}
            | KW_BYTE TK_IDENTIFIER '(' listaParam ')' bloco             ';' {$$ = astCreate(AST_DEC_FUNCAO, $2, astCreate(AST_TIPO_BYTE, 0, 0, 0, 0, 0), $4, $6, 0);}
            | KW_INT TK_IDENTIFIER '=' valor                              ';' {$$ = astCreate(AST_DEC_VAR, $2, astCreate(AST_TIPO_INT, 0, 0, 0, 0, 0), $4, 0, 0);}
            | KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']'                  ';' {$$ = astCreate(AST_DEC_VETOR, $2, astCreate(AST_TIPO_INT, 0, 0, 0, 0, 0), astCreate(AST_LIT_INTEGER, $4, 0, 0, 0, 0), 0, 0);}
            | KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listaValor      ';' {$$ = astCreate(AST_DEC_VETOR_COMPLETO, $2, astCreate(AST_TIPO_INT, 0, 0, 0, 0, 0), astCreate(AST_LIT_INTEGER, $4, 0, 0, 0, 0), $7, 0);}
            | KW_INT TK_IDENTIFIER '(' listaParam ')' bloco              ';' {$$ = astCreate(AST_DEC_FUNCAO, $2, astCreate(AST_TIPO_INT, 0, 0, 0, 0, 0), $4, $6, 0);}
            | KW_FLOAT TK_IDENTIFIER '=' valor                            ';' {$$ = astCreate(AST_DEC_VAR, $2, astCreate(AST_TIPO_FLOAT, 0, 0, 0, 0, 0), $4, 0, 0);}
            | KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']'                ';' {$$ = astCreate(AST_DEC_VETOR, $2, astCreate(AST_TIPO_FLOAT, 0, 0, 0, 0, 0), astCreate(AST_LIT_INTEGER, $4, 0, 0, 0, 0), 0, 0);}
            | KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listaValor    ';' {$$ = astCreate(AST_DEC_VETOR_COMPLETO, $2, astCreate(AST_TIPO_FLOAT, 0, 0, 0, 0, 0), astCreate(AST_LIT_INTEGER, $4, 0, 0, 0, 0), $7, 0);}
            | KW_FLOAT TK_IDENTIFIER '(' listaParam ')' bloco            ';' {$$ = astCreate(AST_DEC_FUNCAO, $2, astCreate(AST_TIPO_FLOAT, 0, 0, 0, 0, 0), $4, $6, 0);}
            ;

listaValor     : valor listaValor                   {$$ = astCreate(AST_LISTAVALOR, 0, $1, $2, 0, 0);}
            |                               {$$ = 0;}
            ;

valor         : LIT_INTEGER                   {$$ = astCreate(AST_LIT_INTEGER, $1, 0, 0, 0, 0);}
            | LIT_FLOAT                     {$$ = astCreate(AST_LIT_FLOAT, $1, 0, 0, 0, 0);}
            | LIT_CHAR                      {$$ = astCreate(AST_LIT_CHAR, $1, 0, 0, 0, 0);}
            ;

expressao        : LIT_INTEGER                   {$$ = astCreate(AST_LIT_INTEGER, $1, 0, 0, 0, 0);}
            | LIT_FLOAT                     {$$ = astCreate(AST_LIT_FLOAT, $1, 0, 0, 0, 0);}
            | LIT_CHAR                      {$$ = astCreate(AST_LIT_CHAR, $1, 0, 0, 0, 0);}
            | LIT_STRING                    {$$ = astCreate(AST_LIT_STRING, $1, 0, 0, 0, 0);}
            | TK_IDENTIFIER                 {$$ = astCreate(AST_TK_IDENTIFIER, $1, 0, 0, 0, 0);}
            | TK_IDENTIFIER '[' expressao ']'    {$$ = astCreate(AST_VETOR, $1, $3, 0, 0, 0);}
            | TK_IDENTIFIER '(' listaParamExpressao ')' {$$ = astCreate(AST_FUNCAO, $1, $3, 0, 0, 0);}
            | '(' expressao ')'                  {$$ = $2;}
            | expressao '+' expressao                 {$$ = astCreate(AST_CMD_ADD, 0, $1, $3, 0, 0);}
            | expressao '-' expressao                 {$$ = astCreate(AST_CMD_SUB, 0, $1, $3, 0, 0);}
            | expressao '*' expressao                 {$$ = astCreate(AST_CMD_MUL, 0, $1, $3, 0, 0);}
            | expressao '/' expressao                 {$$ = astCreate(AST_CMD_DIV, 0, $1, $3, 0, 0);}
            | expressao OPERATOR_AND expressao        {$$ = astCreate(AST_CMD_AND, 0, $1, $3, 0, 0);}
            | expressao OPERATOR_OR expressao         {$$ = astCreate(AST_CMD_OR, 0, $1, $3, 0, 0);}
            | expressao OPERATOR_DIF expressao        {$$ = astCreate(AST_CMD_DIF, 0, $1, $3, 0, 0);}
            | expressao OPERATOR_EQ expressao         {$$ = astCreate(AST_CMD_EQ, 0, $1, $3, 0, 0);}
            | expressao OPERATOR_GE expressao         {$$ = astCreate(AST_CMD_GE, 0, $1, $3, 0, 0);}
            | expressao OPERATOR_LE expressao         {$$ = astCreate(AST_CMD_LE, 0, $1, $3, 0, 0);}
            | expressao '>' expressao                 {$$ = astCreate(AST_CMD_GT, 0, $1, $3, 0, 0);}
            | expressao '<' expressao                 {$$ = astCreate(AST_CMD_LT, 0, $1, $3, 0, 0);}
            | OPERATOR_NOT expressao             {$$ = astCreate(AST_CMD_NOT, 0, $2, 0, 0, 0);}
            ;

listaParam   : param paramFinal              {$$ = astCreate(AST_LISTA_PARAMETRO, 0, $1, $2, 0, 0);}
            ;

param       : KW_BYTE TK_IDENTIFIER         {$$ = astCreate(AST_PARAMETROS_FUNCAO, $2, astCreate(AST_TIPO_BYTE, 0, 0, 0, 0, 0), 0, 0, 0);}
            | KW_FLOAT TK_IDENTIFIER        {$$ = astCreate(AST_PARAMETROS_FUNCAO, $2, astCreate(AST_TIPO_FLOAT, 0, 0, 0, 0, 0), 0, 0, 0);}
            | KW_INT TK_IDENTIFIER          {$$ = astCreate(AST_PARAMETROS_FUNCAO, $2, astCreate(AST_TIPO_INT, 0, 0, 0, 0, 0), 0, 0, 0);}
            |                               {$$ = 0;}
            ;
            
paramFinal  : ',' param paramFinal          {$$ = astCreate(AST_PARAMRESTO, 0, $2, $3, 0, 0);}
            |                               {$$ = 0;}
            ;


bloco       : '{' listaComandos '}'               {$$ = astCreate(AST_BLOCO, 0, $2, 0, 0, 0);}
            ;

listaComandos     : comando comandoFinal                  {$$ = astCreate(AST_LISTA_COMANDO, 0, $1, $2, 0, 0);}
            ;

comando         : KW_READ TK_IDENTIFIER                         {$$ = astCreate(AST_CMD_READ, $2, 0, 0, 0, 0);}
            | KW_PRINT listaParamExpressao                              {$$ = astCreate(AST_CMD_PRINT, 0, $2, 0, 0, 0);}
            | KW_RETURN expressao                                {$$ = astCreate(AST_CMD_RETURN, 0, $2, 0, 0, 0);}
            | KW_IF '(' expressao ')' KW_THEN comando                {$$ = astCreate(AST_CMD_IF, 0, $3, $6, 0, 0);}
            | KW_IF '(' expressao ')' KW_THEN comando KW_ELSE comando    {$$ = astCreate(AST_CMD_IF_ELSE, 0, $3, $6, $8, 0);}
            | KW_LEAP                                       {$$ = astCreate(AST_CMD_LEAP, 0, 0, 0, 0, 0);}
            | KW_LOOP '(' expressao ')' comando                      {$$ = astCreate(AST_CMD_LOOP, 0, $3, $5, 0, 0);}
            | bloco                                         {$$ = $1;}
            | atrib                                         {$$ = $1;}    
            |                                               {$$ = 0;}
            ;

comandoFinal    : ';' comando comandoFinal                              {$$ = astCreate(AST_COMANDORESTO, 0, $2, $3, 0, 0);}
            |                                               {$$ = 0;}
            ;

atrib       : TK_IDENTIFIER '=' expressao                        {$$ = astCreate(AST_CMD_ATRIB, $1, $3, 0, 0, 0);}
            | TK_IDENTIFIER '[' expressao ']' '=' expressao           {$$ = astCreate(AST_CMD_ATRIB_VETOR, $1, $3, $6, 0, 0);}
            ;

listaParamExpressao     : expressao listaParamExpressaoFinal                                 {$$ = astCreate(AST_LISTA_PARAM_EXP, 0, $1, $2, 0, 0);}
            |                                               {$$ = 0;}
            ;

listaParamExpressaoFinal    : ',' expressao listaParamExpressaoFinal                             {$$ = astCreate(AST_LISTA_PARAM_EXP_RESTO, 0, $2, $3, 0, 0);}
            |                                               {$$ = 0;}
            ;

%%

void yyerror(char *msg){
    fprintf(stderr, "%s on line: %d\n", msg, getLineNumber());
    exit(3);
}
