#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE        64 

#define PUTD(x)         printf(#x": %d\n", (x))
#define PUTC(x)         printf(#x": %c\n", (x))

static void mystrncpy(char dst[], char src[], int n) {
  char *pd, *ps;
  int i;
  for (ps = src, pd = dst, i = 0; i < n && *ps; ++ps, ++pd, ++i) {
    *pd = *ps;
  }
  for (; i < n; ++i) *pd++ = 0;
}

static void mystrncat(char dst[], char src[], int n) {
  char *pd, *ps;
  for (pd = dst; *pd; ++pd);
  for (ps = src; *ps && n; --n) *pd++ = *ps++;
  *pd = 0;
}

static int mystrncmp(char *s1, char *s2, int n) {
  for (; n && *s1 && *s2 && *s1 == *s2; --n, ++s1, ++s2) {
    //PUTD(n);
    //PUTC(*s1);
    //PUTC(*s2);
    //getchar();
  }
  if (n) {
    //puts("enter.");
    //PUTD(n);
    if (*s1 == 0 && *s2 == 0) return 0;
    else return *s1 - *s2;
  }
  return 0;
}

main(int argc, char *argv[]) {
  int n;
  n = atoi(argv[3]);
  printf("%d\n", mystrncmp(argv[1], argv[2], n));
}
