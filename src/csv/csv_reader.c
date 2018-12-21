#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "../math/cori-math.h"
#include "csv_reader.h"

int main(){
  matrix_t *X = NULL;
  vector_t *y = NULL;
  read_csv("iris.data", &X, &y);

  X->print(X, 180);
  y->print(y, 180);

  return 0;
}

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

int
in_arr(char str_arr[100][40], char *str)
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

int
read_csv(char *file_name, matrix_t **X, vector_t **y)
{
  int fd;
  int close_err;
  int rv;

  fd = open(file_name, O_RDONLY);
  if(fd == -1) fputs("Open failed!\n", stdout);

  char buffer[1024];
  char value[1024];
  float real_value = 0;
  int value_pos = 0;

  int line = 0;
  int features = 1;
  int feature = 0;
  int first = 1;

  // For strings in csv
  char strings[100][40];
  int count_str = 0;
  int pos = 0;

  // Count number of samples and number of features
  do
    {
      rv = read(fd, buffer, sizeof(buffer));
      if(rv == -1) fputs("Read failed!\n", stdout);

      if(first == 1)
        {
          for(int i = 0; buffer[i] != '\n'; i++)
              if(buffer[i] == ',') ++features;
          first = 0;
        }

      for(int i = 0; i < rv; i++)
          if(buffer[i] == '\n') ++line;

    } 
  while (rv == sizeof(buffer));

  close_err = close(fd);
  if(close_err == -1) fputs("Close failed!\n", stdout);

  // Initialize matrix and vector
  *X = matrix_init(line, features -1);
  *y = vector_init(line);

  fd = open(file_name, O_RDONLY);
  if(fd == -1) fputs("Open failed!\n", stdout);

  line = 0;
  feature = 0;

  do
    {
      rv = read(fd, buffer, sizeof(buffer));
      if(rv == -1) fputs("Read failed!\n", stdout);

      for(int i = 0; i < rv; i++)
        {
          if(buffer[i] != ',' && buffer[i] != '\n')
            {
              value[value_pos] = buffer[i];
              ++value_pos;
            }
          else
            {
              value[value_pos] = '\0';

              if ( is_number(value) )
                {
                  sscanf(value, "%f", &real_value);
                }
              else
                {
                  pos = in_arr(strings, value);
                  if (pos == -1)
                    {
                      strcpy(strings[count_str], value);
                      real_value = count_str;
                      ++count_str;
                    }
                  else
                    {
                      real_value = pos;
                    }
                }

              if(feature == features - 1)
                {
                  (*y)->data[line] = real_value;
                }
              else
                {
                  (*X)->data[line][feature] = real_value;
                }

              if (buffer[i] == '\n')
                {
                  ++line;
                  feature = 0;
                  value_pos = 0;
                }
              if(buffer[i] == ',')
                {
                  ++feature;
                  value_pos = 0;
                }

            }
        }

    }
  while (rv == sizeof(buffer));

  close(fd);
  if(close_err == -1) fputs("Close failed!\n", stdout);

  return 1;
}
