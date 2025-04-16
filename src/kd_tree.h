// kd_tree.h
#ifndef KD_TREE_H
#define KD_TREE_H

#define DIM 2            // 2D point (latitude, longitude)
#define MAX_POINTS 1000  // Maximum number of points
#define MAX_NAME_LEN 100 // Maximum length of the name

typedef struct
{
  double coords[DIM];      // e.g., coords[0] = lat, coords[1] = lon
  char name[MAX_NAME_LEN]; // Name of the location (e.g., restaurant)
} Point;

typedef struct KDNode
{
  Point point;
  struct KDNode *left;
  struct KDNode *right;
  int axis;
} KDNode;
// creates a new kd node
KDNode *create_kd_node(Point point, int axis);

// insert a single point into the kd tree
KDNode *insert(KDNode *root, Point *point, int axis);

// Build entire kd-tree (balanced) from array of points
KDNode *build_kd_tree(Point *points, int start, int end, int axis);

// Nearest neighbor search
void nearest_neighbor(KDNode *root, Point *target, KDNode **best, double *best_dist);

// Free the tree
void free_kd_tree(KDNode *root);

#endif
