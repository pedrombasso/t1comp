#include <stdio.h>
#include <string.h>
#include <time.h>

#include "ast.h"
extern int getLineNumber();

AST *astCreate(int type, hashNode *symbol_node, AST *s0, AST *s1, AST *s2, AST *s3){
    AST *new_node;
    new_node = (AST*) calloc(1, sizeof(AST));
    new_node->type = type;
    new_node->symbol = symbol_node;
    new_node->son[0] = s0;
    new_node->son[1] = s1;
    new_node->son[2] = s2;
    new_node->son[3] = s3;
    new_node->lineNumber = getLineNumber();
    new_node->datatype = NO_DATATYPE;
    return new_node;
}

void astPrint(AST* node, int level){

    int i;
    if(node == 0)return;

    for(i=0; i<=level; i++){
        fprintf(stderr, "  ");
    }


    switch(node->type){
        case AST_CMD_ADD:    
                fprintf(stderr, "AST_ADD %d \n", node->lineNumber);
        break;

        case AST_CMD_SUB:    
                fprintf(stderr, "AST_SUB %d \n", node->lineNumber);
        break;

        case AST_CMD_MUL:    
                fprintf(stderr, "AST_MUL %d \n", node->lineNumber);
        break;

        case AST_CMD_DIV:    
                fprintf(stderr, "AST_DIV %d \n", node->lineNumber);
        break;

        case AST_CMD_AND:    
                fprintf(stderr, "AST_AND %d \n", node->lineNumber);
        break;

        case AST_CMD_OR:     
                fprintf(stderr, "AST_OR %d \n", node->lineNumber);
        break;

        case AST_CMD_DIF:    
                fprintf(stderr, "AST_DIF %d \n", node->lineNumber);
        break;

        case AST_CMD_EQ:     
                fprintf(stderr, "AST_EQ %d \n", node->lineNumber);
        break;

        case AST_CMD_GE:     
                fprintf(stderr, "AST_GE %d \n", node->lineNumber);
        break;

        case AST_CMD_LE:     
                fprintf(stderr, "AST_LE %d \n", node->lineNumber);
        break;

        case AST_CMD_GT:     
                fprintf(stderr, "AST_GT %d \n", node->lineNumber);
        break;

        case AST_CMD_LT:     
                fprintf(stderr, "AST_LT %d \n", node->lineNumber);
        break;

        case AST_CMD_NOT:    
                fprintf(stderr, "AST_NOT %d \n", node->lineNumber);
        break;

        case AST_LIT_INTEGER:   
                fprintf(stderr, "AST_INTEGER %d \n", node->lineNumber);
        break;

        case AST_LIT_FLOAT:     
                fprintf(stderr, "AST_FLOAT %d \n", node->lineNumber);
        break;

        case AST_LIT_CHAR:      
                fprintf(stderr, "AST_CHAR %d \n", node->lineNumber);
        break;

        case AST_LIT_STRING:    
                fprintf(stderr, "AST_STRING %d \n", node->lineNumber);
        break;

        case AST_TK_IDENTIFIER: 
                fprintf(stderr, "AST_IDENTIFIER %d \n", node->lineNumber);
        break;

        case AST_VETOR:        
                fprintf(stderr, "AST_VETOR %d \n", node->lineNumber);
        break;

        case AST_FUNCAO:      
                fprintf(stderr, "AST_FUNCAO %d \n", node->lineNumber);
        break;    

        case AST_DEC_VAR:       
                fprintf(stderr, "AST_DEC_VAR \n");
        break;  

        case AST_DEC_VETOR:       
                fprintf(stderr, "AST_DEC_VETOR \n");
        break;  

        case AST_DEC_FUNCAO:      
                fprintf(stderr, "AST_DEC_FUNCAO \n");
        break;

        case AST_TIPO_BYTE:         
                fprintf(stderr, "AST_TIPO_BYTE \n");
        break;

        case AST_TIPO_FLOAT:        
                fprintf(stderr, "AST_TIPO_FLOAT \n");
        break;

        case AST_TIPO_INT:          
                fprintf(stderr, "AST_TIPO_INT \n");
        break;

        case AST_PARAMETROS_FUNCAO:            
                fprintf(stderr, "AST_PARAMETROS_FUNCAO \n");
        break;

        case AST_LIST_DEC:               
                fprintf(stderr, "AST_LIST_DEC \n");
        break;

        case AST_LISTAVALOR:               
                fprintf(stderr, "AST_LISTAVALOR \n");
        break;

        case AST_LISTA_PARAMETRO:        
                fprintf(stderr, "AST_LISTA_PARAMETRO \n");
        break;

        case AST_BLOCO:                 
                fprintf(stderr, "AST_BLOCO \n");
        break;

        case AST_LISTA_COMANDO:               
                fprintf(stderr, "AST_LISTA_COMANDO \n");
        break;

        case AST_CMD_READ:              
                fprintf(stderr, "AST_CMD_READ \n");
        break;

        case AST_CMD_PRINT:             
                fprintf(stderr, "AST_CMD_PRINT \n");
        break;

        case AST_CMD_RETURN:            
                fprintf(stderr, "AST_CMD_RETURN \n");
        break;

        case AST_CMD_IF:                
                fprintf(stderr, "AST_CMD_IF \n");
        break;

        case AST_CMD_IF_ELSE:           
                fprintf(stderr, "AST_CMD_IF_ELSE \n");
        break;

        case AST_CMD_LEAP:              
                fprintf(stderr, "AST_CMD_LEAP \n");
        break;

        case AST_CMD_LOOP:              
                fprintf(stderr, "AST_CMD_LOOP \n");
        break;

        case AST_COMANDORESTO:              
                fprintf(stderr, "AST_COMANDORESTO \n");
        break;

        case AST_CMD_ATRIB:                 
                fprintf(stderr, "AST_CMD_ATRIB \n");
        break;

        case AST_CMD_ATRIB_VETOR:         
                fprintf(stderr, "AST_CMD_ATRIB_VETOR \n");
        break;

        case AST_LISTA_PARAM_EXP_RESTO:              
                fprintf(stderr, "AST_LISTA_PARAM_EXP_RESTO \n");
        break;

        case AST_LISTA_PARAM_EXP:               
                fprintf(stderr, "AST_LISTA_PARAM_EXP \n");
        break;

        case AST_PARAMRESTO:            
                fprintf(stderr, "AST_PARAMRESTO \n");
        break;

        case AST_DEC_VETOR_COMPLETO:   
                fprintf(stderr, "AST_DEC_VETOR_COMPLETO \n");
        break;

        default:                        
                fprintf(stderr, "AST_UNKNOWN %d \n", node->type);
        break;
    }

    level++;

    for(i=0; i<MAX_SONS; i++)
        astPrint(node->son[i], level);
    
}

void decompile(AST *node, FILE *out) {

	AST *temp = node;
	if (temp == 0) return;

	switch(temp->type) {
		case AST_LIST_DEC:
            decompile(temp->son[0], out);
            decompile(temp->son[1], out);
        break;
		
		case AST_DEC_VAR: 
            decompile(temp->son[0], out);
            fprintf(out,"%s = ", temp->symbol->lit);
            decompile(temp->son[1], out);
            fprintf(out, ";\n");
        break;
		case AST_DEC_VETOR: 
            decompile(temp->son[0], out);
            fprintf(out,"%s ", temp->symbol->lit);
            fprintf(out, "[");
            decompile(temp->son[1], out);
            fprintf(out, "];\n");
        break;
		case AST_DEC_VETOR_COMPLETO: 
            decompile(temp->son[0], out);
            fprintf(out,"%s ", temp->symbol->lit);
            fprintf(out, "[");
            decompile(temp->son[1], out);
            fprintf(out, "]: ");
            decompile(temp->son[2], out);
            fprintf(out, ";\n");
        break;
		case AST_TIPO_BYTE: 
            fprintf(out,"byte ");
        break;
        case AST_TIPO_INT: 
            fprintf(out,"int ");
        break;
		case AST_TIPO_FLOAT: 
            fprintf(out,"float ");
        break;		
		case AST_LISTAVALOR: 
            decompile(temp->son[0], out);
            fprintf(out," ");
            decompile(temp->son[1], out);
        break;
		case AST_LIT_INTEGER: 
            fprintf(out,"%s", temp->symbol->lit);
        break;
		case AST_LIT_FLOAT: 
            fprintf(out,"%s", temp->symbol->lit);
        break;
		case AST_LIT_CHAR: 
            fprintf(out,"'%s'", temp->symbol->lit);
        break;
        case AST_LIT_STRING:
            fprintf(out ,"\"%s\"", temp->symbol->lit);
        break;
        case AST_TK_IDENTIFIER:
            fprintf(out, "%s", temp->symbol->lit);
        break;
		case AST_DEC_FUNCAO: 
            decompile(temp->son[0], out);
            fprintf(out,"%s ", temp->symbol->lit);
            fprintf(out, "(");
            decompile(temp->son[1], out);
            fprintf(out, ")");
            decompile(temp->son[2], out);
        break;
		case AST_LISTA_PARAMETRO: 
            decompile(temp->son[0], out);
            decompile(temp->son[1], out);
        break;
        case AST_PARAMRESTO: 
            fprintf(out, ", ");
            decompile(temp->son[0], out);
            decompile(temp->son[1], out);
        break;
		case AST_PARAMETROS_FUNCAO:
                decompile(temp->son[0], out);
            fprintf(out,"%s ", temp->symbol->lit);
        break;
        case AST_BLOCO: 
            fprintf(out, "{\n");
            decompile(temp->son[0], out);
            fprintf(out, "\n};");
        break;
		case AST_LISTA_COMANDO: 
            if(temp->son[0] != 0){
                decompile(temp->son[0], out);
            }
            decompile(temp->son[1], out);
        break;
		case AST_COMANDORESTO: 
            if( temp->son[0] != 0){
                fprintf(out, ";\n");
                decompile(temp->son[0], out);
            }
            decompile(temp->son[1], out);
        break;
        case AST_CMD_READ: 
            fprintf(out, "read ");
            fprintf(out,"%s", node->symbol->lit);		
        break;
        case AST_CMD_PRINT: 
            fprintf(out, "print ");
            decompile(temp->son[0], out);	
        break;
		case AST_CMD_RETURN:
            fprintf(out,"return ");
            decompile(temp->son[0], out);
        break;
		case AST_CMD_IF: 
            fprintf(out, "if( ");
            decompile(temp->son[0], out);
            fprintf(out, " ) then \n");
            decompile(temp->son[1], out);
        break;
		case AST_CMD_IF_ELSE: 
            fprintf(out, "if( ");
            decompile(temp->son[0], out);
            fprintf(out, " ) then \n");
            decompile(temp->son[1], out);
            fprintf(out, " else \n");
            decompile(temp->son[2], out);
        break;
        case AST_CMD_LEAP:
            fprintf(out, "leap \n");
        break;
        case AST_CMD_LOOP:
            fprintf(out, "loop( ");
            decompile(temp->son[0], out);
            fprintf(out, ") \n");
            decompile(temp->son[1], out);
        break;
        case AST_CMD_ATRIB:
            fprintf(out, "%s = ", temp->symbol->lit);
            decompile(temp->son[0], out);
        break;
        case AST_CMD_ATRIB_VETOR:
            fprintf(out, "%s [", temp->symbol->lit);
            decompile(temp->son[0], out);
            fprintf(out, "] = ");
            decompile(temp->son[1], out);
        break;
        case AST_LISTA_PARAM_EXP:
            decompile(temp->son[0], out);
            decompile(temp->son[1], out);
        break;
        case AST_LISTA_PARAM_EXP_RESTO:
            fprintf(out, ", ");
            decompile(temp->son[0], out);
            decompile(temp->son[1], out);
        break;
        case AST_VETOR:
            fprintf(out, "%s [", temp->symbol->lit);
            decompile(temp->son[0], out);
            fprintf(out, "]");
        break;
        case AST_FUNCAO:
            fprintf(out, "%s (", temp->symbol->lit);
            decompile(temp->son[0], out);
            fprintf(out, ")");
        break;
		case AST_CMD_ADD: 
            decompile(temp->son[0], out);
            fprintf(out, " + ");
            decompile(temp->son[1], out);
        break;
        case AST_CMD_SUB: 
            decompile(temp->son[0], out);
            fprintf(out, " - ");
            decompile(temp->son[1], out);
        break;
        case AST_CMD_MUL: 
            decompile(temp->son[0], out);
            fprintf(out, " * ");
            decompile(temp->son[1], out);
        break;
		case AST_CMD_DIV: 
            decompile(temp->son[0], out);
            fprintf(out, " / ");
            decompile(temp->son[1], out);
        break;
		case AST_CMD_AND: 
            decompile(temp->son[0], out);
            fprintf(out, " and ");
            decompile(temp->son[1], out);
        break;
		case AST_CMD_OR: 
            decompile(temp->son[0], out);
            fprintf(out, " or ");
            decompile(temp->son[1], out);
        break;
		case AST_CMD_DIF: 
            decompile(temp->son[0], out);
            fprintf(out, " != ");
            decompile(temp->son[1], out);
        break;
		case AST_CMD_EQ: 
            decompile(temp->son[0], out);
            fprintf(out, " == ");
            decompile(temp->son[1], out);
        break;
		case AST_CMD_GE: 
            fprintf(out, ">= ");
            decompile(temp->son[0], out);
        break;
		case AST_CMD_LE: 
            decompile(temp->son[0], out);
            fprintf(out, " <= ");
            decompile(temp->son[1], out);			
        break;
		case AST_CMD_GT: 
            decompile(temp->son[0], out);
            fprintf(out, " > ");
            decompile(temp->son[1], out);
        break;
		case AST_CMD_LT: 
            decompile(temp->son[0], out);
            fprintf(out, " < ");
            decompile(temp->son[1], out);
        break;
		case AST_CMD_NOT: 
            fprintf(out, "not ");
            decompile(temp->son[0], out);
        break;
		default: 
            fprintf(stderr, "AST_UNKNOWN(%s)\n", temp->symbol->lit); 
        break;
	}
}

void closeFile(FILE *code){
    fclose(code);
}
