#include "mystdio.h"
#include <fcntl.h>
#include <stdlib.h>

#define BUFSIZ   8192
#define PERMS    0666


MyFile _ioa[OPEN_MAX] = {
  {0, (char *) 0, (char *) 0, _READ, 0},
  {0, (char *) 0, (char *) 0, _WRITE, 1},
  {0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};

static int fillbuf(MyFile *pf) {
  
  int bufsize;

  // error control
  if ((pf->flag & (_EOF | _ERR | _READ)) != _READ) {
    return EOF;
  }

  // buffer data or not
  bufsize = (pf->flag & _UNBUF) ? 1 : BUFSIZ;

  // when using buffer the first time, we need to allocate memory
  if (NULL == pf->base) {
    pf->base = malloc(bufsize);
  }

  // reading data to buffer
  int nread;
  if ((nread = read(pf->fd, pf->base, BUFSIZ)) <= 0) {
    if (nread == 0) {
      // read return 0, means reaching EOF
      pf->flag |= _EOF;
    } else {
      // read return -1, means error
      pf->flag |= _ERR;
    }
    pf->cnt = 0;
    pf->ptr = pf->base;
    return EOF;
  }

  pf->cnt = nread - 1; // the first character will be read
  pf->ptr = pf->base;
  return (unsigned char) *pf->ptr++;
}

static int flushbuf(int c, MyFile *pf) {
  // error control
  if (pf->flag & (_EOF | _ERR | _WRITE) != _WRITE) {
    return EOF;
  }

  int nwrite, ret;

  // directly output when _UNBUF is marked
  if (pf->flag & _UNBUF) {
    nwrite = write(pf->fd, (char *) &c, 1);
    pf->cnt = 0;
    pf->ptr = pf->base + 1;
    return (nwrite == 1) ? c : EOF;
  }

  // first time, allocate memory
  if (pf->base == NULL) {
    pf->base = malloc(BUFSIZ);
    pf->ptr = pf->base;
  }


  // sometimes, we will flush when buffer is not full
  int towrite;
  towrite = pf->ptr - pf->base;
  if (towrite != (nwrite = write(pf->fd, pf->base, towrite))) {
    pf->flag |= _ERR;
    ret = EOF;
  } else {
    ret = c;
  }

  // make a buffer only the first byte is occupied
  pf->cnt = BUFSIZ - 1;
  pf->ptr = pf->base;
  *pf->ptr++ = c;

  return ret;
}

MyFile *myfopen(const char *filename, const char *mode) {
  int fd;
  MyFile *pf;

  // only 'r', 'w' and 'a' are supported
  if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
    return NULL;
  }

  // find a free position
  for (pf = _ioa; pf < _ioa + OPEN_MAX; ++pf) {
    if ((pf->flag & (_WRITE | _READ)) == 0) {
      // _WRITE != 1 && _READ != 1
      break;
    }
  }

  // no free position
  if (pf >= _ioa + OPEN_MAX) {
    return NULL;
  }

  if ('w' == *mode) {
    fd = creat(filename, PERMS);
  } else if ('a' == *mode) {
    if (-1 == (fd = open(filename, O_WRONLY, 0))) {
      fd = creat(filename, PERMS);
    }
    lseek(fd, 0L, 2); // move to the end
  } else {
    // 'r'
    if (-1 == (fd = open(filename, O_RDONLY, 0))) {
      return NULL;
    }
  }

  // initialization
  pf->fd = fd;
  pf->cnt = 0;
  pf->base = NULL;
  pf->flag = ('r' == *mode) ? _READ : _WRITE;
  return pf;
}


int myfclose(MyFile *pf) {

  if (pf->flag & _WRITE){
    flushbuf(0, pf);
  }

  pf->ptr = NULL;
  if (pf->base != NULL) {
    free(pf->base);
    pf->base = NULL;
  }
  pf->cnt = 0;
  pf->flag = 0;
  return close(pf->fd);
}

int mygetc(MyFile *pf) {
  return (--pf->cnt >= 0) ? (unsigned char) *pf->ptr++ 
                          : fillbuf(pf);
}

int myputc(int c, MyFile *pf) {
  return (--pf->cnt >= 0) ? (*pf->ptr++ = c)
                          : flushbuf(c, pf);
}
  
int mygetchar(void) {
  return mygetc(stdin);
}

int myputchar(int c) {
  return myputc(c, stdout);
}

int myfflush(MyFile *pf) {
  int ret;
  if (pf->flag & _WRITE) {
    ret = flushbuf(0, pf);
    // a redundant 0 is write in buffer
    ++pf->cnt;
    --pf->ptr;
  }
  return ret;
}

#undef BUFSIZ
#undef PERMS
