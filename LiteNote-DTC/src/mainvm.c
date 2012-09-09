#include "ilispvm.h"

int main(int argc, char **argv)
{
	if(argc == 1) {
		readline_main();
	}else if(argc == 2) {
		file_main(argv);
	}else{
		printf("Error.\n");
	}

	return 0;
}

void readline_main(void)
{
	Token_t *tokenized_buf;
	ConsCell_t *tree_head;
	VM_Instruction_Set *func;
	char *input;
	int reg[256];
	
	while(1) {
		input = (char *)readline(">>>");
		add_history(input);
		if(input == NULL){
			break;
		}
		printf("%s\n", input);
		tokenized_buf = tokenize(input);
		treePointer = tokenized_buf;
		tree_head = parse(tokenized_buf);
		func = (VM_Instruction_Set *)malloc(sizeof(VM_Instruction_Set));
		func->index = 0;
		func->cons = tree_head;
		generatecoder(tree_head, func, 0);
		func->code[func->index].op = RET;
		func->code[func->index].reg0 = 0;
		if(defun_flag == OFF) {
			fprintf(stdout, "%d\n", VirtualMachine_DirectThreadedCode_Run(func->code, reg));
		}
		defun_flag = OFF;
	}
}


void file_main(char **argv)
{
	Token_t *tokenized_buf;
	ConsCell_t *tree_head;
	VM_Instruction_Set *func;
	char input[1024];
	FILE *fp = NULL;

	fp = fopen(argv[1], "r");

	if(fp == NULL) {
		printf("file not open.");
	}else{
		int reg[256];
		//VM_Instruction_Set *funclist[256];
		//size_t funcnum = 0;
		while(fgets(input, 1024, fp) != NULL) {
			printf("%s\n", input);
			tokenized_buf = tokenize(input);
			treePointer = tokenized_buf;
			tree_head = parse(tokenized_buf);
			func = (VM_Instruction_Set *)malloc(sizeof(VM_Instruction_Set));
			func->index = 0;
			func->cons = tree_head;
			generatecoder(tree_head, func, 0);
			func->code[func->index].op = RET;
			func->code[func->index].reg0 = 0;
			if(defun_flag == OFF) {
				fprintf(stderr, "%d\n", VirtualMachine_DirectThreadedCode_Run(func->code, reg));
			}
			defun_flag = OFF;
		}
		//size_t i;
		//for (i = 0; i < funcnum; i++) {
		//	free(funclist[i]);
		//}
	}
	free(treePointer);

	fclose(fp);
}
