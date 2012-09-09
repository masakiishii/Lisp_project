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
	DBG_P("=====<<<parse>>>=====");
	if((*token_array) == NULL) {
		return NULL;
	}
	
	ConsCell_t *head = new_ConsCell();

	switch(**token_array) {
	
	case '(' :
		DBG_P("<<<'('>>>=");
		head->celltype = T_BEGIN;
		treePointer++;
		head->car = parse(treePointer);
		head->cdr = parse(treePointer);
		break;

	case ')' :
		DBG_P("<<<')'>>>=");
		head->celltype = T_END;
		treePointer++;
		break;
	   
	case '+' : case '-' : case '*' : case '/' :
	case '<' : case '>' :
		DBG_P("<<<'OP'>>>=");
		head->celltype = T_OPERATOR;
		head->svalue = *token_array;
		treePointer++;
		head->cdr = parse(treePointer);
		break;

	default :
		if(isdigit(**token_array)) {
			DBG_P("<<<'NUM'>>>=");
			head->celltype = T_NUMBER;
			head->ivalue = strtol(*token_array, NULL, 10);
			treePointer++;
			head->cdr = parse(treePointer);
		}else{
			DBG_P("<<<'STR'>>>=");
			head->celltype = T_STRING;
			head->svalue = *token_array;
			treePointer++;
			head->cdr = parse(treePointer);
		}
		break;
	}
	return head;
}

void Tree_Dump(ConsCell_t *head, int level)
{
	DBG_P("=====<<<Tree_Dump>>>=====");
	int i;
	if(head == NULL) {

	}else{
		switch(head->celltype){
		case T_BEGIN    :
			if(head->cdr != NULL) {
				Tree_Dump(head->cdr, level+1);
			}else if( (head->cdr == NULL) && (level != 0) ){
				Tree_Dump(head->cdr, level+1);
			}
			for(i=0;i<level;i++)
				DBG_P("\t");
			DBG_P("(");
			Tree_Dump(head->car, level+1);
			break;
		case T_END     :
			for(i=0;i<level;i++)
				DBG_P("\t");
			DBG_P(")");
			break;
		case T_OPERATOR     :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				DBG_P("\t");
			DBG_P("%s", head->svalue);
			break;
		case T_NUMBER   :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				DBG_P("\t");
			DBG_P("%d", head->ivalue);
			break;
		case T_STRING   :
			Tree_Dump(head->cdr, level+1);
			for(i=0;i<level;i++)
				DBG_P("\t");
			DBG_P("S:%s", head->svalue);
			break;
		default :
			break;
		}
	}
}
