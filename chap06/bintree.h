#ifndef BINTREE_H
#define BINTREE_H

typedef struct Tnode {
  char *word;
  int cnt;
  struct Tnode *left;
  struct Tnode *right;
} Tnode;

// when 'word' not in tree, add a 'word' node
// else, ++cnt of the node
Tnode *addtree(Tnode *pn, char *word);

Tnode *freetree(Tnode *pn);

void printtree(Tnode *pn);

// see words with the same first n char as a group
void printgroup(Tnode *pn, int n);

#endif
