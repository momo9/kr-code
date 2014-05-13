#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define PUTG(x)         printf(#x": %g\n", (x))
#define IS_NUMBER       '0'
#define MAX_SIZE        64

// get operator or number
static int getop(char **pps, char s[]) {
  int i;
  char *ps;
  if (**pps == 0) {
    s[0] = 0;
    return EOF;
  }
  // get the string 
  for (i = 0, ps = *pps; ps[i] != ' ' && ps[i] != 0; ++i) {
    s[i] = ps[i];
  }
  if (ps[i] == 0) { // if the whole string is end, set *pps to \0
    *pps += i;
  } else {
    *pps += (i + 1); // if there is still chars, set *pps to the char after space
  }
  s[i] = 0;
  if (isdigit(ps[i - 1])) return IS_NUMBER;
  else return ps[i - 1]; // operator and others
}

static double cal(char equ[]) {
  char s[MAX_SIZE];
  char *ps;
  int sign;
  double t;
  ps = equ;
  do {
    sign = getop(&ps, s);
    switch (sign) {
      case IS_NUMBER: 
        push(atof(s)); 
        break;
      case '+':
        push(pop() + pop());
        break;
      case '-':
        t = pop();
        push(pop() - t);
        break;
      case '%':
        t = pop();
        push((int)pop() % (int)t);
        break;
      default:
        break;
    }
  } while (sign != EOF);
  return pop();
}

main(int argc, char *argv[]) {
  int sign;
  char *ps;
  char s[MAX_SIZE];
  ps = argv[1];
  puts(argv[1]);

  PUTG(cal(argv[1]));
}
