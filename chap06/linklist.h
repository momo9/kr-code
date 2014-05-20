#ifndef LINKLIST_H
#define LINKLIST_H

typedef struct LinkList {
  int num;
  struct LinkList *pre;
  struct LinkList *post;
} LinkList;

// append an element to the end of the list
LinkList *append(LinkList *phead, int num);

LinkList *freelist(LinkList *pl, LinkList *phead);

void printlist(LinkList *pl, LinkList *phead);

#endif
