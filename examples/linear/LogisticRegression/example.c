/**
 * cori-math.h
 *
 * Created: 20/12/2018
 * Author: Georgi Korchakov
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../src/math/cori-math.h"
#include "../../../src/linear/LogisticRegression/LogisticRegression.h"

int main(){
  // {{1}, {0}, {1}, {0}};
  matrix_t* X = matrix_init(4, 1);
  X->data[0][0] = 1;
  X->data[1][0] = 0;
  X->data[2][0] = 1;
  X->data[3][0] = 0;

  //X->print(X, 4);

  vector_t* y = vector_init(4);
  y->data[0] = 0;
  y->data[1] = 1;
  y->data[2] = 0;
  y->data[3] = 1;

  //y->print(y, 4);

  // Model
  logistic_regression_t* model = logistic_regression_init(0.1, 1);
  model->verbose = 1;

  double x1[1] = {0};
  double x2[1] = {1};

  printf("Prediction on 0: %f\n", model->predict(model, x1));
  printf("Cost: %f\n", model->cost(model, X, y));
  printf("Best: %f\n", model->fit(model, X, y));
  printf("Prediction on 0: %f\n", model->predict(model, x1));
  printf("Probability on 0: %f\n", model->predict_proba(model, x1));

  printf("Prediction on 1: %f\n", model->predict(model, x2));
  printf("Probability on 1: %f\n", model->predict_proba(model, x2));

  return 0;
}
