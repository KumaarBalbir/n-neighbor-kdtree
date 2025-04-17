// kd_tree.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "kd_tree.h"
#include "../utils/utils.h"

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

// inserts point p with distance d into the neighbors array
void insert_neighbor(Neighbor neighbors[], int k, Point p, double d)
{
  for (int i = 0; i < k; i++)
  {
    if (neighbors[i].dist == -1 || d < neighbors[i].dist)
    {
      // Shift right to make room for the new neighbor
      for (int j = k - 1; j > i; j--)
      {
        neighbors[j] = neighbors[j - 1];
      }
      neighbors[i].point = p;
      neighbors[i].dist = d;
      break;
    }
  }
}

// K-nearest neighbors search
void k_nearest_neighbors(KDNode *root, Point *target, Neighbor neighbors[], int k, int depth)
{
  if (root == NULL)
    return;

  int axis = depth % DIM;
  double d = euclidean_distance(&root->point, target);
  insert_neighbor(neighbors, k, root->point, d);

  KDNode *next = (target->coords[axis] < root->point.coords[axis]) ? root->left : root->right;
  KDNode *other = (next == root->left) ? root->right : root->left;

  // Traverse closer subtree
  k_nearest_neighbors(next, target, neighbors, k, depth + 1);

  // if we need to traverse the other side
  if (other && fabs(target->coords[axis] - root->point.coords[axis]) < neighbors[k - 1].dist)
  {
    k_nearest_neighbors(other, target, neighbors, k, depth + 1);
  }
}

// returns k nearest neighbors to the target point
Neighbor *find_k_nearest(KDNode *root, Point *target, int k)
{
  Neighbor *neighbors = malloc(k * sizeof(Neighbor));
  for (int i = 0; i < k; i++)
    neighbors[i].dist = -1; // mark as empty
  k_nearest_neighbors(root, target, neighbors, k, 0);
  return neighbors;
}

Point findmin(KDNode *root, int axis, int depth)
{
  if (root == NULL)
    return create_invalid_point();

  int current_axis = depth % DIM;

  if (current_axis == axis)
  {
    // Check only the left subtree for min along this axis
    if (root->left == NULL)
      return root->point;
    else
      return findmin(root->left, axis, depth + 1);
  }
  else
  {
    // Check all three: left, right, current node
    Point left_min = findmin(root->left, axis, depth + 1);
    Point right_min = findmin(root->right, axis, depth + 1);
    return minimum(left_min, right_min, root->point, axis);
  }
}

// delete a nodes from the kd-tree
KDNode *delete_node(KDNode *root, Point x, int depth)
{
  if (root == NULL)
    return NULL;

  int axis = depth % DIM;

  // if current node matches the point to delete
  if (are_points_equal(root->point, x))
  {

    // Case 1: Node has right subtree
    if (root->right != NULL)
    {
      Point min = findmin(root->right, axis, depth + 1);
      root->point = min;
      root->right = delete_node(root->right, min, depth + 1);
    }
    // Case 2: No right child, but has left child
    else if (root->left != NULL)
    {
      Point min = findmin(root->left, axis, depth + 1);
      root->point = min;
      root->right = delete_node(root->left, min, depth + 1);
      root->left = NULL;
    }
    // Case 3: Leaf node
    else
    {
      free(root);
      return NULL;
    }
  }
  else if (x.coords[axis] < root->point.coords[axis])
  {
    root->left = delete_node(root->left, x, depth + 1);
  }
  else
  {
    root->right = delete_node(root->right, x, depth + 1);
  }

  return root;
}

void free_kd_tree(KDNode *root)
{
  if (!root)
    return;
  free_kd_tree(root->left);
  free_kd_tree(root->right);
  free(root);
}
