#include "mysort.h"

static void swap(void *ppdata[], int a, int b) {
  void *t;
  t = ppdata[a];
  ppdata[a] = ppdata[b];
  ppdata[b] = t;
}

void mysort(void *ppdata[], int beg, int end, FunCmp cmp) {
  int i, j, k;
  // make ppdata[beg + 1 ... j] < ppdata[beg]
  // and  ppdata[j + 1 ... end] > ppdata[beg]
  if (beg < end) {
    i = j = beg;
    for (k = beg + 1; k <= end; ++k) {
      if (cmp(ppdata[i], ppdata[k]) > 0) {
        swap(ppdata, ++j, k);
      }
    }
    // set ppdata[beg] in the pivot position
    swap(ppdata, i, j);
    // recursion
    mysort(ppdata, i, j - 1, cmp);
    mysort(ppdata, j + 1, end, cmp);
  }
}
