#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "dcl.h"
#include "getc.h"
#include <stdlib.h>

#define MAX_TOKEN 32
#define MAX_OUT 4096

static char token[MAX_TOKEN];
static char out[MAX_OUT];

static Type gettoken(void) {
  int c, i;
  c = mygetc();
  //putchar(c);

  // initialization
  token[0] = 0;
  switch(c) {
    case '[': // match '[xxx]', save '[xxx]' in token
      for (i = 0; c != ']'; c = mygetc()) {
        token[i++] = c;
      }
      token[i++] = ']';
      token[i] = 0;
      //puts("return bracket");
      return BRACKETS;
    case '(': // match '()' or '(abcd)'
      if ((c = mygetc()) == ')') { // match '()'
        return PARENS;
      } else {
        myungetc(c); // when (abcd), 'a' read should be put back, and call dcl() to explain 'abcd'
        return CALL;
      }
    case ')': case '\n': // when ')' or '\n', let current dcl() return
      return RETURN;
    case '*': // match '*'
      return PTR;
    default:
      //puts("default");
      if (isalpha(c)) { // match a name, write in token
        for (i = 0; isalnum(c); c = mygetc()) {
          token[i++] = c;
        }
        // c read last (not alnum) should be put back
        myungetc(c);
        token[i] = 0;
        //puts("return name.");
        return NAME;
      }
      return OTHER;
  }
}

// explain the declaration between parens
static void dcl(void) {
  int cntp = 0;
  Type tokentype;

  // count the number of pointers
  while ((tokentype = gettoken()) == PTR) {
    ++cntp;
  }

  // the char after last '*' is in tokentype now
  do {
    switch (tokentype) {
      case NAME:
        //puts("name branch");
        strcat(out, token);
        strcat(out, " is ");
        break;
      case PARENS:
        strcat(out, "function returning ");
        break;
      case BRACKETS:
        //puts("brackets branch");
        strcat(out, "array");
        strcat(out, token);
        strcat(out, " of ");
        break;
      case CALL:
        dcl();
        break;
      default:
        puts("error");
        exit(0);
    } 
  } while ((tokentype = gettoken()) != RETURN);

  // when time to return, output all the pointers, and return
  while(cntp--) {
    strcat(out, "pointer to ");
  }
}

// explain a declaration
int explain(void) {
  int ret;
  char type[MAX_TOKEN];

  // initialization
  out[0] = 0;

  // match the type and space
  ret = scanf("%s ", type);
  if (ret == EOF) {
    return EOF;
  }

  dcl();

  // result in extern array 'out'
  printf("%s", out);
  puts(type);

  return 0;
}

#undef MAX_TOKEN
#undef MAX_OUT
