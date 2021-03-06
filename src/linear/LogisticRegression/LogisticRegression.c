/**
 * LogisticRegression.h
 *
 * Created: 19/12/2018
 * Author: Georgi Korchakov
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../math/cori-math.h"
#include "LogisticRegression.h"

/** @brief Initialize logistic regression
 *  @param float learning_rate, learning rate for gradient descent
 *  @param int number_of_features, number of features in dataset
 *  @return logistic_regression_t*, Pointer to initialized logistic_regression_t
 */
logistic_regression_t*
logistic_regression_init (float learning_rate, int number_of_features)
{
  logistic_regression_t *model = malloc(sizeof(*model));

  model->learning_rate = learning_rate;
  model->number_of_features = number_of_features;

  // model->intercept = cori_random();
  model->intercept = 0;

  model->coef = malloc(sizeof(double) * number_of_features);
  for (int i = 0; i < number_of_features; i++)
    {
      // model->coef[i] = cori_random();
      model->coef[i] = 0;
    }

  model->verbose = 0;

  // Initialize method functions
  model->fit = &logistic_regression_gradient_descent;
  // Predict 0 or 1
  model->predict = &logistic_regression_predict_rounded;
  // Predict Probability
  model->predict_proba = &logistic_regression_predict;
  model->cost = &logistic_regression_cost;
  model->score = &logistic_regression_score;

  return model;
}

/** @brief Gives a prediction (probability) for specific data
 *  @param logistic_regression_t *model, logistic regression struct (pointer)
 *  @param double *x, data for prediction
 *  @return double, prediction (probability)
 */
double
logistic_regression_predict (logistic_regression_t *model, double *x)
{
  double y = model->intercept;
  for (int i = 0; i < model->number_of_features; i++)
    {
      y += model->coef[i] * x[i];
    }

  return logistic_regression_sigmoid(y);
}

/** @brief Gives a rounded prediction (0 or 1) for specific data
 *  @param logistic_regression_t *model, logistic regression struct (pointer)
 *  @param double *x, data for prediction
 *  @return double, rounded prediction (0 or 1)
 */
double
logistic_regression_predict_rounded (logistic_regression_t *model, double *x)
{
  double y = logistic_regression_predict (model, x);
  if (y < 0.5)
    {
      return 0;
    }
  else
    {
      return 1;
    }
}

/** @brief Cost Function for logistic regression
 *  @param logistic_regression_t *model, logistic regression struct (pointer)
 *  @param matrix_t *X, feature matrix (pointer)
 *  @param vector_t *y, label vector (pointer)
 *  @return double, cost (how bad are the predictions)
 */
double
logistic_regression_cost (logistic_regression_t *model,
                          matrix_t *X, vector_t *y)
{
  double score = 0;
  for (int i = 0; i < X->m; i++)
    {
      if (y->data[i] == 0)
        {
          score += -log(1 - logistic_regression_predict(model, X->data[i]));
        } 
      else
        {
          score += -log(logistic_regression_predict(model, X->data[i]));
        }
    }

  return score / X->m;
}

/** @brief Calculate derivatives for gradient descent
 *  @param logistic_regression_t *model, logistic regression struct (pointer)
 *  @param matrix_t *X, feature matrix (pointer)
 *  @param vector_t *y, label vector (pointer)
 *  @return logistic_regression_t*, new derivative calculations for each coef
 */
logistic_regression_t*
logistic_regression_calc_derivatives (logistic_regression_t *model,
                                      matrix_t *X, vector_t *y)
{
  // Initialize new logistic_regression_t, used to store calculated parameters
  logistic_regression_t *calculation =
    logistic_regression_init(model->learning_rate, model->number_of_features);

  // Calc derivative for intercept
  for (int i = 0; i < X->m; i++)
    {
      calculation->intercept +=
        logistic_regression_predict(model, X->data[i]) - y->data[i];
    }
  calculation->intercept = calculation->intercept / X->m;

  // Calc derivatives for coefs
  for (int j = 0; j < X->n; j++)
    {
      for (int i = 0; i < X->m; i++)
        {
          calculation->coef[j] +=
            (logistic_regression_predict(model, X->data[i]) - y->data[i]) *
            X->data[i][j];
        }
      calculation->coef[j] = calculation->coef[j] / X->m;
    }

  return calculation;
}

/** @brief Gradient Descent for logistic regression
 *  @param logistic_regression_t *model, logistic regression struct (pointer)
 *  @param matrix_t *X, feature matrix (pointer)
 *  @param vector_t *y, label vector (pointer)
 *  @return double, lowest cost
 */
double
logistic_regression_gradient_descent (logistic_regression_t *model,
                                      matrix_t *X, vector_t *y)
{
  long long int counter = 0;

  // Get the first (worst) cost of the model
  double first_best = logistic_regression_cost(model, X, y);
  double best = first_best * 2;

  if (model->verbose == 1) fprintf(stdout, "First Best: %f\n", first_best);

  // Initialize new logistic_regression_t
  //  used to store new calculated derivatives
  logistic_regression_t *calculation =
    logistic_regression_init(model->learning_rate, model->number_of_features);

  while (logistic_regression_cost(model, X, y) < best)
    {
      ++counter;

      if (model->verbose == 1)
        {
          fputs("--------------------\n", stdout);
          fprintf(stdout, "%lldth iteration\n", counter);
          if (counter == 1)
            {
              fprintf(stdout, "Cost: %f\n", first_best);
            }
          else
            {
              fprintf(stdout, "Cost: %f\n", best);
            }
        }

      best = logistic_regression_cost(model, X, y);

      // Get new derivatives
      calculation = logistic_regression_calc_derivatives(model, X, y);

      // Apply new derivatives to our model
      model->intercept = model->intercept -
        calculation->intercept * model->learning_rate;
      for (int i = 0; i < model->number_of_features; i++)
        {
          model->coef[i] = model->coef[i] -
            calculation->coef[i] * model->learning_rate;
        }

      //TODO Make it a better way
      if (best < 0.001)
        {
          break;
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

double
logistic_regression_score (logistic_regression_t *model,
                           matrix_t *X, vector_t *y)
{
  double score = 0;
  for (int i = 0; i < y->length; i++)
    {
      if (logistic_regression_predict_rounded(model, X->data[i]) == y->data[i])
        ++score;
    }

  return score / y->length;
}

/** @brief Sigmoid math function
 *  @param double x, Input number
 *  @return double, Number between 0 and 1
 */
double
logistic_regression_sigmoid (double x)
{
  return 1 / (1 + exp(-x));
}
