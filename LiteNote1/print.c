#include "ilisp.h"

void print_tree(cons_t *tree, int n)
{
	int i;

	if(tree == NULL){
		for(i=0;i<n;i++)
			printf("  ");
		printf("')'\n");
	}else{

		switch(tree->type){


		case T_BEGIN    :
			if(tree->cdr != NULL) {
				print_tree(tree->cdr, n+1);
			}else if( (tree->cdr == NULL) && (n != 0) ){
				print_tree(tree->cdr, n+1);
			}
			for(i=0;i<n;i++)
				printf("  ");
			printf("'('\n");
			print_tree(tree->car, n+1);
			break;

		case OP_ADD     :
			print_tree(tree->cdr, n+1);

			for(i=0;i<n;i++)
				printf("  ");
			printf("'+'\n");
			break;

		case OP_SUB     :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("  ");
			printf("'-'\n");
			break;

		case OP_MULT    :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("  ");
			printf("'*'\n");
			break;

		case OP_DEV     :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("  ");
			printf("'/'\n");
			break;

		case LESS_THAN     :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("  ");
			printf("'<'\n");
			break;

		case GREATER_THAN    :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("  ");
			printf("'>'\n");
			break;

		case T_NUMBER   :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("  ");
			printf("%d\n", tree->ivalue);
			break;

		case T_IF       :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("  ");
			printf("if\n");
			break;

		case T_SETQ     :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("  ");
			printf("setq\n");
			break;

		case T_DEFUN    :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("  ");
			printf("defun\n");
			break;

		case T_FUNC   :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("  ");
			printf("F:%s\n", tree->svalue);
			break;

		case T_STRING   :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("  ");
			printf("S:%s\n", tree->svalue);
			break;


		case T_ARGUMENT :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("  ");
			printf("A:%d\n", tree->ivalue);
			break;


		}
	}
}
