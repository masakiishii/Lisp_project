#ifndef LISP_H
#define LISP_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
		/* fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__);		\ */
//=======<<<DEBUG MODE>>>=======
#ifdef DEBUG_MODE
#define DBG_P(fmt, ...) {\
		fprintf(stderr, fmt, ##__VA_ARGS__);					\
		fprintf(stderr, "\n");								\
	}											
#else
#define DBG_P(fmt, ...) {						\
	}
#endif
//==============================

#define HASH_BACKET 64
#define TOKENSIZE 1024
#define ON 1
#define OFF 0



typedef enum CellType {
	T_BEGIN,
	T_END,
	T_NUMBER,
	T_ADD,
	T_SUB,
	T_MUL,
	T_DIV,
	T_LT,
	T_GT,
	T_IF,
	T_SETQ,
	T_DEFUN,
	T_FUNC,
	T_ARGUMENT,
	T_STRING
} CellType;

enum OpCode {
	OPLOAD,
	OPADD,
	OPSUB,
	OPMUL,
	OPDEV,
	OPLT,
	OPLEQ,
	OPGT,
	OPGEQ,
	OPIF,
	OPJMP,
	OPDEFUN,
	OPMOV,
	OPCALL,
	OPRET
};

typedef struct Token_t {
	CellType type;
	char *str;
} Token_t;

typedef struct ConsCell_t {
	CellType celltype;
	union {
		struct ConsCell_t *car;
		int ivalue;
		char *svalue;
	};
	struct ConsCell_t *cdr;
} ConsCell_t;

typedef struct ByteCode_t {
	enum OpCode op;
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


//=====<<<Global Value>>>=====
extern int token_pointer;
extern char **treePointer;
extern int f_null_flag;
extern int setq_flag;
extern int defun_flag;
extern int defun_call;


//=====<<<Function>>=======
char **tokenize(char *);
void Dump_Token(char **);
ConsCell_t *new_ConsCell(void);
ConsCell_t *parse(char **);
void Tree_Dump(ConsCell_t *, int);
int VirtualMachine_DirectThreadedCode_Run(ByteCode_t *,int*);
void VirtualMachine_ByteCode_Dump(ByteCode_t *);
int main(int, char **);
void readline_main(void);
void file_main(char **);
int hash(char*);
void make_hashtable_null(FuncTable_t **);
void hash_put(char *,VM_Instruction_Set *);
VM_Instruction_Set *search_func_hash(char *);
void generatecoder(ConsCell_t *, VM_Instruction_Set *, int);
#endif 
