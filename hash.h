#include <stdio.h>

#define HASH_SIZE 997

typedef struct hash_node
{
	int type;
	char *text;
	struct hash_node * next;
} NODE;

NODE *Table[HASH_SIZE];

void hashInit(void);
int hashAddress(char*text);
NODE* hashFind(char* text);
NODE* hashInsert(int type, char *text);
void hashPrint(void);