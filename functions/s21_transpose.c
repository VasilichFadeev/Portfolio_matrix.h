#include <stdlib.h>

#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  // Проверка на NULL указатели и корректность матрицы
  if (is_matrix_null(A) || result == NULL || A->rows <= 0 || A->columns <= 0) {
    return INVALID_MATRIX;
  }
  // Проверка, если матрица результата уже создана
  if (result->matrix != NULL) {
    // Проверяем соответствие размеров
    if (!are_matrices_same_size(A, result)) {
      return CALC_ERROR;
    }
  } else {
    // Создаём новую матрицу, если она не была создана
    int status = s21_create_matrix(A->columns, A->rows, result);
    if (status != OK) return status;
  }
  // Транспонирование
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return OK;
}