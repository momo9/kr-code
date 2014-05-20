#include "deftab.h"
#include "getc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORDSIZE 32

// get the first word from 'line'
// set in 'word'
// return length of the word
static int getword(char *linehead, char *word) {
  int i;
  char *line;
  line = linehead;
  //fprintf(stderr, "%s\n", linehead);
  // skip white
  while (isspace(*line)) ++line;
  // copy the word
  for (i = 0; i < WORDSIZE && !isspace(*line) && *line; ++i, ++line) {
    word[i] = *line;
  }
  if (i == WORDSIZE) {
    // the word is too long
    *word = 0;
    return 0;
  }
  word[i] = 0;
  // return the length read, including white
  return line - linehead;
}

// return 0 when not a definition
static int getdef(char *line) {
  if (strncmp("#define", line, 7) == 0) {
    char def[WORDSIZE], val[WORDSIZE];
    int len;
    // skip '#define'
    line += 7;
    // get 'def'
    len = getword(line, def);
    if (len == 0) {
      return 0;
    }
    line += len;
    // get 'val'
    len = getword(line, val);
    if (len == 0) {
      return 0;
    }
    printf("define %s as %s\n", def, val);
    return install(def, val);
  } else {
    // not a definition
    return 0;
  }
}

main(int argc, char *argv[]) {
  int c;
  FILE *pf;
  char buf[READLINE_BUFSIZE], val[READLINE_BUFSIZE];

  // redirect stdin to argv[1], set definition
  pf = freopen(argv[1], "r", stdin);
  if (pf == 0) exit(0);

  while ((c = readline(buf)) != -1) {
    //fprintf(stderr, "%s\n", buf);
    getdef(buf);
  }
  fclose(stdin);

  // redirect stdin to tty, test the definition
  freopen("/dev/tty", "r", stdin);
  //fprintf(stderr, "here\n");

  char *ret;
  while ((c = readline(buf)) > 0) {
    printf((ret = lookup(buf, val)) ? "%s\n" : "%p\n", ret);
  }
  //fprintf(stderr, "%d\n", c);

  freetab();
}
