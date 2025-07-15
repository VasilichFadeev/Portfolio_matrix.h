#include <math.h>
#include <stdlib.h>

#include "../s21_matrix.h"

#define SUCCESS 1
#define FAILURE 0
#define DIFF_SIZES 2
#define EPSILON 1e-7

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  if (is_matrix_null(A) || is_matrix_null(B)) {
    flag = FAILURE;
  } else if (!are_matrices_same_size(A, B)) {
    flag = DIFF_SIZES;
  } else {
    for (int i = 0; i < A->rows && flag == SUCCESS; i++) {
      for (int j = 0; j < A->columns && flag == SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON) {
          flag = FAILURE;
        }
      }
    }
  }
  return flag;
}