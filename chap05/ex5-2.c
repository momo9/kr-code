#include <stdio.h>
#include "getc.h"
#include <ctype.h>

#define MAX_SIZE        64

// output the result in *pa, return the status
static int getint(double *pa) {
  int c;
  // skip the space
  for (c = mygetc(); isspace(c) && c != EOF; c = mygetc());
  if (c == EOF) return EOF;
  // not a number
  if (!isdigit(c) && c != '+' && c != '-') return 0;

  int sign;
  sign = 1;
  if (c == '+' || c == '-') {
    if (c == '-') sign = -1;
    // have '+' or '-', but not a number
    if (isspace(c = mygetc()) || c == EOF) {
      *pa = 0;
      if (c != EOF) myungetc(c);
      return c;
    }
  }
  // is a number
  *pa = 0;
  for (; isdigit(c) && c != EOF; c = mygetc()) {
    //printf("%c\n", c);
    //getchar();
    *pa = *pa * 10 + (c - '0');
    //printf("%d\n", *pa);
  }
  // the fraction
  if (c == '.') {
    double fac;
    for (fac = 0.1, c = mygetc(); isdigit(c) && c != EOF; c = mygetc(), fac /= 10.0) {
      *pa += (c - '0') * fac;
    }
  }
  *pa *= sign;
  if (c != EOF) myungetc(c);
  return c;
}

main() {
  double a[MAX_SIZE];
  int i, c, k;
  for (i = 0, c = getint(&a[i]); c != EOF; ++i, c = getint(&a[i]));
  for (k = 0; k < i; ++k) {
    printf("%g ", a[k]);
  }
  puts("");
}
