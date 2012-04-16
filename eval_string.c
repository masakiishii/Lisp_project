#include "ilisp.h"

cons_t *eval_string(cons_t *string_head)
{
	cons_t *st_ptr = string_head->cdr;

	switch( string_head->type ){

	case T_IF   :
		if( eval_tree(st_ptr).ivalue ){
				return st_ptr->cdr;
			}else{
				return st_ptr->cdr->cdr;
			}

	}
}

