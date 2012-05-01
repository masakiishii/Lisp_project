#include "ilispvm.h"

void generatecoder(cons_t *treehead, func_t *func, int r)
{
	cons_t *eval_pointer;

	switch(treehead->type){
	case T_BEGIN:
		generatecoder(treehead->car, func, r);
//		generatecoder(treehead->cdr, func, r+1);
		break;

	case  T_NUMBER:
		func->code[func->index].op = SET;
		func->code[func->index].reg0 = r;
		func->code[func->index].data1 = treehead->ivalue;
		func->index++;
		break;

	case T_OPERATOR:
		eval_pointer = treehead->cdr;
		if(strcmp(treehead->svalue, "+") == 0) {
			generatecoder(eval_pointer, func, r);
			while(eval_pointer->cdr != NULL){
				generatecoder(eval_pointer->cdr, func, r+1);
				func->code[func->index].op = ADD;
				func->code[func->index].reg0 = r;
				func->code[func->index].reg1 = r;
				func->code[func->index].reg2 = r+1;
				func->index++;
				eval_pointer = eval_pointer->cdr;
			}
			break;
		}else if(strcmp(treehead->svalue, "-") == 0) {
			generatecoder(eval_pointer, func, r);
			while(eval_pointer->cdr != NULL){
				generatecoder(eval_pointer->cdr, func, r+1);
				func->code[func->index].op = SUB;
				func->code[func->index].reg0 = r;
				func->code[func->index].reg1 = r;
				func->code[func->index].reg2 = r+1;
				func->index++;
				eval_pointer = eval_pointer->cdr;
			}
			break;
		}else if(strcmp(treehead->svalue, "*") == 0) {
			generatecoder(eval_pointer, func, r);
			while(eval_pointer->cdr != NULL){
				generatecoder(eval_pointer->cdr, func, r+1);
				func->code[func->index].op = MULT;
				func->code[func->index].reg0 = r;
				func->code[func->index].reg1 = r;
				func->code[func->index].reg2 = r+1;
				func->index++;
				eval_pointer = eval_pointer->cdr;
			}
			break;
		}else if(strcmp(treehead->svalue, "/") == 0) {
			generatecoder(eval_pointer, func, r);
			while(eval_pointer->cdr != NULL){
				generatecoder(eval_pointer->cdr, func, r+1);
				func->code[func->index].op = DEV;
				func->code[func->index].reg0 = r;
				func->code[func->index].reg1 = r;
				func->code[func->index].reg2 = r+1;
				func->index++;
				eval_pointer = eval_pointer->cdr;
			}
			break;
		}else if(strcmp(treehead->svalue, "<") == 0) {
			generatecoder(eval_pointer, func, r);
			generatecoder(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = LESSTHAN;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			break;
		}else if(strcmp(treehead->svalue, "<=") == 0) {
			generatecoder(eval_pointer, func, r);
			generatecoder(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = L_EQUAL;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			break;
		}else if(strcmp(treehead->svalue, ">") == 0) {
			generatecoder(eval_pointer, func, r);
			generatecoder(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = GREATERTHAN;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			break;
		}else if(strcmp(treehead->svalue, ">=") == 0) {
			generatecoder(eval_pointer, func, r);
			generatecoder(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = G_EQUAL;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			break;
		}

	/* case T_STRING: */
	/* 	eval_pointer = treehead->cdr; */
	/* 	if(strcmp(treehead->svalue, "if") == 0) { */
	/* 		generatecoder(eval_pointer, func, r); */
	/* 		func->code[func->index].op = IF; */
	/* 		func->code[func->index].reg0 = r; */
	/* 		func->code[func->index].reg1 = r; */
	/* 		func->code[func->index].reg2 = r+1; */
	/* 		func->index++; */
	/* 		break; */
	}
}


