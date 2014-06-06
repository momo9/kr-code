#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#define N 34

int main(int argc, char *argv[]) {

  double *a;
  int i, *b;

  //a = myalloc(N * sizeof(double));
  //for (i = 0; i < N; ++i) {
  //  a[i] = (double) i - 3.15;
  //}

  //for (i = 0; i < N; ++i) {
  //  printf("%-2d %6.2f\n", i, a[i]);
  //}
  //myfree(a);

  b = myalloc(sizeof(int));

  *b = 5;
  printf("%d\n", *b);

  myfree(b);

  a = myalloc(N * sizeof(double));
  for (i = 0; i < N; ++i) {
    a[i] = ((double)i - 3.15) * 0.47;
  }

  for (i = 0; i < N; ++i) {
    printf("%-2d %6.2f\n", i, a[i]);
  }
  myfree(a);

  exit(0);
}
