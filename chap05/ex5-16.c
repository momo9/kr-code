#include <stdio.h>
#include "mysort.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 64
#define STR_SIZE 64

// not reverse: 1
// reverse: -1
static int reverse = 1;

// whether consider case 
static int argf = 0;

// whether see as directory
static int argd = 0;

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

// copy src to dst
// a. can transfer all char to upper case
// b. can ignore char which do not match isalnum()
static void strcpyupper(char *dst, const char *src) {
  while (*src) {
    // if argd == 0, every char should be copied
    // if argd == 1, only copy digit and alphbeta
    if (!argd || isalnum(*src)) {
      *dst++ = (argf) ? toupper(*src) : *src;
    }
    ++src;
  }
  *dst = 0;
}

int cmp_ignore_case(char *stra, char *strb) {
  char a[STR_SIZE], b[STR_SIZE];
  strcpyupper(a, stra);
  strcpyupper(b, strb);
  return cmpstr(a, b);
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
          case 'f':
            cmp = cmp_ignore_case;
            argf = 1;
            break;
          case 'd':
            cmp = cmp_ignore_case;
            argd = 1;
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

