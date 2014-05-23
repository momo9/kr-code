#include <stdio.h>
#include <stdarg.h>

static void myprintf(char *s, ...) {
  va_list vl;
  va_start(vl, s);
  while (*s) {
    if (*s == '%') {
      // skip the '%'
      switch(*++s) {
        case 'd':
          printf("%d", va_arg(vl, int));
          break;
        case 'g':
          printf("%g", va_arg(vl, double));
          break;
        case '%':
          putchar('%');
          break;
        default:
          break;
      }
      // skip the character after '%'
      ++s;
    } else {
      putchar(*s++);
    }
  }
  va_end(vl);
}

main() {
  myprintf("I'm %d years old.\n", 20);
  myprintf("My weight is %g kg.\n", 65.4);
  myprintf("[%d][%g][%%]\n", 11, 2.1);
}
