#include "../../s21_matrix.h"

int are_matrices_same_size(matrix_t *a, matrix_t *b) {
  int flag;
  if ((a->columns == b->columns) && (a->rows == b->rows)) {
    flag = 1;
  } else {
    flag = 0;
  }
  return flag;
}