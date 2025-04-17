#ifndef UTILS_H
#define UTILS_H
#include "../src/kd_tree.h"
#include <stdio.h>
#include <stdlib.h>
int load_points(const char *filename, Point points[], int max_points);
double euclidean_distance(Point *a, Point *b);
void print_point(Point *p);
int compare_points(const void *a, const void *b);
Point create_invalid_point();
Point minimum(Point a, Point b, Point c, int axis);

#endif
