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
  if (sucflag && pt) {
    setarray(pt->left);
    if (realsize < MAX_SIZE) {
      ptrarray[realsize++] = pt;
    } else {
      // too many nodes
      sucflag = 0;
    }
    setarray(pt->right);
  }
}

static void uninitialization() {
  realsize = 0;
  sucflag = 1;
}

static int cmpfreq(Tnode **pta, Tnode **ptb) {
//  fprintf(stderr, "%s: %d\n", (*pta)->word, (*pta)->cnt);
//  fprintf(stderr, "%s: %d\n", (*ptb)->word, (*ptb)->cnt);
  return (*pta)->cnt - (*ptb)->cnt;
}

int sortprint(Tnode *proot) {

  //fputs("begin", stderr);
  // put (the pointers of) nodes in an array
  setarray(proot);

  //fputs("set array", stderr);
  // too many nodes
  if (!sucflag) {
    uninitialization();
    return 0;
  }

  //fputs("sort", stderr);
  // sort the nodes according to their cnt (frequency)
  qsort(ptrarray, realsize, sizeof(Tnode *), cmpfreq);

  // print the nodes
  int i;
  for (i = 0; i < realsize; ++i) {
    printf("%s: %d\n", ptrarray[i]->word, ptrarray[i]->cnt);
  }

  uninitialization();
  return 1;

}


#undef MAX_SIZE
