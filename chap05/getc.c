#include <stdio.h>
#include "getc.h"

static int buf;

int mygetc(void) {
  int res;
  if (buf != 0) {
    res = buf;
    buf = 0;
  } else {
    res = getchar();
  }
  return res;
}
void myungetc(int c) {
  buf = c;
}
