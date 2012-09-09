#include "ilispvm.h"

Token_t *treePointer = NULL;

ConsCell_t *parse(Token_t *t)
{

	if(t->type == T_END) {
		treePointer++;
		return NULL;
	}

	ConsCell_t *treehead = (ConsCell_t *)malloc(sizeof(ConsCell_t));

	switch(t->type) {

	case T_BEGIN :
		treehead->type = T_BEGIN;
		treehead->svalue = t->str;
		treePointer++;
		treehead->car = parse(treePointer);
		treehead->cdr = parse(treePointer);
		break;

	case T_OPERATOR :
		treehead->type = T_OPERATOR;
		treehead->svalue = t->str;
		treePointer++;
		treehead->cdr = parse(treePointer);
		break;

	case T_STRING :
		treehead->type = T_STRING;
		treehead->svalue = t->str;
		treePointer++;
		treehead->cdr = parse(treePointer);
		break;

	case T_NUMBER :
		treehead->type = T_NUMBER;
		treehead->ivalue = strtol(t->str, NULL, 10);
		treePointer++;
		treehead->cdr = parse(treePointer);
		break;

	default :
		break;

	}
	return treehead;
}
