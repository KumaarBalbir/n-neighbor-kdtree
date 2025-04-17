#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int load_points(const char *filename, Point points[], int max_points)
{
  FILE *file = fopen(filename, "r");
  if (!file)
  {
    perror("Error opening file");
    return -1;
  }

  char line[256];
  int count = 0;

  // Skip header line
  if (fgets(line, sizeof(line), file) == NULL)
  {
    fclose(file);
    return -1; // File is empty or error
  }

  // Read each line
  while (fgets(line, sizeof(line), file))
  {
    if (count >= max_points)
      break;

    // Remove trailing newline
    line[strcspn(line, "\n")] = 0;

    // Parse the line
    char name[MAX_NAME_LEN];
    double lat, lon;

    if (sscanf(line, "%[^,],%lf,%lf", name, &lat, &lon) == 3)
    {
      strncpy(points[count].name, name, MAX_NAME_LEN - 1);
      points[count].name[MAX_NAME_LEN - 1] = '\0'; // Ensure null-termination
      points[count].coords[0] = lat;
      points[count].coords[1] = lon;
      count++;
    }
  }

  fclose(file);
  return count;
}

double euclidean_distance(Point *a, Point *b)
{
  double sum = 0;
  sum = (a->coords[0] - b->coords[0]) * (a->coords[0] - b->coords[0]) +
        (a->coords[1] - b->coords[1]) * (a->coords[1] - b->coords[1]);
  return sqrt(sum);
}

void print_point(Point *p)
{
  printf("%s: (%.6f, %.6f)\n", p->name, p->coords[0], p->coords[1]);
}

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

// creates an invalid point, when no point is found
Point create_invalid_point()
{
  Point p;
  for (int i = 0; i < DIM; i++)
    p.coords[i] = INFINITY;
  strcpy(p.name, "INVALID");
  return p;
}