#include <stdio.h>

#define N       8

static int a[N] = {2, 7, 3, 1, 5, 8, 4, 6};
static void shellsort(int a[]) {
  int i, j;
  for (i = 1; i < N; ++i) {
    for (j = i - 1; j >= 0 && a[j] > a[j + 1]; j--) {
      int temp;
      temp = a[j];
      a[j] = a[j + 1];
      a[j + 1] = temp;
    }
  }
}

main() {
  shellsort(a);
  int i;
  for (i = 0; i < N; ++i) {
    printf("%d ", a[i]);
  }
  puts("");
}
