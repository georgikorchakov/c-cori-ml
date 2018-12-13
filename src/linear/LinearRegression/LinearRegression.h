#ifndef _LINEAR_REGRESSION_H
#define _LINEAR_REGRESSION_H

/**
 * LinearRegression.h
 *
 * Created: 5/12/2018
 * Author: Georgi Korchakov
 */

typedef struct linear_regression_t linear_regression_t;

struct linear_regression_t{
    /*---------- Data ----------*/
	int number_of_features;
    float learning_rate;
    int verbose;

	double* coef_;
	double intercept_;

    /*---------- Pointers to method functions ----------*/

    /** @brief Gradient Descent for linear regression
     *  @param linear_regression_t *model, linear regression struct (pointer)
     *  @param matrix_t *X, feature matrix (pointer)
     *  @param vector_t *y, label vector (pointer)
     *  @return double, lowest cost
     */
    double (*fit)(linear_regression_t *model, matrix_t *X, vector_t *y);

    /** @brief Gives a prediction for specific data
     *  @param linear_regression_t *model, linear regression struct (pointer)
     *  @param double *x, data for prediction 
     *  @return double, prediction
     */
    double (*predict)(linear_regression_t *model, double *x);

    /** @brief Cost Function for linear regression
     *  @param linear_regression_t *model, linear regression struct (pointer)
     *  @param matrix_t *X, feature matrix (pointer)
     *  @param vector_t *y, label vector (pointer)
     *  @return double, cost (how bad are the predictions)
     */
    double (*cost)(linear_regression_t *model, matrix_t *X, vector_t *y);
};

/** @brief Initialize Linear Regression
 *  @param float learning_rate, learning rate for gradient descent
 *  @param int number_of_features, number of features in dataset
 *  @return linear_regression_t*, Pointer to initialized linear_regression_t model (pointer)
 */
linear_regression_t* linear_regression_init(float learning_rate, int number_of_features);

/** @brief Gives a prediction for specific data
 *  @param linear_regression_t *model, linear regression struct (pointer)
 *  @param double *x, data for prediction 
 *  @return double, prediction
 */
double linear_regression_predict(linear_regression_t *model, double *x);

/** @brief Cost Function for linear regression
 *  @param linear_regression_t *model, linear regression struct (pointer)
 *  @param matrix_t *X, feature matrix (pointer)
 *  @param vector_t *y, label vector (pointer)
 *  @return double, cost (how bad are our predictions)
 */
double linear_regression_cost(linear_regression_t *model, matrix_t *X, vector_t *y);

/** @brief Calculate derivatives for gradient descent
 *  @param linear_regression_t *model, linear regression struct (pointer)
 *  @param matrix_t *X, feature matrix (pointer)
 *  @param vector_t *y, label vector (pointer)
 *  @return linear_regression_t*, new derivative calculations for each coef_
 */
linear_regression_t* linear_regression_calc_derivatives(linear_regression_t *model, matrix_t *X, vector_t *y);

/** @brief Gradient Descent for linear regression
 *  @param linear_regression_t *model, linear regression struct (pointer)
 *  @param matrix_t *X, feature matrix (pointer)
 *  @param vector_t *y, label vector (pointer)
 *  @return double, lowest cost
 */
double linear_regression_gradient_descent(linear_regression_t *model, matrix_t *X, vector_t *y);

#endif // ifndef _LINEAR_REGRESSION_H
