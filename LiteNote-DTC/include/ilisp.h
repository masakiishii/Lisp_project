#ifndef LISP_H
#define LISP_H
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define HASH_BACKET 64
#define TOKENSIZE 1024
#define FREELIST 8
#define ON 1
#define OFF 0
#define EOL '\0'


//=======<<<DEBUG MODE>>>=======
#ifdef DEBUG_MODE
#define DBG_P(fmt, ...) {\
		fprintf(stderr, fmt, ##__VA_ARGS__);					\
		fprintf(stderr, "\n");								\
	}											
#define DBG_PL(fmt, ...) {\
		fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__);	\
		fprintf(stderr, fmt, ##__VA_ARGS__);				\
		fprintf(stderr, "\n");								\
	}											
#else
#define DBG_P(fmt, ...) {\
	}
#define DBG_PL(fmt, ...) {\
	}

#endif
//==============================

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

typedef enum OpCode {
	OPLOAD,
	OPADD,
	OPSUB,
	OPMUL,
	OPDIV,
	OPLT,
	OPGT,
	OPIF,
	OPJMP,
	OPMOV,
	OPCALL,
	OPRET
} OpCode;


typedef struct _Token {
	CellType type;
	char *str;
} Token;

typedef struct _ConsCell {
	CellType celltype;
	union {
		struct _ConsCell *car;
		int ivalue;
		char *svalue;
	};
	struct _ConsCell *cdr;
} ConsCell;

typedef struct _ByteCode {
	OpCode op;
	int reg0;
	union {
		int reg1;
		int data1;
	};
	union {
		int reg2;
		int data2;
		struct _ByteCode *pc2;
	};
} ByteCode;

typedef struct _VirtualMachineByteCodeLine {
	ByteCode code[256];
	int index;
	ConsCell *cons;
} VirtualMachineByteCodeLine;

typedef struct _FuncTable {
	VirtualMachineByteCodeLine *fn_t;
	char *key;
	struct _FuncTable *next;
} FuncTable;

typedef struct _Tokenizer {
	char **(*spliter)(char *line);
	void (*delete)(char **token, struct _Tokenizer *t);
	void (*dump)(char **token);
	char **freelist[FREELIST];
} Tokenizer;

typedef struct _Parser {
	ConsCell *(*parser)(char **token);
	void (*delete)(ConsCell *root, struct _Parser *p);
	void (*dump)(ConsCell *root, int level);
	ConsCell *freelist[FREELIST];
} Parser;

typedef struct _Compiler {
	void (*compiler)(ConsCell *root, VirtualMachineByteCodeLine *func, int r);
	void (*delete)(struct _Compiler *c);
} Compiler;

typedef struct _VirtualMachine {
	int (*DirectThreadedCode_Run)(ByteCode *bytecode, int *op);
	void (*delete)(struct _VirtualMachine *vm);
	void (*dump)(ByteCode *bytecode);
} VirtualMachine;


//=====================<<<Global Value>>>===========================
extern int token_pointer;
extern char **treePointer;
extern ConsCell *rootPointer;
extern int f_null_flag;
extern int setq_flag;
extern int defun_flag;
extern int defun_call;
extern int freelist_token_stack;
extern int freelist_cell_stack;
//=====================<<<Function>>================================
int main(int argc, char **argv);
void ilisp_shell(void);
void ilisp_script(char **input);
void ilisp_main(Tokenizer *t, Parser *p, char *line, VirtualMachineByteCodeLine *func);

void *imalloc(size_t size);

Tokenizer *new_Tokenizer(void);
char **Tokenizer_spliter(char *line);
void Tokenizer_delete(char **token, Tokenizer *t);
void Tokenizer_dump(char **token);


ConsCell *new_ConsCell(void);
Parser *new_Parser(void);
void Parser_delete(ConsCell *root, Parser *p);
ConsCell *Parser_parser(char **token);
void Parser_Dump(ConsCell *root, int level);


Compiler *new_Compiler(void);
void Compiler_delete(Compiler *c);
void Compiler_compile(ConsCell *root, VirtualMachineByteCodeLine *func, int r);


VirtualMachine *new_VirtualMachine(void);
int VirtualMachine_DirectThreadedCode_Run(ByteCode *op, int *sp);
void VirtualMachine_ByteCode_Dump(ByteCode *vmcode);
void VirtualMachine_delete(VirtualMachine *vm);

int hash(char *c);
void make_hashtable_null(FuncTable **h_val);
void hash_put(char *key,VirtualMachineByteCodeLine *value);
VirtualMachineByteCodeLine *search_func_hash(char *key);


#endif 
