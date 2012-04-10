#include "ilisp.h"

cons_t *parse(char **t)
{
  if(**t == ')'){

	return NULL;

  }

  cons_t *head = (cons_t *)malloc(sizeof(cons_t));
  cons_t *p=head;

  int n = sizeof(t)/sizeof(*t);

  while(n--){

	switch(**t){
	
	case '(' :
	  p->type = T_BEGIN;
	  t++;
      p->car = parse(t);
	  t++;
	  p->cdr = parse(t);  
	  break;
	   

	case '-' :
	  if( isalnum(*(*t+1))){
		p->type = T_NUMBER;
        p->ivalue = atoi(*t);
		return NULL;
	  } 
	  break;

	case '+' :
	  p->type = OP_ADD;
	  t++;
	  p->cdr = parse(t); 
	  break;

	case '*' :
	  p->type = OP_MULT;
	  t++;
	  p->cdr = parse(t); 
	  break;

	case '/' :
	  p->type = OP_SUB;
	  t++;
	  p->cdr = parse(t); 
	  break;

	default :
	  if(isdigit(**t)){
		p->type = T_NUMBER;
		p->ivalue = atoi(*t);
		return NULL;
	  }else if(isalpha(**t)){
		p->type = T_STRING;
		p->svalue = *t;
		t++;
		p->cdr = parse(t);
	  } 
	  break;
	}
  }
  return head;
}
