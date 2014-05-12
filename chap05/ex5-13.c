#include <stdio.h>
#include <stdlib.h>
#include "getc.h"

#define MAX_LINE 64

main(int argc, char *argv[]) {
  int n = 10;
  if (argc > 2) {
    puts("argument error.");
    exit(-1);
  } else if (argc == 2) {
    n = atoi(argv[1] + 1);
  }

  char *lines[MAX_LINE];
  int nline, i;
  nline = readlines(lines, MAX_LINE);
  
  puts("start output");
  for (i = (n < nline) ? nline - n : 0; i < nline; ++i) {
    puts(lines[i]);
  }
}
