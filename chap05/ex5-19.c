#include <stdio.h>
#include "dcl.h"

main() {
  int ret;
  while ((ret = unexp()) != EOF);
}
