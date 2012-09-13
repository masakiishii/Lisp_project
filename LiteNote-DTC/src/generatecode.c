#include "ilispvm.h"

int defun_flag;

void generatecoder(ConsCell_t *treehead, VM_Instruction_Set *func, int r)
{
	ConsCell_t *eval_pointer;
	int if_index;
	int jump_index;
	ConsCell_t *arg_ptr;

	switch(treehead->celltype){
	case T_BEGIN:
	DBG_P("=====<<<T_BEGIN>>>=====");
		treehead = treehead->car;
		eval_pointer = treehead->cdr;
		if(treehead->celltype == T_OPERATOR){
			generatecoder(treehead, func, r);
			break;
		}
	case T_IF :
			DBG_P("=====<<<if>>>=====");
			generatecoder(eval_pointer, func, r);
			func->code[func->index].op = OPIF;
			func->code[func->index].reg0 = r;
			if_index = func->index;
			func->index++;
			generatecoder(eval_pointer->cdr, func, r);
			func->code[func->index].op = OPJMP;
			func->code[func->index].reg0 = 0;
			jump_index = func->index;
			func->index++;
			func->code[if_index].pc2 = &func->code[func->index];
		   	generatecoder(eval_pointer->cdr->cdr, func, r);
			func->code[jump_index].pc2 = &func->code[func->index];
			break;

	case T_DEFUN :
			DBG_P("=====<<<defun>>>=====");
			defun_flag = ON;
			int counter = 0;
			ConsCell_t *arg = treehead->cdr->cdr->car;
			while(arg != NULL) {
				counter++;
				arg = arg->cdr;
			}
			VM_Instruction_Set *newfunc;
			newfunc = (VM_Instruction_Set *)malloc(sizeof(VM_Instruction_Set));
			hash_put(treehead->cdr->svalue, newfunc);
			newfunc->index = 0;
			newfunc->cons = treehead;
			generatecoder(eval_pointer->cdr->cdr, newfunc, counter);
			newfunc->code[newfunc->index].op = OPRET;
			newfunc->code[newfunc->index].reg0 = counter;
		}else{
			VM_Instruction_Set *s_func;
			int counter = 0;
			s_func = search_func_hash(treehead->svalue);
			while(treehead->cdr != NULL){
				generatecoder(treehead->cdr, func, r + counter);
				treehead = treehead->cdr;
				counter++;
			}
				func->code[func->index].op = OPCALL;
				func->code[func->index].reg0 = r;
				func->code[func->index].pc2 = &s_func->code[0];
				func->index++;
		}
		break;

	case  T_NUMBER:
		DBG_P("=====<<<T_NUMBER>>>=====");
		func->code[func->index].op = OPLOAD;
		func->code[func->index].reg0 = r;
		func->code[func->index].data1 = treehead->ivalue;
		func->index++;
		break;

//	case T_OPERATOR:
//		DBG_P("=====<<<T_OPERATOR>>>=====");
	case T_ADD ;
			DBG_P("=====<<<OPADD>>>=====");
		eval_pointer = treehead->cdr;
			generatecoder(eval_pointer, func, r);
			while((eval_pointer->cdr->celltype != T_END)){
				generatecoder(eval_pointer->cdr, func, r+1);
				func->code[func->index].op = OPADD;
				func->code[func->index].reg0 = r;
				func->code[func->index].reg1 = r;
				func->code[func->index].reg2 = r+1;
				func->index++;
				eval_pointer = eval_pointer->cdr;
			}
			break;

   case T_SUB ;
			DBG_P("=====<<<OPSUB>>>=====");
		eval_pointer = treehead->cdr;
			generatecoder(eval_pointer, func, r);
			while((eval_pointer->cdr->celltype != T_END)){
				generatecoder(eval_pointer->cdr, func, r+1);
				func->code[func->index].op = OPSUB;
				func->code[func->index].reg0 = r;
				func->code[func->index].reg1 = r;
				func->code[func->index].reg2 = r+1;
				func->index++;
				eval_pointer = eval_pointer->cdr;
			}
			break;

	case T_MUL ;
			DBG_P("=====<<<OPMUL>>>=====");
		eval_pointer = treehead->cdr;
			generatecoder(eval_pointer, func, r);
			while((eval_pointer->cdr->celltype != T_END)){
				generatecoder(eval_pointer->cdr, func, r+1);
				func->code[func->index].op = OPMUL;
				func->code[func->index].reg0 = r;
				func->code[func->index].reg1 = r;
				func->code[func->index].reg2 = r+1;
				func->index++;
				eval_pointer = eval_pointer->cdr;
			}
			break;

	case T_DIV ;
			DBG_P("=====<<<OPDEV>>>=====");
		eval_pointer = treehead->cdr;
			generatecoder(eval_pointer, func, r);
			while((eval_pointer->cdr->celltype != T_END)){
				generatecoder(eval_pointer->cdr, func, r+1);
				func->code[func->index].op = OPDEV;
				func->code[func->index].reg0 = r;
				func->code[func->index].reg1 = r;
				func->code[func->index].reg2 = r+1;
				func->index++;
				eval_pointer = eval_pointer->cdr;
			}
			break;
	case T_LT ;
			DBG_P("=====<<<OPLT>>>=====");
		eval_pointer = treehead->cdr;
			generatecoder(eval_pointer, func, r);
			generatecoder(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = OPLT;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			break;
	case T_GT ;
			DBG_P("=====<<<OPGT>>>=====");
		eval_pointer = treehead->cdr;
			generatecoder(eval_pointer, func, r);
			generatecoder(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = OPGT;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			break;

	case T_STRING:{
		DBG_P("=====<<<OPMOV>>>=====");
		int counter = 0;
		arg_ptr = func->cons->cdr->cdr->car;
		while(arg_ptr != NULL) {
			if(strcmp(arg_ptr->svalue, treehead->svalue) == 0) {
				func->code[func->index].op = OPMOV;
				func->code[func->index].reg0 = r;
				func->code[func->index].reg1 = counter;
				func->index++;	
			}
			arg_ptr = arg_ptr->cdr;
			counter++;
		}
		break;
	}
	case T_END :{
		DBG_P("=====<<<T_END>>>=====");
	}

	default :
		break;
  }
}

