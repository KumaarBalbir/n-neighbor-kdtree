// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "kd_tree.h"
#include "point.h"
#include "../utils/utils.h"

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("{\"error\": \"Usage: ./nearest_neighbor <lat> <lon>\"}\n");
        return 1;
    }
    double user_lat = atof(argv[1]);
    double user_lon = atof(argv[2]);
  // load points from csv
  Point points[MAX_POINTS];
  int n = load_points("data/zomato_locations.csv", points, MAX_POINTS);

  if (n <= 0)
  {
    fprintf(stderr, "Failed to load points\n");
    return 1;
  }

  // build kd tree
  KDNode *root = build_kd_tree(points, 0, n - 1, 0);

  Point user_location;
  // printf("Enter your location (lat lon): ");
  // if (scanf("%lf %lf", &user_location.coords[0], &user_location.coords[1]) != 2) {
  //   fprintf(stderr, "Invalid input. Please enter two numbers (latitude longitude).\n");
  //   return 1; // Exit with error
  // }
  user_location.coords[0] = user_lat;
  user_location.coords[1] = user_lon;
  strcpy(user_location.name, "User");

  KDNode *best = NULL;
  double best_dist = DBL_MAX;
  nearest_neighbor(root, &user_location, &best, &best_dist);

  // printf("\nYour Location:\n");
  // print_point(&user_location);
  // printf("\nNearest Location:\n");
  // print_point(&best->point);
  // printf("Distance: %.6f\n", best_dist);

  printf("{\"name\": \"%s\", \"lat\": %lf, \"lon\": %lf}\n",
           best->point.name, best->point.coords[0], best->point.coords[1]);

  free_kd_tree(root);
  return 0;
}
