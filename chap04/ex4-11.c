#include <stdio.h>
#include <ctype.h>

static int get_non_space(void) {
  static int last = 0;
  int c;
  for (c = (last) ? last : getchar(); isspace(c) && c != EOF; c = getchar());
  if (c == EOF) return EOF;
  else putchar(c);
  for (c = getchar(); !isspace(c) && c != EOF; c = getchar()) {
    putchar(c);
  }
  putchar('\n');
  if (c == EOF) return EOF;
  else {
    last = c;
    return 0;
  }
}

main() {
  int c;
  for (c = get_non_space(); c != EOF; c = get_non_space());
}
