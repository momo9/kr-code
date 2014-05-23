#include <stdio.h>
#include <ctype.h>

#define HEX_WIDTH 3

static int linewidth = 10;

// return new position
static int inc(int pos, int width) {
  pos += width;
  //fprintf(stderr, "%d\n", pos);
  // <RETURN> when reach 'linewidth'
  if (pos >= linewidth) {
    putchar('\n');
    return 0;
  }
  return pos;
}

main(int argc, char *argv[]) {
  int c, pos;
  if (argc > 1) {
    linewidth = atoi(argv[1]);
  }
  pos = 0;
  while ((c = getchar()) != EOF) {
    if (isgraph(c)) {
      // print graphic characters directly
      putchar(c);
      pos = inc(pos, 1);
    } else {
      // print other characters in hex
      printf("%%%0*X", HEX_WIDTH - 1, c);
      pos = inc(pos, HEX_WIDTH);
    }
  }
}
