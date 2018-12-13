#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "../math/cori-math.h"
#include "csv_reader.h"

int main(){
  matrix_t *X = NULL;
  vector_t *y = NULL;
  read_csv("iris.data", X, y);

  return 0;
}

int
read_csv(char *file_name, matrix_t *X, vector_t *y){
  int fd;
  int close_err;
  int rv;
    
  fd = open(file_name, O_RDONLY);
  if(fd == -1) fputs("Open failed!\n", __stdoutp);

  char buffer[1024];
  char value[1024];
  float real_value = 0;
  int value_pos = 0;

  int line = 0;
  int features = 1;
  int feature = 0;
  int first = 1;

  do
    {
      rv = read(fd, buffer, sizeof(buffer));
      if(rv == -1) fputs("Read failed!\n", __stdoutp);

      if(first == 1)
        {
          for(int i = 0; buffer[i] != '\n'; i++)
              if(buffer[i] == ',') ++features;
          fprintf(__stdoutp, "%d\n", features);
          first = 0;
        }

      for(int i = 0; i < rv; i++)
          if(buffer[i] == '\n') ++line;

    } 
  while (rv == sizeof(buffer));

  close_err = close(fd);
  if(close_err == -1) fputs("Close failed!\n", __stdoutp);

  X = matrix_init(line+1, features -1);
  y = vector_init(line+1);

  fd = open(file_name, O_RDONLY);
  if(fd == -1) printf("Open failed!\n");

  line = 0;
  feature = 0;

  do
    {
      rv = read(fd, buffer, sizeof(buffer));
      if(rv == -1) fputs("Read failed!\n", __stdoutp);

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
              sscanf(value, "%f", &real_value);

              //printf("%d --- %d\n", line, feature);
              if(feature == features - 1)
                {
                  y->data[line] = real_value;
                }
              else
                {
                  X->data[line][feature] = real_value;
                }
                
              {
                if(buffer[i] == ',')
                  {
                    ++feature;
                    value_pos = 0;
                  }
                else if (buffer[i] == '\n')
                  {
                    ++line;
                    feature = 0;
                    value_pos = 0;
                  }
              }
            }
        }

    }
  while (rv == sizeof(buffer));

  X->print(X, 180);
  y->print(y, 180);
  close(fd);
  if(close_err == -1) fputs("Close failed!\n", __stdoutp);

  return 1;
}
