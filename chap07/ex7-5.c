#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define OPSIZE 64

typedef enum {
  NUM = 1,
  OP = 2,
  RET = 3
} OpType;

static OpType getop(char *s) {
  int c, i;
  // skip the white characters
  while (isspace(c = getchar()) && c != '\n');
  if (c == EOF) {
    s[0] = 0;
    return EOF;
  }
  // get a return
  if (c == '\n') {
    s[0] = 0;
    return RET;
  }
  // copy an operator (number or real operator)
  for (i = 0; !isspace(c) && c != EOF; i++, c = getchar()) {
    s[i] = c;
  }
  s[i] = 0;
  ungetc(c, stdin);

  // is a real operator
  if (i == 1 && (s[0] == '+' || s[0] == '-')) {
    return OP;
  }
  // fprintf(stderr, "i: %d\n", i);
  // otherwise, is a number
  return NUM;
}

main() {
  double num;
  int ret;
  char s[OPSIZE];
  OpType type;
  while ((type = getop(s)) != EOF) {
    switch (type) {
      case NUM:
        // fprintf(stderr, "num: %s\n", s);
        if ((ret = sscanf(s, "%lg", &num)) == 1) {
          push(num);
        } else {
          // the number can not match %lg
          puts("error!");
          exit(0);
        }
        break;
      case OP:
        // fprintf(stderr, "op: %s\n", s);
        switch (s[0]) {
          case '+':
            push(pop() + pop());
            break;
          case '-':
            num = pop();
            push(pop() - num);
            break;
        }
        break;
      case RET:
        // fprintf(stderr, "return\n", s);
        // <return> means the expression is over, print the result
        printf("%g\n", pop());
        break;
    }
  }

}
