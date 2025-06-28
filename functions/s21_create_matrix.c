#include <stdlib.h>

#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = OK;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    flag = INVALID_MATRIX;
  } else {
    // Выделение памяти под массив указателей на строки
    result->matrix = (double **)malloc(rows * sizeof(double *));
    // Выделение памяти для каждой строки матрицы
    for (int i = 0; i < rows && !flag; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
    }
    if (!flag) {
      // Установка размеров матрицы в структуре
      result->rows = rows;
      result->columns = columns;
    }
  }
  return flag;
}