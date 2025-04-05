// point.c
#include <stdio.h>
#include <math.h>
#include "point.h"

double euclidean_distance(Point *a, Point *b)
{
  double sum = 0;
  for (int i = 0; i < DIM; i++)
  {
    double diff = a->coords[i] - b->coords[i];
    sum += diff * diff;
  }
  return sqrt(sum);
}

void print_point(Point *p)
{
  printf("%s: (%.6f, %.6f)\n", p->name, p->coords[0], p->coords[1]);
}
