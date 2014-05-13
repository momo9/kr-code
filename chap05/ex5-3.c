#include <stdio.h>

#define MAX_SIZE        64

static void mystrcat(char s[], char t[]) {
  char *ps, *pt;
  for (ps = s; *ps; ++ps);
  for (pt = t; *pt; ++ps, ++pt) *ps = *pt;
  *ps = 0;
}

main(int argc, char *argv[]) {
  char s[MAX_SIZE];
  char *pa, *ps;

  // copy argv[1] to s;
  for (ps = s, pa = argv[1]; *pa; ++pa, ++ps) *ps = *pa;
  *ps = 0;
  mystrcat(s, argv[2]);
  puts(s);
}

#undef MAX_SIZE
