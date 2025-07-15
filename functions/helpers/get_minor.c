#include <stdlib.h>

#include "../../s21_matrix.h"

int get_minor(matrix_t *A, int row, int col, matrix_t *minor) {
  int flag = OK;
  if (is_matrix_null(A) || minor == NULL || A->rows < 2 || A->columns < 2 ||
      row < 0 || row >= A->rows || col < 0 || col >= A->columns) {
    flag = INVALID_MATRIX;
  } else {
    int status = s21_create_matrix(A->rows - 1, A->columns - 1, minor);
    if (status != 0) {
      flag = status;
    } else {
      for (int i = 0, mi = 0; i < A->rows; i++) {
        if (i == row) continue;
        for (int j = 0, mj = 0; j < A->columns; j++) {
          if (j == col) continue;
          minor->matrix[mi][mj++] = A->matrix[i][j];
        }
        mi++;
      }
    }
  }
  return flag;
}