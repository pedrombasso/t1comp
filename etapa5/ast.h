
#ifndef AST_HEADER
#define AST_HEADER

#include <stdio.h>
#include "hash.h"


#define MAX_SONS 4

#define AST_TK_IDENTIFIER       1
#define AST_DEC_VAR     		2
#define AST_DEC_VETOR     		3
#define AST_DEC_FUNCAO    		4

#define AST_LIT_INTEGER         5
#define AST_LIT_FLOAT           6
#define AST_LIT_CHAR            7
#define AST_LIT_STRING          8


#define AST_TIPO_BYTE       	9
#define AST_TIPO_FLOAT      	10
#define AST_TIPO_INT        	11

#define AST_VETOR              	12
#define AST_FUNCAO            	13

#define AST_CMD_ADD             14
#define AST_CMD_SUB             15
#define AST_CMD_MUL             16
#define AST_CMD_DIV             17
#define AST_CMD_DIF             18
#define AST_CMD_EQ              19
#define AST_CMD_GE              20
#define AST_CMD_LE              21
#define AST_CMD_GT              22   
#define AST_CMD_LT              23    
#define AST_CMD_AND             24
#define AST_CMD_OR              25
#define AST_CMD_NOT             26
#define AST_CMD_READ            27
#define AST_CMD_PRINT           28
#define AST_CMD_RETURN          29
#define AST_CMD_IF              30
#define AST_CMD_IF_ELSE         31
#define AST_CMD_LEAP            32
#define AST_CMD_LOOP            33

#define AST_PARAMETROS_FUNCAO   34
#define AST_LIST_DEC            35
#define AST_LISTAVALOR          36
#define AST_LISTA_PARAMETRO     37
#define AST_BLOCO               38
#define AST_LISTA_COMANDO       39
#define AST_COMANDORESTO        40
#define AST_CMD_ATRIB           41
#define AST_CMD_ATRIB_VETOR     42
#define AST_LISTA_PARAM_EXP_RESTO   43
#define AST_LISTA_PARAM_EXP         44
#define AST_PARAMRESTO          	45
#define AST_DEC_VETOR_COMPLETO		46




typedef struct astnode{
    int type;
    int datatype;
    hashNode *symbol;
    struct astnode* son[MAX_SONS];
    int lineNumber;
} AST;



AST *astCreate(int type, hashNode *symbol_node, AST *s0, AST *s1, AST *s2, AST *s3);
void astPrint(AST *node, int level);
void decompile(AST *node, FILE *out);
void closeFile(FILE *code);

#endif