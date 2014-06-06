// cannot work because cannot read directory file

#ifndef MYDIRENT_H
#define MYDIRENT_H

#define NAMESIZ 255

typedef struct {
  long ino;
  char name[NAMESIZ + 1];
} MyDirent;

typedef struct {
  int fd;
  MyDirent d;
} MyDir;

MyDir *myopendir(char *dirname);

MyDirent *myreaddir(MyDir *pdir);

void myclosedir(MyDir *pdir);

#endif
