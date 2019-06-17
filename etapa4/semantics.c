#include "semantics.h"
#include <stdlib.h>
#include <stdio.h>
int semanticFailure = 0;


void update_hash_function_variables(AST* node)
{
	// Children[0] - type
	// Children[1] - text
	// Children[2] - rest list
	if(node == NULL)
		return;
	//printf("..%s\n", node->son[1]->symbol->text);
	//printf("..%d\n", node->son[0]->type);
	//hashUpdateType(node->son[1]->symbol->text, ID_TYPE idType, VAL_TYPE valType, PARAM_LIST *params, int length);
	if(! hashUpdateType( node->son[1]->symbol->text, ID_TYPE_SCALAR, node->son[0]->type + 10, NULL, 0))
	{
		printf("%s already declared!\n", node->son[1]->symbol->text);
		semanticFailure = 1;
	}
	update_hash_function_variables(node->son[2]);
}
DATA_TYPE semanticsIsDeclared(char* text)
{
	HASH_NODE* node = hashFind(text);
	DATA_TYPE r;
	if(node->dataType.identifierType != -1)
		return node->dataType;
	else if(node->type == SYMBOL_LITERAL_INT || node->type == SYMBOL_LITERAL_REAL || node->type == SYMBOL_LITERAL_CHAR)
	{
		r.identifierType = node->type + 10;
		r.valueType = ID_TYPE_SCALAR;
		return r;
	}
	else {
		r.identifierType = -1;
		r.valueType = -1;
		return r;
	}
}
int semanticsIsNumericType(VAL_TYPE valueType)
{
	return valueType == VAL_TYPE_INT
		|| valueType == VAL_TYPE_CHAR
		|| valueType == VAL_TYPE_FLOAT;
}
int semanticsIsCompatible(VAL_TYPE valueType1, VAL_TYPE valueType2)
{
	return valueType1 == valueType2
		|| (semanticsIsNumericType(valueType1) && semanticsIsNumericType(valueType2));
}

int semanticsMatchParameters(PARAM_LIST *paramsDecl, AST *paramsCall)
{
	for (; paramsDecl && paramsCall; paramsDecl=paramsDecl->next, paramsCall=paramsCall->son[1])
	{
		if (! semanticsIsCompatible(paramsDecl->valueType, semanticsCheckType(paramsCall->son[0])) )
		{
			return 0;
		}
	}
	// If stopped the loop, then at least one of the list has come to the end (== NULL)
	// If both have, then they are equivalent, otherwise they're not
	return (void*)paramsDecl == (void*)paramsCall;
}

int semanticsGreaterNumericType(VAL_TYPE type1, VAL_TYPE type2)
{
	if (type1 == VAL_TYPE_FLOAT || type2 == VAL_TYPE_FLOAT)
		return VAL_TYPE_FLOAT;
	else if (type1 == VAL_TYPE_INT || type2 == VAL_TYPE_INT)
		return VAL_TYPE_INT;
	else
		return VAL_TYPE_CHAR;
}

PARAM_LIST* semanticsGetParamsTypes(AST *node)
{
	PARAM_LIST *first=NULL, *params=NULL, *prior=NULL;

	if (node && node->type == AST_PARAMETRO) {
		for ( ; node; node=node->son[2], prior=params) {
			params = (PARAM_LIST*) malloc(sizeof(PARAM_LIST));
			params->valueType = (VAL_TYPE) node->son[0]->type + 10;
			params->next = NULL;

			if (prior) {
				prior->next = params;
			} else {
				first = params;
			}
		}
	}

	return first;
}

VAL_TYPE semanticsCheckVariables(AST* node)
{

	printf("\nNode %d \n",node->type);

	DATA_TYPE symbolDataType;
	VAL_TYPE rightValueType;
	VAL_TYPE conditionValueType;
	VAL_TYPE indexValueType;
	VAL_TYPE leftExprType;
	VAL_TYPE rightExprType;
	ID_TYPE idType;
	VAL_TYPE valueType;
	PARAM_LIST *params;
	int length = 0;

	if (!node) {
		return VAL_TYPE_UNIT;
	}

	switch (node->type) {

		case AST_TIPO_INT:
		case AST_TIPO_BYTE:
		case AST_TIPO_FLOAT:
			// This case should not happen
			return;
		case AST_DEC_VETOR_SIMPLES:			
		case AST_DEC_VETOR_COMPLETO:
			length = atoi(node->son[2]->symbol->text);
		case AST_DEC_SIMPLES:		
		case AST_DEC_FUNCAO:
			return semanticsCheckVariables(node->son[0]);
		case AST_FUNCAO:

			// printf(" \n entrou dec func %d\n",node->type);
			// return 0;
			if(node->type == AST_DEC_VETOR_SIMPLES || AST_DEC_VETOR_COMPLETO ){
			idType = ID_TYPE_VECTOR;
			// printf(" \n if 1 \n");
			}

			if(node->type == AST_DEC_SIMPLES ){
			// printf(" \n if 2 \n");	
			idType = ID_TYPE_SCALAR;
			// printf(" \n if 2 \n");
			}
			if(node->type == AST_DEC_FUNCAO ){			
			idType = ID_TYPE_FUNCTION;
			printf(" \n if 3 \n");
			}

			valueType = node->son[0]->type + 3;
			params = semanticsGetParamsTypes(node->son[2]);

			if(node->type == AST_DEC_FUNCAO)
			{
				/*Update hash funcion variables*/
				update_hash_function_variables(node->son[2]);
			}

			if(! hashUpdateType( node->son[1]->symbol->text, idType, valueType, params, length))
			{
				printf("Error in node %d : %s already declared!\n",node->type, node->son[1]->symbol->text);
				semanticFailure = 1;
				return -1;
			}
			return VAL_TYPE_UNIT;

		case AST_DEC_VAR:
			return semanticsCheckVariables(node->son[0]);

		case AST_DEC:
			return semanticsCheckVariables(node->son[0]);	

		case AST_LIST_DEC:
			// Check this declaration node (first), then check the rest of the program
			if (semanticsCheckVariables(node->son[0]) != -1){
				return semanticsCheckVariables(node->son[1]);}
			else
				return -1;
		default:
			// This node should not exist
			semanticFailure = 1;
			printf("Default %d\n",node->type);
			return -1;
	}
}

VAL_TYPE semanticsCheckType(AST* node)
{
	DATA_TYPE symbolDataType;
	VAL_TYPE rightValueType;
	VAL_TYPE conditionValueType;
	VAL_TYPE indexValueType;
	VAL_TYPE leftExprType;
	VAL_TYPE rightExprType;
	ID_TYPE idType;
	VAL_TYPE valueType;
	PARAM_LIST *params;
	int length = 0;

	if (!node) {
		return VAL_TYPE_UNIT;
	}
	//printf("%d\n",node->type);
	switch (node->type) {
		case SYMBOL:
			//printf("Symbol %s is %d\n",node->symbol->text, node->symbol->type);
			switch (node->symbol->type) {
				case SYMBOL_LITERAL_INT:
					return VAL_TYPE_INT;
				case SYMBOL_LITERAL_REAL:
					return VAL_TYPE_FLOAT;
				case SYMBOL_LITERAL_CHAR:
					return VAL_TYPE_CHAR;
				case SYMBOL_LITERAL_STRING:
					return VAL_TYPE_STRING;
				case SYMBOL_IDENTIFIER:
					// Identifier alone in an expression can only appear if it's a scalar OR a variable scalar
					if (node->symbol->dataType.identifierType == ID_TYPE_SCALAR)
						return node->symbol->dataType.valueType;
					else
					{
						DATA_TYPE d = semanticsIsDeclared(node->symbol->text);
						if(d.identifierType == ID_TYPE_SCALAR)
						{
							HASH_NODE* n = hashFind(node->symbol->text);
							return n->dataType.valueType;
						}
						else {
							semanticFailure = 1;
							printf("Error in node %d : %s undeclared!\n",node->type, node->symbol->text);
							return -1;
						}
					}
				default:
					// This case should not happen
					semanticFailure = 1;
					printf("%d\n",node->type);
					return -1;
			}
		case AST_TIPO_INT:
		case AST_TIPO_BYTE:
		case AST_TIPO_FLOAT:
			// This case should not happen
			return;
		case AST_DEC_VETOR_SIMPLES:
		case AST_DEC_VETOR_COMPLETO:
		case AST_DEC_VAR:
		case AST_DEC_SIMPLES:
			return VAL_TYPE_UNIT;

		case AST_DEC_FUNCAO:

				// Check the type of the function body, the function returns the type of
				// the "return" commands in the body, now we must check it
				symbolDataType = semanticsIsDeclared(node->son[1]->symbol->text); //node->son[1]->symbol->dataType;
				//printf("%d\n", node->son[3]->type);
				VAL_TYPE returnType = semanticsCheckType(node->son[3]);
				//printf(" %d=%d\n", returnType, symbolDataType.valueType);
				if (returnType == VAL_TYPE_UNIT
					|| semanticsIsCompatible(returnType, symbolDataType.valueType))
					return VAL_TYPE_UNIT;
				else {
					semanticFailure = 1;
					printf("Error in node %d : Function error\n", node->type);
					return -1;
				}
		case AST_LISTA_DEC:
		case AST_PARAMETRO:
			// This case should not happen
			return;
		case AST_LISTA_COMANDO:
		//printf(".%d\n",node->son[0]->type);
			// Check the type of the command (first), note: single command doesn't have a type
			leftExprType = semanticsCheckType(node->son[0]);
			if (leftExprType != -1) {
				// Then call recursively for the next command (rest)
				rightExprType = semanticsCheckType(node->son[1]);
				if (semanticsIsCompatible(leftExprType, rightExprType)) {
					//printf("case 1: ");
					return leftExprType;
				}
				else if (leftExprType == VAL_TYPE_UNIT) {
					//printf("case 2: ");
					return rightExprType;
				}
				else if (rightExprType == VAL_TYPE_UNIT) {
					//printf("case 3: (%d)\n",leftExprType);
					return leftExprType;
				}
				else {
					semanticFailure = 1;
					printf("Error in node %d : check list of commands\n",node->type);
					return -1;
				}
			} else{
				return -1;
		case AST_LISTA_PARAM_EXP:
			// Check the type of the expression (first), note: the type of an expression in a
			// list is irrelevant, it should just be well typed
			if (semanticsCheckType(node->son[0]) != -1)
				// Then call recursively for the next expression (rest)
				return semanticsCheckType(node->son[1]);
			else
				return -1;
		// case TREE_LIST_OUT:
		// 	// Check the type of the element (first)
		// 	if (semanticsCheckType(node->son[0]) != -1)
		// 		// Then call recursively for the next element (rest)
		// 		return semanticsCheckType(node->son[1]);
		// 	else
		// 		return -1;
		case AST_CMD_NOP:
			return VAL_TYPE_UNIT;
		// case TREE_COMM_IN:
		// 	// Check the type of the list of input
		// 	if (semanticsCheckType(node->son[0]) != -1)
		// 		return VAL_TYPE_UNIT;
		// 	else
		// 		return -1;
		// case TREE_COMM_OUT:
		// 	// Check the type of the list of output
		// 	if (semanticsCheckType(node->son[0]) != -1)
		// 		return VAL_TYPE_UNIT;
		// 	else
		// 		return -1;
		case AST_CMD_ATRIB:
			symbolDataType = semanticsIsDeclared(node->son[0]->symbol->text); //node->son[0]->symbol->dataType;
			rightValueType = semanticsCheckType(node->son[1]);

			// Left side must be scalar and of a type compatible with the right side
			if (rightValueType != -1
			&& symbolDataType.identifierType == ID_TYPE_SCALAR
			&& semanticsIsCompatible(symbolDataType.valueType, rightValueType))
			{
				return VAL_TYPE_UNIT;
			}
			else {
				semanticFailure = 1;
				printf("Error in node %d : maybe check value assignment\n",node->type);
				return -1;
				}
			}
		case AST_CMD_ATRIB_VETOR:

			//printf(".%d\n", semanticsListOutOfRange(hashFind(node->son[0]->symbol->text)->dataType.params, atoi(node->son[1]->symbol->text)));
			//hashFind(node->son[0]->symbol->text)->dataType.params;


			symbolDataType = semanticsIsDeclared(node->son[0]->symbol->text); //node->son[0]->symbol->dataType;
			indexValueType = semanticsCheckType(node->son[1]);
			rightValueType = semanticsCheckType(node->son[2]);



			// Left side must be a vector, the index expression an integer, and the vector
			// type must be compatible with the right side
			if (rightValueType != -1
			&& symbolDataType.identifierType == ID_TYPE_VECTOR // Se é vector, deve aceitar real também como índice
			&& (indexValueType == VAL_TYPE_INT || indexValueType == VAL_TYPE_CHAR)
			&& semanticsIsCompatible(symbolDataType.valueType, rightValueType)) {
				return VAL_TYPE_UNIT;
			} else {
				semanticFailure = 1;
				//printf("Assign vector error: %d\n",symbolDataType.identifierType);
				printf("Error in node %d : Vector \'%s\' assign error!\n", node->type, node->son[0]->symbol->text);
				return -1;
			}
		case AST_CMD_IF:
			conditionValueType = semanticsCheckType(node->son[0]);
			// The condition expression should be compatible with int, because it'll be tested for zero
			if (semanticsIsCompatible(VAL_TYPE_BYTE, conditionValueType) || semanticsIsCompatible(VAL_TYPE_INT, conditionValueType)) {//(semanticsIsCompatible(VAL_TYPE_INT, conditionValueType))

				// Check the type of the Then-Command and the Else-Command
				VAL_TYPE thenCommandType = semanticsCheckType(node->son[1]);
				VAL_TYPE elseCommandType = semanticsCheckType(node->son[2]);
				//printf("%d %d\n", thenCommandType, elseCommandType);
				if (thenCommandType != -1 && elseCommandType != -1) {
					// If the Then-Command has no type (no "return" command), then the type
					// of the If-Command will be the type of the Else-command, and vice-versa
					if (thenCommandType == VAL_TYPE_UNIT) {
						return elseCommandType;
					} else if (elseCommandType == VAL_TYPE_UNIT) {
						return thenCommandType;
					} else if (semanticsIsCompatible(thenCommandType,elseCommandType)) { //else if (thenCommandType == elseCommandType)
					// If both command have any type (they have "return" commands), then
					// both types must be equal and this will be the type of the If-Command		// Equal or compatible?
							return thenCommandType;
					} else {
						semanticFailure = 1;
						printf("%d\n",node->type);
						return -1;
					}
				} else{
					return -1;
					}
			} else {
				semanticFailure = -1;
				return -1;
			}
		case AST_CMD_LOOP:
			conditionValueType = semanticsCheckType(node->son[0]);

			// The condition expression should be compatible with int, because it'll be tested for zero
			if (semanticsIsCompatible(VAL_TYPE_BYTE, conditionValueType) || semanticsIsCompatible(VAL_TYPE_INT, conditionValueType)) {//if (semanticsIsCompatible(VAL_TYPE_INT, conditionValueType)) {

				// Check the type of the loop body
				return semanticsCheckType(node->son[1]);
			} else {
				semanticFailure = -1;
				return -1;
			}
		case AST_CMD_RETURN:
			//printf("%d\n", node->son[0]->type);
			return semanticsCheckType(node->son[0]);
		case AST_TK:
			symbolDataType = semanticsIsDeclared(node->son[0]->symbol->text); //node->son[0]->symbol->dataType;

			// Identifier must be function and the call must match the declaration
			if (symbolDataType.identifierType == ID_TYPE_FUNCTION
			&& semanticsMatchParameters(symbolDataType.params, node->son[1])) {
				return symbolDataType.valueType;
			} else {
				semanticFailure = -1;
				return -1;
			}
		case AST_TK_VET:
			symbolDataType = semanticsIsDeclared(node->son[0]->symbol->text); //node->son[0]->symbol->dataType;
			indexValueType = semanticsCheckType(node->son[1]);

			// Left side must be a vector, the index expression an integer, and the vector
			// type must be compatible with the right side
			if (symbolDataType.identifierType == ID_TYPE_VECTOR
			&& (indexValueType == VAL_TYPE_INT || indexValueType == VAL_TYPE_CHAR)){
				return symbolDataType.valueType;
			} else {
				semanticFailure = 1;
				printf("Error in node %d: Vector \'%s\' read error!\n", node->type, node->son[0]->symbol->text);
				return -1;
			}
		case AST_CMD_ADD:
		case AST_CMD_SUB:
		case AST_CMD_MUL:
		case AST_CMD_DIV:
			leftExprType = semanticsCheckType(node->son[0]);
			rightExprType = semanticsCheckType(node->son[1]);
			//printf("%s\n", node->son[0]->son[0]->symbol->text);
			// Only numeric type can be operands
			if ((leftExprType == VAL_TYPE_INT || leftExprType == VAL_TYPE_CHAR || leftExprType == VAL_TYPE_FLOAT)
			&&  (rightExprType == VAL_TYPE_INT || rightExprType == VAL_TYPE_CHAR || rightExprType == VAL_TYPE_FLOAT)) {
				// Division returns always a real type
				if (node->type == AST_CMD_DIV) {
					return VAL_TYPE_FLOAT;
				} else {
				// Other operations return the greater type of both operands
					return semanticsGreaterNumericType(leftExprType, rightExprType);
				}
			} else {
				semanticFailure = 1;
				printf("Error in node %d\n",node->type);
				return -1;
			}
		case AST_CMD_LT:
		case AST_CMD_GT:
		case AST_CMD_LE:
		case AST_CMD_GE:
		case AST_CMD_EQ:
		case AST_CMD_DIF:
			leftExprType = semanticsCheckType(node->son[0]);
			rightExprType = semanticsCheckType(node->son[1]);

			// Only numeric type can be operands
			if ((leftExprType == VAL_TYPE_INT || leftExprType == VAL_TYPE_CHAR || leftExprType == VAL_TYPE_FLOAT)
			&&  (rightExprType == VAL_TYPE_INT || rightExprType == VAL_TYPE_CHAR || rightExprType == VAL_TYPE_FLOAT)) {
				return VAL_TYPE_BYTE;
			} else {
				semanticFailure = 1;
				printf("Error in node %d\n",node->type);
				return -1;
			}
		case AST_CMD_AND:
		case AST_CMD_OR:
			leftExprType = semanticsCheckType(node->son[0]);
			rightExprType = semanticsCheckType(node->son[1]);

			// Both expressions should be compatible with int, because they'll be tested for zero
			if (semanticsIsCompatible(VAL_TYPE_INT, leftExprType)
			&& semanticsIsCompatible(VAL_TYPE_INT, rightExprType)) {
				return VAL_TYPE_BYTE;
			} else {
				semanticFailure = 1;
				printf("Error in node %d\n",node->type);
				return -1;
			}
		case AST_DEC:
		case AST_LIST_DEC:
			// Check this declaration node (first), then check the rest of the program
			if (semanticsCheckType(node->son[0]) != -1)
				return semanticsCheckType(node->son[1]);
			else
				return -1;
		default:
			// This node should not exist
			semanticFailure = 1;
			printf("%d\n",node->type);
			return -1;
	}
}
