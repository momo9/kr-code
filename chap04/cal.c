#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "cal.h"

#define PUTG(x)         printf(#x": %g\n", (x))
#define IS_VAR          'A'
#define IS_NUMBER       '0'
#define MAX_SIZE        64

// 26 variables: A B C D ... Z
static double var[26];
// variable to save the last answer
static double ans;
// usefull when assignment
static char cur_var;

// get operator or number
static int getop(char **pps, char s[]) {
  int i;
  char *ps;
  if (**pps == 0) {
    s[0] = 0;
    return EOF;
  }
  // get the string (an operator or a number)
  for (i = 0, ps = *pps; ps[i] != ' ' && ps[i] != 0; ++i) {
    s[i] = ps[i];
  }
  
  if (ps[i] == 0) { // the whole equation is over, set *pps to \0
    *pps += i;
  } else { // the whole equation is not over, set *pps to the char after ' '
    *pps += (i + 1);
  }
  s[i] = 0;
  if (isdigit(ps[i - 1])) return IS_NUMBER;
  else if (i == 1 && isupper(ps[0])) return IS_VAR;
  else return ps[i - 1]; // an operator or other, the judgement is in cal()
}

static int is_str(char str[], char s[]) {
  int i;
  for (i = 0; str[i] && s[i] && str[i] == s[i]; ++i);
  if (str[i] == 0 && s[i] == 0) {
    return 1; // str and s are the same
  } else {
    return 0; // str and s are diffrent
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
      case IS_VAR:
        cur_var = s[0]; // used for assignment
        push(var[cur_var - 'A']);
        break;
      case '=':
        pop(); 
        // usage: 5 A = ; in this process, origin 'A' will be pushed into the stack, so pop it
        var[cur_var - 'A'] = pop();
        push(var[cur_var - 'A']); // the assignment also have a value
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
