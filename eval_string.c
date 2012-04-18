#include "ilisp.h"

cons_t *eval_string(cons_t *string_head)
{
	cons_t *st_ptr = string_head->cdr;
	int bucket;

	switch( string_head->type ){

	case T_IF    :
		if( eval_tree(st_ptr).ivalue ){
				return st_ptr->cdr;
			}else{
				return st_ptr->cdr->cdr;
			}

	case T_SETQ    :
		hash_val(string_head->cdr);
		return string_head;

	case T_DEFUN   :


	case T_STRING  :
		return search_hash(string_head);


	}
}

