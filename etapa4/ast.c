#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern FILE *out;



AST* astCreate(int type, HASH_NODE* symbol, AST* son0, AST* son1, AST* son2, AST* son3) {
   AST* newnode;
   newnode = (AST*) calloc(1, sizeof(AST));
   newnode->type = type;
   newnode->symbol = symbol;
   newnode->son[0] = son0;
   newnode->son[1] = son1;
   newnode->son[2] = son2;
   newnode->son[3] = son3;
   return newnode;
}
AST* astCreate_son(int type)
{
	return astCreate(type, NULL, NULL, NULL, NULL, NULL);
}
AST* astCreate_symbol(HASH_NODE* hash_symbol)
{
	return astCreate(SYMBOL, hash_symbol, NULL, NULL, NULL, NULL);
}


void astPrint(AST* node, int level) {
	int i;
	if (node == NULL) {
		return;
    }
	for(i=0; i<level; ++i) {
		fprintf(stderr, "  ");
    }

  fprintf(stderr, "%d: ", node->type);
	switch(node->type) {

    case AST_LISTA_DEC :
      fprintf(stderr, "AST_LISTA_DEC \n");
      break;

		case SYMBOL : 					
         	fprintf(stderr,"SYMBOL ");
			break;

		case PROGRAMA : 
            fprintf(stderr, "PROGRAMA\n");
            break;
    case AST_DEC : 
            fprintf(stderr, "AST_DEC \n");
            break;
    case AST_DEC_FUNCAO : 
            fprintf(stderr, "AST_DEC_FUNCAO \n");
            break;
    case AST_DEC_VAR : 
            fprintf(stderr, "AST_DEC_VAR \n");
            break;  
    case AST_DEC_SIMPLES : 
            fprintf(stderr, "AST_DEC_SIMPLES \n");
            break;
     case AST_LIST_DEC : 
            fprintf(stderr, "AST_LIST_DEC \n");
            break;    
     case AST_TIPO_INT : 
            fprintf(stderr, "AST_TIPO_INT \n");
      break;
      case AST_TIPO_FLOAT : 
            fprintf(stderr, "AST_TIPO_FLOAT \n");
      break;
      case AST_TIPO_BYTE : 
            fprintf(stderr, "AST_TIPO_BYTE \n");
      break;

      case AST_DEC_VETOR_SIMPLES : 
            fprintf(stderr, "AST_DEC_VETOR_SIMPLES \n");
      break;

      case AST_DEC_VETOR_COMPLETO : 
            fprintf(stderr, "AST_DEC_VETOR_COMPLETO \n");
      break;

      case AST_LISTA_PARAMETRO : 
            fprintf(stderr, "AST_LISTA_PARAMETRO \n");
      break;

      case AST_FUNCAO : 
            fprintf(stderr, "AST_FUNCAO \n");
      break;

      case AST_BLOCO : 
            fprintf(stderr, "AST_BLOCO \n");
      break;

      case AST_LISTA_COMANDO : 
            fprintf(stderr, "AST_LISTA_COMANDO \n");
      break;

      case AST_CMD_LEAP : 
            fprintf(stderr, "AST_CMD_LEAP \n");
      break;

      case AST_PARAMETRO : 
            fprintf(stderr, "AST_PARAMTRO \n");
      break;

      case AST_CMD_ATRIB : 
            fprintf(stderr, "AST_CMD_ATRIB \n");
      break;

      case AST_CMD_ATRIB_VETOR : 
            fprintf(stderr, "AST_CMD_ATRIB_VETOR \n");
      break;

      case AST_INT : 
            fprintf(stderr, "AST_INT \n");
      break;

      case AST_FLOAT : 
            fprintf(stderr, "AST_FLOAT \n");
      break;

      case AST_BYTE : 
            fprintf(stderr, "AST_BYTE \n");
      break;

      case AST_CMD_READ : 
            fprintf(stderr, "AST_CMD_READ \n");
      break;

      case AST_CMD_RETURN : 
            fprintf(stderr, "AST_CMD_RETURN \n");
      break;

      case AST_CMD_LOOP : 
            fprintf(stderr, "AST_CMD_LOOP\n");
      break;

      case AST_CMD_IF : 
            fprintf(stderr, "AST_CMD_IF\n");
      break;


      case AST_CMD_PRINT : 
            fprintf(stderr, "AST_CMD_PRINT\n");
      break;

      case AST_LISTA_ELEMENTOS : 
            fprintf(stderr, "AST_LISTA_ELEMENTOS\n");
      break;

      case AST_STRING : 
            fprintf(stderr, "AST_STRING\n");
      break;
      case AST_PARENTESIS : 
            fprintf(stderr, "AST_PARENTESIS\n");
      break;

      case AST_TK : 
            fprintf(stderr, "AST_TK\n");
      break;

      case AST_TK_VET : 
            fprintf(stderr, "AST_TK_VET\n");
      break;

      case AST_CMD_ADD : 
            fprintf(stderr, "AST_CMD_ADD\n");
      break;

      case AST_CMD_SUB : 
            fprintf(stderr, "AST_CMD_SUB\n");
      break;

      case AST_CMD_MUL : 
            fprintf(stderr, "AST_CMD_MUL\n");
      break;

      case AST_CMD_DIV : 
            fprintf(stderr, "AST_CMD_DIV\n");
      break;

      case AST_CMD_LT : 
            fprintf(stderr, "AST_CMD_LT\n");
      break;

      case AST_CMD_GT : 
            fprintf(stderr, "AST_CMD_GT\n");
      break;

      case AST_CMD_AND : 
            fprintf(stderr, "AST_CMD_AND\n");
      break;

      case AST_CMD_OR : 
      fprintf(stderr, "AST_CMD_OR\n");
      break;

      case AST_CMD_NOT : 
      fprintf(stderr, "AST_CMD_NOT\n");
      break;  

      case AST_CMD_LE : 
      fprintf(stderr, "AST_CMD_LE\n");
      break;      

      case AST_CMD_GE : 
      fprintf(stderr, "AST_CMD_GE\n");
      break;      

      case AST_CMD_EQ : 
      fprintf(stderr, "AST_CMD_EQ\n");
      break;      

      case AST_CMD_DIF : 
      fprintf(stderr, "AST_CMD_DIF\n");
      break;  

      case AST_CMD_OP_NOT : 
      fprintf(stderr, "AST_CMD_OP_NOT\n");
      break;        

      case AST_LISTA_PARAM_EXP : 
      fprintf(stderr, "AST_LISTA_PARAM_EXP\n");
      break; 

      default: 
            fprintf(stderr, "AST_UNKNOWN\n");
      break;
	}

   if(node->symbol)
       fprintf(stderr, ": %s\n", node->symbol->text);

	for(i=0; i< MAX_SONS; ++i) {
		astPrint(node->son[i], level + 1);
    }
}

void decompile(AST* node, FILE* outfile)
{
    //fprintf(outfile, "entrou no decompile\n");
    if (node) {
      //fprintf(outfile, "entrou no if\n");
      //fprintf(outfile, "\ncase:%d\n",node->type);
    switch (node->type) {
      case SYMBOL:
        if (node->symbol) {
          switch (node->symbol->type) {
            case SYMBOL_LITERAL_STRING:
              fprintf(outfile, "\"%s\"", node->symbol->text);
            break;
            case SYMBOL_LITERAL_CHAR:
              fprintf(outfile, "'%s'", node->symbol->text);
            break;
            default:
              fprintf(outfile, "%s", node->symbol->text);
          }
        }
        else{//fprintf(outfile, "entrou no else\n");
          fprintf(outfile, T_TOKEN_ERROR);
        }
      break;
      case AST_DEC:
        //fprintf(outfile, "entrou no AST_DEC\n");
        decompile(node->son[0], outfile);
      break;

      case AST_LISTA_DEC : 
        decompile(node->son[0], outfile);
        if(node->son[1]){
          fprintf(outfile, " ");
          decompile(node->son[1], outfile);
        }
      break;

      case AST_DEC_VAR:
        //fprintf(outfile, "entrou no AST_DEC_VAR\n");
        decompile(node->son[0], outfile);
      break;

      case AST_TIPO_INT:
        fprintf(outfile, "int");
      break;

      case AST_TIPO_FLOAT : 
            fprintf(outfile, "float");
      break;
      case AST_TIPO_BYTE : 
            fprintf(outfile, "byte");
      break;

      case AST_DEC_SIMPLES:
        decompile(node->son[0], outfile);
        fprintf(outfile, " ");
        decompile(node->son[1], outfile);

        if (node->son[2]) {
          fprintf(outfile, " = ");
          decompile(node->son[2], outfile);
        }
        fprintf(outfile, ";");
      break;

      case AST_LIST_DEC : 
            decompile(node->son[0], outfile);
        fprintf(outfile, "\n");
        decompile(node->son[1], outfile);

        break;  

      case AST_DEC_VETOR_SIMPLES:
        decompile(node->son[0], outfile);
        fprintf(outfile, " ");
        decompile(node->son[1], outfile);

        
          fprintf(outfile, "[");
          decompile(node->son[2], outfile);
          fprintf(outfile, "]");
        
        fprintf(outfile, ";");
      break;

      case AST_DEC_VETOR_COMPLETO:
        decompile(node->son[0], outfile);
        fprintf(outfile, " ");
        decompile(node->son[1], outfile);
        fprintf(outfile, "[");
        decompile(node->son[2], outfile);
        fprintf(outfile, "]");
        fprintf(outfile, ":");
        decompile(node->son[3], outfile);
        fprintf(outfile, ";");
      break;

      case AST_DEC_FUNCAO:
          decompile(node->son[0], outfile);
      break;

      case AST_FUNCAO : 
        decompile(node->son[0], outfile);    
        fprintf(outfile, " ");
        decompile(node->son[1], outfile);
        fprintf(outfile, "(");
        if(node->son[2])
            decompile(node->son[2], outfile);
        fprintf(outfile, ")");
        fprintf(outfile, "{\n");
        decompile(node->son[3], outfile);
        fprintf(outfile, "}");
        fprintf(outfile, ";");
      break;

      case AST_BLOCO : 
        decompile(node->son[0], outfile);    

      break;
      
      case AST_CMD_LEAP : 
        fprintf(outfile, "leap;\n");    

      break;

      case AST_CMD_NOP :     

      break;

      case AST_PARAMETRO :

        if(node->son[0] != NULL){

          decompile(node->son[0], outfile);    
          fprintf(outfile, " ");
          decompile(node->son[1], outfile);
          
          if(node->son[2])
            fprintf(outfile, ",");
              decompile(node->son[2], outfile);  
        }
      break;

      case AST_CMD_ATRIB : 
         decompile(node->son[0], outfile);    
        fprintf(outfile, " = ");
        decompile(node->son[1], outfile);
        fprintf(outfile, ";\n");    

      break;

      case AST_CMD_ATRIB_VETOR : 
         decompile(node->son[0], outfile);    
        fprintf(outfile, "[");
        decompile(node->son[1], outfile);
        fprintf(outfile, "]");
        fprintf(outfile, " = ");
        decompile(node->son[2], outfile);
        fprintf(outfile, ";\n");    

      break;

      case AST_INT : 
      decompile(node->son[0], outfile); 
      

      break;

      case AST_FLOAT : 
      decompile(node->son[0], outfile); 
      

      break;

      case AST_BYTE : 
      decompile(node->son[0], outfile); 
      

      break;
      
      case AST_LISTA_COMANDO : 
        decompile(node->son[0], outfile);
         if(node->son[1])
        decompile(node->son[1], outfile);

        break; 

        case AST_CMD_READ : 
        fprintf(outfile, "read"); 
        fprintf(outfile, " ");
        decompile(node->son[0], outfile);
        fprintf(outfile, ";\n");
        break; 

        case AST_CMD_RETURN : 
        fprintf(outfile, "return"); 
        fprintf(outfile, " ");
        decompile(node->son[0], outfile);
        fprintf(outfile, ";\n");
        break; 

        case AST_CMD_LOOP : 
        fprintf(outfile, "loop"); 
        fprintf(outfile, "(");
        decompile(node->son[0], outfile);
        fprintf(outfile, ")");
        fprintf(outfile, "{\n");
        decompile(node->son[1], outfile);

        fprintf(outfile, "};\n");
        break;

        case AST_CMD_IF : 
        fprintf(outfile, "if"); 
        fprintf(outfile, "(");
        decompile(node->son[0], outfile);
        fprintf(outfile, ")");
        fprintf(outfile, " then{ \n");
        decompile(node->son[1], outfile);
        fprintf(outfile, "}");
        if(node->son[2]){
          fprintf(outfile, " else{\n");
          decompile(node->son[2], outfile);
          fprintf(outfile, " };\n");
        }else fprintf(outfile, ";\n");
        //fprintf(outfile, ";\n");
        break;

        case AST_LISTA_ELEMENTOS : 

        decompile(node->son[0], outfile);
        if(node->son[1]){
          fprintf(outfile, " ,");
          decompile(node->son[1], outfile);

        }
        
        break;

        case AST_STRING : 
        fprintf(outfile, "\"");
        decompile(node->son[0], outfile); 
        fprintf(outfile, "\"");

      break;

      case AST_CMD_PRINT : 
        fprintf(outfile, "print ");
        decompile(node->son[0], outfile); 
        fprintf(outfile, ";\n");

      break;

      case AST_PARENTESIS : 
        fprintf(outfile, "(");
        decompile(node->son[0], outfile); 
        fprintf(outfile, ")");

      break;

      case AST_TK : 
        decompile(node->son[0], outfile);
        if(node->son[1]){
          fprintf(outfile, "(");
          decompile(node->son[1], outfile);
          fprintf(outfile, ")");
        } 


      break;

      case AST_TK_VET : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, "[");
        decompile(node->son[1], outfile); 
        fprintf(outfile, "]");

      break;

      case AST_CMD_ADD : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " + ");
        decompile(node->son[1], outfile); 


      break;


      case AST_CMD_SUB : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " - ");
        decompile(node->son[1], outfile); 


      break;

      case AST_CMD_MUL : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " * ");
        decompile(node->son[1], outfile); 


      break;

      case AST_CMD_DIV : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " / ");
        decompile(node->son[1], outfile); 


      break;

      case AST_CMD_LT : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " < ");
        decompile(node->son[1], outfile); 


      break;


      case AST_CMD_GT : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " > ");
        decompile(node->son[1], outfile); 


      break;

      case AST_CMD_AND : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " and ");
        decompile(node->son[1], outfile); 


      break;

      case AST_CMD_OR : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " or ");
        decompile(node->son[1], outfile); 


      break;

      case AST_CMD_NOT : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " not ");
        decompile(node->son[1], outfile); 
        break;
      case AST_CMD_LE : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " <= ");
        decompile(node->son[1], outfile); 
        break;
      case AST_CMD_GE : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " >= ");
        decompile(node->son[1], outfile); 
        break;
      case AST_CMD_EQ : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " == ");
        decompile(node->son[1], outfile); 
        break;

      case AST_CMD_DIF : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " != ");
        decompile(node->son[1], outfile);       

      break;


      case AST_CMD_OP_NOT : 
        decompile(node->son[0], outfile); 
        fprintf(outfile, " not ");
        decompile(node->son[1], outfile);       

      break;

      case AST_LISTA_PARAM_EXP : 
       decompile(node->son[0], outfile);
        if(node->son[1]){
          fprintf(outfile, " ,");
          decompile(node->son[1], outfile);
        }
      break;



      default:
        fprintf(outfile, T_TOKEN_ERROR);

    }
  }
}
