#include <stdio.h>

#define N       64

static void escape(char s[], char t[]) {
  int it, is;
  for (it = 0, is = 0; t[it]; ++it) {
    switch (t[it]) {
      case '\n':
        s[is++] = '\\';
        s[is++] = 'n';
        break;
      case '\t':
        s[is++] = '\\';
        s[is++] = 't';
        break;
      default:
        s[is++] = t[it];
        break;
    }
  }
  s[is] = t[it];
}

static void escape_rvt(char s[], char t[]) {
  int it, is;
  for (it = 0, is = 0; t[it]; ++it) {
    switch (t[it]) {
      case '\\':
        ++it;
        switch (t[it]) {
          case 'n':
            s[is++] = '\n';
            break;
          case 't':
            s[is++] = '\t';
            break;
        }
        break;
      default:
        s[is++] = t[it];
        break;
    }
  }
}

main(int argc, char *argv[]) {
  char *t = argv[1];
  char s[N];

  puts(t);
  //escape(s, t);
  escape_rvt(s, t);
  puts(s);
}
