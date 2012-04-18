#include "ilisp.h"

int null_flag=0;
cons_t *hashtable[HASH_BACKET];

int hash(char c)
{
	return c % HASH_BACKET;
}

void hash_val(cons_t *h_val)
{

	int bucket;
	cons_t *oldheader;

	if(null_flag == 0){
	makenull(hashtable);
		null_flag = 1;
	};

	bucket = hash(h_val->svalue[0]);

	oldheader = hashtable[bucket];
	hashtable[bucket] = (cons_t *)malloc(sizeof(cons_t));

	hashtable[bucket]->val = h_val->cdr->ivalue;
	hashtable[bucket]->svalue = h_val->svalue;
	hashtable[bucket]->next = oldheader;
}

void makenull(cons_t *h_val[])
{
	int i;
	for(i=0;i<HASH_BACKET;i++)
		h_val[i] = NULL;
}

cons_t *search_hash(cons_t *search_head)
{
	cons_t *p;
	int flag = 1;
	char *str = search_head->svalue;

	p = hashtable[hash(str[0])];

	while(p != NULL && flag){
		if(strcmp(p->svalue, str))
			p = p->next;
		else
			flag=0;
	}
	return p;
}
