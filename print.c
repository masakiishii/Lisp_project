#include "ilisp.h"

void print_tree(cons_t *tree, int n)
{
	int i;

	if(tree == NULL){
		for(i=0;i<n;i++)
			printf("\t");
		printf("')'\n");
	}else{

		switch(tree->type){


		case T_BEGIN    :
			if(tree->cdr != NULL) {
				print_tree(tree->cdr, n+1);
			}
			for(i=0;i<n;i++)
				printf("\t");
			printf("'('\n");
			print_tree(tree->car, n+1);
			break;

		case OP_ADD     :
			print_tree(tree->cdr, n+1);

			for(i=0;i<n;i++)
				printf("\t");
			printf("'+'\n");
			break;

		case OP_SUB     :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("\t");
			printf("'-'\n");
			break;

		case OP_MULT    :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("\t");
			printf("'*'\n");
			break;

		case OP_DEV     :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("\t");
			printf("'/'\n");
			break;

		case L_THAN     :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("\t");
			printf("'<'\n");
			break;

		case M_THAN    :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("\t");
			printf("'>'\n");
			break;

		case T_NUMBER   :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("\t");
			printf("%d\n", tree->ivalue);
			break;

		case T_IF       :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("\t");
			printf("if\n");
			break;

		case T_STRING   :
			print_tree(tree->cdr, n+1);
			for(i=0;i<n;i++)
				printf("\t");
			printf("%s\n", tree->svalue);
			break;
		}
	}
}
