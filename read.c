#include "ilisp.h"

cons_t *iread(void)
{
	char **t;
	cons_t *head;
//	int n=0;

 	t = tokenize();

	if(t == NULL){
		return NULL;
	}

	tree_pointer = t;
	head = parse(t);

	return head;
}
