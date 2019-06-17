#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantics_types.h"

#define HASH_SIZE 997
#define SYMBOL_LITERAL_INT 1
#define SYMBOL_LITERAL_REAL 2
#define SYMBOL_LITERAL_CHAR 3
#define SYMBOL_LITERAL_STRING 4
#define SYMBOL_IDENTIFIER 7

extern char *yytext;

typedef struct hash_node
{
	int type;
	char *text;
	struct hash_node *next;
	DATA_TYPE dataType;
} HASH_NODE;



HASH_NODE *Table[HASH_SIZE];
void hashInit(void);
void hashPrint(void);
HASH_NODE* hashInsert(int type, char *text);
HASH_NODE* hashFind(char *text);
int hashAddress(char *text);
int hashUpdateType(char * text, ID_TYPE idType, VAL_TYPE valType, PARAM_LIST *params, int length); // Retorna 1 se dataType é atualizado, 0 se contrário

#endif