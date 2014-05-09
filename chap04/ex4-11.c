#include <stdio.h>
#include <ctype.h>

static int get_non_space(void) {
  // buffer the char read for test the end
  static int last = 0;
  int c;
  // skip the white spaces
  for (c = (last) ? last : getchar(); isspace(c) && c != EOF; c = getchar());
  if (c == EOF) return EOF;
  else putchar(c);
  for (c = getchar(); !isspace(c) && c != EOF; c = getchar()) {
    putchar(c);
  }
  putchar('\n');
  if (c == EOF) return EOF;
  // when not EOF, should be buffered
  else {
    last = c;
    return 0;
  }
}

main() {
  int c;
  for (c = get_non_space(); c != EOF; c = get_non_space());
}
