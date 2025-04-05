// point.h
#ifndef POINT_H
#define POINT_H

#define DIM 2 // 2D point (latitude, longitude)

typedef struct
{
  double coords[DIM]; // e.g., coords[0] = lat, coords[1] = lon
  char name[100];     // Name of the location (e.g., restaurant)
} Point;

double euclidean_distance(Point *a, Point *b);
void print_point(Point *p);

#endif
