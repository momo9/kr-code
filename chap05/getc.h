#ifndef GETC_H
#define GETC_H

int mygetc(void);
void myungetc(int c);
int readline(char *s);
int readlines(char *line[], int max_line);

#endif
