#include "ilispvm.h"

char **treePointer = NULL;
int setq_flag = 0;
int defun_flag = OFF;
int defun_call = OFF;

ConsCell_t *new_ConsCell(void)
{
	ConsCell_t *Cell = (ConsCell_t *)malloc(sizeof(ConsCell_t));
	Cell->celltype = 0;
	Cell->car = NULL;
	Cell->ivalue = 0;
	Cell->svalue = NULL;
	Cell->cdr = NULL;
	return Cell;
}

ConsCell_t *parse(char **token_array)
{
	if((*token_array) == NULL) {
		return NULL;
	}

	ConsCell_t *head = (ConsCell_t *)malloc(sizeof(ConsCell_t));

	switch(**token_array){
	
	case '(' :
		head->celltype = T_BEGIN;
		treePointer++;
		head->car = parse(treePointer);
		head->cdr = parse(treePointer);
		break;

	case ')' :
		head->celltype = T_END;
		treePointer++;
		break;
	   
	case '-' :
		if(isalnum(*(*token_array+1))) {
			head->celltype = T_NUMBER;
			head->ivalue = strtol(*token_array, NULL, 10);
			treePointer++;
			head->cdr = parse(treePointer);

		}else{
			head->celltype = T_SUB;
			treePointer++;
			head->cdr = parse(treePointer);
		}
		break;

	case '+' :
		head->celltype = T_ADD;
		treePointer++;
		head->cdr = parse(treePointer); 
		break;

	case '*' :
		head->celltype = T_MUL;
		treePointer++;
		head->cdr = parse(treePointer); 
		break;

	case '/' :
		head->celltype = T_DIV;
		treePointer++;
		head->cdr = parse(treePointer); 
		break;

	case '<' :
		head->celltype = T_LT;
		treePointer++;
		head->cdr = parse(treePointer);
		break;

	case '>' :
		head->celltype = T_GT;
		treePointer++;
		head->cdr = parse(treePointer);
		break;

	default :
		if(isdigit(**token_array)) {
			head->celltype = T_NUMBER;
			head->ivalue = strtol(*token_array, NULL, 10);
			treePointer++;
			head->cdr = parse(treePointer);
		}else if(isalpha(**token_array)) {
			if((strncmp(*token_array, "if", 3) == 0)) {
				head->celltype = T_IF;
				head->svalue = *token_array;
				treePointer++;
				head->cdr = parse(treePointer);
			}else if((strncmp(*token_array, "setq", 5) == 0)) {
				setq_flag = 1;
				head->celltype = T_SETQ;
				treePointer++;
				head->cdr = parse(treePointer);
			}else if((strncmp(*token_array, "defun", 6) == 0)) {
				head->celltype = T_DEFUN;
				defun_flag = ON;
				treePointer++;
				head->cdr = parse(treePointer);
			}else{
			    if((strncmp(*(token_array-1), "defun", 6) == 0)) {
					head->celltype = T_FUNC;				
					head->svalue = *token_array;
					treePointer++;
					head->cdr = parse(treePointer);
				}else if((**(token_array-1) == '(')) {
					if(defun_call == OFF) {
						head->celltype = T_ARGUMENT;
						head->svalue = *token_array;
						treePointer++;
						head->cdr = parse(treePointer);
					}else{
						head->celltype = T_FUNC;				
						head->svalue = *token_array;
						treePointer++;
						head->cdr = parse(treePointer);
					}
				
				}else if((defun_flag == ON) && (**(token_array-1) != '(') ) {
					head->celltype = T_ARGUMENT;
					head->svalue = *token_array;
					treePointer++;
					head->cdr = parse(treePointer);
				}else{
					head->celltype = T_STRING;				
					head->svalue = *token_array;
					treePointer++;
					head->cdr = parse(treePointer);
				}
			}
		}
		break;
	}
	return head;

}

void Tree_Dump(ConsCell_t *head, int level)
{
	int i;

	if(head == NULL){
		fprintf(stderr,"error!\n");
	}else{

		switch(head->celltype){
		case T_BEGIN    :
			if(head->cdr != NULL) {
				Tree_Dump(head->cdr, level+1);
			}else if( (head->cdr == NULL) && (level != 0) ){
				Tree_Dump(head->cdr, level+1);
			}
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'('\n");
			Tree_Dump(head->car, level+1);
			break;
		case T_END :
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"')'\n");
			break;
		case T_ADD     :
			Tree_Dump(head->cdr, level+1);

			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'+'\n");
			break;

		case T_SUB     :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'-'\n");
			break;

		case T_MUL    :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'*'\n");
			break;

		case T_DIV     :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'/'\n");
			break;

		case T_LT    :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'<'\n");
			break;

		case T_GT    :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'>'\n");
			break;

		case T_NUMBER   :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"%d\n", head->ivalue);
			break;

		case T_IF       :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"if\n");
			break;

		case T_SETQ     :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"setq\n");
			break;

		case T_DEFUN    :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"defun\n");
			break;

		case T_FUNC   :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"F:%s\n", head->svalue);
			break;

		case T_STRING   :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"S:%s\n", head->svalue);
			break;


		case T_ARGUMENT :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"A:%d\n", head->ivalue);
			break;
		}
	}

}
