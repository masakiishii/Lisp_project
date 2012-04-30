#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef enum Type {
	T_BEGIN,
	T_END,
	T_OPERATOR,
	T_NUMBER,
	T_STRING
} Type;


enum opcode {
	SET,
	ADD,
	SUB,
	MULT,
	DEV,
	RET
};

typedef struct token {
	Type type;
	char *str;
} token_t;

typedef struct cons_t {
	Type type;
	union {
		struct cons_t *car;
		int ivalue;
		char *svalue;
	};
	struct cons_t *cdr;
} cons_t;

typedef struct op {
	enum opcode op;
	int reg0;
	union {
		int reg1;
		int data1;
		struct op *pc1;
	};
	union {
		int reg2;
		int data2;
	};
} bytecode_t;

typedef struct func_t {
	bytecode_t code[256];
	int index;
} func_t;

//=====global value=====
extern int token_pointer;
extern token_t *treePointer;


//=====function=======
char *skip_space(char *);
token_t *tokenize(char *);
void push_token(token_t *, token_t *);
token_t parse_begin(char *);
token_t parse_end(char *);
token_t parse_operater(char *);
token_t parse_number(char *);
token_t parse_symbol(char *);
cons_t *parse(token_t *);
int vm_run(bytecode_t *);
int main(int, char **);
void readline_main(void);
void file_main(char **);
