#include <stdlib.h>

#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;
  if (is_matrix_null(A) || is_matrix_null(B) || result == NULL) {
    flag = INVALID_MATRIX;
  }
  if (!sizes_bigger_than_zero(A) || !sizes_bigger_than_zero(B)) {
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