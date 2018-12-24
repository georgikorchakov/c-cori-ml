/**
 * cori-math.h
 *
 * Created: 24/12/2018
 * Author: Georgi Korchakov
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../src/math/cori-math.h"
#include "../../../src/csv/csv_reader.h"
#include "../../../src/linear/LogisticRegression/LogisticRegression.h"

int main(){
  // Read train dataset
  dimentions_t csv_train_shape = get_csv_dimentions("iris_train.data");
  matrix_t *X_train = get_csv_features("iris_train.data", 4, csv_train_shape);
  vector_t *y_train = get_csv_labels("iris_train.data", 4, csv_train_shape);

  // Read test dataset
  dimentions_t csv_test_shape = get_csv_dimentions("iris_test.data");
  matrix_t *X_test = get_csv_features("iris_test.data", 4, csv_test_shape);
  vector_t *y_test = get_csv_labels("iris_test.data", 4, csv_test_shape);

  // Initialize model
  logistic_regression_t* model = logistic_regression_init(0.1, 4);
  model->verbose = 1;

  // Train the model
  model->fit(model, X_train, y_train);

  // Test the model
  printf("Test set accuracy = %lf\n", model->score(model, X_test, y_test));
  printf("Train set accuracy = %lf\n", model->score(model, X_train, y_train));

  return 0;
}
