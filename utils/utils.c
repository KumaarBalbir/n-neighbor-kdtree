#include "utils.h"
#include <errno.h>
#include <string.h>

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
  char line[256];

  // Skip header line
  if (fgets(line, sizeof(line), file) == NULL)
  {
    fclose(file);
    return -1;
  }

  while (fgets(line, sizeof(line), file))
  {
    char name[100];
    double lat, lon;

    // Parse line manually to handle empty coordinates
    char *token = strtok(line, ",");
    if (!token)
      continue;
    strncpy(name, token, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';

    token = strtok(NULL, ",");
    if (!token || *token == '\n')
      continue;
    lat = atof(token);

    token = strtok(NULL, ",");
    if (!token || *token == '\n')
      continue;
    lon = atof(token);

    strncpy(points[count].name, name, sizeof(points[count].name) - 1);
    points[count].name[sizeof(points[count].name) - 1] = '\0';
    points[count].coords[0] = lat;
    points[count].coords[1] = lon;

    printf("Loaded point %d: %s (%lf, %lf)\n",
           count, points[count].name,
           points[count].coords[0], points[count].coords[1]);
    count++;
  }

  fclose(file);
  printf("Total points loaded: %d\n", count);
  return count;
}