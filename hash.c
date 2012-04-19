#include "ilisp.h"

int null_flag=0;
h_table *hashtable[HASH_BACKET];

int hash(char c)
{
	return c % HASH_BACKET;
}

void hash_val(cons_t *h_val)
{

	int bucket;
	h_table *oldheader;

	if(null_flag == 0){
	makenull(hashtable);
		null_flag = 1;
	};

	bucket = hash(h_val->svalue[0]);

	oldheader = hashtable[bucket];
	hashtable[bucket] = (h_table *)malloc(sizeof(cons_t));

	hashtable[bucket]->symbol = h_val->svalue;
	hashtable[bucket]->i_val = h_val->cdr->ivalue;
	hashtable[bucket]->next = oldheader;
}

void makenull(cons_t *h_val[])
{
	int i;
	for(i=0;i<HASH_BACKET;i++)
		h_val[i] = NULL;
}

int search_hash(cons_t *search_head)
{
	h_table *p;
	int flag = 1;
	char *str = search_head->svalue;

	p = hashtable[hash(str[0])];

	while(p != NULL && flag){
		if(strcmp(p->symbol, str))
			p = p->next;
		else
			flag=0;
	}
//	p->ivalue = p->val;
	return p->i_val;
}
