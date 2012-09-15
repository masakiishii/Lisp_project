#include "ilisp.h"

int f_null_flag = 0;

FuncTable_t *functable[HASH_BACKET];

int hash(char *c)
{
	return (c[0] % HASH_BACKET);
}

void make_hashtable_null(FuncTable_t **h_val)
{
	int i;
	for(i = 0;i < HASH_BACKET; i++)
		h_val[i] = NULL;
}

void hash_put(char *key, VM_ByteCode_Set *value)
{
	int bucket;
	FuncTable_t *oldheader;

	if(f_null_flag == 0) {
		make_hashtable_null(functable);
		f_null_flag = 1;
	};

	bucket = hash(key);

	oldheader = functable[bucket];
	functable[bucket] = (FuncTable_t *)malloc(sizeof(FuncTable_t));

	functable[bucket]->fn_t = value;
	functable[bucket]->key = key;
	functable[bucket]->next = oldheader;
}

VM_ByteCode_Set *search_func_hash(char *key)
{
	FuncTable_t *p;
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
