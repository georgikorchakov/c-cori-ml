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
    Matrix_t* X = MatrixInit(4, 3);
    X->data[0][0] = 1;
    X->data[0][1] = 2;
    X->data[0][2] = 3;

    X->data[1][0] = 2;
    X->data[1][1] = 1;
    X->data[1][2] = 1;

    X->data[2][0] = 4;
    X->data[2][1] = 5;
    X->data[3][2] = 6;

    X->data[3][0] = 5;
    X->data[3][1] = 6;
    X->data[3][2] = 3;

    //X->Print(X, 4);

    Vector_t* y = VectorInit(4);
    y->data[0] = 1;
    y->data[1] = 2;
    y->data[2] = 4;
    y->data[3] = 5;
    
    //y->Print(y, 4);

    // Model
    LinearRegression_t* model = LinearRegressionInit(0.001, 3);
    //model->verbose = 1;

    double x[3] = {3, 4, 5};

    printf("Prediction: %f\n", model->Predict(model, x));
	printf("Cost: %f\n", model->Cost(model, X, y));
	printf("Best: %f\n", model->Fit(model, X, y));
	printf("Prediction: %f\n", model->Predict(model, x));

    return 0;
}
