#include <stdio.h>
#include "mysort.h"
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 64

// not reverse: 1
// reverse: -1
static int reverse = 1;

// a > b, return positive * reverse
// a == b, return zero
// a < b, return negtive * reverse
int cmpnum(char *stra, char *strb) {
  int a, b;
  a = atoi(stra);
  b = atoi(strb);
  return (a - b) * reverse;
}

int cmpstr(char *stra, char *strb) {
  return strcmp(stra, strb) * reverse;
}

main(int argc, char *argv[]) {
  char *num[MAX_SIZE];
  int i, len;
  // default: compare as string
  FunCmp cmp = cmpstr;
  i = 0;
  while(--argc) {
    if ((*++argv)[0] == '-') {
      // - means options
      char c;
      while (c = *++argv[0]) {
        switch(c) {
          case 'r':
            reverse = -1;
            break;
          case 'n':
            cmp = cmpnum;
            break;
          default:
            puts("argument error.");
            exit(0);
        }
      }
    } else {
      // not - means number (negtive number not considered)
      num[i++] = *argv;
    }
  }
  len = i;

  mysort(num, 0, len - 1, cmp);

  for (i = 0; i < len; ++i) {
    puts(num[i]);
  }
}

