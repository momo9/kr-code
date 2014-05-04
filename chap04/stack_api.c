#include "stack_api.h"
#include "stack.h"

double get_top() {
  double t;
  t = pop();
  push(t);
  return t;
}
void cpy_top() {
  double t;
  t = pop();
  push(t);
  push(t);
}
void swap_top() {
  double a, b;
  a = pop();
  b = pop();
  push(a);
  push(b);
}

