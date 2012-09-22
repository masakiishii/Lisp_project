#include <ilisp.h>

#define MAX_MEMORY_SIZE 8
Map *virtualmachine_memory[MAX_MEMORY_SIZE] = {NULL};
static int virtualmachine_memory_index = 0;

Map *new_Map(const char *key, void *value)
{
	Map *ret = (Map *)imalloc(sizeof(Map));
	ret->key = (const char *)imalloc(strlen(key) + 1);
	strncpy((char *)ret->key, key, strlen(key) + 1);
	ret->value = value;
	return ret;
}

void store_to_virtualmachine_memory(Map *map)
{
	virtualmachine_memory[virtualmachine_memory_index++] = map;
}

void *fetch_from_virtualmachine_memory(const char *key)
{
	int i = 0;
	Map *map;
	for(i = 0; i < virtualmachine_memory_index; i++) {
		map = virtualmachine_memory[i];
		if(strlen(map->key) == strlen(key) && (strncmp(map->key ,key, strlen(key)) == 0)) {
			return map->value;
		}
	}
	return NULL;
}
