#include "../../s21_matrix.h"

int is_matrix_square(matrix_t *a) {
  int flag;
  if (a->columns == a->rows) {
    flag = 1;
  } else {
    flag = 0;
  }
  return flag;
}