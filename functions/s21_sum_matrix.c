#include <stdlib.h>

#include "../s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // Проверка на NULL указатели и корректность матриц
  if (is_matrix_null(A) || is_matrix_null(B) || result == NULL ||
      A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    return INVALID_MATRIX;
  }
  // Проверка совпадения размеров
  if (!are_matrices_same_size(A, B)) {
    return CALC_ERROR;
  }
  // Создание матрицы с результатом
  int status = OK;
  if (result->matrix == NULL) {
    status = s21_create_matrix(A->rows, A->columns, result);
  } else if (!are_matrices_same_size(A, result)) {
    return CALC_ERROR;
  }
  if (status == OK) {
    // Выполняем сложение
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return status;
}