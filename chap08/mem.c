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

// the Header of block before freed block
static Header *pfree = NULL;

static Header *_corealloc(int n) {
  char *p;
  Header *ph;
  
  if (n < MINALLOC) {
    n = MINALLOC;
  }

  if ((char *)-1 == (p = sbrk(n * sizeof(Header)))) {
    return NULL;
  }

  ph = (Header *)p;

  ph->s.size = n;
  myfree(++ph);

  return pfree;
}

void *myalloc(size_t n) {
  Header *ppre, *p;
  int nunit;

  nunit = (n - 1 + sizeof(Header)) / sizeof(Header) + 1;
  // ceil(n / sizeof(Header)) + 1
  // including the memory of header

  if ((ppre = pfree) == NULL) {
    // initialization
    base.s.ptr = ppre = pfree = &base;
    base.s.size = 0;
  }

  for (p = pfree->s.ptr; ; ppre = p, p = p->s.ptr) {
    if (p->s.size >= nunit) {
      if (p->s.size == nunit) {
        ppre->s.ptr = p->s.ptr;
      } else {
        p->s.size -= nunit;
        p += p->s.size;
        p->s.size = nunit;
      }
      pfree = ppre;
      return (p + 1);
    }

    // no appropriate malloc controlled memory
    if (p->s.ptr == pfree) {
      if (NULL == (p = _corealloc(nunit))) {
        return NULL;
      }
    }
  }
}

void myfree(void *p) {
  Header *ph, *piter;

  ph = (Header *)p - 1;

  //   ------------
  //   |          |    
  // piter   ph   --->  piter->s.ptr
  for (piter = pfree; piter < ph && ph < piter->s.ptr; piter = piter->s.ptr) {
    // case 1
    //        -----------------------
    //        |                     |
    //    ph  --> piter->s.ptr      piter
    // 
    // case 2
    //     -----------------------
    //     |                     |
    //     --> piter->s.ptr      piter    ph
    if (piter->s.ptr < piter && (ph > piter || ph < piter->s.ptr)) {
      break;
    }
  }

  if (piter + piter->s.size == ph) {
    //   ---------------
    //   |             |
    // |piter  |ph   |piter->s.ptr   |
    //
    //   --------------
    //   |            |
    // |piter(ph)    |piter->s.ptr   |
    piter->s.size += ph->s.size;
    ph = piter;
  } else {
    //  ----------------------
    //  |                    |
    // |piter   |...|ph    |piter->s.ptr  |
    //
    //  -------------- ---------
    //  |            | |       |
    // |piter   |...|ph    |piter->s.ptr  |
    ph->s.ptr = piter->s.ptr;
    piter->s.ptr = ph;
  }

  if (ph + ph->s.size == ph->s.ptr) {
    //  ----------
    //  |        |
    // |ph     |ph->s.ptr   |
    //
    //  --------------------------------
    //  |        
    // |ph                  |xxxxxxx|
    ph->s.size += ph->s.ptr->s.size;
    ph->s.ptr = ph->s.ptr->s.ptr;
  }

  pfree = piter;
}

size_t headersize() {
  return sizeof(Header);
}

