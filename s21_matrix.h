#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#define OK 0
#define INVALID_MATRIX 1
#define CALC_ERROR 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int get_minor(matrix_t *A, int row, int col, matrix_t *minor);
int is_matrix_null(matrix_t *a);
int is_matrix_square(matrix_t *a);
int are_matrices_same_size(matrix_t *a, matrix_t *b);
int sizes_bigger_than_zero(matrix_t *a);
#endif