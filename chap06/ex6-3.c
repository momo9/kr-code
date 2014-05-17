#include "bintreex.h"
#include "getword.h"
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 128

main(int argc, char *argv[]) {
  Tnode *proot = 0;
  int c, n;
  char buf[BUF_SIZE];

  while ((c = getword(buf, BUF_SIZE)) != EOF) {
    if (isvar(c)) {
      //fputs("before add\n", stderr);
      proot = addtree(proot, buf, getlinenumber());
    }
  }

  printtree(proot);

  //fprintf(stderr, "%d\n", proot);

  proot = freetree(proot);

  //fprintf(stderr, "%d\n", proot);
}
