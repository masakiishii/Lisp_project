#include "ilisp.h"

Type than_flag = ZERO_FLAG;
int if_flag = IF_OFF;

cons_t eval_tree(cons_t *ev_head)
{
	cons_t *eval_pointer;

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
			ev_head->ivalue = 1;
			than_flag = TRUE_FLAG;
			if( if_flag == IF_ON ){
				return *ev_head;
			}
			return *ev_head->cdr;
		}else{
			ev_head->ivalue = 0;
			than_flag = FALSE_FLAG;
			if( if_flag == IF_ON ){
				return *ev_head;
			}
			return *ev_head->cdr->cdr;
		}

	case M_THAN    :
		if( eval_tree(ev_head->cdr).ivalue > eval_tree(ev_head->cdr->cdr).ivalue ){
			ev_head->ivalue = 1;
			than_flag = TRUE_FLAG;
			if( if_flag == IF_ON ){
				return *ev_head;
			}
			return *ev_head->cdr;
		}else{
			ev_head->ivalue = 0;
			than_flag = FALSE_FLAG;
			if( if_flag == IF_ON ){
				return *ev_head;
			}

			return *ev_head->cdr->cdr;
		}

	case  T_NUMBER  :
		return *ev_head;

	case  T_IF      : if_flag = IF_ON;
	case  T_SETQ    :
	case  T_DEFUN   :
	case  T_STRING  :
		return *eval_string(ev_head);

	default         :
		return *ev_head;
	}
}
