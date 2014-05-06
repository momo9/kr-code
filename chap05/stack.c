#include <stdio.h>
#include "stack.h"

#define STACK_SIZE    64

static double a[STACK_SIZE];
static int top;

double pop() {
  if (top > 0) {
    return a[--top];
  } else {
    puts("The stack is empty.");
  }
}

void push(double data) {
  if (top == STACK_SIZE) {
    puts("The stack is full.");
  } else {
    a[top++] = data;
  }
}

void print_stack() {
  int i;
  for (i = 0; i < top; ++i) {
    printf("%g ", a[i]);
  }
  puts("");
}

void clear() {
  top = 0;
}
#undef STACK_SIZE
