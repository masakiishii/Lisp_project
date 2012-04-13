#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#define SPACE ' '
//#define COMMA ','
//#define NUMBER 'n'
//#define STRING 's'

//#define L_THAN '<'
//#define M_THAN '>'
//#define VARIABLE 'v'
//#define ARGUMENT 'a'
//#define FUNC 'f'
//#define DEF 'd'
//#define IF 'i'
//#define SETQ 'S'

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
  T_STRING
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
int eval_tree(cons_t *);

/* global */
extern char **tree_pointer;
extern int than_flag;

