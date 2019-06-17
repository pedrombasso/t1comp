#ifndef AST_HEADER
#define AST_HEADER

#include "hash.h"
#define MAX_SONS 4
#define T_TOKEN_ERROR "ERRO"

typedef int TREE_TYPE;

#define SYMBOL 			0
#define PROGRAMA 		1

#define AST_DEC			2 
#define AST_DEC_FUNCAO 	3
#define AST_DEC_VAR 	4
#define AST_DEC_SIMPLES 5 
#define AST_DEC_VETOR_SIMPLES 6 
#define AST_DEC_VETOR_COMPLETO 7 

#define AST_TIPO_INT 	8
#define AST_TIPO_FLOAT 9
#define AST_TIPO_BYTE 10


#define	AST_LIST_DEC 	11
#define AST_LISTA_PARAMETRO 12
#define AST_FUNCAO 13
#define AST_BLOCO 14
#define AST_LISTA 15
#define AST_CMD_LEAP 16
#define AST_LISTA_COMANDO 17
#define AST_CMD_NOP 18
#define AST_PARAMETRO 19
#define AST_CMD_ATRIB 20
#define AST_INT 21
#define AST_FLOAT 22
#define AST_BYTE 23
#define AST_CMD_ATRIB_VETOR 24
#define AST_CMD_READ 25
#define AST_CMD_RETURN 26
#define AST_CMD_LOOP 27
#define AST_CMD_IF 28
#define AST_LISTA_ELEMENTOS 29
#define AST_STRING 30
#define AST_CMD_PRINT 31
#define AST_PARENTESIS 32
#define AST_TK 33
#define AST_TK_VET 34
#define AST_CMD_ADD 35
#define AST_CMD_SUB 36
#define AST_CMD_MUL 37
#define AST_CMD_DIV 38
#define AST_CMD_LT 39
#define AST_CMD_GT 40
#define AST_CMD_AND 41
#define AST_CMD_OR 42
#define AST_CMD_NOT 43
#define AST_CMD_LE 44
#define AST_CMD_GE 45
#define AST_CMD_EQ 46
#define AST_CMD_DIF 47
#define AST_CMD_OP_NOT 48
#define AST_LISTA_PARAM_EXP 49
#define AST_LISTA_DEC 50

typedef struct ast_node{
	
	struct ast_node *son[MAX_SONS];
	TREE_TYPE type;
	HASH_NODE* symbol;
} AST;

AST* astCreate(int type, HASH_NODE* symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void astPrint(AST* node, int level);
AST* astCreate_son(int type);
AST* astCreate_symbol(HASH_NODE* hash_symbol);
void decompile(AST *node, FILE* outfile);

#endif