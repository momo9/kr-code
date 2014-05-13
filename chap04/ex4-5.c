#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

#define PUTG(x)         printf(#x": %g\n", (x))
#define IS_NUMBER       '0'
#define MAX_SIZE        64

// get operator or number
// more details in "cal.c"
static int getop(char **pps, char s[]) {
  int i;
  char *ps;
  if (**pps == 0) {
    s[0] = 0;
    return EOF;
  }
  for (i = 0, ps = *pps; ps[i] != ' ' && ps[i] != 0; ++i) {
    s[i] = ps[i];
  }
  if (ps[i] == 0) {
    *pps += i;
  } else {
    *pps += (i + 1);
  }
  s[i] = 0;
  if (isdigit(ps[i - 1])) return IS_NUMBER;
  else return ps[i - 1];
}

static int is_exp(char s[]) {
  char sexp[] = "exp";
  int i;
  for (i = 0; sexp[i] && s[i] && sexp[i] == s[i]; ++i);
  if (sexp[i] == 0 && s[i] == 0) {
    return 1; // when s == "exp"
  } else {
    return 0; // when s != "exp"
  }
}
static double cal(char equ[]) {
  char s[MAX_SIZE];
  char *ps;
  int sign;
  double t;
  ps = equ;
  do {
    sign = getop(&ps, s);
    //puts(ps);
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
        if (is_exp(s)) {
          t = pop();
          //PUTG(t);
          //getchar();
          push(exp(t));
        }
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
