#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "stack_api.h"

#define PUTG(x)         printf(#x": %g\n", (x))
#define IS_NUMBER       '0'
#define MAX_SIZE        64

main(int argc, char *argv[]) {
  push(4.1);
  push(4.2);
  push(4.3);
  print_stack();

  puts("get_top");
  PUTG(get_top());
  print_stack();

  puts("swap");
  swap_top();
  print_stack();

  puts("copy");
  cpy_top();
  print_stack();

  puts("clear");
  clear();
  print_stack();
}
