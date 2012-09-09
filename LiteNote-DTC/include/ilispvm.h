#ifndef LISP_H
#define LISP_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#ifdef DEBUG_MODE
#define DBG_P(...) {\
		fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__);	\
		fprintf(stderr, __VA_ARGS__);						\
		fprintf(stderr, "\n");								\
	}											
#else
#define DBG_P(...) {	\
	}
#endif


#define HASH_BACKET 64
#define TOKENSIZE 1024
#define ON 1
#define OFF 0

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
	LESSTHAN,
	L_EQUAL,
	GREATERTHAN,
	G_EQUAL,
	IF,
	JUMP,
	DEFUN,
	MOV,
	CALL,
	RET
};

typedef struct Token_t {
	Type type;
	char *str;
} Token_t;

typedef struct ConsCell_t {
	Type type;
	union {
		struct ConsCell_t *car;
		int ivalue;
		char *svalue;
	};
	struct ConsCell_t *cdr;
} ConsCell_t;

typedef struct ByteCode_t {
	enum opcode op;
	int reg0;
	union {
		int reg1;
		int data1;
	};
	union {
		int reg2;
		int data2;
		struct ByteCode_t *pc2;
	};
} ByteCode_t;

typedef struct VM_Instruction_Set {
	ByteCode_t code[256];
	int index;
	ConsCell_t *cons;
} VM_Instruction_Set;

typedef struct FuncTable_t {
	VM_Instruction_Set *fn_t;
	char *key;
	struct FuncTable_t *next;
} FuncTable_t;


//=====global value=====
extern int token_pointer;
extern Token_t *treePointer;
extern int f_null_flag;
extern int defun_flag;

//=====function=======
char *skip_space(char *);
Token_t *tokenize(char *);
void push_token(Token_t *, Token_t *);
Token_t parse_begin(char *);
Token_t parse_end(char *);
Token_t parse_operater(char *);
Token_t parse_number(char *);
Token_t parse_symbol(char *);
ConsCell_t *parse(Token_t *);
int VirtualMachine_DirectThreadedCode_Run(ByteCode_t *,int*);
int main(int, char **);
void readline_main(void);
void file_main(char **);
int hash(char*);
void make_hashtable_null(FuncTable_t **);
void hash_put(char *,VM_Instruction_Set *);
VM_Instruction_Set *search_func_hash(char *);
void generatecoder(ConsCell_t *, VM_Instruction_Set *, int);
#endif 
