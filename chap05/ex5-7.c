#include <stdio.h>
#include "getc.h"

#define SIZE            64

main(int argc, char *argv[]) {
  char *line[SIZE];
  int nline;
  char **ppl;
  nline = readlines(line, SIZE);
  for (ppl = line; nline; --nline) {
    puts(*ppl++);
  }
}
