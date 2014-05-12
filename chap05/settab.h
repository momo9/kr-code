#ifndef SETTAB_H
#define SETTAB_H

#define LINE_SIZE 64

typedef enum {
  YES,
  NO
} Tab;

// set up the tab look-up-table
void settab(int argc, char *argv[]);

// is stop position: return YES
// not stop position: return NO
Tab isstop(int index);

#endif
