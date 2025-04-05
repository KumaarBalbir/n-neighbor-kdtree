// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "kd_tree.h"
#include "point.h"
#include "../utils/utils.h"

#define MAX_POINTS 1000

int main()
{
  Point points[MAX_POINTS];
  int n = load_points("../data/zomato_locations.csv", points);
  if (n <= 0)
  {
    fprintf(stderr, "Failed to load points\n");
    return 1;
  }

  KDNode *root = build_kd_tree(points, 0, n - 1, 0);

  Point user_location;
  printf("Enter your location (lat lon): ");
  scanf("%lf %lf", &user_location.coords[0], &user_location.coords[1]);
  strcpy(user_location.name, "User");

  KDNode *best = NULL;
  double best_dist = DBL_MAX;
  nearest_neighbor(root, &user_location, &best, &best_dist);

  printf("\nYour Location:\n");
  print_point(&user_location);
  printf("\nNearest Location:\n");
  print_point(&best->point);
  printf("Distance: %.6f\n", best_dist);

  free_kd_tree(root);
  return 0;
}
