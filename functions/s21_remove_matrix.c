#include <stdlib.h>

#include "../s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  // Очистка памяти строк
  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i] != NULL) {
      free(A->matrix[i]);
    }
  }
  // Очистка памяти столбцов
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}