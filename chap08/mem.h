#ifndef MEM_H
#define MEM_H

void *myalloc(size_t n);

void free(void *p);

size_t headersize();

#endif
