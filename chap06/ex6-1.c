#include <stdio.h>
#include "getword.h"

#define BUF_SIZE 128

main() {
  char buf[BUF_SIZE];
  int c;
  while ((c = getword(buf, BUF_SIZE)) != EOF) {
    if (c) {
      puts(buf);
    }
  }
}
