#ifndef MYSORT_H
#define MYSORT_H

typedef int (*FunCmp)(void *pda, void *pdb);

void mysort(void *ppdata[], int beg, int end, FunCmp cmp);

#endif
