#include <stdlib.h>

#include "../s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (A == NULL) return;
  if (A->matrix != NULL) {
    // Освобождаем каждую строку
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
      }
    }
    // Освобождаем массив указателей
    free(A->matrix);
    A->matrix = NULL;
  }
  // Обнуляем размеры
  A->rows = 0;
  A->columns = 0;
}