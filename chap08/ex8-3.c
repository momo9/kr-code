#include "mystdio.h"

int main(int argc, char *argv[]) {
  MyFile *pf;
  if (1 == argc) {
    // read from stdin
    pf = stdin;
  } else {
    // read from argv[1]
    if ((pf = myfopen(argv[1], "r")) == NULL) {
      return 1;
    }
  }

  int c;
  while ((c = mygetc(pf)) != EOF) {
    //write(1, &c, 1);
    myputchar(c);
  }

  myfclose(pf);
  myfflush(stdout);
}
