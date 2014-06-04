#include <stdio.h>
#include "mem.h"

#define MINALLOC 1024

typedef union Header {
  struct {
    union Header *ptr;
    size_t size;
  } s;
  double align;
} Header;

static Header base;
static Header *pfree = NULL;

void *myalloc(size_t n) {
  Header *ppre;
  int nunit;

  nunit = (n - 1 + sizeof(Header)) / sizeof(Header) + 1;
  // ceil(n / sizeof(Header)) + 1

  if ((ppre = pfree) == NULL) {
    // initialization
    base.s.ptr = ppre = pr
  }
}

void free(void *p);

size_t headersize() {
  return sizeof(Header);
}

