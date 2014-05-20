#include "deftab.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 101

typedef struct DefNode {
  struct DefNode *next;
  char *def;
  char *val;
} DefNode;

static DefNode *tab[HASHSIZE];

static DefNode *nalloc(char *def, char *val) {
  DefNode *pres;
  pres = malloc(sizeof(DefNode));

  pres->next = 0;
  pres->def = malloc(strlen(def) + 1); // +1 for '\0'
  strcpy(pres->def, def);
  pres->val = malloc(strlen(val) + 1); // +1 for '\0'
  strcpy(pres->val, val);

  return pres;
}

static unsigned int hash(char *w) {
  // hashing function from K&R
  unsigned int hashval;
  hashval = 0;
  while (*w) {
    hashval = hashval * 31 + *w++;
  }
  return hashval % HASHSIZE;
}

static DefNode *append(DefNode *pdn, char *def, char *val) {
  if (pdn) {
    if (strcmp(pdn->def, def) == 0) {
      // if the definition exists, replace the former value
      free(pdn->val);
      pdn->val = malloc(strlen(val) + 1);
      strcpy(pdn->val, val);
    } else {
      pdn->next = append(pdn->next, def, val);
    }
  } else {
    // if the definition does not exist, add a new definition
    pdn = nalloc(def, val);
  }
  return pdn;
}
int install(char *def, char *val) {
  int hashval;
  hashval = hash(def);
  tab[hashval] = append(tab[hashval], def, val);
}

// print the hash table, for test
static void printnode(DefNode *pdn) {
  if (pdn) {
    printf("def: %s; val: %s\n", pdn->def, pdn->val);
    printnode(pdn->next);
  }
}
void printtab(void) {
  int i;
  for (i = 0; i < HASHSIZE; ++i) {
    printf("%d:\n", i);
    printnode(tab[i]);
  }
}

static DefNode *freenode(DefNode *pdn) {
  if (pdn) {
    //fprintf(stderr, "free %s.\n", pdn->def);
    pdn->next = freenode(pdn->next);
    free(pdn->def);
    free(pdn->val);
    free(pdn);
  }
  return pdn = 0;
}
void freetab(void) {
  int i;
  for (i = 0; i < HASHSIZE; ++i) {
    tab[i] = freenode(tab[i]);
  }
}

// look up 'def' in hash table, set its value in 'val' and return it
static void lookuplist(DefNode *pdn, char *def, char *val) {
  if (pdn) {
    if (strcmp(pdn->def, def) == 0) {
      strcpy(val, pdn->val);
    } else {
      lookuplist(pdn->next, def, val);
    }
  }
}
char *lookup(char *def, char *val) {
  int hashval;
  hashval = hash(def);
  *val = 0;
  lookuplist(tab[hashval], def, val);
  // if '*val' is still 0, 'def' is not found
  // when not found, return a NULL pointer
  return (*val == 0) ? 0 : val;
}

static DefNode *unlist(DefNode *pdn, char *def) {
  if (pdn) {
    if (strcmp(pdn->def, def) == 0) {
      //fprintf(stderr, "free %s\n", pdn->def);
      // when found, remove this node, and return its 'next'
      DefNode *pnext;
      free(pdn->def);
      free(pdn->val);
      pnext = pdn->next;
      free(pdn);
      return pnext;
    } else {
      pdn->next = unlist(pdn->next, def);
      return pdn;
    }
  } else {
    return 0;
  }
}
void uninstall(char *def) {
  int hashval;
  hashval = hash(def);
  tab[hashval] = unlist(tab[hashval], def);
}
