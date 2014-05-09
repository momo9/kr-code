#include <stdio.h>
#include <string.h>
#include <assert.h>

static int strrindex(char s[], char t[]) {
  int lens, lent;
  lens = strlen(s);
  lent = strlen(t);
  assert(lens > lent);

  int i, j, k;
  // check from end
  for (i = lens - lent; i >= 0; --i) {
    for (j = i, k = 0; t[k] && t[k] == s[j]; ++j, ++k);
    if (t[k] == 0) return i;
  }
  return -1;
}

main(int argc, char *argv[]) {
  
  printf("%d\n", strrindex(argv[1], argv[2]));
}
