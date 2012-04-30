#include "ilisp.h"

token_t *treePointer = NULL;

cons_t *parse(token_t *t)
{

	/* if(t->type == T_END) { */
	/* 	return NULL; */
	/* } */

	cons_t *treehead = (cons_t *)malloc(sizeof(cons_t));

	switch(t->type) {

	case T_BEGIN :
		treehead->type = T_BEGIN;
		treehead->svalue = t->str;
		treePointer++;
		treehead->car = parse(treePointer);
		treehead->cdr = parse(treePointer);
		break;

	case T_END :
		treehead->type = T_END;
		treehead->svalue = t->str;
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

	}
	return treehead;
}
