#ifndef GETC_H
#define GETC_H

#define READLINE_BUFSIZE        1024

int mygetc(void);
void myungetc(int c);

// read a line to s
// return the number of words
// 0 means '\n'
// -1 means EOF or overflow
int readline(char *s);

// read at most max_line lines
// save every head in line[]
// and return the number of read lines
int readlines(char *line[], int max_line);

#endif
