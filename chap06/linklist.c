#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// insert a node 'pnew' after 'pthis'
static LinkList *insert(LinkList *pthis, LinkList *pnew) {
  pthis->post->pre = pnew;
  pnew->post = pthis->post;
  pthis->post = pnew;
  pnew->pre = pthis;
}

// return a new node with 'num'
static LinkList *lalloc(int num) {
  LinkList *pl;
  pl = malloc(sizeof(LinkList));

  pl->num = num;

  return pl;
}

// append an element to the end of the list
LinkList *append(LinkList *phead, int num) {
  if (phead) {
    // when phead exists, insert a new node after the last node
    LinkList *pback, *pnew;
    pback = phead->pre;
    pnew = lalloc(num);
    pback = insert(pback, pnew);
  } else {
    // create a new node, set as phead
    phead = lalloc(num);
    phead->pre = phead;
    phead->post = phead;
  }
  return phead;
}

LinkList *freelist(LinkList *pl, LinkList *phead) {
  if (pl->post != phead) {
    // when post is not phead, the node is not the last node
    pl->post = freelist(pl->post, phead);
  }
  //printf("free %d\n", pl->num);
  free(pl); pl = 0;
  return pl;
}

void printlist(LinkList *pl, LinkList *phead) {
  printf("%d\n", pl->num);
  if (pl->post != phead) {
    printlist(pl->post, phead);
  }
}
