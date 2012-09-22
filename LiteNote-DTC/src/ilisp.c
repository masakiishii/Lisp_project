#include <ilisp.h>

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
	char **tmp_token;
	ConsCell *tmp_cell;
	FILE *fp = fopen(input[1], "r");;

	if(fp == NULL) {
		fprintf(stderr, "Error! File is not open.");
		fclose(fp);
		exit(EXIT_FAILURE);
	}

	Tokenizer *t = new_Tokenizer();
	Parser *p = new_Parser();
	VirtualMachineByteCodeLine *func  = new_VirtualMachineByteCodeLine();

	while(fgets(line, 256, fp) != NULL) {
		fprintf(stderr, "%s\n", line);
		ilisp_main(t, p, line, func);
	}

	while(freelist_token_stack--) {
		tmp_token = t->freelist[freelist_token_stack];
		t->delete(tmp_token, t);
	
	}
	while(freelist_cell_stack--) {
		tmp_cell = p->freelist[freelist_cell_stack];
		p->delete(tmp_cell, p);
	
	}
	fclose(fp);
	free(t);
	free(p);
	free(func->code);
	free(func);
}

ConsCell *rootPointer;
void ilisp_main(Tokenizer *t, Parser *p, char *line, VirtualMachineByteCodeLine *func)
{
	char **token = t->spliter(line);
	treePointer = token;
	ConsCell *root = p->parser(token);
	rootPointer = root;
	int reg[256];

#ifdef DEBUG_MODE
	DBG_P("==========<<<Dump>>>===========");
	t->dump(token);
	p->dump(root, 0);
#endif

	Compiler *c = new_Compiler();
	VirtualMachine *vm = new_VirtualMachine();

//	func = (VirtualMachineByteCodeLine *)imalloc(sizeof(VirtualMachineByteCodeLine));
//	func->index = 0;
//	func->cons = tree_head;
	func->cons = root;
	c->compile(root, func, 0);
	func->code[func->index].op = OPRET;
	func->code[func->index].reg0 = 0;
	func->size = func->index-1;

	if(defun_flag == OFF) {
		fprintf(stderr, "%d\n", vm->DirectThreadedCode_Run(func, reg));
	}
	c->delete(c);
	t->delete(token, t);
	p->delete(rootPointer, p);
	vm->delete(vm);
	defun_flag = OFF;
}
