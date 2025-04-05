#include "utils.h"

int load_points(const char *filename, Point points[])
{
  FILE *file = fopen(filename, "r");
  if (!file)
  {
    perror("Unable to open file");
    return -1;
  }

  int count = 0;
  while (fscanf(file, "%[^,],%lf,%lf\n", points[count].name,
                &points[count].coords[0], &points[count].coords[1]) == 3)
  {
    count++;
  }

  fclose(file);
  return count;
}