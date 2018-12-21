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
 *  @return linear_regression_t*, Pointer to initialized linear_regression_t
 */
linear_regression_t*
linear_regression_init (float learning_rate, int number_of_features)
{
  linear_regression_t *model = malloc(sizeof(*model));

  model->learning_rate = learning_rate;
  model->number_of_features = number_of_features;

  // Initialize model->intercept_ to be random value between 0 and 1
  model->intercept_ = cori_random();

  model->coef_ = malloc(sizeof(double) * number_of_features);
  for (int i = 0; i < number_of_features; i++)
    {
      // Initialize model->coef_[i] to be random value between 0 and 1
      model->coef_[i] = cori_random();
    }
  model->verbose = 0;

  // Initialize method functions
  model->fit = &linear_regression_gradient_descent;
  model->predict = &linear_regression_predict;
  model->cost = &linear_regression_cost;

  return model;
}

/** @brief Gives a prediction for specific data
 *  @param linear_regression_t *model, linear regression struct (pointer)
 *  @param double *x, data for prediction
 *  @return double, prediction
 */
double
linear_regression_predict (linear_regression_t *model, double *x)
{
  double y = model->intercept_;
  for (int i = 0; i < model->number_of_features; i++)
    {
      y += model->coef_[i] * x[i];
    }

  return y;
}

/** @brief Cost Function for linear regression
 *  @param linear_regression_t *model, linear regression struct (pointer)
 *  @param matrix_t *X, feature matrix (pointer)
 *  @param vector_t *y, label vector (pointer)
 *  @return double, cost (how bad are the predictions)
 */
double
linear_regression_cost (linear_regression_t *model, matrix_t *X, vector_t *y)
{
  double score = 0;
  double error = 0;

  for (int i = 0; i < X->m; i++)
    {
      error = linear_regression_predict(model, X->data[i]) - y->data[i];
      score += error * error;
    }

  return score / (2 * X->m);
}

/** @brief Calculate derivatives for gradient descent
 *  @param linear_regression_t *model, linear regression struct (pointer)
 *  @param matrix_t *X, feature matrix (pointer)
 *  @param vector_t *y, label vector (pointer)
 *  @return linear_regression_t*, new derivative calculations for each coef_
 */
linear_regression_t*
linear_regression_calc_derivatives (linear_regression_t *model,
                                    matrix_t *X, vector_t *y)
{
  // Initialize new linear_regression_t, used to store calculated parameters
  linear_regression_t *calculation =
    linear_regression_init(model->learning_rate, model->number_of_features);

  // Calc derivative for intercept
  for (int i = 0; i < X->m; i++)
    {
      calculation->intercept_ += linear_regression_predict(model, X->data[i]) -
                                   y->data[i];
    }
  calculation->intercept_ = calculation->intercept_ / X->m;

  // Calc derivatives for coefs
  for (int j = 0; j < X->n; j++)
    {
      for (int i = 0; i < X->m; i++)
        {
          calculation->coef_[j] +=
            (linear_regression_predict(model, X->data[i]) - y->data[i]) *
              X->data[i][j];
        }
      calculation->coef_[j] = calculation->coef_[j] / X->m;
    }

  return calculation;
}

/** @brief Gradient Descent for linear regression
 *  @param linear_regression_t *model, linear regression struct (pointer)
 *  @param matrix_t *X, feature matrix (pointer)
 *  @param vector_t *y, label vector (pointer)
 *  @return double, lowest cost
 */
double
linear_regression_gradient_descent (linear_regression_t *model,
                                    matrix_t *X, vector_t *y)
{
  long long int counter = 0;

  // Get the first (worst) cost of the model
  double first_best = linear_regression_cost(model, X, y) * 2;
  double best = first_best;

  if (model->verbose == 1) fprintf(stdout, "First Best: %f\n", first_best);

  // Initialize new linear_regression_t
  //  used to store new calculated derivatives
  linear_regression_t *calculation =
    linear_regression_init (model->learning_rate, model->number_of_features);

  // Iterate while cost is better than previous
  while (linear_regression_cost(model, X, y) < best)
    {
      ++counter;

      if (model->verbose == 1)
        {
          fputs("--------------------\n", stdout);
          fprintf(stdout, "%lldth iteration\n", counter);
          fprintf(stdout, "Cost: %f\n", best);
        }

      best = linear_regression_cost(model, X, y);

      // Get new derivatives
      calculation = linear_regression_calc_derivatives(model, X, y);

      // Apply new derivatives to our model
      model->intercept_ = model->intercept_ -
        calculation->intercept_ * model->learning_rate;
      for (int i = 0; i < model->number_of_features; i++)
        {
          model->coef_[i] = model->coef_[i] -
            calculation->coef_[i] * model->learning_rate;
        }
    }

  if (model->verbose == 1)
    {
      fputs("\n*******************************\n", stdout);
      fprintf(stdout, "* Iterations: %15lld *\n", counter);
      fprintf(stdout, "* First Cost: %15f *\n", first_best);
      fprintf(stdout, "* Best Cost: %16f *\n", best);
      fprintf(stdout, "*******************************\n");
    }

  return best;
}

