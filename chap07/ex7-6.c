#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 4096

main(int argc, char *argv[]) {
  if (argc != 3) {
    puts("usage: ex7-6.out <file1> <file2>");
    exit(1);
  } else {
    FILE *pf1 = fopen(argv[1], "r");
    FILE *pf2 = fopen(argv[2], "r");
    char buf1[LINESIZE], buf2[LINESIZE];
    char *pl1, *pl2;
    char flag = 0x00;

    do {
      pl1 = fgets(buf1, LINESIZE, pf1);
      pl2 = fgets(buf2, LINESIZE, pf2);
      if (!pl1 || !pl2) {
        break;
      }
      if (strcmp(buf1, buf2) != 0) {
        break;
      }
    } while(1);


    if (feof(pf1)) {
      flag |= 0x01;
    }
    if (feof(pf2)) {
      flag |= 0x02;
    }

    switch(flag) {
      case 0x00:
        // end loop when EOF is not reached
        // means there are diffrent lines
        printf("%s: %s\n", argv[1], buf1);
        printf("%s: %s\n", argv[2], buf2);
        break;
      case 0x01:
        // only <file1> reach EOF
        printf("%s: EOF\n", argv[1]);
        printf("%s: %s\n", argv[2], buf2);
        break;
      case 0x02:
        // only <file2> reach EOF
        printf("%s: %s\n", argv[1], buf1);
        printf("%s: EOF\n", argv[2]);
        break;
      case 0x03:
        // both reach EOF
        // means the two files are the same
        printf("%s and %s are the same.\n", argv[1], argv[2]);
        break;
    }

    fclose(pf1);
    fclose(pf2);
  }
}
