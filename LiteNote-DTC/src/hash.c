#include "ilisp.h"

int f_null_flag = 0;

FuncTable *functable[HASH_BACKET];

int hash(char *c)
{
	return (c[0] % HASH_BACKET);
}

void make_hashtable_null(FuncTable **h_val)
{
	int i;
	for(i = 0;i < HASH_BACKET; i++)
		h_val[i] = NULL;
}

void hash_put(char *key, VirtualMachineByteCodeLine *value)
{
	int bucket;
	FuncTable *oldheader;

	if(f_null_flag == 0) {
		make_hashtable_null(functable);
		f_null_flag = 1;
	};

	bucket = hash(key);

	oldheader = functable[bucket];
	functable[bucket] = (FuncTable *)malloc(sizeof(FuncTable));

	functable[bucket]->fn_t = value;
	functable[bucket]->key = key;
	functable[bucket]->next = oldheader;
}

VirtualMachineByteCodeLine *search_func_hash(char *key)
{
	FuncTable *p;
	char *str = key;

	p = functable[hash(str)];

	while(p != NULL) {
		if(strncmp(p->key, str, sizeof(str)) == 0) {
			break;
		}else{
			p = p->next;
		}
	}
	if(p == NULL) {
		return NULL;
	}else{
		return p->fn_t;
	}
}
