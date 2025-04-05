// kd_tree.c
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "kd_tree.h"
#include "point.h"

static int current_axis = 0; // Global variable to store current axis

// Comparator function for qsort
int compare_points(const void *a, const void *b)
{
  Point *p1 = (Point *)a;
  Point *p2 = (Point *)b;
  if (p1->coords[current_axis] < p2->coords[current_axis])
    return -1;
  if (p1->coords[current_axis] > p2->coords[current_axis])
    return 1;
  return 0;
}

KDNode *build_kd_tree(Point points[], int start, int end, int depth)
{
  if (start > end)
    return NULL;

  current_axis = depth % DIM; // Set current axis before sorting
  int mid = (start + end) / 2;

  // Sort based on axis
  qsort(points + start, end - start + 1, sizeof(Point), compare_points);

  KDNode *node = (KDNode *)malloc(sizeof(KDNode));
  node->point = points[mid];
  node->axis = current_axis;
  node->left = build_kd_tree(points, start, mid - 1, depth + 1);
  node->right = build_kd_tree(points, mid + 1, end, depth + 1);

  return node;
}

void nearest_neighbor(KDNode *root, Point *target, KDNode **best, double *best_dist)
{
  if (!root)
    return;

  double dist = euclidean_distance(&root->point, target);
  if (dist < *best_dist)
  {
    *best_dist = dist;
    *best = root;
  }

  int axis = root->axis;
  KDNode *near = (target->coords[axis] < root->point.coords[axis]) ? root->left : root->right;
  KDNode *far = (near == root->left) ? root->right : root->left;

  nearest_neighbor(near, target, best, best_dist);

  // Prune only if necessary
  if (fabs(root->point.coords[axis] - target->coords[axis]) < *best_dist)
  {
    nearest_neighbor(far, target, best, best_dist);
  }
}

void free_kd_tree(KDNode *root)
{
  if (!root)
    return;
  free_kd_tree(root->left);
  free_kd_tree(root->right);
  free(root);
}
