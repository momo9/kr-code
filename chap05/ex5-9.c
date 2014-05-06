#include <stdio.h>
#include <stdlib.h>

static int tab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static int month_day(int year, int day, int *pm, int *pd) {
  int leap;
  int (*a)[13], *p;
  if (year <= 0) return -1;
  leap = (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) ? 1 : 0;
  a = tab + leap;
  if (day > 365 + leap) return -1;
  int d;
  for (d = day, p = *a + 1; d > *p; d -= *p++);
  *pm = p - *a;
  *pd = d;
  return 0;
}

static int day_of_year(int year, int month, int date) {
  int leap;
  int (*a)[13], *p;
  if (year <= 0) return -1;
  leap = (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) ? 1 : 0;
  a = tab + leap;
  if (month < 1 || month > 12) return -1;
  if (date < 1 || date > *(*a + month)) return -1;

  p = *a;
  while (month--) {
    date += *p++;
  }
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
