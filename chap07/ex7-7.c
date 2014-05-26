#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 4096

static int except;
static int showline;
static char *pattern;
static char buf[LINESIZE];

static void putline(int showline, int i, char *buf) {
  if (showline) {
    printf("%d ", i);
  }
  printf("%s", buf);
}

static void grep(FILE *pf) {
  char *p1, *p2;
  int i;
  i = 0;
  while (p1 = fgets(buf, LINESIZE, pf)) {
    // check pattern
    p2 = strstr(buf, pattern); 
    ++i; // update line number
    if (except) {
      if (0 == p2) {
        putline(showline, i, p1);
      }
    } else {
      if (p2) {
        putline(showline, i, p1);
      }
    }
  }
}

main(int argc, char *argv[]) {
  int c;
  if (argc < 2) {
    // at least input the pattern
    fprintf(stderr, "Please input a pattern.\n");
    exit(1);
  }
  pattern = *++argv; --argc;
  // puts(pattern);
  while (--argc > 0 && (*++argv)[0] == '-') { // first character of the next argument
    // fprintf(stderr, "%s\n", *argv);
    while ((c = *++argv[0]) != 0) { // next character of this argument
      // putc(c, stderr);
      switch (c) {
        case 'x':
          except = 1;
          break;
        case 'n':
          showline = 1;
          break;
        default:
          fprintf(stderr, "Cannot recognize argument '-%c'.\n", c);
          exit(1);
          break;
      }
    }
  }
  // fputs("here\n", stderr);
  // if (showline) {
  //   puts("showline");
  // }
  // if (except) {
  //   puts("except");
  // }
  // puts("files:");
  
  // no file name, grep from stdin
  if (argc == 0) {
    printf("stdin:\n");
    grep(stdin);
    exit(0);
  }
  FILE *pf;
  char *filename;
  // there are file names, and argv points at the first file name
  while (argc-- > 0) {
    filename = *argv++;
    printf("%s: \n", filename);
    pf = fopen(filename, "r");
    if (pf) {
      grep(pf);
      fclose(pf);
    } else {
      printf("%s does not exist.\n", filename);
    }
  }
  exit(0);
}
