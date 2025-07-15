#include <stdlib.h>

#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  // Проверка, что память на матрицы была выделена
  if (is_matrix_null(A) || result == NULL) {
    return INVALID_MATRIX;
  }
  // Проверка размеров
  if (!is_matrix_square(A)) {
    return CALC_ERROR;
  }
  *result = 0.0;
  // Обработка единичной матрицы
  if (A->rows == 1) {
    *result = A->matrix[0][0];
    return OK;
  }
  double det = 0.0;
  int sign = 1;
  // Расчёт определителя через нахождение миноров матрицы
  for (int j = 0; j < A->columns; j++) {
    matrix_t minor = {0};
    if (get_minor(A, 0, j, &minor)) {
      return INVALID_MATRIX;
    }
    double minor_det = 0.0;
    if (s21_determinant(&minor, &minor_det)) {
      s21_remove_matrix(&minor);
      return INVALID_MATRIX;
    }
    det += sign * A->matrix[0][j] * minor_det;
    sign *= -1;
    s21_remove_matrix(&minor);
  }
  *result = det;
  return OK;
}