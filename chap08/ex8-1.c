#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024

main(int argc, char *argv[]) {
  if (argc > 2) {
    fprintf(stderr, "Usage: ex8-1.out <filename>\n");
    exit(1);
  }

  int fd, nread;
  char buf[SIZE];

  if (argc == 2) {
    if ((fd = open(argv[1], O_RDONLY, 0)) == -1) {
      fprintf(stderr, "Cannot open %s\n", argv[1]);
      exit(1);
    }
  } else {
    fd = 0;
  }

  while ((nread = read(fd, buf, SIZE)) > 0) {
    //fprintf(stderr, "nread: %d\n", nread);
    write(1, buf, nread);
  }

  close(fd);

  exit(0);
}
