#ifndef __SEMANTICS__
#define __SEMANTICS__

#include "semantics_types.h"
#include "ast.h"

extern int semanticFailure;

int semanticsIsCompatible(VAL_TYPE valueType1, VAL_TYPE valueType2);
DATA_TYPE semanticsIsDeclared(char* text);
int semanticsMatchParameters(PARAM_LIST *paramsDecl, AST *paramsCall);
int semanticsGreaterNumericType(VAL_TYPE type1, VAL_TYPE type2);
PARAM_LIST* semanticsGetParamsTypes(AST *node);
VAL_TYPE semanticsCheckVariables(AST* node);
VAL_TYPE semanticsCheckType(AST* node);
void update_hash_function_variables(AST* node);
#endif
