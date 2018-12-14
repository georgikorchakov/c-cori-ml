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
    // {{1,2,3}, {2,1,1}, {4,5,6}, {5,6,3}};
    matrix_t* X = matrix_init(4, 3);
    X->data[0][0] = 1;
    X->data[0][1] = 2;
    X->data[0][2] = 3;

    X->data[1][0] = 2;
    X->data[1][1] = 1;
    X->data[1][2] = 1;

    X->data[2][0] = 4;
    X->data[2][1] = 5;
    X->data[2][2] = 6;

    X->data[3][0] = 5;
    X->data[3][1] = 6;
    X->data[3][2] = 3;

    X->print(X, 4);

    vector_t* y = vector_init(4);
    y->data[0] = 1;
    y->data[1] = 2;
    y->data[2] = 4;
    y->data[3] = 5;
    
    y->print(y, 4);

    // Model
    linear_regression_t* model = linear_regression_init(0.001, 3);
    //model->verbose = 1;

    double x[3] = {3, 4, 5};

    printf("Prediction: %f\n", model->predict(model, x));
	printf("Cost: %f\n", model->cost(model, X, y));
	printf("Best: %f\n", model->fit(model, X, y));
	printf("Prediction: %f\n", model->predict(model, x));

    return 0;
}
