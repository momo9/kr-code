#ifndef DEFTAB_H
#define DEFTAB_H

// associate def and val
// false when return 0
int install(char *def, char *val);

// set value of 'def' in val, and return it
// false when return 0
char *lookup(char *def, char *val);

// unset 'def'
// false when return 0
void uninstall(char *def);

// free the hash table
void freetab(void);

// print the hash table
void printtab(void);

#endif
