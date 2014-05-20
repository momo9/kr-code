#include "bintreex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// return the line number last written
// for line number is increasing
// judge the last line number can avoid duplication
static int lastline(Tnode *pn) {
  return pn->linetab->pre->num;
}

// allocate a tree node, whose word is 'word'
// cnt == 1
// no left, no right
static Tnode *talloc(char *word) {
  Tnode *pn;
  pn = malloc(sizeof(Tnode));

  pn->linetab = 0; // initialization is important
  
  pn->word = malloc(strlen(word) + 1); // +1 for '\0'
  strcpy(pn->word, word);

  pn->cnt = 1;
  pn->left = 0;
  pn->right = 0;
}

Tnode *freetree(Tnode *pn) {
  if (pn) {
    pn->left = freetree(pn->left);
    pn->right = freetree(pn->right);
    //printf("free %s\n", pn->word);
    freelist(pn->linetab, pn->linetab);
    free(pn->word); // 'word' is from malloc()
    pn->word = 0;
    free(pn);
    pn = 0;
  }
  return pn;
}

Tnode *addtree(Tnode *pn, char *word, int line) {
  if (pn) {
    // pn exist
    int cmp;
    if ((cmp = strcmp(word, pn->word)) < 0) {
      // 'word' < 'pn->word'
      pn->left = addtree(pn->left, word, line);
    } else if (cmp > 0) {
      // 'word' > 'pn->word'
      pn->right = addtree(pn->right, word, line);
      // 'word' == 'pn->word'
    } else {
      if (lastline(pn) != line) {
        // append a line number when no duplication
        pn->linetab = append(pn->linetab, line);
      }
      ++pn->cnt;
    }
  } else {
    // 'word' not exist
    pn = talloc(word);
    pn->linetab = append(pn->linetab, line);
  }
  return pn;
}

void printtree(Tnode *pn) {
  if (pn) {
    printtree(pn->left);
    printf("%s: %d, in the following lines\n", pn->word, pn->cnt);
    printlist(pn->linetab, pn->linetab);
    printtree(pn->right);
  }
}
