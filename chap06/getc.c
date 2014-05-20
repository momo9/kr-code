#include <stdio.h>
#include <string.h>
#include "getc.h"

#define MAX_SIZE        8192
#define MAX_LINE        READLINE_BUFSIZE

static int buf;

static char read_buffer[MAX_SIZE];

// if buf is valid, read but; else getchar()
int mygetc(void) {
  int res;
  if (buf != 0) {
    res = buf;
    buf = 0;
  } else {
    res = getchar();
  }
  return res;
}

// put a char in buf
void myungetc(int c) {
  buf = c;
}

// read a line in s
int readline(char *s) {
  int c, i;
  for (c = getchar(), i = 0; c != EOF && c != '\n'; c = getchar(), ++i) {
    if (i >= MAX_LINE) {
      return -1;
    }
    *s++ = c;
  }
  *s = 0;
  return (c == EOF) ? -1 : i;
}

int readlines(char *line[], int max_line) {
  int nline, len;
  char s[MAX_LINE];
  char *pw;
  // all the lines are saved in read_buffer(static)
  for (pw = read_buffer, nline = 0; (len = readline(s)) > 0 && nline < max_line; pw += (len + 1)) {
    if (pw - read_buffer + len + 1 > MAX_SIZE) {
      // overflow
      return -1;
    }
    strcpy(pw, s);
    line[nline++] = pw;
  }
  return nline;
}
#undef MAX_SIZE
#undef MAX_LINE
