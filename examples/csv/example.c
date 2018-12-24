#include <stdio.h>
#include "../../src/math/cori-math.h"
#include "../../src/csv/csv_reader.h"

int main(){
  dimentions_t dim;
  dim = get_csv_dimentions("iris.data");
  matrix_t *X = get_csv_features("iris.data", 4, dim);
  vector_t *y = get_csv_labels("iris.data", 4, dim);

  X->print(X, X->m);
  y->print(y, y->length);

  printf("m = %d, n = %d\n", dim.m, dim.n);

  return 0;
}
