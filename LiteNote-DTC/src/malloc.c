#include "ilisp.h"

void *imalloc(size_t size)
{
	void *m = malloc(size);
	if(m == NULL) {
		fprintf(stderr, "malloc Error!\n");
		exit(EXIT_FAILURE);
	}
	memset(m, 0, size);
	return m;
}
