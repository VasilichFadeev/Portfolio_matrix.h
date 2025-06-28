#include <stdlib.h>

#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || A->matrix == NULL || A->rows <= 0 ||
      A->columns <= 0) {
    return INVALID_MATRIX;
  }
  if (result->matrix != NULL) {
    if (result->rows != A->columns || result->columns != A->rows) {
      return CALC_ERROR;
    }
  } else {
    int status = s21_create_matrix(A->columns, A->rows, result);
    if (status != OK) {
      return status;
    }
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return OK;
}