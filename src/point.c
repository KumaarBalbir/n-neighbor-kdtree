// point.c
#include <stdio.h>
#include <math.h>
#include "point.h"

double euclidean_distance(Point *a, Point *b)
{
  double sum = 0;
  sum = (a->coords[0] - b->coords[0]) * (a->coords[0] - b->coords[0]) +
        (a->coords[1] - b->coords[1]) * (a->coords[1] - b->coords[1]);
  return sqrt(sum);
}

void print_point(Point *p)
{
  printf("%s: (%.6f, %.6f)\n", p->name, p->coords[0], p->coords[1]);
}
