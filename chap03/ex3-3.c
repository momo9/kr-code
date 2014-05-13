#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define N       64

enum Type {
  NUMBER,
  UPPER,
  LOWER,
  OTHER
};

static enum Type getType(char c) {
  if (isdigit(c)) {
    return NUMBER;
  } else if (isupper(c)) {
    return UPPER;
  } else if (islower(c)) {
    return LOWER;
  } else {
    return OTHER;
  }
}

static void expand(char *dst, char *src) {
  char pre = 0, post;
  while (*src) {
    if (*src == '-') {
      // get the next char
      post = *++src;
      // pre - post can be expanded
      if (post && getType(pre) == getType(post) && pre < post) {
        char c;
        for (c = pre + 1; c < post; ++c) {
          pre = *dst++ = c;
        }
      // pre - post can not be expanded, just print the '-'
      } else {
        pre = *dst++ = '-';
      }
    // just print if not '-'
    } else {
      pre = *dst++ = *src++;
    }
  }
  *dst = 0;
}

main (int argc, char *argv[]) {
  char c;
  char s[N];
  expand(s, argv[1]);
  puts(s);
}
