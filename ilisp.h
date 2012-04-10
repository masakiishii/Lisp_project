#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BEGIN '('
#define OP_ADD '+'
#define OP_SUB '-'
#define END ')'
#define SPACE ' '
#define COMMA ','
#define NUMBER 'n'
#define STRING 's'
#define MULT '*'
#define DEV '/'
#define L_THAN '<'
#define M_THAN '>'
#define VARIABLE 'v'
#define ARGUMENT 'a'
#define FUNC 'f'
#define DEF 'd'
#define IF 'i'
#define SETQ 'S'


int token(void);

typedef struct cons_t{
  enum type;
  union{
	struct cons_t *car;
	int ivalue;
	char *svalue;
  };
  struct cons_t *cdr;
}cons_t;

enum = Type { BEGIN = '(' , END = ')' , OP_ADD = '+' , OP_SUB = '-' , OP_MULT = '*' , OP_DEV = '/' ,
              SPACE = ' ' , COMMA = ',' , NUMBER = 'n' , STRING = 's' }; 
