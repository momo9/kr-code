#include "settab.h"
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB 8

static Tab tablut[LINE_SIZE];

void settab(int argc, char *argv[]) {
  int i;
  // initialization: all the positions are not stop positions
  for (i = 0; i < LINE_SIZE; ++i) {
    tablut[i] = NO;
  }
  if (argc == 1) {
    // default
    for (i = DEFAULT_TAB - 1; i < LINE_SIZE; i += DEFAULT_TAB) {
      tablut[i] = YES;
    }
  } else {
    int num;
    while (--argc) {
      num = atoi(*++argv);
      if (num >= 0 && num < LINE_SIZE) {
        tablut[num] = YES;
      }
    }
  }
}

// set up the tab look-up-table (for ex5-12)
int settab_mn(int argc, char *argv[]) {
  int i, m, n;
  // initialization
  for (i = 0; i < LINE_SIZE; ++i) {
    tablut[i] = NO;
  }
  if (argc == 1) {
    // default
    for (i = DEFAULT_TAB - 1; i < LINE_SIZE; i += DEFAULT_TAB) {
      tablut[i] = YES;
    }
    return 0;
  } else if (argc == 3) {
    while (--argc) {
      switch ((*++argv)[0]) {
        case '-':
          // the start column
          m = atoi(*argv + 1);
          break;
        case '+':
          // one stop position per n column
          n = atoi(*argv + 1);
          break;
        default:
          puts("argument error.");
          return -1;
      }
    }
    for (i = m; i < LINE_SIZE; i += n) {
      tablut[i] = YES;
    }
    return 0;
  } else {
    puts("argument error.");
    return -1;
  }
}

Tab isstop(int index) {
  return tablut[index];
}

#undef DEFAULT_TAB
