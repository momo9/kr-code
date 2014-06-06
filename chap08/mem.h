#ifndef MEM_H
#define MEM_H

void *myalloc(size_t n);

void myfree(void *p);

size_t headersize();

#endif
