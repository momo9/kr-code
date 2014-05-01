#include <stdio.h>

#define N       8
#define PUTD(x) printf(#x": %d\n", (x))

static int a[N] = {2, 4, 10, 13, 26, 33, 41, 47};

static int binsearch(int a[], int val) {
  int low, mid, high;
  low = 0;
  high = N - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (val > a[mid]) low = mid + 1;
    else if (val < a[mid]) high = mid - 1;
    else return mid;
  }
  return -1;
}

main() {
  int i;
  for (i = 0; i < N; ++i) {
    PUTD(binsearch(a, a[i]));
  }
  PUTD(binsearch(a, 46));
}

