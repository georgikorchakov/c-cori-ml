#ifndef _LOGISTIC_REGRESSION_H
#define _LOGISTIC_REGRESSION_H

/**
 * LogisticRegression.h
 *
 * Created: 19/12/2018
 * Author: Georgi Korchakov
 */

typedef struct logistic_regression_t logistic_regression_t;

struct logistic_regression_t{
  /*---------- Data ----------*/
  int number_of_features;
  float learning_rate;
  int verbose;

  double* coef;
  double intercept;

  /*---------- Pointers to method functions ----------*/

  /** @brief Gradient Descent for logistic regression
   *  @param logistic_regression_t *model, logistic regression struct (pointer)
   *  @param matrix_t *X, feature matrix (pointer)
   *  @param vector_t *y, label vector (pointer)
   *  @return double, lowest cost
   */
  double (*fit)(logistic_regression_t *model, matrix_t *X, vector_t *y);

  /** @brief Gives a prediction for specific data
   *  @param logistic_regression_t *model, logistic regression struct (pointer)
   *  @param double *x, data for prediction
   *  @return double, prediction
   */
  double (*predict)(logistic_regression_t *model, double *x);

  /** @brief Cost Function for logistic regression
   *  @param logistic_regression_t *model, logistic regression struct (pointer)
   *  @param matrix_t *X, feature matrix (pointer)
   *  @param vector_t *y, label vector (pointer)
   *  @return double, cost (how bad are the predictions)
   */
  double (*cost)(logistic_regression_t *model, matrix_t *X, vector_t *y);

};

/** @brief Initialize logistic regression
 *  @param float learning_rate, learning rate for gradient descent
 *  @param int number_of_features, number of features in dataset
 *  @return logistic_regression_t*, Pointer to initialized logistic_regression_t
 */
logistic_regression_t*
logistic_regression_init(float learning_rate,
                         int number_of_features);

/** @brief Gives a prediction for specific data
 *  @param logistic_regression_t *model, logistic regression struct (pointer)
 *  @param double *x, data for prediction
 *  @return double, prediction
 */
double
logistic_regression_predict (logistic_regression_t *model, double *x);

/** @brief Cost Function for logistic regression
 *  @param logistic_regression_t *model, logistic regression struct (pointer)
 *  @param matrix_t *X, feature matrix (pointer)
 *  @param vector_t *y, label vector (pointer)
 *  @return double, cost (how bad are the predictions)
 */
double
logistic_regression_cost (logistic_regression_t *model,
                          matrix_t *X, vector_t *y);

/** @brief Calculate derivatives for gradient descent
 *  @param logistic_regression_t *model, logistic regression struct (pointer)
 *  @param matrix_t *X, feature matrix (pointer)
 *  @param vector_t *y, label vector (pointer)
 *  @return logistic_regression_t*, new derivative calculations for each coef
 */
logistic_regression_t*
logistic_regression_calc_derivatives (logistic_regression_t *model,
                                      matrix_t *X, vector_t *y);

/** @brief Gradient Descent for logistic regression
 *  @param logistic_regression_t *model, logistic regression struct (pointer)
 *  @param matrix_t *X, feature matrix (pointer)
 *  @param vector_t *y, label vector (pointer)
 *  @return double, lowest cost
 */
double
logistic_regression_gradient_descent (logistic_regression_t *model,
                                      matrix_t *X, vector_t *y);

/** @brief Sigmoid math function
 *  @param double x, Input number
 *  @return double, Number between 0 and 1
 */
double
logistic_regression_sigmoid (double x);

#endif // ifndef _LOGISTIC_REGRESSION_H
