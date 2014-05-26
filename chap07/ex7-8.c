#include <stdio.h>
#include <stdlib.h>

#define LINE_PER_PAGE 30
#define LINESIZE      1024

static char *filename;
static int page;

static void puthead() {
  printf("page: %-25d %s\n", page, filename);
}

static void putfile(FILE *pf) {
  static char buf[LINESIZE];
  int nline;
  page = 1, nline = 1;
  while (fgets(buf, LINESIZE, pf)) {
    // get a line and print
    if (1 == nline) {
      // put a header when first line
      puthead(), ++page;
    }
    printf("%2d %s", nline, buf);
    if (++nline > LINE_PER_PAGE) {
      // reset 'nline' as 1 when reach the end of a page
      nline = 1;
      printf("\n");
    }
  }

  // pad empty lines of the last page
  while (nline <= LINE_PER_PAGE) {
    printf("%2d\n", nline++);
  }

  printf("\n");
}

main(int argc, char *argv[]) {
  FILE *pf;
  while (--argc > 0) {
    filename = *++argv;
    if (pf = fopen(filename, "r")) {
      putfile(pf);
      fclose(pf);
    } else {
      fprintf(stderr, "%s does not exist.\n", filename);
    }
  }
  exit(0);
}
