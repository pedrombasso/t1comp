#include "tacs.h"
#include <stdlib.h>
#include <stdio.h>

TAC * tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2){

  TAC* newTac;
  newTac = (TAC*) calloc(1,sizeof(TAC));
  newTac->type = type;
  newTac->res = res;
  newTac->op1 = op1;
  newTac->op2 = op2;
  newTac->prev = 0;
  newTac->next = 0;
  return newTac;
}


TAC* tacJoin(TAC* l1, TAC* l2){

  TAC *tac;
  if (!l1) return l2;
  if (!l2) return l1;
  for (tac = l2; tac->prev; tac = tac->prev)
  ;
  tac->prev = l1;
  l1->next = l2;
  return l2;
}


void tacPrintBack(TAC* last){

  TAC* tac;
  for(tac = last; tac; tac = tac->prev){
    fprintf(stderr, "TAC(");
    switch (tac->type) {
      case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
      case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
      case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
      case TAC_LE: fprintf(stderr, "TAC_LE"); break;
      case TAC_GE: fprintf(stderr, "TAC_GE"); break;
      case TAC_NE: fprintf(stderr, "TAC_NE"); break;
      case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;
      case TAC_AND: fprintf(stderr, "TAC_AND"); break;
      case TAC_OR: fprintf(stderr, "TAC_OR"); break;
      case TAC_LESS: fprintf(stderr, "TAC_LESS"); break;
      case TAC_GREATER: fprintf(stderr, "TAC_GREATER"); break;
      case TAC_NEG: fprintf(stderr, "TAC_NEG"); break;
      case TAC_MULT: fprintf(stderr, "TAC_MULT"); break;
      case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
      case TAC_DECLARACAO: fprintf(stderr, "TAC_DECLARACAO"); break;
      case TAC_FUNC: fprintf(stderr, "TAC_FUNC"); break;
      case TAC_VAR: fprintf(stderr, "TAC_VAR"); break;
      case TAC_VECTOR: fprintf(stderr, "TAC_VECTOR"); break;
      case TAC_EMPTY: fprintf(stderr, "TAC_EMPTY"); break;
      case TAC_READ: fprintf(stderr, "TAC_READ"); break;
      case TAC_MOVE_IND: fprintf(stderr, "TAC_MOVE_IND"); break;
      case TAC_PRINT: fprintf(stderr, "TAC_PRINT"); break;
      case TAC_RETURN: fprintf(stderr, "TAC_RETURN"); break;
      case TAC_BYTE: fprintf(stderr, "TAC_BYTE"); break;
      case TAC_SHORT: fprintf(stderr, "TAC_SHORT"); break;
      case TAC_LONG: fprintf(stderr, "TAC_LONG"); break;
      case TAC_FLOAT: fprintf(stderr, "TAC_FLOAT"); break;
      case TAC_DOUBLE: fprintf(stderr, "TAC_DOUBLE"); break;
      case TAC_DEF: fprintf(stderr, "TAC_DEF"); break;
      case TAC_VAR_INIT: fprintf(stderr, "TAC_VAR_INIT"); break;
      case TAC_VECTOR_INIT: fprintf(stderr, "TAC_VECTOR_INIT"); break;
      case TAC_PARAM: fprintf(stderr, "TAC_PARAM"); break;
      case TAC_EXPR_VECTOR: fprintf(stderr, "TAC_EXPR_VECTOR"); break;
      case TAC_EXPR: fprintf(stderr, "TAC_EXPR"); break;
      case TAC_EXPR_FUNC: fprintf(stderr, "TAC_EXPR_FUNC"); break;
      case TAC_ONEARG: fprintf(stderr, "TAC_ONEARG"); break;
      case TAC_JUMP: fprintf(stderr, "TAC_JUMP"); break;
      case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
      case TAC_END: fprintf(stderr, "TAC_END"); break;
      case TAC_BEGIN: fprintf(stderr, "TAC_BEGIN"); break;
      case TAC_JFALSE: fprintf(stderr, "TAC_JFALSE"); break;
      case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); break;
      case TAC_JTRUE: fprintf(stderr, "TAC_JTRUE"); break;
      case TAC_MOVE_INC :fprintf(stderr, "TAC_MOVE_INC"); break;



      default: fprintf(stderr, "TAC_UNKOWN"); break;
    }
    if (tac->res) fprintf(stderr, ", %s", tac->res->text); else fprintf(stderr, ", 0");
    if (tac->op1) fprintf(stderr, ", %s", tac->op1->text); else fprintf(stderr, ", 0");
    if (tac->op2) fprintf(stderr, ", %s", tac->op2->text); else fprintf(stderr, ", 0");
    fprintf(stderr, ")\n");

 }
}

TAC* tacGenerate(ASTREE *node){

  if (!node) return 0;

  int i = 0;

  TAC* code[MAX_SONS];

  TAC* result = 0;


  for (i=0; i< MAX_SONS; i++){

    code[i] = tacGenerate(node->son[i]);
  }


  switch (node->type) {


    case AST_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
    break;

    case AST_LE : result = makeOperation(TAC_LE, code[0], code[1]);
    break;

    case AST_GE : result = makeOperation(TAC_GE, code[0], code[1]);
    break;

    case AST_NE : result = makeOperation(TAC_NE, code[0], code[1]);
    break;

    case AST_EQ : result = makeOperation(TAC_EQ, code[0], code[1]);
    break;

    case AST_AND : result = makeOperation(TAC_AND, code[0], code[1]);
    break;

    case AST_OR : result = makeOperation(TAC_OR, code[0], code[1]);
    break;

    case AST_LESS : result = makeOperation(TAC_LESS, code[0], code[1]);
    break;

    case AST_GREATER : result = makeOperation(TAC_GREATER, code[0], code[1]);
    break;

    case AST_NEG : result = makeOperation(TAC_NEG, code[0], code[1]);
    //nao sei se é assim pq n sei se é operacao
    break;

    case AST_MULT : result = makeOperation(TAC_MULT, code[0], code[1]);
    break;

    case AST_ADD : result = makeOperation(TAC_ADD, code[0], code[1]);
    break;

    case AST_SUB : result = makeOperation(TAC_SUB, code[0], code[1]);
    break;

    case AST_DIV : result = makeOperation(TAC_DIV, code[0], code[1]);
    break;

    case AST_WHEN : result = makeWhen(code[0], code[1]);
    break;

    case AST_ELSE : result = makeWhenElse(code[0], code[1], code[2]);
    break;

    case AST_WHILE : result = makeWhile(code[0], code[1]);
    break;

    case AST_FOR : result = makeFor(code[0], code[1], code[2], code[3]);
    /// resolver a funcao pois nao sei, mas a chamada ta certa
    break;

    case AST_EMPTY :
    break;

    //------------------------------------------------------------------------------
    //como AST_BYTE e afins sao apenas palavras reservadas entao é vazio, faz sentido?
    //------------------------------------------------------------------------------
    case AST_BYTE :
    break;

    case AST_SHORT :
    break;

    case AST_LONG :
    break;

    case AST_FLOAT :
    break;

    case AST_DOUBLE :
    break;
    //------------------------------------------------------------------------------
    //------------------------------------------------------------------------------

    case AST_BLOCO : result = code[0];
    break;

    case AST_DECLARACAO : result = tacJoin(code[0], code[1]);
    break;

    case AST_FUNC_PARAM : result = makeFunc(code[0], code[1]->res, code[2], code[3]);
    break;
    //talvez de erro no symbol (NAME -> TK_IDENTIFIER)

    case AST_FUNC : result = tacJoin(code[0], code[1]);
    break;

    case AST_VAR_INIT : result = tacCreate(code[1]->type, code[0]->res, code[1]? code[1]->op1 : 0 , code[1]? code[1]->res : 0);
    break;


    case AST_VECTOR_INIT : result = makeVector(code[0], code[1], code[2]);
    break;
    //talvez de erro no symbol (NAME -> TK_IDENTIFIER)

    case AST_RETURN : result = tacJoin(code[0], tacCreate(TAC_RETURN, code[0]? code[0]->res : 0, 0, 0));
    break;

    case AST_READ : result = tacJoin(code[0], tacCreate(TAC_READ, code[0]->res, 0, 0));
    break;
    //talvez de erro no symbol (NAME -> TK_IDENTIFIER)

    case AST_CMDLIST : result = tacJoin(code[0], code[1]);
    break;

    case AST_EXPR_VECTOR : result = tacJoin(tacJoin(code[0],code[1]),result);
    break;
    //talvez de erro no symbol (NAME -> TK_IDENTIFIER)





//// --------------------------------------------------------------------------
//// --------------------------------------------------------------------------
///// ---------------EM DESENVOLVIMENTO----------------------------------------
//// --------------------------------------------------------------------------
//// --------------------------------------------------------------------------



    case AST_VAR : result = tacJoin(code[0],result);
    break;
    case AST_VECTOR : result = tacCreate(code[0]->type, code[0]->res,0,0);
    break;
    case AST_PRINT : result = tacJoin(code[0], tacCreate(TAC_PRINT, makeTemp(), node->symbol, 0));
    break;
    case AST_VALORLIST : result = tacJoin(code[0], code[1]);
    break;
    case AST_DEF : result = tacJoin(code[0], code[1]);
    break;
    case AST_PARAMLIST : result = tacJoin(code[0], code[1]);
    break;
    case AST_ARG : result = tacJoin(code[0], code[1]);
    break;
    case AST_PARAM : result = tacCreate(TAC_PARAM, node->symbol, 0, 0);
    break;
    case AST_EXPR : result = tacCreate(TAC_EXPR, code[0]->res, 0, 0);
    break;
    case AST_EXPR_FUNC : result = tacJoin(code[1], tacCreate(TAC_EXPR_FUNC, makeTemp(), code[0]->res, 0));
    break;
    case AST_ONEARG : result = tacJoin(code[0], tacCreate(TAC_EXPR, 0, code[0]?code[0]->res:0, 0));
    break;



    //defaut é assim mesmo? nao é uma recursao pra joinar a arvore toda?
    default: result = tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);
  }


  return result;
}

/* ---------------INSTRUCAO FOR NA ARVORE-------------
 KW_FOR '(' name '=' expr KW_TO expr ')' cmd {$$ = astreeCreate(AST_FOR, 0, $3, $5, $7, $9);}

  case AST_FOR:
      fprintf(FileTree,"for(");
      nodeType(node->son[0]);
      fprintf(FileTree,"= ");
      nodeType(node->son[1]);
      fprintf(FileTree,"to ");
      nodeType(node->son[2]);
      fprintf(FileTree,")\n");
      nodeType(node->son[3]);
    break;
*/

TAC* makeFor(TAC* variable, TAC* value1, TAC* maxvalue, TAC* cmd) {
  //fazer incremento

  HASH_NODE* targetEnd = makeLabel();
  HASH_NODE* targetBegin = makeLabel();

  HASH_NODE* var = makeTemp();

  TAC* labelBegin = tacCreate(TAC_LABEL, targetBegin, 0, 0);
  TAC* labelEnd = tacCreate(TAC_LABEL, targetEnd, 0, 0);

  TAC* varRefresh = tacCreate(TAC_MOVE_INC, variable->res, variable->res, 0);
  TAC* cont = tacCreate(TAC_SUB, var, maxvalue?maxvalue->res:0, variable->res);
  TAC* whenFalse = tacCreate(TAC_JFALSE, targetEnd, var, 0);
  TAC* whenTrue = tacCreate(TAC_JUMP, targetBegin, 0, 0);
  TAC* atrib = tacCreate(TAC_MOVE, variable->res, value1?value1->res:0, 0);

  return tacJoin(value1, tacJoin(maxvalue, tacJoin(atrib, tacJoin(labelBegin,tacJoin(cont, tacJoin(whenFalse, tacJoin(cmd, tacJoin(varRefresh, tacJoin(whenTrue, labelEnd)))))))));
}

//TAC* makeFor(TAC* op1, TAC* op2, TAC* valorLimite, TAC* cmd) {


//  return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(cont, code[1]), labelBegin), compareLess), code[2]), cont), whenTrue), labelEnd) ;
//}


//TAC* makeWhen(TAC* expr, TAC* then) {
//  HASH_NODE* targetElse = makeLabel();
//  HASH_NODE* targetEnd = makeLabel();
//
//  TAC* jumpEnd = tacCreate(TAC_JUMP, targetEnd, 0, 0);
//
//  TAC* labelEnd = tacCreate(TAC_LABEL, targetEnd, 0, 0);
//
//  return tacJoin(tacJoin(tacJoin(tacJoin(expr ,jumpEnd), then), jumpEnd), labelEnd);
//}

TAC* makeWhen(TAC* expr, TAC* then) {

  HASH_NODE* targetEnd = makeLabel();

  TAC* jumpEnd = tacCreate(TAC_JFALSE, targetEnd, expr?expr->res:0, 0);
  TAC* labelEnd = tacCreate(TAC_LABEL, targetEnd, 0, 0);

  return tacJoin(expr,tacJoin(jumpEnd,tacJoin(then,labelEnd)));
}


//// --------------------------------------------------------------------------
//// --------------------------------------------------------------------------
///// ---------------VERIFICAR POREM ACHO QUE TA PRONTO------------------------
//// --------------------------------------------------------------------------
//// --------------------------------------------------------------------------

TAC* makeWhenElse(TAC* expr, TAC* then, TAC* els) {
  HASH_NODE* targetElse = makeLabel();
  HASH_NODE* targetEnd = makeLabel();

  TAC* jumpElse = tacCreate(TAC_JFALSE, targetElse, expr->res, 0);
  TAC* jumpEnd = tacCreate(TAC_JUMP, targetEnd, 0, 0);

  TAC* labelElse = tacCreate(TAC_LABEL, targetElse, 0, 0);
  TAC* labelEnd = tacCreate(TAC_LABEL, targetEnd, 0, 0);

  return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(expr ,jumpElse), then), jumpEnd), labelElse), els), labelEnd);
}

TAC* makeWhile(TAC* expr, TAC* cmd) {
  HASH_NODE* targetBegin = makeLabel();
  HASH_NODE* targetEnd = makeLabel();

  TAC* jumpBegin = tacCreate(TAC_JUMP, targetBegin, 0, 0);
  TAC* jumpEnd = tacCreate(TAC_JFALSE, targetEnd, expr->res, 0);

  TAC* labelBegin = tacCreate(TAC_LABEL, targetBegin, 0, 0);
  TAC* labelEnd = tacCreate(TAC_LABEL, targetEnd, 0, 0);

  return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(labelBegin, expr), jumpEnd), cmd), jumpBegin), labelEnd);
}

TAC* makeFunc(TAC* type, HASH_NODE* symbol, TAC* params, TAC* cmds) {
  TAC* begin = tacCreate(TAC_BEGIN, symbol, 0, 0);
  TAC* end = tacCreate(TAC_END, symbol, 0, 0);

  return tacJoin(tacJoin(tacJoin(params, begin), cmds), end);
}

TAC* makeOperation(int type, TAC* op1, TAC* op2) {
  TAC* result;
  result = tacCreate(type, makeTemp(), op1? op1->res : 0, op2? op2->res : 0);
  result = tacJoin(op2, result);
  result = tacJoin(op1, result);
  return result;
}

TAC* makeVector(TAC* name, TAC* expr_ind, TAC* cmd){

  TAC *result = 0;


  result = tacJoin(name,result);
  result = tacJoin(expr_ind,result);
  result = tacJoin(cmd,result);

  result = tacCreate(TAC_MOVE_IND, name->res, expr_ind ? expr_ind->res : 0, cmd ? cmd->res : 0);


  return result;
}
