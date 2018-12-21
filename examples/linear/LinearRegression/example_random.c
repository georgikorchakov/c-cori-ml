/**
 * cori-math.h
 *
 * Created: 9/12/2018
 * Author: Georgi Korchakov
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../src/math/cori-math.h"
#include "../../../src/linear/LinearRegression/LinearRegression.h"

int main(){
  matrix_t* X = matrix_init(100, 1);
  X->fill_random(X, 0, 10);
  X->print(X, 4);

  vector_t* y = vector_init(100);
  vector_fill_random_using_matrix(y, X, 3); //TODO Make it usefull
  y->print(y, 4);

  // Model
  linear_regression_t* model = linear_regression_init(0.001, 1);
  model->verbose = 1;

  printf("Score from fitting function = %f\n", model->fit(model, X, y));
  printf("prediction on first line = %f\n", model->predict(model, X->data[0]));
  printf("Cost = %f\n", model->cost(model, X, y));

  return 0;
}
