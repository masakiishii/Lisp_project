#include "ilisp.h"

Type than_flag = ZERO_FLAG;

cons_t eval_tree(cons_t *ev_head)
{
//	if(ev_head->cdr == NULL){
//		return ev_head->ivalue;
//	}

	cons_t *eval_pointer;
//	printf("----------\n");
//	print_tree(ev_head,0);
	switch(ev_head->type){

	case T_BEGIN    :
		ev_head->ivalue = eval_tree(ev_head->car).ivalue;
		return *ev_head;

	case OP_ADD     :
		eval_pointer = ev_head->cdr;
		ev_head->ivalue = eval_tree(eval_pointer).ivalue;
		while(eval_pointer->cdr != NULL) {
			eval_pointer = eval_pointer->cdr;
			ev_head->ivalue += eval_tree(eval_pointer).ivalue;
		}
		return *ev_head;

	case OP_SUB     :
		eval_pointer = ev_head->cdr;
		ev_head->ivalue = eval_tree(eval_pointer).ivalue;
		while(eval_pointer->cdr != NULL) {
			eval_pointer = eval_pointer->cdr;
			ev_head->ivalue -= eval_tree(eval_pointer).ivalue;
		}
		return *ev_head;

	case OP_MULT    :
		eval_pointer = ev_head->cdr;
		ev_head->ivalue = eval_tree(eval_pointer).ivalue;
		while(eval_pointer->cdr != NULL) {
			eval_pointer = eval_pointer->cdr;
			ev_head->ivalue *= eval_tree(eval_pointer).ivalue;
		}
		return *ev_head;

	case OP_DEV     :
		eval_pointer = ev_head->cdr;
		ev_head->ivalue = eval_tree(eval_pointer).ivalue;
		while(eval_pointer->cdr != NULL) {
			eval_pointer = eval_pointer->cdr;
			ev_head->ivalue /= eval_tree(eval_pointer).ivalue;
		}
		return *ev_head;

	case L_THAN    :
		if( eval_tree(ev_head->cdr).ivalue < eval_tree(ev_head->cdr->cdr).ivalue ){
			than_flag = TRUE_FLAG;
			return *ev_head->cdr;
		}else{
			than_flag = FALSE_FLAG;
			return *ev_head->cdr->cdr;
		}

	case M_THAN    :
		than_flag = 1;
		if( eval_tree(ev_head->cdr).ivalue > eval_tree(ev_head->cdr->cdr).ivalue ){
			return *ev_head->cdr;
		}else{
			return *ev_head->cdr->cdr;
		}

	case  T_NUMBER  :
		return *ev_head;

	case T_IF         :
		return *eval_string(ev_head);

	default         :
		return *ev_head;
	}
}
