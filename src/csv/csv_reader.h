#ifndef _CSV_READER_H
#define _CSV_READER_H

/**
 * csv_reader.h
 *
 * Created: 12/12/2018
 * Author: Georgi Korchakov
 */

int in_arr(char str_arr[100][40], char *str);

int is_number(char *str);

int read_csv(char* file_name, matrix_t **X, vector_t **y);

#endif // ifndef _CSV_READER_H
