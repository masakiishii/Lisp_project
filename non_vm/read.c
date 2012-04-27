#include "ilisp.h"

cons_t *iread(char *line)
{
	char **t;
	cons_t *head;
	cons_t *h_ptr;

	if(line == NULL){
		t = tokenize(NULL);
	}else{
		t = tokenize(line);
	}

	if(t == NULL){
		return NULL;
	}

	tree_pointer = t;
	head = parse(t);

	return head;
}
