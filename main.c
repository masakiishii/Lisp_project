#include <stdio.h>
#include <readline/readline.h>
#include "ilisp.h"

int main(void)
{
	cons_t *tree_head;
	cons_t answer_tree;

	while(1){
		tree_head = iread();	
		if(tree_head == NULL){
			break;
		}

		print_tree(tree_head, 0);
		answer_tree = eval_tree(tree_head);

		if( (than_flag == TRUE_FLAG) && (if_flag == IF_OFF) ){
			printf("T\n");
		}else if( (than_flag == FALSE_FLAG) && (if_flag == IF_OFF) ){
			printf("Nil\n");
		}else{
				printf("%d\n", answer_tree.ivalue);
		}
		
		than_flag = ZERO_FLAG;
		if_flag = IF_OFF;
	}
	printf("bye\n");

	return 0;
}
