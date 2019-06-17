#include "hash.h"

#include "y.tab.h"


void initMe(void) {
	int i=0;
	for(i=0; i<HASHSIZE; i++){
		HashTable[i] = 0;
	}
}

int hashAddress(char *lit) {
	int address = 1;
	int i;
	
	for (i=0; i<strlen(lit); i++){
		address = (address * lit[i]) % HASHSIZE +1;
	}

	return address-1;
}


hashNode* hashFind(char *text)
{
	int address = hashAddress(text);
	hashNode* node;
	for(node=HashTable[address]; node; node = node->lit)
	{
		if(strcmp(text, node->lit) == 0)
			return node;
	}
	return 0;
}



hashNode* hashInsert(int type, char *text)
{
	hashNode *newNode;
	int address = hashAddress(text);

	if((newNode = hashFind(text)) != 0)
		return newNode;

	newNode = (hashNode*)calloc(1, sizeof(hashNode));
	newNode->type = type;
	newNode->lit = calloc(strlen(yytext) + 1, sizeof(char));
	strcpy(newNode->lit, text);
	newNode->next = HashTable[address];
	HashTable[address] = newNode;
	return newNode;
}



void hashPrint(){
	int i=0;
	hashNode *node;
	
	for(i=0; i<HASHSIZE; i++)
		for(node = HashTable[i]; node!=0; node=node->next)
			printf("Table[%d] has %s \n", i, node->lit);

}

bool hashNaoDeclarado(){
	hashNode *node;
	bool error = false;

	int i;
	for (i = 0; i < HASHSIZE; i++){
			for( node = HashTable[i]; node; node = node->next){
				if (node->dec == false && node->type == TK_IDENTIFIER){
					fprintf(stderr, "Erro semantico: '%s' não declarado.\n",node->lit);
					error = true;
				}
			}
	}
	return error;
}

