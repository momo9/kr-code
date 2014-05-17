#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// allocate a tree node, whose word is 'word'
// cnt == 1
// no left, no right
static Tnode *talloc(char *word) {
  Tnode *pn;
  pn = malloc(sizeof(Tnode));
  
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
    free(pn->word); // 'word' is from malloc()
    pn->word = 0;
    free(pn);
    pn = 0;
  }
  return pn;
}

Tnode *addtree(Tnode *pn, char *word) {
  if (pn) {
    // pn exist
    int cmp;
    if ((cmp = strcmp(word, pn->word)) < 0) {
      // 'word' < 'pn->word'
      pn->left = addtree(pn->left, word);
    } else if (cmp > 0) {
      // 'word' > 'pn->word'
      pn->right = addtree(pn->right, word);
      // 'word' == 'pn->word'
    } else {
      ++pn->cnt;
    }
  } else {
    // 'word' not exist
    pn = talloc(word);
  }
  return pn;
}

void printtree(Tnode *pn) {
  if (pn) {
    printtree(pn->left);
    printf("%s: %d\n", pn->word, pn->cnt);
    printtree(pn->right);
  }
}

void printgroup(Tnode *pn, int n) {
  static char *head = ""; // the initial value can match nothing
  if (pn) {
    int cmp;

    printgroup(pn->left, n);

    if ((cmp = strncmp(head, pn->word, n)) != 0) {
      // cannot match, output a group mark, and change head
      printf("## group ");
      int i;
      char *p;
      for (i = 0, p = pn->word; i < n && *p; ++i, ++p) {
        printf("%c", *p);
      }
      puts("");
      head = pn->word;
    }
    printf("%s: %d\n", pn->word, pn->cnt); // print regardless of matching

    printgroup(pn->right, n);
  }
}
