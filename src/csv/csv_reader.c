#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "../math/cori-math.h"
#include "csv_reader.h"

/** @brief Gets dimentions of given csv file
 *  @param char *filename, Name of csv file
 *  @return dimentions_t, struct with m (cols) and n (rows) of given csv file
 */
dimentions_t
get_csv_dimentions (char *filename)
{
  int fd;
  int size;
  int first_iteration = 1;
  char buffer[1024];
  dimentions_t dim;
  dim.m = 0;
  dim.n = 0;
  fd = open(filename, O_RDONLY);

  do
    {
      size = read(fd, buffer, sizeof(buffer));
      if (size == -1) fputs("Read failed!\n", stdout);

      if (first_iteration == 1)
        {
          for (int i = 0; buffer[i] != '\n'; i++)
            if (buffer[i] == ',') ++dim.n;
          dim.n += 1;
          first_iteration = 0;
        }

      for (int i = 0; i < size; i++)
        if (buffer[i] == '\n') ++dim.m;

    } 
  while (size == sizeof(buffer));

  return dim;
}

/** @brief Gets only the features of given csv file
 *  @param char *filename, Name of csv file
 *  @param int label_position, position of your column containing labels
 *  @param dimentions_t dim, dimentions of that csv file
 *  @return matrix_t*, matrix pointer with all features, without labels
 */
matrix_t*
get_csv_features (char *filename, int label_position, dimentions_t dim)
{
  int fd;
  int size;
  char buffer[1024];
  fd = open(filename, O_RDONLY);

  matrix_t *X = matrix_init(dim.m, dim.n - 1);

  char value_buffer[1024];
  int value_pos = 0;
  double value = 0;

  // For strings in csv
  char strings_buffer[100][40];
  int strings_count = 0;
  int string_position = 0;

  int line = 0;
  int position = 0;

  do
    {
      size = read(fd, buffer, sizeof(buffer));
      if (size == -1) fputs("Read failed!\n", stdout);

      for (int i = 0; i < size; i++)
        {
          if (buffer[i] != ',' && buffer[i] != '\n')
            {
              value_buffer[value_pos] = buffer[i];
              ++value_pos;
            }
          else
            {
              value_buffer[value_pos] = '\0';

              if (is_number(value_buffer))
                {
                  sscanf(value_buffer, "%lf", &value);
                }
              else
                {
                  string_position = in_arr(strings_buffer, value_buffer);
                  if (string_position == -1)
                    {
                      strcpy(strings_buffer[strings_count], value_buffer);
                      value = strings_count;
                      ++strings_count;
                    }
                  else
                    {
                      value = string_position;
                    }
                }

              if (position != label_position)
                {
                  X->data[line][position] = value;
                }

              if (buffer[i] == '\n')
                {
                  ++line;
                  position = 0;
                }

              if (buffer[i] == ',')
                ++position;

              value_pos = 0;
            }
        }
    } 
  while (size == sizeof(buffer));

  return X;
}

/** @brief Gets only the laels of given csv file
 *  @param char *filename, Name of csv file
 *  @param int label_position, position of your column containing labels
 *  @param dimentions_t dim, dimentions of that csv file
 *  @return vector_t*, vector pointer with all labels, without features
 */
vector_t*
get_csv_labels (char *filename, int label_position, dimentions_t dim)
{
  int fd;
  int size;
  char buffer[1024];
  fd = open(filename, O_RDONLY);

  vector_t *y = vector_init(dim.m);

  char value_buffer[1024];
  int value_pos = 0;
  double value = 0;

  // For strings in csv
  char strings_buffer[100][40];
  int strings_count = 0;
  int string_position = 0;

  int line = 0;
  int position = 0;

  do
    {
      size = read(fd, buffer, sizeof(buffer));
      if (size == -1) fputs("Read failed!\n", stdout);

      for (int i = 0; i < size; i++)
        {
          if (buffer[i] != ',' && buffer[i] != '\n')
            {
              value_buffer[value_pos] = buffer[i];
              ++value_pos;
            }
          else
            {
              value_buffer[value_pos] = '\0';

              if (is_number(value_buffer))
                {
                  sscanf(value_buffer, "%lf", &value);
                }
              else
                {
                  string_position = in_arr(strings_buffer, value_buffer);
                  if (string_position == -1)
                    {
                      strcpy(strings_buffer[strings_count], value_buffer);
                      value = strings_count;
                      ++strings_count;
                    }
                  else
                    {
                      value = string_position;
                    }
                }

              if (position == label_position)
                {
                  y->data[line] = value;
                }

              if (buffer[i] == '\n')
                {
                  ++line;
                  position = 0;
                }

              if (buffer[i] == ',')
                ++position;

              value_pos = 0;
            }
        }
    } 
  while (size == sizeof(buffer));

  return y;
}

/** @brief Checks whether a string is a number
 *  @param char *str, string for checking
 *  @return int, 0 - not a numberm 1 - number
 */
int
is_number (char *str)
{
  for(int i = 0; str[i] != '\0'; i++)
    {
      if (str[i] != '.' &&
          (str[i] < '0' || str[i] > '9'))
        {
          return 0;
        }
    }

  return 1;
}

/** @brief Search in array whit strings for given string
 *  @param str_arr[100][40], array whit strings
 *  @param char *str, string to search for
 *  @return int, position of given string or -1 if there is no string like this
 */
int
in_arr (char str_arr[100][40], char *str)
{
  for (int i = 0; i < 100; i++)
    {
      if ( strcmp(str_arr[i], str) == 0 )
        {
          return i;
        }
    }

  return -1;
}

