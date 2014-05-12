#include <stdio.h>
#include "settab.h"

// it is a little hard to test
static void entab(void) {
  int cntspace, cnt, c;
  cnt = 0, cntspace = 0;
  while((c = getchar()) != EOF && cnt < LINE_SIZE) {
    if (c == ' ') {
      if (isstop(cnt) == YES) {
        // if in stop position, print a '\t', and clear the space count
        putchar('\t');
        cntspace = 0;
      } else {
        // if not stop position, count the space number
        ++cntspace;
      }
    } else {
      // when not space, print the counted ' 's, and print the char directly
      while (cntspace--) putchar(' ');
      cntspace = 0;
      putchar(c);
    }
    ++cnt;
  }
}

static void detab(void) {
  int cnt, c;
  cnt = 0;
  while ((c = getchar()) != EOF && cnt < LINE_SIZE) {
    if (c == '\t') {
      // when input is '\t', print ' ' until the stop position
      while(isstop(cnt++) == NO) {
        putchar(' ');
      }
      putchar(' ');
    } else {
      putchar(c);
      ++cnt;
    }
  }
  // for test
  // '*' denotes the stop position
  int i;
  for (i = 0; i < LINE_SIZE; ++i) {
    putchar((isstop(i) == YES) ? '*' : ' ');
  }
  putchar('\n');
}

main(int argc, char *argv[]) {
  int res;
  res = settab_mn(argc, argv);
  if (res == 0) {
    detab();
  }
}
