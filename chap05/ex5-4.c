#include <stdio.h>

static int strend(char s[], char t[]) {
  char *ps, *pt;
  for (ps = s; *ps; ++ps);
  for (pt = t; *pt; ++pt);
  for (; *ps == *pt && pt != t && ps != s; --pt, --ps);
  if (pt == t && *pt == *ps) return 1;
  else return 0;
}

main(int argc, char *argv[]) {
  printf("%d\n", strend(argv[1], argv[2]));
}
