#include <stdlib.h>

#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;
  if (A == NULL || A->matrix == NULL || B == NULL || B->matrix == NULL ||
      result == NULL) {
    flag = INVALID_MATRIX;
  }
  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    flag = INVALID_MATRIX;
  }
  if (A->columns != B->rows) {
    flag = CALC_ERROR;
  }
  int status = s21_create_matrix(A->rows, B->columns, result);
  if (status != 0) {
    flag = status;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return flag;
}