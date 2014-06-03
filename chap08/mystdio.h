#ifndef MYSTDIO_H
#define MYSTDIO_H

#define NULL            0
#define EOF             (-1)
#define OPEN_MAX        20

#define feof(p)         (((p)->flag & _EOF) != 0)
#define ferror(p)       (((p)->flag & _ERR) != 0)
#define fileno(p)       ((p)->fd)


typedef struct {
  int cnt;
  char *ptr;
  char *base;
  int flag;
  int fd;
} MyFile;

enum {
  _READ  = 01,
  _WRITE = 02,
  _UNBUF = 04,
  _EOF   = 010,
  _ERR   = 020
};

extern MyFile _ioa[];

#define stdin  (&_ioa[0])
#define stdout (&_ioa[1])
#define stderr (&_ioa[2])

MyFile *myfopen(const char *filename, const char *mode);

int myfclose(MyFile *pf);

int mygetc(MyFile *pf);

int myputc(int c, MyFile *pf);

int mygetchar(void);

int myputchar(int c);

int myfflush(MyFile *pf);

#endif
