#include <stdio.h>
#include <readline/readline.h>
#include "ilisp.h"

int main(int argc,char **argv)
{
  cons_t *tree;
  
  tree = iread();
  //	eval();
  print(tree,0);


  printf("\n");

  return 0;
}
