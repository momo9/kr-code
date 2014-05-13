#include <stdio.h>
#include "cal.h"

#define PUTG(x)         printf(#x": %g\n", (x))
#define BUF_SIZE        128

static char readbuf[BUF_SIZE];

// read a line to readbuf[]
static int readline() {
  int c, i;
  for (i = 0, c = getchar(); c != '\n' && c != EOF; c = getchar(), ++i) {
    readbuf[i] = c;
  }
  readbuf[i] = 0;
  return i;
}

main(int argc, char *argv[]) {

  int len;
  for (len = readline(); len > 0; len = readline()) {
    PUTG(cal(readbuf));
  }
}
