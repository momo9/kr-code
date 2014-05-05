#include <stdio.h>
#include <string.h>
#include "getc.h"

#define MAX_SIZE        8192
#define MAX_LINE        64

static int buf;

static char read_buffer[MAX_SIZE];

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
void myungetc(int c) {
  buf = c;
}

int readline(char *s) {
  int c, i;
  for (c = getchar(), i = 0; c != EOF && c != '\n'; c = getchar(), ++i) {
    if (i >= MAX_LINE) {
      return -1;
    }
    *s++ = c;
  }
  *s = 0;
  return i;
}

int readlines(char *line[], int max_line) {
  int nline, len;
  char s[MAX_LINE];
  char *pw;
  for (pw = read_buffer, nline = 0; (len = readline(s)) > 0 && nline < max_line; pw += (len + 1)) {
    if (pw - read_buffer + len + 1 > MAX_SIZE) {
      return -1;
    }
    strcpy(pw, s);
    line[nline++] = pw;
  }
  return nline;
}
#undef MAX_SIZE
#undef MAX_LINE
