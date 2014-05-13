#include <stdio.h>
#include <string.h>

#define MAX_SIZE        64

// recursive version of string reverse
static void rvrs(char s[], int beg, int end) {
  if (beg <= end) {
    int temp;
    temp = s[beg];
    s[beg++] = s[end];
    s[end--] = temp;
    rvrs(s, beg, end);
  }
}

main(int argc, char *argv[]) {
  char s[MAX_SIZE];
  while (gets(s)) {
    rvrs(s, 0, strlen(s) - 1);
    puts(s);
  }
}

#undef MAX_SIZE
