#include <stdlib.h>

#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  // Проверка на NULL указатели и корректность матрицы
  if (is_matrix_null(A) || result == NULL || !sizes_bigger_than_zero(A)) {
    return INVALID_MATRIX;
  }
  // Создание матрицы с результатом
  int status = OK;
  if (result->matrix == NULL) {
    status = s21_create_matrix(A->rows, A->columns, result);
  } else if (!are_matrices_same_size(A, result)) {
    return CALC_ERROR;
  }
  if (status == OK) {
    // Выполняем умножение на число
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return status;
}