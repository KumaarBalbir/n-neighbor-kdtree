#include "utils.h"
#include <errno.h>

int load_points(const char *filename, Point points[])
{
  printf("Attempting to open file: %s\n", filename);
  FILE *file = fopen(filename, "r");
  if (!file)
  {
    printf("Error opening file: %s (errno: %d)\n", strerror(errno), errno);
    return -1;
  }

  int count = 0;
  while (fscanf(file, "%[^,],%lf,%lf\n", points[count].name,
                &points[count].coords[0], &points[count].coords[1]) == 3)
  {
    printf("Loaded point %d: %s (%lf, %lf)\n",
           count, points[count].name,
           points[count].coords[0], points[count].coords[1]);
    count++;
  }

  fclose(file);
  printf("Total points loaded: %d\n", count);
  return count;
}