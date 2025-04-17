// kd_tree.h
#ifndef KD_TREE_H
#define KD_TREE_H

#define DIM 2                // 2D point (latitude, longitude)
#define MAX_POINTS 1000      // Maximum number of points
#define MAX_NAME_LEN 100     // Maximum length of the name
static int current_axis = 0; // Global variable to store current axis

typedef struct
{
  double coords[DIM];      // e.g., coords[0] = lat, coords[1] = lon
  char name[MAX_NAME_LEN]; // Name of the location (e.g., restaurant)
} Point;

// struct to store neighbor information wrt a point
typedef struct
{
  Point point;
  double dist;
} Neighbor;

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

KDNode *build_kd_tree_sequential(Point *points, int n);

int search_point(KDNode *root, Point *target);

// Nearest neighbor search
void nearest_neighbor(KDNode *root, Point *target, KDNode **best, double *best_dist);

void insert_neighbor(Neighbor neighbors[], int k, Point p, double d);

void k_nearest_neighbors(KDNode *root, Point *target, Neighbor neighbors[], int k, int depth);

Neighbor *find_k_nearest(KDNode *root, Point *target, int k);

Point findmin(KDNode *root, int axis, int depth);

Point findmax(KDNode *root, int axis, int depth);

KDNode *delete_node(KDNode *root, Point x, int depth);

// Free the tree
void free_kd_tree(KDNode *root);

#endif
