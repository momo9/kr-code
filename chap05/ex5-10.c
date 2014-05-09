#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

// arguments version for calculator
main(int argc, char *argv[]) {
  char c;
  double t;
  //while (--argc) {
  //  printf("%s\n", *++argv);
  //}
  //exit(0);
  while (--argc) {
    // get the first char of argv[x]
    c = **++argv;
    //printf("%c\n", c);
    //printf("%s\n", *argv);
    //getchar();
    if (isdigit(c)) {
      push(atof(*argv));
      //puts("push");
      continue;
    } else {
      // the first char is '+' or '-', and the second char is a number
      if ((c == '+' || c == '-') && isdigit(*(*argv + 1))) {
        //printf("%c\n", *(*argv + 1));
        //printf("%d\n", isdigit(*(*argv + 1)));
        push(atof(*argv));
        //puts("push");
        continue;
      }
      // the first char is an operator
      switch (c) {
        case '+':
          push(pop() + pop());
          break;
        case '-':
          t = pop();
          push(pop() - t);
          break;
        case '*':
          push(pop() * pop());
          break;
        case '/':
          t = pop();
          push(pop() / t);
          break;
        default:
          assert(0);
          break;
      }
    }
  }
  printf("%g\n", pop());
}
