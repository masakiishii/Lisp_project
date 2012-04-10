#include "ilisp.h"

cons_t *parse(char **t)
{
  cons_t *head = (cons_t *)malloc(sizeof(cons_t));
  cons_t *p=head;

  int n = sizeof(t)/sizeof(*t);

  while(n--){

	switch((enum)**t){
	
	case BEGIN :
	  p->type = BEGIN;
	  t++;
	  p->cdr = parse(t);  break;
	   

	case END :
	  p->type = END;
	  return NULL;     　 break;

	case OP_ADD  :
	case OP_SUB  :
	case OP_MULT :
	case OP_DEV  :
	  if( isalnum(*(*t+1)) ){
		  p->type = NUMBER;
		  t++;
		  p->cdr = parse(t);
		}else{
		p->type = (enum)**t;
        t++;
		p->cdr = parse(t);
	  }
	  break;

	default :
	  p->type  = NUMBER;
	  t++;
	  p->cdr = parse(t);
	  break;

	}
  } 
  return head;
}

