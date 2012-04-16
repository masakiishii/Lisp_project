#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum Type {
  T_BEGIN,
  T_END,
  OP_ADD,
  OP_SUB,
  OP_MULT,
  OP_DEV,
  L_THAN,
  M_THAN,
  /*  T_SPACE,*/
/*  T_COMMA,*/
  T_NUMBER,
  T_STRING,
  T_IF,
  TRUE_FLAG,
  FALSE_FLAG,
  ZERO_FLAG,
} Type;

typedef struct cons_t {
	Type type;
	union{
		struct cons_t *car;
		int ivalue;
		char *svalue;
  };
  struct cons_t *cdr;
} cons_t;

char **tokenize(void);
cons_t *parse(char **);
cons_t *iread(void);
void print_tree(cons_t *,int);
void print_test(char **);
cons_t eval_tree(cons_t *);
cons_t *eval_string(cons_t *);


/* global */
extern char **tree_pointer;
extern Type than_flag;
extern int if_flag;

#define IF_ON    1
#define IF_OFF   0
