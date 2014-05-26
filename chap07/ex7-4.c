#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

static int myscanf(char *s, ...) {
  va_list vl;
  va_start(vl, s);
  int i, ret;
  for (i = 0; *s; ++s) {
    if (*s == '%') {
      // match argument
      switch(*++s) {
        case 'd':
          ret = scanf("%d", va_arg(vl, int *));
          i += ret;
          if (ret == 0) {
            // ret = 0 means match failure
            va_end(vl);
            return i;
          }
          break;
        case 'g':
          ret = scanf("%lg", va_arg(vl, double *));
          i += ret;
          if (ret == 0) {
            va_end(vl);
            return i;
          }
          break;
        default:
          break;
      }
    } else if (*s == ' ') {
      // match at least one white character
      if (!isspace(ret = getchar())) {
        // already return, no need to ungetc
        va_end(vl);
        return i;
      }
      while (isspace(ret = getchar()));
      ungetc(ret, stdin);
    } else {
      // strict matching
      if ((ret = getchar()) != *s) {
        va_end(vl);
        return i;
      }
    }
  }
  va_end(vl);
  return i;
}

main() {
  int age, ret;
  double weight;
  ret = myscanf("age:%d, weight:%g", &age, &weight);
  printf("%d, age: %d, weight: %g\n", ret, age, weight);
}
