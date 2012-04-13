#include <stdio.h>
#include <readline/readline.h>
#include "ilisp.h"

int main(void)
{
  cons_t *tree_head;
  int answer;

  tree_head = iread();

  print_tree(tree_head, 0);

  answer = eval_tree(tree_head);

  printf("%d\n", answer);

  printf("\n");

  return 0;
}
