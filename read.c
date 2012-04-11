#include "ilisp.h"

cons_t *iread(void)
{
  char **t;
  cons_t *r;
  int n=0;

  t = tokenize();
//  exit(1);
//  n = sizeof(t)/sizeof(*t);
  while(1){
	  n+=1;
	  if(t[n] == NULL)
		  break;
  }

  r = parse(t,n);

  return r;
}
