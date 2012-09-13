#include <stdio.h>
#include <readline/readline.h>
#include "ilisp.h"

cons_t *defun_pointer;

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
	cons_t *tree_head;
	cons_t answer_tree;

		while(1) {
			tree_head = iread(NULL);
			if(tree_head == NULL) {
				break;
			}
//  		print_tree(tree_head, 0);
			if(defun_flag == DEFUN_ON) {
				defun_pointer = tree_head->car->cdr;
				defun_eval(defun_pointer->cdr->car, defun_pointer->cdr->cdr);
				arg_numbering(defun_pointer->cdr->car);
//			print_tree(tree_head, 0);
				hash_func(defun_pointer);
			}else{
				answer_tree = eval_tree(tree_head);

				if((than_flag == TRUE_FLAG) && (if_flag == IF_OFF)) {
					printf("T\n");
				}else if((than_flag == FALSE_FLAG) && (if_flag == IF_OFF)) {
					printf("Nil\n");
				}else if(setq_flag == 0 && defun_flag == DEFUN_OFF) {
					printf("%d\n", answer_tree.ivalue);
				}
			}

			setq_flag = 0;
			than_flag = ZERO_FLAG;
			if_flag = IF_OFF;
			defun_flag = DEFUN_OFF;
		}
		printf("bye\n");
}

void file_main(char **argv)
{
	cons_t *tree_head;
	cons_t answer_tree;
	char input[HEAP_SIZE];
	char **token_file = {NULL};
	FILE *fp = NULL;

	fp = fopen(argv[1], "r");

	if(fp == NULL) {
		printf("file not open");
	}else{

		while ( fgets(input, HEAP_SIZE, fp) != NULL) {
			printf("%s\n", input);
			tree_head = iread(input);
			if(tree_head == NULL) {
				break;
			}
//			print_tree(tree_head, 0);
			if(defun_flag == DEFUN_ON) {
				defun_pointer = tree_head->car->cdr;
				defun_eval(defun_pointer->cdr->car, defun_pointer->cdr->cdr);
				arg_numbering(defun_pointer->cdr->car);
				print_tree(tree_head, 0);
				hash_func(defun_pointer);
			}else{
				answer_tree = eval_tree(tree_head);

				if((than_flag == TRUE_FLAG) && (if_flag == IF_OFF)) {
					printf("T\n");
				}else if((than_flag == FALSE_FLAG) && (if_flag == IF_OFF)) {
					printf("Nil\n");
				}else if(setq_flag == 0 && defun_flag == DEFUN_OFF) {
					printf("%d\n", answer_tree.ivalue);
				}
			}

			setq_flag = 0;
			than_flag = ZERO_FLAG;
			if_flag = IF_OFF;
			defun_flag = DEFUN_OFF;
		}
		printf("bye\n");
	}
	fclose(fp);
}
