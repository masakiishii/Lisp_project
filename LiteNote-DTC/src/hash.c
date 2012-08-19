#include "ilispvm.h"

int f_null_flag = 0;

f_table *functable[HASH_BACKET];

int hash(char *c)
{
	return (c[0] % HASH_BACKET);
}

void make_hashtable_null(f_table **h_val)
{
	int i;
	for(i = 0;i < HASH_BACKET; i++)
		h_val[i] = NULL;
}

void hash_put(char *key, func_t *value)
{
	int bucket;
	f_table *oldheader;

	if(f_null_flag == 0) {
		make_hashtable_null(functable);
		f_null_flag = 1;
	};

	bucket = hash(key);

	oldheader = functable[bucket];
	functable[bucket] = (f_table *)malloc(sizeof(f_table));

	functable[bucket]->fn_t = value;
	functable[bucket]->key = key;
	functable[bucket]->next = oldheader;
}

func_t *search_func_hash(char *key)
{
	f_table *p;
	char *str = key;

	p = functable[hash(str)];

	while(p != NULL) {
		if(strcmp(p->key, str)) {
			p = p->next;
		}else{
			break;
		}
	}
	if(p == NULL) {
		return NULL;
	}else{
		return p->fn_t;
	}
}
