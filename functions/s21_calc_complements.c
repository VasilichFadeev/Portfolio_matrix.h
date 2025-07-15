#include <math.h>
#include <stdlib.h>

#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  // Проверка входных параметров
  if (is_matrix_null(A) || result == NULL) {
    return INVALID_MATRIX;
  }
  // Проверка что матрица квадратная
  if (!is_matrix_square(A)) {
    return CALC_ERROR;
  }
  // Проверка на специальные значения
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (isnan(A->matrix[i][j]) || isinf(A->matrix[i][j])) {
        return INVALID_MATRIX;
      }
    }
  }
  // Обработка матрицы 1x1
  if (A->rows == 1) {
    int status = s21_create_matrix(1, 1, result);
    if (status != 0) return status;
    result->matrix[0][0] = 1;
    return OK;
  }
  // Создание результирующей матрицы
  int status = s21_create_matrix(A->rows, A->columns, result);
  if (status != 0) {
    return status;
  }
  // Вычисление алгебраических дополнений
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor = {0};
      if (get_minor(A, i, j, &minor)) {
        s21_remove_matrix(result);
        return INVALID_MATRIX;
      }
      double det = 0;
      if (s21_determinant(&minor, &det)) {
        s21_remove_matrix(&minor);
        s21_remove_matrix(result);
        return INVALID_MATRIX;
      }
      result->matrix[i][j] = ((i + j) % 2 ? -1 : 1) * det;
      s21_remove_matrix(&minor);
    }
  }
  return OK;
}