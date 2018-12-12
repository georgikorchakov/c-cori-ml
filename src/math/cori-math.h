#ifndef _CORI_MATH_H
#define _CORI_MATH_H

/**
 * cori-math.h
 *
 * Created: 5/12/2018
 * Author: Georgi Korchakov
 */
typedef struct matrix_t matrix_t;
typedef struct vector_t vector_t;

struct matrix_t{
    /*---------- Data ----------*/
    int m;
	int n;
	double** data;

    /*---------- Pointers to method functions ----------*/
    void (*FillRandom)(matrix_t* matrix, int lowest, int highest);
    void (*Print)(matrix_t* matrix, int lines);
};

struct vector_t{
    /*---------- Data ----------*/
    int length;
    double* data;

    /*---------- Pointers to method functions ----------*/
    void (*FillRandom)(vector_t* vector, int lowest, int highest);
    void (*Print)(vector_t* vector, int lines);
};

/** @brief Sigmoid math function
 *  @param float x, Input number
 *  @return float, Number between 0 and 1
 */
double sigmoid(double x);

/** @brief Random function
 *  @return double, Random number between 0 and 1
 */
double cori_random();

/** @brief Generates a random number in a given range
 *  @param int lower, lower boundary of range
 *  @param int upper, upper boundary of range
 *  @return double, Random number in the range [lower, upper]
 */
double cori_random_between(int lower, int upper);

void VectorFillRandomUsingMatrix(vector_t* vector, matrix_t* matrix, int displacement);

void printLine(int n);

/** @brief Initialize Matrix
 *  @param int m, Number of Samples
 *  @param int n, Number of Features
 *  @return matrix_t*, Pointer to initialized matrix_t matrix (pointer)
 */
matrix_t* MatrixInit(int m, int n);
void MatrixFillRandom(matrix_t* matrix, int lower, int upper);
void MatrixPrint(matrix_t* matrix, int lines);

/** @brief Initialize Vector
 *  @param int length, Length of vector
 *  @return vector_t*, Pointer to initialized vector_t vector (pointer)
 */
vector_t* VectorInit(int length);
void VectorFillRandom(vector_t* vector, int lower, int upper);
void VectorPrint(vector_t* vector, int lines);

#endif // ifndef _CORI_MATH_H
