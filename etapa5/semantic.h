#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include <stdio.h>
#include "ast.h"
#include "y.tab.h"
#include<stdbool.h>


void checarDeclaracao(AST *node);
void checarNaoDeclarado(void);
void checarOperandos(AST* node);

bool checarInt(int datatype);
bool checarBool(int datatype);
bool checarFloat(int datatype);
bool checarVetor(int datatype);
bool checarVariavel(int datatype);
bool checarFuncao(int datatype);
bool checarParametros(AST* fun, AST* node);
bool checarTipo(int datatype1, int datatype2);
bool checarCompatibilidade(int var, int atrib);

int getTipo(int datatype1, int datatype2);

AST* getFuncao(AST* rnode, char* lit);


#endif