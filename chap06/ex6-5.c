#include "deftab.h"
#include "getc.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1024

main() {
  char buf[MAXSIZE], line[MAXSIZE], *ret;
  int c;

  install("name", "Liang");
  install("city", "Tianjin");
  install("name", "Mo");
  install("major", "EE-CS");
  install("team", "Arsenal");

  while ((c = readline(line)) > 0) {
    printf((ret = lookup(line, buf)) ? "%s\n" : "%p\n", ret);
  }

  //printtab();

  uninstall("team");

  while ((c = readline(line)) > 0) {
    printf((ret = lookup(line, buf)) ? "%s\n" : "%p\n", ret);
  }

  freetab();
}
