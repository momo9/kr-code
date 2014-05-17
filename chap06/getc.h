#ifndef GETC_H
#define GETC_H

int mygetc(void);
void myungetc(int c);

// read a line to s
int readline(char *s);

// read at most max_line lines
// save every head in line[]
// and return the number of read lines
int readlines(char *line[], int max_line);

#endif
