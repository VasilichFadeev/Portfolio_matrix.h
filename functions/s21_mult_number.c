#include <stdlib.h>

#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (A == NULL || result == NULL || A->matrix == NULL || A->rows <= 0 ||
      A->columns <= 0) {
    return INVALID_MATRIX;
  }
  if (result->matrix != NULL) {
    if (result->rows != A->rows || result->columns != A->columns) {
      return CALC_ERROR;
    }
  } else {
    int status = s21_create_matrix(A->rows, A->columns, result);
    if (status != OK) {
      return status;
    }
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return OK;
}