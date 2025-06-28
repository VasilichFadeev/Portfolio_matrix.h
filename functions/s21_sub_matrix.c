#include <stdlib.h>

#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // Проверка, что память выделенa и размер матрицы не менее 1
  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL || A->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
      B->columns <= 0) {
    return INVALID_MATRIX;
  }
  // Проверка размерностей входных матриц
  if (A->rows != B->rows || A->columns != B->columns) {
    return CALC_ERROR;
  }
  // Проверка матрицы результата (если уже выделена)
  if (result->matrix != NULL) {
    if (result->rows != A->rows || result->columns != A->columns) {
      return CALC_ERROR;  // Размеры не совпадают
    }
  } else {
    // Если матрица результата не выделена, создаём новую
    int status = s21_create_matrix(A->rows, A->columns, result);
    if (status != OK) {
      return status;
    }
  }
  // Вычитание
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return OK;
}