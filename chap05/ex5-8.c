#include <stdio.h>
#include <stdlib.h>

static int tab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static int month_day(int year, int day, int *pm, int *pd) {
  int leap;
  if (year <= 0) return -1;
  leap = (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) ? 1 : 0;
  if (day > 365 + leap) return -1;
  int m, d;
  for (m = 1, d = day; d > tab[leap][m]; d -= tab[leap][m++]);
  *pm = m;
  *pd = d;
  return 0;
}

static int day_of_year(int year, int month, int date) {
  int leap;
  if (year <= 0) return -1;
  leap = (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) ? 1 : 0;
  if (month < 1 || month > 12) return -1;
  if (date < 1 || date > tab[leap][month]) return -1;

  int i;
  for (i = 1; i < month; ++i) date += tab[leap][i];
  return date;
}

main(int argc, char *argv[]) {
  int year, day, m, d;
  year = atoi(argv[1]);
  day = atoi(argv[2]);
  int res;
  res = month_day(year, day, &m, &d);
  if (res == 0) printf("%d.%d\n", m, d);

  char s[64];
  gets(s);
  m = atoi(s);
  gets(s);
  d = atoi(s);
  day = day_of_year(year, m, d);
  if (day > 0) printf("%d\n", day);
}
