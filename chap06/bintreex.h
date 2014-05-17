#ifndef BINTREEX_H
#define BINTREEX_H

#include "linklist.h"

typedef struct Tnode {
  LinkList *linetab;
  char *word;
  int cnt;
  struct Tnode *left;
  struct Tnode *right;
} Tnode;

// when 'word' not in tree, add a 'word' node, add line number infomation
// else, ++cnt of the node, append a line number if not duplicated
Tnode *addtree(Tnode *pn, char *word, int line);

Tnode *freetree(Tnode *pn);

void printtree(Tnode *pn);

#endif
