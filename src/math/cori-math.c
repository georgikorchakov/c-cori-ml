/**
 * cori-math.c
 *
 * Created: 5/12/2018
 * Author: Georgi Korchakov
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "cori-math.h"

/** @brief Sigmoid math function
 *  @param float x, Input number
 *  @return float, Number between 0 and 1
 */
double sigmoid(double x){
    return 1 / (1 + exp(-x));
}

/** @brief Random function
 *  @return double, Random number between 0 and 1
 */
double cori_random(){
    sranddev();
    return (double)rand()/RAND_MAX;
}

/** @brief Generates a random number in a given range
 *  @param int lower, lower boundary of range
 *  @param int upper, upper boundary of range
 *  @return double, Random number in the range [lower, upper]
 */
double cori_random_between(int lower, int upper){
    return lower + (upper - lower) * cori_random();
}

void VectorFillRandomUsingMatrix(Vector_t* vector, Matrix_t* matrix, int displacement){
    if(vector->length != matrix->m){
        printf("Number of samples and number of results do not match!\n");
        return;
    }

    if(matrix->n != 1){
        printf("There are more than 1 features!\n");
        return;
    }

    for(int i = 0; i < vector->length; i++){
        vector->data[i] = displacement * matrix->data[i][0] + cori_random();
    }
}

void printLine(int n){
	printf("+");
	for(int i = 0; i < n; i++){
		printf("----------+");
	}	
}

/** @brief Initialize Matrix
 *  @param int m, Number of Samples
 *  @param int n, Number of Features
 *  @return Matrix_t*, Pointer to initialized Matrix_t matrix (pointer)
 */
Matrix_t* MatrixInit(int m, int n){
    Matrix_t* matrix = malloc(sizeof(*matrix));

    matrix->data = malloc(m * sizeof(double*));
	for(int i = 0; i < m; i++){
		matrix->data[i] = malloc(n * sizeof(double));
	}
    
	matrix->m = m;
	matrix->n = n;
	
    for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			matrix->data[i][j] = 0;
		}
	}

    matrix->FillRandom = &MatrixFillRandom;
    matrix->Print = &MatrixPrint;

    return matrix;
}

void MatrixFillRandom(Matrix_t* matrix, int lower, int upper){
    for(int i = 0; i < matrix->m; i++){
		for(int j = 0; j < matrix->n; j++){
			matrix->data[i][j] = cori_random_between(lower, upper);
		}
	}
}

void MatrixPrint(Matrix_t* matrix, int lines){
    printLine(matrix->n);
    if(lines > matrix->m) lines = matrix->m;

    for(int i = 0; i < lines; i++){
		printf("\n");
		for(int j = 0; j < matrix->n; j++){
			printf("|%10f", matrix->data[i][j]);
		}
        printf("|\n");
		printLine(matrix->n);
	}
	printf("\n");
}

/** @brief Initialize Vector
 *  @param int length, Length of vector
 *  @return Vector_t*, Pointer to initialized Vector_t vector (pointer)
 */
Vector_t* VectorInit(int length){
    Vector_t* vector = malloc(sizeof(*vector));

	vector->data = malloc(length * sizeof(double));

	vector->length = length;
	
    for(int i = 0; i < length; i++){
		vector->data[i] = 0;
	}

    vector->FillRandom = &VectorFillRandom; 
    vector->Print = &VectorPrint;

    return vector;
}

void VectorFillRandom(Vector_t* vector, int lower, int upper){
    for(int i = 0; i < vector->length; i++){
		vector->data[i] = cori_random_between(lower, upper);
	}
}

void VectorPrint(Vector_t* vector, int lines){
    if(lines > vector->length) lines = vector->length;

    for(int i = 0; i < lines; i++){
        printLine(1);
		printf("\n");
		printf("|%10f|\n", vector->data[i]);
	}
	printLine(1);
	printf("\n");
}
