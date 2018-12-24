#ifndef _CSV_READER_H
#define _CSV_READER_H

/**
 * csv_reader.h
 *
 * Created: 12/12/2018
 * Author: Georgi Korchakov
 */

typedef struct
{
  int m;
  int n;
} dimentions_t;

/** @brief Gets dimentions of given csv file
 *  @param char *filename, Name of csv file
 *  @return dimentions_t, struct with m (cols) and n (rows) of given csv file
 */
dimentions_t
get_csv_dimentions (char *filename);

/** @brief Gets only the features of given csv file
 *  @param char *filename, Name of csv file
 *  @param int label_position, position of your column containing labels
 *  @param dimentions_t dim, dimentions of that csv file
 *  @return matrix_t*, matrix pointer with all features, without labels
 */
matrix_t*
get_csv_features (char *filename, int label_position, dimentions_t dim);

/** @brief Gets only the laels of given csv file
 *  @param char *filename, Name of csv file
 *  @param int label_position, position of your column containing labels
 *  @param dimentions_t dim, dimentions of that csv file
 *  @return vector_t*, vector pointer with all labels, without features
 */
vector_t*
get_csv_labels (char *filename, int label_position, dimentions_t dim);

/** @brief Search in array whit strings for given string
 *  @param str_arr[100][40], array whit strings
 *  @param char *str, string to search for
 *  @return int, position of given string or -1 if there is no string like this
 */
int
in_arr(char str_arr[100][40], char *str);

/** @brief Checks whether a string is a number
 *  @param char *str, string for checking
 *  @return int, 0 - not a numberm 1 - number
 */
int
is_number(char *str);

#endif // ifndef _CSV_READER_H
