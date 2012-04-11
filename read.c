#include "ilisp.h"

cons_t *iread(void)
{
  char **t;
  cons_t *r;

  t = tokenize();
  r = parse(t);

  return r;
}
