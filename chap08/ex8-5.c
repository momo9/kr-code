#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
//#include "mydirent.h"

#define MAXNAME 1024

static char self[] = ".";
static char par[] = "..";

static int recur = 0;

static int putdir(char *dirname) {

  DIR *pdir;
  struct dirent *pentry;
  static struct stat stbuf;
  char buf[MAXNAME];

  if (NULL == (pdir = opendir(dirname))) {
    fprintf(stderr, "Cannot access %s.\n", dirname);
    return -1;
  }

  while (NULL != (pentry = readdir(pdir))) {
    if (0 != strcmp(self, pentry->d_name) && 
        0 != strcmp(par,  pentry->d_name)) {
      
      // get file name
      if (strlen(dirname) + strlen(pentry->d_name) + 2 > MAXNAME) {
        // + 2 means '/' and '\0'
        fprintf(stderr, "File name is too long.\n");
        continue;
      }
      sprintf(buf, "%s/%s", dirname, pentry->d_name);
        
      if (recur) {

        if (-1 == (stat(buf, &stbuf))) {
          fprintf(stderr, "Cannot access %s.\n", buf);
          continue;
        }

        // if the file is a directory, call recursively
        if (S_ISDIR(stbuf.st_mode)) {
          putdir(buf);
          continue;
        }
      }

      // not a directory or not -r argument
      // output directly
      puts(buf);
    }
  }

  closedir(pdir);

  return 0;
}

// cannot work
//static int myputdir(char *dirname) {
//
//  MyDir *pdir;
//  MyDirent *pentry;
//
//  if (NULL == (pdir = myopendir(dirname))) {
//    fprintf(stderr, "Cannot access %s.\n", dirname);
//    return -1;
//  }
//
//  while (NULL != (pentry = myreaddir(pdir))) {
//    if (0 != strcmp(self, pentry->name) && 
//        0 != strcmp(par,  pentry->name)) {
//      puts(pentry->name);
//    }
//  }
//
//  myclosedir(pdir);
//
//  return 0;
//}

int main(int argc, char *argv[]) {
  
  char *dirname;
  int c;

  // argument control
  while (--argc > 0 && '-' == (*++argv)[0]) {
    c = *++argv[0];
    switch (c) {
      case 'r': case 'R':
        recur = 1;
        break;
      default:
        fprintf(stderr, "Invalid argument -%c.\n", c);
        exit(1);
        break;
    }
  }

  // no directory, print "."
  if (0 == argc) {
    dirname = self;
    putdir(dirname);
    exit(0);
  }

  // print all directories
  while (argc-- > 0) {
    dirname = (argv++)[0];
    putdir(dirname);
  }
  exit(0);
}
