#ifndef _LINEAR_REGRESSION_H
#define _LINEAR_REGRESSION_H
/**
 * LinearRegression.h
 *
 * Created: 5/12/2018
 * Author: Georgi Korchakov
 */

typedef struct LinearRegression_t LinearRegression_t;

struct LinearRegression_t{
    /*---------- Data ----------*/
	int number_of_features;
    float learning_rate;
    int verbose;

	double* coef_;
	double intercept_;

    /*---------- Pointers to method functions ----------*/

    /** @brief Gradient Descent for linear regression
     *  @param LinearRegression_t* model, linear regression struct (pointer)
     *  @param Matrix_t* X, feature matrix (pointer)
     *  @param Vector_t* y, label vector (pointer)
     *  @return double, lowest cost
     */
    double (*Fit)(LinearRegression_t* model, Matrix_t* X, Vector_t* y);

    /** @brief Gives a prediction for specific data
     *  @param LinearRegression_t* model, linear regression struct (pointer)
     *  @param double* x, data for prediction 
     *  @return double, prediction
     */
    double (*Predict)(LinearRegression_t* model, double* x);

    /** @brief Cost Function for linear regression
     *  @param LinearRegression_t* model, linear regression struct (pointer)
     *  @param Matrix_t* X, feature matrix (pointer)
     *  @param Vector_t* y, label vector (pointer)
     *  @return double, cost (how bad are the predictions)
     */
    double (*Cost)(LinearRegression_t* model, Matrix_t* X, Vector_t* y);
};

/** @brief Initialize Linear Regression
 *  @param float learning_rate, learning rate for gradient descent
 *  @param int number_of_features, number of features in dataset
 *  @return LinearRegression_t*, Pointer to initialized LinearRegression_t model (pointer)
 */
LinearRegression_t* LinearRegressionInit(float learning_rate, int number_of_features);

/** @brief Gives a prediction for specific data
 *  @param LinearRegression_t* model, linear regression struct (pointer)
 *  @param double* x, data for prediction 
 *  @return double, prediction
 */
double LinearRegressionPredict(LinearRegression_t* model, double* x);

/** @brief Cost Function for linear regression
 *  @param LinearRegression_t* model, linear regression struct (pointer)
 *  @param Matrix_t* X, feature matrix (pointer)
 *  @param Vector_t* y, label vector (pointer)
 *  @return double, cost (how bad are our predictions)
 */
double LinearRegressionCost(LinearRegression_t* model, Matrix_t* X, Vector_t* y);

/** @brief Calculate derivatives for gradient descent
 *  @param LinearRegression_t* model, linear regression struct (pointer)
 *  @param Matrix_t* X, feature matrix (pointer)
 *  @param Vector_t* y, label vector (pointer)
 *  @return LinearRegression_t*, new derivative calculations for each coef_
 */
LinearRegression_t* LinearRegressionCalcDerivatives(LinearRegression_t* model, Matrix_t* X, Vector_t* y);

/** @brief Gradient Descent for linear regression
 *  @param LinearRegression_t* model, linear regression struct (pointer)
 *  @param Matrix_t* X, feature matrix (pointer)
 *  @param Vector_t* y, label vector (pointer)
 *  @return double, lowest cost
 */
double LinearRegressionGradientDescent(LinearRegression_t* model, Matrix_t* X, Vector_t* y);

#endif // ifndef  _LINEAR_REGRESSION_H
