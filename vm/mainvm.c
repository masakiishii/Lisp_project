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
 
}

void file_main(char **argv)
{
	token_t *tokenized_buf;
	cons_t *tree_head;
	func_t *func;

	char input[1024];
	FILE *fp = NULL;

	fp = fopen(argv[1], "r");

	if(fp == NULL) {
		printf("file not open.");
	}else{

		while(fgets(input, 1024, fp) != NULL) {
			printf("%s\n", input);
			tokenized_buf = tokenize(input);
			treePointer = tokenized_buf;
			tree_head = parse(tokenized_buf);
			func = (func_t *)malloc(sizeof(func_t));
			func->index = 0;
			generatecoder(tree_head, func, 0);
			func->code[func->index].op = RET;
			func->code[func->index].reg0 = 0;
			fprintf(stderr, "%d\n", vm_run(func->code));
			
		}
	}
}