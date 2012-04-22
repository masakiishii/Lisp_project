#include "ilisp.h"

cons_t *iread(void)
{
	char **t;
	cons_t *head;
	cons_t *h_ptr;

 	t = tokenize();

	if(t == NULL){
		return NULL;
	}

	tree_pointer = t;
	head = parse(t);

	return head;
}
