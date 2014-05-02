#include <stdio.h>
//#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

static double atof(char s[]) {
  // skip the whitespace
  int i;
  for (i = 0; isspace(s[i]); ++i);

  // judge the sign
  int sign;
  sign = (s[i] == '-') ? -1 : 1;
  assert(isdigit(s[i]) || s[i] == '-' || s[i] == '+');
  if (!isdigit(s[i])) ++i;

  // integer
  double val;
  for (val = .0; isdigit(s[i]); ++i) {
    val = 10.0 * val + (s[i] - '0');
  }

  assert(s[i] == '.' || s[i] == 0);
  if (s[i] == 0) return val * sign;

  // fraction
  ++i;
  double frac;
  for (frac = 10.0; isdigit(s[i]); ++i, frac *= 10.0) {
    val += ((s[i] - '0') / frac);
  }

  // scientific
  assert(s[i] == 'e' || s[i] == 'E' || s[i] == 0);
  if (s[i] == 0) return val * sign;
  ++i;

  char *pow = &s[i];
  int sci = atof(pow);
  //puts(pow);
  //printf("%d\n", sci);
  if (sci < 0) {
    int i;
    sci = -sci;
    for (i = 0; i < sci; ++i) {
      val /= 10.0;
    }
  } else {
    int i;
    for (i = 0; i < sci; ++i) {
      val *= 10.0;
    }
  }

  return val * sign;
}

main(int argc, char *argv[]) {

  printf("%g\n", atof(argv[1]));
}
