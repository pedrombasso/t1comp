#include <stdio.h>
#include "semantic.h"

AST* rootNode = 0;
bool erroSemantico = false;

void checarDeclaracao(AST *node){
    if(node == 0) 
        return;

    if(rootNode == 0)
        rootNode = node;

    int i;

    for(i=0; i<MAX_SONS; i++){
        checarDeclaracao(node->son[i]);
    }

    if(node->symbol == 0) 
        return;

    switch(node->type){
        case AST_DEC_VAR:
        case AST_PARAMETROS_FUNCAO:
            if(node->symbol->dec == true){
                fprintf(stderr, "Erro semantico: '%s' na linha line %i\n", node->symbol->lit, node->lineNumber);
                erroSemantico = true;
                break;
            }
            if(node->son[0]->type == AST_TIPO_BYTE)
                node->symbol->datatype = DATATYPE_BYTE;
            else if(node->son[0]->type == AST_TIPO_INT)
                node->symbol->datatype = DATATYPE_INT;
            else if(node->son[0]->type == AST_TIPO_FLOAT)
                node->symbol->datatype = DATATYPE_FLOAT;            

            node->symbol->dec = true;
            node->datatype = node->symbol->datatype;
            break;

        case AST_DEC_VETOR:
        case AST_DEC_VETOR_COMPLETO:
            if(node->symbol->dec == true){
                fprintf(stderr, "Erro semantico: '%s' na linha line %i\n", node->symbol->lit, node->lineNumber);
                erroSemantico = true;
                break;
            }
            if(node->son[0]->type == AST_TIPO_BYTE)
                node->symbol->datatype = DATATYPE_BYTE_VEC;
            else if(node->son[0]->type == AST_TIPO_INT)
                node->symbol->datatype = DATATYPE_INT_VEC;
            else if(node->son[0]->type == AST_TIPO_FLOAT)
                node->symbol->datatype = DATATYPE_FLOAT_VEC;

            node->symbol->dec = true;
            node->datatype = node->symbol->datatype;
            break;

        case AST_DEC_FUNCAO:
            if(node->symbol->dec == true){
                fprintf(stderr, "Erro semantico: '%s' na linha line %i\n", node->symbol->lit, node->lineNumber);
                erroSemantico = true;
                break;
            }
            if(node->son[0]->type == AST_TIPO_BYTE)
                node->symbol->datatype = DATATYPE_BYTE_FUN;
            else if(node->son[0]->type == AST_TIPO_INT)
                node->symbol->datatype = DATATYPE_INT_FUN;
            else if(node->son[0]->type == AST_TIPO_FLOAT)
                node->symbol->datatype = DATATYPE_FLOAT_FUN;

            node->symbol->dec = true;
            node->datatype = node->symbol->datatype;
            break;

        default:
            break;
    }
}



void checarOperandos(AST* node){
	if (node == 0 ){
        return;
    }
    
    int i;
	for ( i = 0; i < MAX_SONS; i++){
        checarOperandos(node->son[i]);
    }
    
	switch(node->type){
        case AST_TK_IDENTIFIER:
            if(node->symbol == 0){
                fprintf(stderr, "Erro semantico - Linha %i: Sem símbolo.\n", node->lineNumber);
                erroSemantico = 1;
                break;
            }
            if((node->symbol->type != TK_IDENTIFIER) || !checarVariavel(node->symbol->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: %s tipo nao compatível \n", node->lineNumber, node->symbol->lit);
                erroSemantico = 1;
            }
            node->datatype = node->symbol->datatype;
        break;

        case AST_VETOR:
            if(node->symbol == 0){
                fprintf(stderr, "Erro semantico - Linha %i: Sem símbolo.\n", node->lineNumber);
                erroSemantico = 1;
                break;
            }
            if((node->symbol->type != TK_IDENTIFIER) || !checarVetor(node->symbol->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: %s tipo nao compatível \n", node->lineNumber, node->symbol->lit);
                erroSemantico = 1;
            }
            if(!checarInt(node->son[0]->datatype)){
                fprintf(stderr,  "Erro semantico - Linha %i: Deve ser inteiro.\n", node->son[0]->lineNumber);
                erroSemantico = 1;
            }
            node->datatype = node->symbol->datatype;
        break;

        case AST_FUNCAO:
            if(node->symbol == 0){
                fprintf(stderr,  "Erro semantico - Linha %i: Sem símbolo.\n", node->lineNumber);
                erroSemantico = 1;
                break;
            }
            if((node->symbol->type != TK_IDENTIFIER) || !checarFuncao(node->symbol->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: %s tipo nao compatível \n", node->lineNumber, node->symbol->lit);
                erroSemantico = 1;
            }
            AST* aux = getFuncao(rootNode, node->symbol->lit);
            if(!checarParametros(aux->son[1], node->son[0])){
                fprintf(stderr, "Erro semantico - Linha %i: Parametros das funcoes errados.\n", node->lineNumber);
                erroSemantico = 1;
            }
            node->datatype = node->symbol->datatype;
        break;

        case AST_LIT_INTEGER:
        case AST_TIPO_INT:
            node->datatype = DATATYPE_INT;
        break;

        case AST_LIT_FLOAT:
        case AST_TIPO_FLOAT:
            node->datatype = DATATYPE_FLOAT;
        break;

        case AST_LIT_CHAR:
        case AST_TIPO_BYTE:
            node->datatype = DATATYPE_BYTE;
        break;

        case AST_LIT_STRING:
            node->datatype = DATATYPE_STRING;
        break; 

        case AST_DEC_VETOR:
            if(!checarInt(node->son[1]->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: Deve ser inteiro.\n", node->son[1]->lineNumber);
                erroSemantico = 1;
            }
            if(node->symbol == 0){
                fprintf(stderr, "Erro semantico - Linha %i: Sem símbolo.\n", node->lineNumber);
                erroSemantico = 1;
                break;
            }
            if(!checarVetor(node->symbol->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: %s tipo nao compatível \n", node->lineNumber, node->symbol->lit);
                erroSemantico = 1;
            }
            node->datatype = node->symbol->datatype;
        break;

        case AST_DEC_VETOR_COMPLETO:
            if(!checarInt(node->son[1]->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: Deve ser inteiro.\n", node->son[1]->lineNumber);
                erroSemantico = 1;
            }
            if(node->symbol == 0){
                fprintf(stderr, "Erro semantico - Linha %i: Sem símbolo.\n", node->lineNumber);
                erroSemantico = 1;
                break;
            }
            if(!checarCompatibilidade(node->symbol->datatype, node->son[2]->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: Elementos do vetor devem ser compativeis.\n", node->son[1]->lineNumber);
                erroSemantico = 1;
            }
            if(!checarVetor(node->symbol->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: %s tipo nao compatível \n", node->lineNumber, node->symbol->lit);
                erroSemantico = 1;
            }
            node->datatype = node->symbol->datatype;
        break;

        case AST_DEC_FUNCAO:
            if(node->symbol == 0){
                fprintf(stderr, "Erro semantico - Linha %i: Sem símbolo.\n", node->lineNumber);
                erroSemantico = 1;
                break;
            }
            if(!checarCompatibilidade(node->symbol->datatype, node->son[2]->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: Funcao sem retorno.\n", node->lineNumber);
                erroSemantico = 1;
            }
            node->datatype = node->symbol->datatype;
        break; 

        case AST_CMD_ADD:
        case AST_CMD_SUB:
        case AST_CMD_DIV:
        case AST_CMD_MUL:
            node->datatype = getTipo(node->son[0]->datatype, node->son[1]->datatype);
            if(node->datatype == NO_DATATYPE){
                fprintf(stderr, "Erro semantico - Linha %i: Operandos nao compativeis.\n", node->lineNumber);
                erroSemantico = 1;
            }
         break;

        case AST_CMD_EQ:
        case AST_CMD_DIF:
        case AST_CMD_GE:
        case AST_CMD_LE:
        case AST_CMD_LT:
        case AST_CMD_GT:        
            if(checarBool(node->son[0]->datatype)&&checarBool(node->son[1]->datatype)){
                node->datatype = DATATYPE_BOOL;
                break;
            }
            else if(getTipo(node->son[0]->datatype, node->son[1]->datatype) == NO_DATATYPE){
                fprintf(stderr, "Erro semantico - Linha %i: Operandos nao compativeis.\n", node->lineNumber);
                erroSemantico = 1;
            }
            node->datatype = DATATYPE_BOOL;
            break;
        case AST_CMD_AND:
        case AST_CMD_OR:
            if(!checarTipo(node->son[0]->datatype, node->son[1]->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: Operandos nao compativeis.\n", node->lineNumber);
                erroSemantico = 1;
            }
            node->datatype = DATATYPE_BOOL;
        break;

               
        case AST_DEC_VAR:
        case AST_CMD_ATRIB:
            if(node->symbol == 0){
                fprintf(stderr, "Erro semantico - Linha %i: Sem símbolo.\n", node->lineNumber);
                erroSemantico = 1;
                break;
            }
            if(!checarCompatibilidade(node->symbol->datatype, node->son[0]->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: Operandos nao compativeis.\n", node->lineNumber);
                erroSemantico = 1;
            }
            node->datatype = node->symbol->datatype;
            break;
        
        
        
        case AST_CMD_PRINT:
            if(node->son[0]->datatype == NO_DATATYPE){
                fprintf(stderr, "Erro semantico - Linha %i: Funcao nao printa.\n", node->lineNumber);
                erroSemantico = 1;
            }
            break;
        case AST_BLOCO:
            node->datatype = node->son[0]->datatype;
            break;

        case AST_CMD_IF:
        case AST_CMD_IF_ELSE:
        case AST_CMD_LOOP:
            if(!checarBool(node->son[0]->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: Deve ser booleano.\n", node->lineNumber);
                erroSemantico = 1;
            }
        break;

        case AST_CMD_ATRIB_VETOR:
            if(node->symbol == 0){
                fprintf(stderr, "Erro semantico - Linha %i: Sem símbolo.\n", node->lineNumber);
                erroSemantico = 1;
                break;
            }
            if((node->symbol->type != TK_IDENTIFIER) || !checarVetor(node->symbol->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: %s tipo nao compatível \n", node->lineNumber, node->symbol->lit);
                erroSemantico = 1;
            }
            if(!checarCompatibilidade(node->symbol->datatype, node->son[1]->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: Deve ser compatível.\n", node->lineNumber);
                erroSemantico = 1;
            }
            if(!checarInt(node->son[0]->datatype)){
                fprintf(stderr, "Erro semantico - Linha %i: Deve ser inteiro.\n", node->son[1]->lineNumber);
                erroSemantico = 1;
            }
            node->datatype = node->symbol->datatype;
        break;

        case AST_LISTAVALOR:
            if(node->son[0] == 0){
                node->datatype = NO_DATATYPE;
            }
            else if(node->son[1] == 0){
                node->datatype = node->son[0]->datatype;
            }
            else{
                node->datatype = getTipo(node->son[0]->datatype, node->son[1]->datatype);
            }
        break;

        case AST_LISTA_COMANDO:
        case AST_COMANDORESTO:
            if((node->son[0]==0)&&(node->son[1]==0)){
                node->datatype = NO_DATATYPE;
            }
            else if(node->son[0]==0){
                node->datatype = node->son[1]->datatype;
            }
            else if(node->son[1]==0){
                node->datatype = node->son[0]->datatype;
            }
            else{
                if(node->son[0]->datatype==NO_DATATYPE && node->son[1]->datatype==NO_DATATYPE)
                    node->datatype = NO_DATATYPE;
                else if(node->son[0]->datatype==NO_DATATYPE)
                    node->datatype = node->son[1]->datatype;
                else if(node->son[1]->datatype==NO_DATATYPE)
                    node->datatype = node->son[0]->datatype;
                else
                    node->datatype = getTipo(node->son[0]->datatype, node->son[1]->datatype);
            }
        break;

        case AST_LISTA_PARAM_EXP_RESTO:
        case AST_LISTA_PARAM_EXP:
            if(node->son[0] == 0){
                node->datatype = NO_DATATYPE;
            }
            else if(node->son[1] == 0){
                node->datatype = node->son[0]->datatype;
            }
            else{
                if(node->son[0]==NO_DATATYPE || node->son[1]==NO_DATATYPE)
                    node->datatype = NO_DATATYPE;
                else
                    node->datatype = DATATYPE_STRING;
            }
        break;

        case AST_CMD_RETURN:
            node->datatype = node->son[0]->datatype;
        break;

        case AST_CMD_READ:
        case AST_CMD_LEAP:
        case AST_LIST_DEC:
        case AST_PARAMETROS_FUNCAO:
        case AST_PARAMRESTO:
        case AST_LISTA_PARAMETRO: 

        default:
        break;
	}
}

bool checarInt(int datatype){
    switch (datatype){
        case DATATYPE_BYTE:
        case DATATYPE_BYTE_VEC:
        case DATATYPE_BYTE_FUN:
        case DATATYPE_INT:
        case DATATYPE_INT_VEC: 
        case DATATYPE_INT_FUN:
            return true;
            break;
        
        default:
            return false;
            break;
    }
}

bool checarFloat(int datatype){
    switch (datatype){
        case DATATYPE_FLOAT:
        case DATATYPE_FLOAT_VEC:
        case DATATYPE_FLOAT_FUN:
            return true;
            break;
        
        default:
            return false;
            break;
    }
}

bool checarBool(int datatype){
    if(datatype == DATATYPE_BOOL)
        return true;
    else
        return false;
    
}

bool checarVariavel(int datatype){
    switch(datatype){
        case DATATYPE_INT:
        case DATATYPE_BYTE:
        case DATATYPE_FLOAT:
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool checarFuncao(int datatype){
    switch(datatype){
        case DATATYPE_BYTE_FUN:
        case DATATYPE_INT_FUN:
        case DATATYPE_FLOAT_FUN:
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool checarVetor(int datatype){
    switch(datatype){
        case DATATYPE_INT_VEC:
        case DATATYPE_BYTE_VEC:
        case DATATYPE_FLOAT_VEC:
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool checarTipo(int datatype1, int datatype2){
   if(
        (checarInt(datatype1)&&checarInt(datatype2)) || (checarFloat(datatype1)&&checarFloat(datatype2)) || (checarBool(datatype1)&&checarBool(datatype2))){
            return true;
        }
    else{
        return false;
    }
}

void checarNaoDeclarado(){
    if(hashNaoDeclarado())
        erroSemantico = true;
}

bool checarCompatibilidade(int var, int atrib){
    if(checarFloat(var)){
        if(checarFloat(atrib)||checarInt(atrib))
            return true;
        else
            return false;
    }
    else if (checarInt(var)){
        if(checarInt(atrib))
            return true;
        else
            return false;
    }
    else if(checarBool(var)){
        if(checarBool(atrib))
            return true;
        else 
            return false;
    }
    return false;
}



int getTipo(int datatype1, int datatype2){
    if((!checarInt(datatype1)&&!checarFloat(datatype1))||(!checarInt(datatype2)&&!checarFloat(datatype2))){
        return NO_DATATYPE;
    }
    else if(checarFloat(datatype1)||checarFloat(datatype2)){
        return DATATYPE_FLOAT;
    }
    return DATATYPE_INT;
}

AST* getFuncao(AST* rnode, char* lit){
    if(rnode == 0 || rnode->son[0]==0)
        return 0;
    if( strcmp(rnode->son[0]->symbol->lit, lit) == 0 ){
        return rnode->son[0];
    }
    return getFuncao(rnode->son[1], lit);
}

bool checarParametros(AST* fun, AST* node){
    if(fun == 0){
        if(node == 0)
            return true;
        else
            return false;
    }
    else if(node == 0){
        return false;
    }
    if(!checarCompatibilidade(fun->son[0]->datatype, node->son[0]->datatype)){
        return false;
    }
    else{
        return checarParametros(fun->son[1], node->son[1]);
    }
    
}