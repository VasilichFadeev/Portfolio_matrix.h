#include <math.h>
#include <stdlib.h>

#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (is_matrix_null(A) || result == NULL) {
    return INVALID_MATRIX;
  }
  if (A->rows != A->columns) {
    return 2;
  }
  double det = 0;
  if (s21_determinant(A, &det) || fabs(det) < 1e-7) {
    return CALC_ERROR;
  }
  matrix_t complements = {0};
  matrix_t transposed = {0};
  if (s21_calc_complements(A, &complements) ||
      s21_transpose(&complements, &transposed)) {
    s21_remove_matrix(&complements);
    return INVALID_MATRIX;
  }
  int status = s21_create_matrix(A->rows, A->columns, result);
  if (status == 0) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = transposed.matrix[i][j] / det;
      }
    }
  }
  s21_remove_matrix(&complements);
  s21_remove_matrix(&transposed);
  return status;
}