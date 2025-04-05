// kd_tree.h
#ifndef KD_TREE_H
#define KD_TREE_H

#include "point.h"

typedef struct KDNode
{
  Point point;
  struct KDNode *left;
  struct KDNode *right;
  int axis;
} KDNode;

// Build tree from array of points
KDNode *build_kd_tree(Point points[], int start, int end, int depth);

// Nearest neighbor search
void nearest_neighbor(KDNode *root, Point *target, KDNode **best, double *best_dist);

// Free the tree
void free_kd_tree(KDNode *root);

#endif
