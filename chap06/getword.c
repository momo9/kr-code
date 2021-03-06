#include "getword.h"
#include "getc.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// indicate the current line number
static int linenumber = 1;

int getlinenumber() {
  return linenumber;
}

int isvar(char c) {
  return isalnum(c) || c == '_';
}

static void skiperror() {
  int c;
  while (!isspace(c = mygetc()));
  myungetc(c);
}

int getword(char *word, int limit) {
  int c;
  char *w = word;
  // skip space and line count
  while (isspace(c = mygetc())) {
    if (c == '\n') {
      ++linenumber;
    }
  }
  switch (c) {
    // is comments
    case '/':
      if ((c = mygetc()) == '/') {
        // acctually comments
        *w++ = '/'; --limit;
        *w++ = '/'; --limit; // do not consider the case where limit < 2
        // copy until '\n' or limit is reached
        while ((c = mygetc()) != '\n' && limit-- > 1) { // left one for '\0'
          *w++ = c;
        }
        if (c == '\n') {
          myungetc(c);
        }
        if (limit <= 1) {
          // limit is reached, which is an error
          // skip the line
          while ((c = mygetc()) != '\n');
          myungetc(c);
          return *word = 0;
        }
        // normal return
        *w = 0;
        return *word;
      } else {
        // error, just one '/'
        // skip the error word
        skiperror();
        return *word = 0;
      }
      break;
    case '\"':
      // is string constant
      *w++ = '\"'; --limit;
      // copy until a '\"' or limit is reached
      while ((c = mygetc()) != '\"' && limit-- > 2) { // left for '\"' and '\0'
        *w++ = c;
      }
      if (limit <= 2 || !isspace(c = mygetc())) {
        // limit is reached and error case
        // skip the word
        skiperror();
        return *word = 0;
      }
      // normal case
      *w++ = '\"';
      *w = 0;
      myungetc(c);
      return *word;
      break;
    case EOF:
      *word = 0;
      return EOF;
      break;
    default:
      if (isvar(c)) {
        // is a variable
        //fputs("isvar\n", stderr);
        *w++ = c;
        while (isvar(c = mygetc()) && limit-- > 1) { // left one for '\0'
          //fputc(c, stderr);
          *w++ = c;
        }
        if (limit == 1 || !isspace(c)) {
          // limit is reached or error case, skip the word
          skiperror();
          return *word = 0;
        }
        // normal case
        *w = 0;
        //fprintf(stderr, "%s\n", word);
        myungetc(c);
        return *word;
      } else {
        // undefined case
        return *word = 0;
      }
      break;
  }
}

