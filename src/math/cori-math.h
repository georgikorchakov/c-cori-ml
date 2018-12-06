#ifndef _CORI_MATH_H
#define _CORI_MATH_H

/**
 * cori-math.h
 *
 * Created: 5/12/2018
 * Author: Georgi Korchakov
 */
typedef struct Matrix_t Matrix_t;
typedef struct Vector_t Vector_t;

struct Matrix_t{
    /*---------- Data ----------*/
    int m;
	int n;
	double** data;

    /*---------- Pointers to method functions ----------*/
    void (*FillRandom)(Matrix_t* matrix, int lowest, int highest);
    void (*Print)(Matrix_t* matrix, int lines);
};

struct Vector_t{
    /*---------- Data ----------*/
    int length;
    double* data;

    /*---------- Pointers to method functions ----------*/
    void (*FillRandom)(Vector_t* vector, int lowest, int highest);
    void (*Print)(Vector_t* vector, int lines);
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

void VectorFillRandomUsingMatrix(Vector_t* vector, Matrix_t* matrix, int displacement);

void printLine(int n);

/** @brief Initialize Matrix
 *  @param int m, Number of Samples
 *  @param int n, Number of Features
 *  @return Matrix_t*, Pointer to initialized Matrix_t matrix (pointer)
 */
Matrix_t* MatrixInit(int m, int n);
void MatrixFillRandom(Matrix_t* matrix, int lower, int upper);
void MatrixPrint(Matrix_t* matrix, int lines);

/** @brief Initialize Vector
 *  @param int length, Length of vector
 *  @return Vector_t*, Pointer to initialized Vector_t vector (pointer)
 */
Vector_t* VectorInit(int length);
void VectorFillRandom(Vector_t* vector, int lower, int upper);
void VectorPrint(Vector_t* vector, int lines);

#endif // ifndef _CORI_MATH_H
