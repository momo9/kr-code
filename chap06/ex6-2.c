#include "bintree.h"
#include "getword.h"
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 128

main(int argc, char *argv[]) {
  Tnode *proot = 0; // initialization is important
  int c, n;
  char buf[BUF_SIZE];

  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 6; // default: 6
  }

  while ((c = getword(buf, BUF_SIZE)) != EOF) {
    if (isvar(c)) {
      //fputs("before add\n", stderr);
      proot = addtree(proot, buf);
    }
  }

  printgroup(proot, n);

  proot = freetree(proot);
}
