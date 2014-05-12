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

Tab isstop(int index) {
  return tablut[index];
}

#undef DEFAULT_TAB
