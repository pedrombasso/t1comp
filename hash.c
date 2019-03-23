#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* yytext;

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

NODE* hashInsert(int type, char *text)
{
	NODE *newNode;
	int address = hashAddress(text);

	if((newNode = hashFind(text)) != 0)
		return newNode;

	newNode = (NODE*)calloc(1, sizeof(NODE));
	newNode->type = type;
	newNode->text = calloc(strlen(yytext) + 1, sizeof(char));
	strcpy(newNode->text, text);
	newNode->next = Table[address];
	Table[address] = newNode;
}

NODE* hashFind(char* text)
{
	int address = hashAddress(text);
	NODE* node;
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
	NODE* node;
	for (i=0; i<HASH_SIZE; ++i)
	{
		for (node=Table[i]; node; node=node->next)
			fprintf(stderr, "Table[%d] has %s\n", i, node->text);
	}
}
