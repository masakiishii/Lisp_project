#include "ilisp.h"

int h_null_flag=0;
int f_null_flag=0;
int s_null_flag=0;
int search_setq_val_flag = 1;

h_table *hashtable[HASH_BACKET];

f_table *functable[HASH_BACKET];

int stacktable[ARG_STACK][ARG_LENGTH] = {0};
//int stack_index[ARG_STACK] = {0};
int stack_index[ARG_STACK] = {-1};

int hash(char c)
{
	return c % HASH_BACKET;
}

void hash_val(cons_t *h_val)
{

	int bucket;
	h_table *oldheader;

	if(h_null_flag == 0){
	makenull(hashtable);
		h_null_flag = 1;
	};

	bucket = hash(h_val->svalue[0]);

	oldheader = hashtable[bucket];
	hashtable[bucket] = (h_table *)malloc(sizeof(h_table));

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

	while (p != NULL && flag) {
		if (strcmp(p->symbol, str)){
			p = p->next;
		} else {
			flag = 0;
		}
	}
	
	return p->i_val;
}


void hash_func(cons_t *h_func)
{

	int bucket;
	f_table *oldheader;

	if(f_null_flag == 0){
	makenull(functable);
		f_null_flag = 1;
	};

	bucket = hash(h_func->svalue[0]);

	oldheader = functable[bucket];
	functable[bucket] = (f_table *)malloc(sizeof(f_table));

	functable[bucket]->fn_t = *h_func;
	functable[bucket]->next = oldheader;
}

cons_t search_func_hash(cons_t *search_func_head)
{
	f_table *p;
	int flag = 1;
	char *str = search_func_head->svalue;

	p = functable[hash(str[0])];

	while(p != NULL && flag){
		if(strcmp(p->fn_t.svalue, str)){
			p = p->next;
		}else{
			flag=0;
		}
	}

	return *p->fn_t.cdr;
}

void stack_push(int st_arg, int st_number)
{
	stack_index[st_number]++;
	stacktable[st_number][stack_index[st_number]] = st_arg;
}

 void stack_pop(int st_pop) 
 { 
 	stack_index[st_pop]--;
 }

int stack_get_topindex(int topindex)
{
	return stacktable[topindex][stack_index[topindex]];
}
