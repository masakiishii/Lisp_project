#include <stdio.h>
#include <readline/readline.h>
#include "ilisp.h"

int main(void)
{
	cons_t *tree_head;
	int answer;

	while(1){
		tree_head = iread();	
		if(tree_head == NULL){
			break;
		}

		print_tree(tree_head, 0);
		answer = eval_tree(tree_head);

		if( (than_flag == 1) && (answer == 1) ){
			printf("T\n");
		}else if( (than_flag == 1) && (answer == 0) ){
			printf("Nil\n");
		}else{
			printf("%d\n", answer);
		}
		
	}
	printf("bye\n");

	return 0;
}
