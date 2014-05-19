#include "treesort.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 4096

static Tnode *ptrarray[MAX_SIZE];
static int realsize;
// 0 when false, 1 when may success
static int sucflag = 1;

int maxsize() {
  return MAX_SIZE;
}

static void setarray(Tnode *pt) {
  // set all the nodes in ptrarray in middle order
  if (sucflag) {
    setarray(pt->left);
    if (pt) {
      if (realsize < MAX_SIZE) {
        ptrarray[realsize++] = pt;
      } else {
        // too many nodes
        sucflag = 0;
      }
    }
    setarray(pt->right);
  }
}

static void uninitialization() {
  realsize = 0;
  sucflag = 1;
}

static int cmpfreq(Tnode *pta, Tnode *ptb) {
  if (pta->cnt < ptb->cnt) {
    return -1;
  } else if (pta->cnt > ptb->cnt) {
    return 1;
  } else {
    return 0;
  }
}

int sortprint(Tnode *proot) {

  setarray(proot);

  if (!success) {
    uninitialization();
    return 0;
  }

  qsort(ptrarray, realsize, sizeof(Tnode *), cmpfreq);

  int i;
  for (i = 0; i < realsize; ++i) {
    printf("%s: %d\n", ptrarray[i]->word, ptrarray[i]->cnt);
  }

  uninitialization();
  return 1;

}


#undef MAX_SIZE
