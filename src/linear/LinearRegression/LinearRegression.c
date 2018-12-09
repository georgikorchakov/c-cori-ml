/**
 * LinearRegression.c
 *
 * Created: 5/12/2018
 * Author: Georgi Korchakov
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../math/cori-math.h"
#include "LinearRegression.h"

/** @brief Initialize linear regression
 *  @param float learning_rate, learning rate for gradient descent
 *  @param int number_of_features, number of features in dataset
 *  @return LinearRegression_t*, Pointer to initialized LinearRegression_t model (pointer)
 */
LinearRegression_t* LinearRegressionInit(float learning_rate, int number_of_features){
    LinearRegression_t* model = malloc(sizeof(*model));

    model->learning_rate = learning_rate;
	model->number_of_features = number_of_features;

	// Initialize model->intercept_ to be random value between 0 and 1
	model->intercept_ = cori_random();

	// Allocate 
	model->coef_ = malloc(sizeof(double) * number_of_features);
	for(int i = 0; i < number_of_features; i++){
		// Initialize model->coef_[i] to be random value between 0 and 1
		model->coef_[i] = cori_random();
	}
    model->verbose = 0;
    
    model->Fit = &LinearRegressionGradientDescent;
    model->Predict = &LinearRegressionPredict;
    model->Cost = &LinearRegressionCost;

    return model;
}

/** @brief Gives a prediction for specific data
 *  @param LinearRegression_t* model, linear regression struct (pointer)
 *  @param double* x, data for prediction
 *  @return double, prediction
 */
double LinearRegressionPredict(LinearRegression_t* model, double* x){
    double y = model->intercept_;
    for(int i = 0; i < model->number_of_features; i++){
        y += model->coef_[i] * x[i];
    }

    return y;
}

/** @brief Cost Function for linear regression
 *  @param LinearRegression_t* model, linear regression struct (pointer)
 *  @param Matrix_t* X, feature matrix (pointer)
 *  @param Vector_t* y, label vector (pointer)
 *  @return double, cost (how bad are the predictions)
 */
double LinearRegressionCost(LinearRegression_t* model, Matrix_t* X, Vector_t* y){
    double score = 0;
	double error = 0;

	for(int i = 0; i < X->m; i++){
		error = LinearRegressionPredict(model, X->data[i]) - y->data[i];
		score += error * error;
	}

	return score / (2 * X->m);
}

/** @brief Calculate derivatives for gradient descent
 *  @param LinearRegression_t* model, linear regression struct (pointer)
 *  @param Matrix_t* X, feature matrix (pointer)
 *  @param Vector_t* y, label vector (pointer)
 *  @return LinearRegression_t*, new derivative calculations for each coef_
 */
LinearRegression_t* LinearRegressionCalcDerivatives(LinearRegression_t* model, Matrix_t* X, Vector_t* y){
	LinearRegression_t* calculation = LinearRegressionInit(model->learning_rate, model->number_of_features);
	
	for(int i = 0; i < X->m; i++){
		calculation->intercept_ += LinearRegressionPredict(model, X->data[i]) - y->data[i];
	}
	calculation->intercept_ = calculation->intercept_ / X->m;

	for(int j = 0; j < X->n; j++){
		for(int i = 0; i < X->m; i++){
			calculation->coef_[j] += (LinearRegressionPredict(model, X->data[i]) - y->data[i]) * X->data[i][j];
		}
		calculation->coef_[j] = calculation->coef_[j] / X->m;
	}
	
	return calculation;
}

/** @brief Gradient Descent for linear regression
 *  @param LinearRegression_t* model, linear regression struct (pointer)
 *  @param Matrix_t* X, feature matrix (pointer)
 *  @param Vector_t* y, label vector (pointer)
 *  @return float, lowest cost
 */
double LinearRegressionGradientDescent(LinearRegression_t* model, Matrix_t* X, Vector_t* y){
	double best = LinearRegressionCost(model, X, y) * 2;
    if(model->verbose == 1) printf(" First Best: %f\n", best);
	LinearRegression_t* calculation = LinearRegressionInit(model->learning_rate, model->number_of_features);

	while(LinearRegressionCost(model, X, y) < best){
		if(model->verbose == 1) printf("----------Best: %f\n", best);
		best = LinearRegressionCost(model, X, y);
		calculation = LinearRegressionCalcDerivatives(model, X, y);

		model->intercept_ = model->intercept_ - calculation->intercept_ * model->learning_rate;
		for(int i = 0; i < model->number_of_features; i++){
			model->coef_[i] = model->coef_[i] - calculation->coef_[i] * model->learning_rate;
		}
	}

	return best;
}
