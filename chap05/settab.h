#ifndef SETTAB_H
#define SETTAB_H

#define LINE_SIZE 64

typedef enum {
  YES,
  NO
} Tab;

// set up the tab look-up-table (for ex5-11)
void settab(int argc, char *argv[]);

// set up the tab look-up-table (for ex5-12)
// return 0 when success
// return 1 when fault
int settab_mn(int argc, char *argv[]);

// is stop position: return YES
// not stop position: return NO
Tab isstop(int index);

#endif
