#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_BACKET 64
#define ARG_STACK    8
#define ARG_LENGTH  64

typedef enum Type {
  T_BEGIN,
  T_END,
  OP_ADD,
  OP_SUB,
  OP_MULT,
  OP_DEV,
  L_THAN,
  M_THAN,
  T_NUMBER,
  T_STRING,
  T_FUNC,
  T_IF,
  T_SETQ,
  T_DEFUN,
  T_ARGUMENT,
  TRUE_FLAG,
  FALSE_FLAG,
  ZERO_FLAG,
} Type;

typedef struct cons_t {
	Type type;
	int define_func_flag;
	union{
		struct cons_t *car;
		int ivalue;
		char *svalue;
	};
	struct cons_t *cdr;
} cons_t;

typedef struct h_table {
    char *symbol;
	int i_val;
	struct h_table *next;
} h_table;

typedef struct f_table {
	cons_t fn_t;
	struct f_table *next;
} f_table;

typedef struct stack {
	int stack_arg;
	struct stack *next;
} stack;


char **tokenize(void);
cons_t *parse(char **);
cons_t *iread(void);
void print_tree(cons_t *,int);
void print_test(char **);
cons_t eval_tree(cons_t *);
void hash_val(cons_t *);
void makenull(cons_t *h_val[]);
int search_hash(cons_t *);
int hash(char );
void defun_eval(cons_t *, cons_t *);
void arg_numbering(cons_t *);
void hash_func(cons_t *);
cons_t search_func_hash(cons_t *);
void stack_push(int, int);
void stack_pop(int);
int stack_get_topindex(int);

/* global */
extern char **tree_pointer;
extern Type than_flag;
extern int if_flag;
extern int h_null_flag;
extern int f_null_flag;
extern int s_null_flag;
extern h_table *hashtable[HASH_BACKET];
extern f_table *functable[HASH_BACKET];
extern int setq_flag;
extern int defun_flag;
extern cons_t *defun_pointer;
extern int stacktable[ARG_STACK][ARG_LENGTH];
extern int stack_index[ARG_STACK];
extern int search_setq_val_flag;

#define IF_ON    1
#define IF_OFF   0
#define DEFUN_ON  1
#define DEFUN_OFF 0
#define ARGUEMENT_NUM 1
#define ON 1
#define OFF 0
