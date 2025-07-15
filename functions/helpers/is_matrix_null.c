#include <stdlib.h>

#include "../../s21_matrix.h"

int is_matrix_null(matrix_t *a) {
  int flag;
  if (a == NULL || a->matrix == NULL) {
    flag = 1;
  } else {
    flag = 0;
  }
  return flag;
}