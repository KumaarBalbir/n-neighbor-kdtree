// kd_tree.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "kd_tree.h"
#include "../utils/utils.h"

static int current_axis = 0; // Global variable to store current axis

// Comparator function for quick sort
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

KDNode *create_kd_node(Point point, int axis)
{
  KDNode *node = (KDNode *)malloc(sizeof(KDNode));
  if (!node)
  {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  node->point = point;
  node->left = NULL;
  node->right = NULL;
  node->axis = axis;
  return node;
}

// inserts a single point into the kd-tree (used in sequential build)
KDNode *insert(KDNode *root, Point *point, int axis)
{
  if (root == NULL)
    return create_kd_node(*point, axis);

  // Compare the point with the root based on the current axis
  if (point->coords[axis] < root->point.coords[axis])
    root->left = insert(root->left, point, (axis + 1) % DIM);
  else
    root->right = insert(root->right, point, (axis + 1) % DIM);

  return root;
}

// median based balanced kd-tree construction
KDNode *build_kd_tree(Point *points, int start, int end, int axis)
{
  if (start > end)
    return NULL;

  current_axis = axis;
  int mid = (start + end) / 2;

  // Sort points in range [start, end] by current axis
  qsort(points + start, end - start + 1, sizeof(Point), compare_points);

  KDNode *node = create_kd_node(points[mid], axis);
  node->left = build_kd_tree(points, start, mid - 1, (axis + 1) % DIM);
  node->right = build_kd_tree(points, mid + 1, end, (axis + 1) % DIM);

  return node;
}

// builds kd-tree sequentially, point by point -> may lead to unbalanced kd-tree
KDNode *build_kd_tree_sequential(Point *points, int n)
{
  KDNode *root = NULL;
  int axis = 0;
  for (int i = 0; i < n; i++)
  {
    root = insert(root, &points[i], axis);
    axis = (axis + 1) % DIM;
  }
  return root;
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
