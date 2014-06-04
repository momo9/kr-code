// cannot work because cannot read directory file

#include "mydirent.h"
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MyDir *myopendir(char *dirname) {
  struct stat stbuf;
  int fd;
  MyDir *pd;

  if (-1 == (fd = open(dirname, O_RDONLY, 0)) || // cannot open
      -1 == stat(dirname, &stbuf) ||             // cannot get stat
      !(S_ISDIR(stbuf.st_mode)) ||               // is not a directory
      NULL == (pd = malloc(sizeof(MyDir)))) {    // cannot allocate memory
    fprintf(stderr, "Cannot open '%s'.\n", dirname);
    return NULL;
  }

  pd->fd = fd;
  return pd;
}

MyDirent *myreaddir(MyDir *pdir) {
  struct dirent entbuf;
  static MyDirent ent;

  int nread;

  while (sizeof(entbuf) == 
        (nread = read(pdir->fd, &entbuf, sizeof(entbuf)))) {
    if (entbuf.d_ino == 0) { // not occuppied
      continue;
    }

    ent.ino = entbuf.d_ino;
    strncpy(ent.name, entbuf.d_name, entbuf.d_reclen);
    ent.name[entbuf.d_reclen] = '\0';
    return &ent;
  }
  return NULL; // no files left
}

void myclosedir(MyDir *pdir) {
  if (pdir) {
    close(pdir->fd);
    free(pdir);
  }
}
