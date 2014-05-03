#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "cal.h"

#define PUTG(x)         printf(#x": %g\n", (x))
#define IS_VAR          'A'
#define IS_NUMBER       '0'
#define MAX_SIZE        64

static double var[26];
static double ans;

// get operator or number
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
  else if (isupper(ps[i - 1])) return IS_VAR;
  else return ps[i - 1];
}

static int is_str(char str[], char s[]) {
  int i;
  for (i = 0; str[i] && s[i] && str[i] == s[i]; ++i);
  if (str[i] == 0 && s[i] == 0) {
    return 1;
  } else {
    return 0;
  }
}
double cal(char equ[]) {
  char s[MAX_SIZE];
  char *ps;
  int sign;
  double t;
  ps = equ;
  do {
    sign = getop(&ps, s);
    //puts(ps);
    //printf("%d\n", sign);
    //puts(s);
    //getchar();
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
        if (is_str("exp", s)) {
          t = pop();
          //PUTG(t);
          //getchar();
          push(exp(t));
        } else if (is_str("ans", s)) {
          push(ans);
        }
        break;
    }
  } while (sign != EOF);
  //puts("print:");
  //print_stack();
  ans = pop();
  return ans;
}

#undef IS_NUMBER
#undef MAX_SIZE
#undef IS_VAR
