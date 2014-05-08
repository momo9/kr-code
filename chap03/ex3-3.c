#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define N       64

// can be isdigit(), isupper(), islower() and so on
typedef int (*pfun_type)(int);

static void exp_one(char s1[], int *pis1, int lens1,
                    char s2[], int *pis2,
                    pfun_type pf) {
  int end;
  end = *pis1 + 2;

  // out of range || not a group  || not succesive
  if (end > lens1 || !pf(s1[end]) || s1[*pis1 + 1] != '-') {
    // copy
    for (; s1[*pis1] && *pis1 <= end; ++(*pis1)) {
      s2[(*pis2)++] = s1[*pis1];
    }
    // give an end
    if (s1[*pis1] == 0) {
      s2[(*pis2)++] = 0;
    } 
    return;
  }

  // expand
  char c;
  for (c = s1[*pis1]; c <= s1[end]; ++c) {
    s2[(*pis2)++] = c;
  }

  *pis1 = end + 1;
}

static void expand(char s1[], char s2[]) {
  int len, is1, is2;
  len = strlen(s1);
  for (is1 = 0, is2 = 0; is1 <= len;) {
    if (isdigit(s1[is1])) {
      exp_one(s1, &is1, len, s2, &is2, isdigit);
    } else if (isupper(s1[is1])) {
      exp_one(s1, &is1, len, s2, &is2, isupper);
    } else if (islower(s1[is1])) {
      exp_one(s1, &is1, len, s2, &is2, islower);
    // copy
    } else {
      s2[is2++] = s1[is1++];
    }
  }
}

main(int argc, char *argv[]) {
  char *s1 = argv[1];
  char s2[N];

  expand(s1, s2);
  puts(s2);
}
