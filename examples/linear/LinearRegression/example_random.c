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
    Matrix_t* X = MatrixInit(100, 1);
    X->FillRandom(X, 0, 10);
    X->Print(X, 4);

    Vector_t* y = VectorInit(100);
    VectorFillRandomUsingMatrix(y, X, 3); //TODO Make it usefull
    y->Print(y, 4);
    
    // Model
    LinearRegression_t* model = LinearRegressionInit(0.001, 1);
    //model->verbose = 1;

    printf("Score from fitting function = %f\n", model->Fit(model, X, y));
    printf("prediction on first line = %f\n", model->Predict(model, X->data[0]));
    printf("Cost = %f\n", model->Cost(model, X, y));

    return 0;
}
