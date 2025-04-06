#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
