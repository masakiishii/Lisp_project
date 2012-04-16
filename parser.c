#include "ilisp.h"

char **tree_pointer = NULL;

cons_t *parse(char **t)
{
	if( (*t) == NULL){

		return NULL;
	}

	if((**t) == ')') {
		
		return NULL;
		
	}
	
	cons_t *head = (cons_t *)malloc(sizeof(cons_t));

	switch(**t){
	
	case '(' :
		head->type = T_BEGIN;
		tree_pointer++;
		head->car = parse(tree_pointer);
//		tree_pointer++;
		head->cdr = parse(tree_pointer);
//		head->cdr = NULL;
		break;
	   
	case '-' :
		if(isalnum(*(*t+1))){
			head->type = T_NUMBER;
			head->ivalue = strtol(*t, NULL, 10);
			tree_pointer++;
			head->cdr = parse(tree_pointer);

		}else{
			head->type = OP_SUB;
			tree_pointer++;
			head->cdr = parse(tree_pointer);
		}
		break;

	case '+' :
		head->type = OP_ADD;
		tree_pointer++;
		head->cdr = parse(tree_pointer); 
		break;

	case '*' :
		head->type = OP_MULT;
		tree_pointer++;
		head->cdr = parse(tree_pointer); 
		break;

	case '/' :
		head->type = OP_DEV;
		tree_pointer++;
		head->cdr = parse(tree_pointer); 
		break;

	case '<' :
		head->type = L_THAN;
		tree_pointer++;
		head->cdr = parse(tree_pointer);
		break;

	case '>' :
		head->type = M_THAN;
		tree_pointer++;
		head->cdr = parse(tree_pointer);
		break;

	default :
		if(isdigit(**t)){
			head->type = T_NUMBER;
			head->ivalue = strtol(*t, NULL, 10);
			tree_pointer++;
			head->cdr = parse(tree_pointer);

		}else if(isalpha(**t)){
//			if( strcmp(*t, "if") ){
			if( strncmp(*t, "if", 3) == 0 ) {
				head->type = T_IF;
				head->svalue = *t;
				tree_pointer++;
				head->cdr = parse(tree_pointer);
				tree_pointer++;
				head->cdr->cdr = parse(tree_pointer);
			}else{
				head->type = T_STRING;
				head->svalue = *t;
				tree_pointer++;
				head->cdr = parse(tree_pointer);
			}
		} 
		break;
	}

	return head;
}
