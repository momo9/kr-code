#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE        64
#define PUTD(x)         printf(#x": %d\n", (x))

// use layer to mark the ending
// use pos to mark the writing position
static int layer = 0, pos;
static void myitoa(int n, char s[]) {
  char *ps;
  ps = s;
  if (layer == 0) pos = 0;
  // write the sign
  if (n < 0) {
    n = -n;
    ps[0] = '-';
    ++ps;
  }

  if (n / 10 != 0) {
    ++layer;
    myitoa(n / 10, ps);
  }
  
  // deeper layer will be write earlier
  ps[pos++] = '0' + n % 10;
  if (layer != 0) --layer;
  else ps[pos] = 0;
}

main(int argc, char *argv[]) {
  char s[MAX_SIZE];
  int n, i;
  for (i = 1; i < argc; ++i) {
    n = atoi(argv[i]);
    myitoa(n, s);
    puts(s);
  }
}

#undef MAX_SIZE
