#include "ilispvm.h"

void generatecoder(cons_t *treehead, func_t *func, int r)
{
	cons_t *eval_pointer;
	int if_index;
	int jump_index;
	cons_t *arg_ptr;

	switch(treehead->type){
	case T_BEGIN:
		treehead = treehead->car;
		eval_pointer = treehead->cdr;
		if(treehead->type == T_OPERATOR){
			generatecoder(treehead, func, r);
			break;
		}
		if(strncmp(treehead->svalue, "if", sizeof("if")+1) == 0) {
			generatecoder(eval_pointer, func, r);
			func->code[func->index].op = IF;
			func->code[func->index].reg0 = r;
			if_index = func->index;
			func->index++;
			generatecoder(eval_pointer->cdr, func, r);
			func->code[func->index].op = JUMP;
			func->code[func->index].reg0 = 0;
			jump_index = func->index;
			func->index++;
			func->code[if_index].pc2 = &func->code[func->index];
		   	generatecoder(eval_pointer->cdr->cdr, func, r);
			func->code[jump_index].pc2 = &func->code[func->index];
			break;
		}else if(strncmp(treehead->svalue, "defun", sizeof("defun")+1) == 0) {
			int counter = 0;
			cons_t *arg = treehead->cdr->cdr->car;
			while(arg != NULL) {
				counter++;
				arg = arg->cdr;
			}
			func_t *newfunc;
			newfunc = (func_t *)malloc(sizeof(func_t));
			hash_put(treehead->cdr->svalue, newfunc);
			newfunc->index = 0;
			newfunc->cons = treehead;
			generatecoder(eval_pointer->cdr->cdr, newfunc, counter);
			newfunc->code[newfunc->index].op = RET;
			newfunc->code[newfunc->index].reg0 = counter;
		}else{
			func_t *s_func;
			int counter = 0;
			s_func = search_func_hash(treehead->svalue);
			while(treehead->cdr != NULL){
				generatecoder(treehead->cdr, func, r + counter);
				treehead = treehead->cdr;
				counter++;
			}
				func->code[func->index].op = CALL;
				func->code[func->index].reg0 = r;
				func->code[func->index].pc2 = &s_func->code[0];
				func->index++;
		}
		break;

	case  T_NUMBER:
		func->code[func->index].op = SET;
		func->code[func->index].reg0 = r;
		func->code[func->index].data1 = treehead->ivalue;
		func->index++;
		break;

	case T_OPERATOR:
		eval_pointer = treehead->cdr;
		if(strncmp(treehead->svalue, "+", sizeof("+")+1) == 0) {
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
		}else if(strncmp(treehead->svalue, "-", sizeof("-")+1) == 0) {
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
		}else if(strncmp(treehead->svalue, "*", sizeof("*")+1) == 0) {
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
		}else if(strncmp(treehead->svalue, "/", sizeof("/")+1) == 0) {
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
		}else if(strncmp(treehead->svalue, "<", sizeof("<")+1) == 0) {
			generatecoder(eval_pointer, func, r);
			generatecoder(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = LESSTHAN;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			break;
		}else if(strncmp(treehead->svalue, "<=", sizeof("<=")+1) == 0) {
			generatecoder(eval_pointer, func, r);
			generatecoder(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = L_EQUAL;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			break;
		}else if(strncmp(treehead->svalue, ">", sizeof(">")+1) == 0) {
			generatecoder(eval_pointer, func, r);
			generatecoder(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = GREATERTHAN;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			break;
		}else if(strncmp(treehead->svalue, ">=", sizeof(">=")+1) == 0) {
			generatecoder(eval_pointer, func, r);
			generatecoder(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = G_EQUAL;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			break;
		}

	case T_STRING:{
		int counter = 0;
		arg_ptr = func->cons->cdr->cdr->car;
		while(arg_ptr != NULL) {
			if(strcmp(arg_ptr->svalue, treehead->svalue) == 0) {
				func->code[func->index].op = MOV;
				func->code[func->index].reg0 = r;
				func->code[func->index].reg1 = counter;
				func->index++;	
			}
			arg_ptr = arg_ptr->cdr;
			counter++;
		}
		break;
	}
  }
}

