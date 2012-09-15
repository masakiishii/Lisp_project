#include "ilisp.h"

void ilisp_shell(void)
{
	/* char **tokenized_buf; */
	/* ConsCell *tree_head; */
	/* VirtualMachineByteCodeLine *func; */
	/* char *input; */
	/* int reg[256]; */
	
	/* while(1) { */
	/* 	input = (char *)readline(">>>"); */
	/* 	add_history(input); */
	/* 	if(input == NULL){ */
	/* 		break; */
	/* 	} */
	/* 	fprintf(stderr, "%s\n", input); */
	/* 	tokenized_buf = tokenize(input); */
	/* 	treePointer = tokenized_buf; */
	/* 	tree_head = parse(tokenized_buf); */
	/* 	func = (VirtualMachineByteCodeLine *)malloc(sizeof(VirtualMachineByteCodeLine)); */
	/* 	func->index = 0; */
	/* 	func->cons = tree_head; */
	/* 	Compiler(tree_head, func, 0); */
	/* 	func->code[func->index].op = OPRET; */
	/* 	func->code[func->index].reg0 = 0; */
	/* 	if(defun_flag == OFF) { */
	/* 		fprintf(stderr, "%d\n", VirtualMachine_DirectThreadedCode_Run(func->code, reg)); */
	/* 	} */
	/* 	defun_flag = OFF; */
	/* } */
}

void ilisp_script(char **input)
{
	char line[256] = {0};
	FILE *fp = fopen(input[1], "r");;

	if(fp == NULL) {
		fprintf(stderr, "Error! File is not open.");
		fclose(fp);
		exit(EXIT_FAILURE);
	}

	Tokenizer *t = new_Tokenizer();
	Parser *p = new_Parser();

	while(fgets(line, 256, fp) != NULL) {
		fprintf(stderr, "%s\n", line);
		ilisp_main(t, p, line);
	}
	fclose(fp);
	free(t);
	free(p);
}

void ilisp_main(Tokenizer *t, Parser *p, char *line)
{
	char **token = t->spliter(line);
	ConsCell *root = p->parser(token);
	VirtualMachineByteCodeLine *func;
	int reg[256];

#ifdef DEBUG_MODE
	DBG_P("==========<<<Dump>>>===========");
	t->dump(token);
	p->dump(root);
#endif

	Compiler *c = new_Compiler();
	VirtualMachine *vm = new_VirtualMachine();

	func = (VirtualMachineByteCodeLine *)malloc(sizeof(VirtualMachineByteCodeLine));
	func->index = 0;
//	func->cons = tree_head;
	func->cons = root;
	c->compiler(root, func, 0);
	func->code[func->index].op = OPRET;
	func->code[func->index].reg0 = 0;

	if(defun_flag == OFF) {
		fprintf(stderr, "%d\n", vm->DirectThreadedCode_Run(func->code, reg));
	}
	defun_flag = OFF;

	c->delete(c);
	t->delete(token);
	p->delete(root);
	vm->delete(vm);
}
