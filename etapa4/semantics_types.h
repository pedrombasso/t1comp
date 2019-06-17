#ifndef __SEMANTICS_TYPE__
#define __SEMANTICS_TYPE__

typedef int ID_TYPE;
#define ID_TYPE_SCALAR 1
#define ID_TYPE_VECTOR 2
#define ID_TYPE_FUNCTION 3

typedef int VAL_TYPE;
#define VAL_TYPE_INT 11
#define VAL_TYPE_FLOAT 12
#define VAL_TYPE_BYTE 13

#define VAL_TYPE_CHAR 14
#define VAL_TYPE_STRING 15

#define VAL_TYPE_UNIT 16

typedef struct param_list_node
{
  VAL_TYPE valueType;
  struct param_list_node *next;
} PARAM_LIST;

typedef struct data_type
{
  ID_TYPE identifierType;    /* used for identifier, can be either VECTOR, SCALAR or FUNCTION */
  VAL_TYPE valueType;        /* value of the expression containing the symbol,
                              * e.g. INT if it's a vector of int, or CHAR if it's a function returning char, etc. */
  PARAM_LIST *params;         /* used for functions, stores the types of the params of the function*/
  int paramsLength;			/*Used to determine whether an assignment to a vector is out of range*/
} DATA_TYPE;

#endif
