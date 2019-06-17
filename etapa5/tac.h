#ifndef TACS_HEADER
#define TACS_HEADER


#include "hash.h"


#define TAC_SYMBOL 0
#define TAC_LE 1
#define TAC_GE 2
#define TAC_NE 3
#define TAC_EQ 4
#define TAC_AND 5
#define TAC_OR 6
#define TAC_LESS 7
#define TAC_GREATER 8
#define TAC_NEG 9
#define TAC_MULT 10
#define TAC_ADD 11
#define TAC_SUB 12
#define TAC_DIV 13
#define TAC_DECLARACAO 14
#define TAC_FUNC 15
#define TAC_VAR 16
#define TAC_VECTOR 17

#define TAC_EMPTY 19
#define TAC_READ 20
#define TAC_PRINT 21
#define TAC_RETURN 22

#define TAC_BYTE 24
#define TAC_SHORT 25
#define TAC_LONG 26
#define TAC_FLOAT 27
#define TAC_DOUBLE 28


#define TAC_DEF 34

#define TAC_VAR_INIT 36
#define TAC_VECTOR_INIT 37


#define TAC_PARAM 40
#define TAC_EXPR_VECTOR 41
#define TAC_EXPR 42
#define TAC_EXPR_FUNC 43
#define TAC_ONEARG 44

#define TAC_BEGIN 45
#define TAC_END 46
#define TAC_LABEL 47
#define TAC_JUMP 48
#define TAC_JFALSE 49
#define TAC_MOVE 50
#define TAC_MOVE_IND 51
#define TAC_JTRUE 52
#define TAC_MOVE_INC 53





typedef struct tac_struct{
  int type;
  HASH_NODE * res;
  HASH_NODE * op1;
  HASH_NODE * op2;
  struct tac_struct * prev;
  struct tac_struct * next;

}TAC;

TAC* tacGenerate(ASTREE *node);
void tacPrintBack(TAC* lTAC);
TAC* tacJoin(TAC* l1, TAC* l2);
TAC* makeWhen(TAC* expr, TAC* then);
TAC* makeFor(TAC* op1, TAC* op2, TAC* valorLimite, TAC* cmd);
TAC* makeWhenElse(TAC* expr, TAC* then, TAC* els);
TAC* makeOperation(int type, TAC* op1, TAC* op2);
TAC* makeVector(TAC* symbol, TAC* expr_ind, TAC* cmd);
TAC* makeFunc(TAC* type, HASH_NODE* symbol, TAC* params, TAC* cmds);
TAC* makeWhile(TAC* expr, TAC* cmd) ;
TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2);

#endif
