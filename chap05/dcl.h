#ifndef DCL_H
#define DCL_H

typedef enum {
  NAME,
  PARENS,
  BRACKETS,
  CALL,
  RETURN,
  PTR,
  OTHER
} Type;

// explain a declaration
int explain(void);

// transform explain to declaration
int unexp(void);

#endif
