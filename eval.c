#include "ilisp.h"

Type than_flag = ZERO_FLAG;
int if_flag = IF_OFF;

cons_t eval_tree(cons_t *ev_head)
{
	cons_t *eval_pointer;
	cons_t str_val_cons;
	int n=0;

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

	case  T_IF      : 
		if_flag = IF_ON;
		if( eval_tree(ev_head->cdr).ivalue ){
			return eval_tree(ev_head->cdr->cdr);
		}else{
			return eval_tree(ev_head->cdr->cdr->cdr);
		}

	case  T_SETQ    :
		hash_val(ev_head->cdr);
		return *ev_head;


	case T_ARGUMENT :
		if( (ev_head->ivalue < 0) || (ev_head->ivalue > 9)){
			str_val_cons = search_func_hash(ev_head);
			while(ev_head != NULL){ 
				stack_push(ev_head->cdr, n++); 
				ev_head = ev_head->cdr; 
			} 
			return eval_tree(str_val_cons.cdr);
		}else{
			str_val_cons.ivalue = stack_pop(ev_head->ivalue);
			return str_val_cons;
		}

	case  T_STRING  :
		str_val_cons.ivalue = search_hash(ev_head);
		str_val_cons.type = T_NUMBER;
		return str_val_cons;
		

	default         :
		return *ev_head;
	}
}

void defun_eval(cons_t *arg, cons_t *rept)
{
	cons_t *arg_ptr = arg;
	cons_t *rept_ptr = rept;
	int arg_number = 0;

	switch(rept_ptr->type){

	case T_ARGUMENT :
		while( arg_ptr != NULL ){
			if( strcmp(arg_ptr->svalue, rept_ptr->svalue) == 0 ){
				rept_ptr->ivalue = arg_number;
				break;
			}
			arg_ptr = arg_ptr->cdr;		
			arg_number++;
		}

		if(rept_ptr->cdr != NULL)
			defun_eval(arg,rept_ptr->cdr);

		break;


	default :
		if(rept_ptr->car != NULL)
			defun_eval(arg,rept_ptr->car);

		if(rept_ptr->cdr != NULL)
			defun_eval(arg,rept_ptr->cdr);
					   
		break;
	}
}

void arg_numbering(cons_t *d_p)
{
	int arg_number = 0;

	while( d_p != NULL ){
		d_p->ivalue = arg_number++;
		d_p = d_p->cdr;
	}
}
