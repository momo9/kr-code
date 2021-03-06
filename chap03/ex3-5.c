#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SIZE       64

// reverse the string
static void reverse(char s[]) {
  int i, j;
  for (i = 0, j = strlen(s) - 1; i < j; ++i, --j) {
    int c;
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

// transfer n(integer) to a character
static char getd(int n) {
  assert(n < 16);

  if (n < 10) {
    return n + '0';
  } else {
    return n - 10 + 'A';
  }
}

static void itob(int n, char s[], int b, int wid) {
  assert(b <= 16);
  int rmd, i;
  // get left-lsb
  for (rmd = n, i = 0; rmd; rmd /= b) {
    s[i++] = getd(rmd % b);
  }
  for (; i < wid; ++i) {
    s[i] = ' ';
  }
  s[i] = 0;
  // transfer to right-lsb
  reverse(s);
}

main(int argc, char *argv[]) {
  const int N = atoi(argv[1]);
  const int RADIX = atoi(argv[2]);
  const int W = atoi(argv[3]);

  char s[SIZE];
  itob(N, s, RADIX, W);
  puts(s);
}
