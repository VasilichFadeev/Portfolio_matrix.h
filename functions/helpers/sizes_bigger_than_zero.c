#include "../../s21_matrix.h"

int sizes_bigger_than_zero(matrix_t *a) {
  int flag;
  if (a->columns <= 0 || a->rows <= 0) {
    flag = 0;
  } else {
    flag = 1;
  }
  return flag;
}