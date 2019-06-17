#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//extern char* yytext;

void hashInit(void)
{
	int i;
	for(i=0; i < HASH_SIZE; ++i)
	{
		Table[i] = 0;
	}
}

int hashAddress(char *text)
{
	int address = 1;
	int i;
	for (i=0; i<strlen(text); ++i)
	{
		address = (address*text[i]) % HASH_SIZE + 1;
	}
	return address -1;
}

HASH_NODE* hashInsert(int type, char *text)
{
	HASH_NODE *newNode;
	int address = hashAddress(text);

	if((newNode = hashFind(text)) != 0)
		return newNode;

	newNode = (HASH_NODE*)calloc(1, sizeof(HASH_NODE));
	newNode->type = type;

	newNode->dataType.identifierType = -1;
	newNode->dataType.valueType = -1;
	newNode->dataType.params = NULL;


	newNode->text = calloc(strlen(yytext) + 1, sizeof(char));
	strcpy(newNode->text, text);
	newNode->next = Table[address];
	Table[address] = newNode;
	return newNode;
}

HASH_NODE* hashFind(char *text)
{
	int address = hashAddress(text);
	HASH_NODE* node;
	for(node=Table[address]; node; node=node->next)
	{
		if(strcmp(text, node->text) == 0)
			return node;
	}
	return 0;
}

void hashPrint(void)
{
	int i;
	HASH_NODE* node;
	for (i=0; i<HASH_SIZE; ++i)
	{
		for (node=Table[i]; node; node=node->next)
			fprintf(stderr, "Table[%d] has %s\n", i, node->text);
	}
}

int hashUpdateType(char * text, ID_TYPE idType, VAL_TYPE valType, PARAM_LIST *params, int length)
{
    int i;
    HASH_NODE *node;
    for(i=0; i<HASH_SIZE; i++)
      for(node = Table[i]; node; node=node->next)
        if(!strcmp(node->text,text))
    			if(node->dataType.identifierType == -1)
    			{
    				node->dataType.identifierType = idType;
    				node->dataType.valueType = valType;
            		node->dataType.params = params;
            		node->dataType.paramsLength = length;
    				return 1;
    			}
    			else
    				return 0;
    return 0;
}

