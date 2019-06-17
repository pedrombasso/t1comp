#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



#define HASHSIZE 997

#define NO_DATATYPE             0
#define DATATYPE_BYTE           1
#define DATATYPE_INT            2
#define DATATYPE_FLOAT          3
#define DATATYPE_BYTE_VEC       4
#define DATATYPE_INT_VEC        5
#define DATATYPE_FLOAT_VEC      6
#define DATATYPE_BYTE_FUN       7
#define DATATYPE_INT_FUN        8
#define DATATYPE_FLOAT_FUN      9
#define DATATYPE_BOOL           10
#define DATATYPE_STRING         11

typedef struct hashnode{
	int type;
	int datatype;	
	char *lit;
	struct hashnode *next;
	bool dec;
}hashNode;

hashNode *HashTable[HASHSIZE];

extern char *yytext;

void initMe(void);
int hashAddress(char *lit);
hashNode* hashInsert(int type, char *text);
void hashPrint(void);
hashNode* hashFind(char *text);
bool hashNaoDeclarado(void);


#endif