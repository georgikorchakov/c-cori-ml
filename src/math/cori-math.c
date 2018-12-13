/**
 * cori-math.c
 *
 * Created: 5/12/2018
 * Author: Georgi Korchakov
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "cori-math.h"

/** @brief Sigmoid math function
 *  @param float x, Input number
 *  @return float, Number between 0 and 1
 */
double
sigmoid (double x)
{
  return 1 / (1 + exp(-x));
}

/** @brief Random function
 *  @return double, Random number between 0 and 1
 */
double
cori_random ()
{
  sranddev();
  return (double)rand() / RAND_MAX;
}

/** @brief Generates a random number in a given range
 *  @param int lower, lower boundary of range
 *  @param int upper, upper boundary of range
 *  @return double, Random number in the range [lower, upper]
 */
double
cori_random_between (int lower, int upper)
{
  return lower + (upper - lower) * cori_random();
}

void
vector_fill_random_using_matrix (vector_t *vector, matrix_t *matrix, int displacement)
{
  if (vector->length != matrix->m)
    {
      fputs("Number of samples and number of results do not match!\n", __stdoutp);
      return;
    }

  if (matrix->n != 1)
    {
      fputs("There are more than 1 features!\n", __stdoutp);
      return;
    }

  for (int i = 0; i < vector->length; i++)
    {
      vector->data[i] = displacement * matrix->data[i][0] + cori_random();
    }
}

void
print_line (int n)
{
  putc('+', __stdoutp);
  for (int i = 0; i < n; i++)
    {
      fputs("----------+", __stdoutp);
    }	
}

/** @brief Initialize Matrix
 *  @param int m, Number of Samples
 *  @param int n, Number of Features
 *  @return matrix_t*, Pointer to initialized matrix_t matrix (pointer)
 */
matrix_t*
matrix_init (int m, int n)
{
  matrix_t *matrix = malloc(sizeof(*matrix));

  matrix->data = malloc(m * sizeof(double*));
  for (int i = 0; i < m; i++)
    {
      matrix->data[i] = malloc(n * sizeof(double));
    }
    
  matrix->m = m;
  matrix->n = n;
	
  for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
        {
          matrix->data[i][j] = 0;
        }
    }

  matrix->fill_random = &matrix_fill_random;
  matrix->print = &matrix_print;

  return matrix;
}

void
matrix_fill_random (matrix_t *matrix, int lower, int upper)
{
  for (int i = 0; i < matrix->m; i++)
      for (int j = 0; j < matrix->n; j++)
          matrix->data[i][j] = cori_random_between(lower, upper);
}

void
matrix_print (matrix_t *matrix, int lines)
{
  print_line (matrix->n);
  if (lines > matrix->m) lines = matrix->m;

  for (int i = 0; i < lines; i++)
    {
      putc('\n', __stdoutp);
      for (int j = 0; j < matrix->n; j++)
        {
          fprintf(__stdoutp, "|%10f", matrix->data[i][j]);
        }
      fputs("|\n", __stdoutp);
      print_line(matrix->n);
    }
  putc('\n', __stdoutp);
}

/** @brief Initialize Vector
 *  @param int length, Length of vector
 *  @return vector_t*, Pointer to initialized vector_t vector (pointer)
 */
vector_t*
vector_init (int length)
{
  vector_t *vector = malloc(sizeof(*vector));

  vector->data = malloc(length * sizeof(double));

  vector->length = length;
	
  for (int i = 0; i < length; i++)
    {
      vector->data[i] = 0;
	}

  vector->fill_random = &vector_fill_random; 
  vector->print = &vector_print;
 
  return vector;
}

void
vector_fill_random (vector_t *vector, int lower, int upper)
{
  for (int i = 0; i < vector->length; i++)
      vector->data[i] = cori_random_between(lower, upper);
}

void
vector_print (vector_t *vector, int lines)
{
  if (lines > vector->length) lines = vector->length;

  for (int i = 0; i < lines; i++)
    {
      print_line(1);
      putc('\n', __stdoutp);
      fprintf(__stdoutp, "|%10f|\n", vector->data[i]);
    }
  print_line (1);
  putc('\n', __stdoutp);
}

