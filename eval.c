#include "ilisp.h"

int than_flag = 0;

int eval_tree(cons_t *ev_head)
{
//	if(ev_head->cdr == NULL){
//		return ev_head->ivalue;
//	}

	cons_t *eval_pointer;
//	printf("----------\n");
//	print_tree(ev_head,0);
	switch(ev_head->type){

	case T_BEGIN    :
		ev_head->ivalue = eval_tree(ev_head->car);
//		printf("T_BEGIN : %d\n", ev_head->ivalue);
		return ev_head->ivalue;

	case OP_ADD     :
		eval_pointer = ev_head->cdr;
		ev_head->ivalue = eval_tree(eval_pointer);
//		printf("OP_ADD1 : %d\n", ev_head->ivalue);
		while(eval_pointer->cdr != NULL) {
//			printf("hoge\n");
			eval_pointer = eval_pointer->cdr;
			ev_head->ivalue += eval_tree(eval_pointer);
//			printf("OP_ADD2 : %d\n", ev_head->ivalue);
		}
//		printf("OP_ADD3 : %d\n", ev_head->ivalue);
		return ev_head->ivalue;

	case OP_SUB     :
		eval_pointer = ev_head->cdr;
		ev_head->ivalue = eval_tree(eval_pointer);
		while(eval_pointer->cdr != NULL) {
			eval_pointer = eval_pointer->cdr;
			ev_head->ivalue -= eval_tree(eval_pointer);
		}
		return ev_head->ivalue;

	case OP_MULT    :
		eval_pointer = ev_head->cdr;
		ev_head->ivalue = eval_tree(eval_pointer);
		while(eval_pointer->cdr != NULL) {
			eval_pointer = eval_pointer->cdr;
			ev_head->ivalue *= eval_tree(eval_pointer);
		}
		return ev_head->ivalue;

	case OP_DEV     :
		eval_pointer = ev_head->cdr;
		ev_head->ivalue = eval_tree(eval_pointer);
		while(eval_pointer->cdr != NULL) {
			eval_pointer = eval_pointer->cdr;
			ev_head->ivalue /= eval_tree(eval_pointer);
		}
		return ev_head->ivalue;

	case L_THAN    :
		than_flag  = 1;
		if( eval_tree(ev_head->cdr) < eval_tree(ev_head->cdr->cdr) ){
			return 1;
		}else{
			return 0;
		}

	case M_THAN    :
		than_flag = 1;
		if( eval_tree(ev_head->cdr) > eval_tree(ev_head->cdr->cdr) ){
			return 1;
		}else{
			return 0;
		}

	case  T_NUMBER  :
		return ev_head->ivalue;

	default         :
		return ev_head->ivalue;
	}
}

