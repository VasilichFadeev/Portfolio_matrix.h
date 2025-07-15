#include <check.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

#include "s21_matrix.h"

// Тест создания матрицы
START_TEST(test_create_matrix_ok) {
  matrix_t mat = {0};
  // Создание матрицы размером 3 на 4
  int res = s21_create_matrix(3, 4, &mat);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(mat.rows, 3);
  ck_assert_int_eq(mat.columns, 4);
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_matrix_null) {
  matrix_t mat = {0};
  ck_assert_int_eq(s21_create_matrix(-1, 2, &mat), 1);
  ck_assert_int_eq(s21_create_matrix(2, -1, &mat), 1);
  ck_assert_int_eq(s21_create_matrix(0, 2, &mat), 1);
  s21_remove_matrix(&mat);
}
END_TEST

// Тест на количество строк = 0
START_TEST(test_create_matrix_rows_0) {
  matrix_t a = {0};
  int res = s21_create_matrix(0, 1, &a);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&a);
}
END_TEST

// Тест на количество столбцов = 0
START_TEST(test_create_matrix_cols_0) {
  matrix_t a = {0};
  int res = s21_create_matrix(5, 0, &a);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&a);
}
END_TEST

// Тест на минусовые размеры
START_TEST(test_create_matrix_size_minus) {
  matrix_t mat = {0};
  ck_assert_int_eq(s21_create_matrix(-1, 5, &mat), 1);
  s21_remove_matrix(&mat);
}
END_TEST

// Тест на нулевой указатель
START_TEST(test_create_matrix_null_pointer) {
  ck_assert_int_eq(s21_create_matrix(2, 2, NULL), 1);
}
END_TEST

// Тест для сравнения матриц (матрицы одинаковые)
START_TEST(test_eq_matrix_ok) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(3, 3, &a);
  s21_create_matrix(3, 3, &b);
  // Сравниваем матрицы
  //   1 2 3   1 2 3
  //   4 5 6 и 4 5 6
  //   7 8 9   7 8 9

  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 4;
  a.matrix[1][1] = 5;
  a.matrix[1][2] = 6;
  a.matrix[2][0] = 7;
  a.matrix[2][1] = 8;
  a.matrix[2][2] = 9;

  b.matrix[0][0] = 1;
  b.matrix[0][1] = 2;
  b.matrix[0][2] = 3;
  b.matrix[1][0] = 4;
  b.matrix[1][1] = 5;
  b.matrix[1][2] = 6;
  b.matrix[2][0] = 7;
  b.matrix[2][1] = 8;
  b.matrix[2][2] = 9;

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

// Тест для сравнения матриц (матрицы разные)
START_TEST(test_eq_matrix_fail_values) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  // Сравниваем матрицы
  //     1 2 и 1 2
  //     4 5   3 4

  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[1][0] = 4;
  a.matrix[1][1] = 5;

  b.matrix[0][0] = 1;
  b.matrix[0][1] = 2;
  b.matrix[1][0] = 3;
  b.matrix[1][1] = 4;

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

// Тест сравнения десятичных дробей (меньше требуемой точности)
START_TEST(test_eq_matrix_fraction_lower) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  // Сравниваем матрицы
  // 0.1 0.2 и 0.1 0.2
  // 0.3 0.4   0.3 0.4

  a.matrix[0][0] = 0.1;
  a.matrix[0][1] = 0.2;
  a.matrix[1][0] = 0.3;
  a.matrix[1][1] = 0.4;

  b.matrix[0][0] = 0.1;
  b.matrix[0][1] = 0.2;
  b.matrix[1][0] = 0.3;
  b.matrix[1][1] = 0.4;

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

// Тест сравнения десятичных дробей (больше требуемой точности) с положительным
// результатом
START_TEST(test_eq_matrix_fraction_higher_ok) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  // Сравниваем матрицы
  // 0.13523734 0.2 и 0.13523725 0.2
  // 0.3        0.4   0.3        0.4

  a.matrix[0][0] = 0.13523734;
  a.matrix[0][1] = 0.2;
  a.matrix[1][0] = 0.3;
  a.matrix[1][1] = 0.4;

  b.matrix[0][0] = 0.13523725;
  b.matrix[0][1] = 0.2;
  b.matrix[1][0] = 0.3;
  b.matrix[1][1] = 0.4;

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

// Тест сравнения десятичных дробей (больше требуемой точности) с плохим
// результатом
START_TEST(test_eq_matrix_fraction_higher_fail) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  // Сравниваем матрицы
  // 0.13523834 0.2 и 0.13523725 0.2
  // 0.3        0.4   0.3        0.4

  a.matrix[0][0] = 0.13523834;
  a.matrix[0][1] = 0.2;
  a.matrix[1][0] = 0.3;
  a.matrix[1][1] = 0.4;

  b.matrix[0][0] = 0.13523725;
  b.matrix[0][1] = 0.2;
  b.matrix[1][0] = 0.3;
  b.matrix[1][1] = 0.4;

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

// Тест для сравнения матриц (матрицы разных размеров)
START_TEST(test_eq_matrix_diff_sizes) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(3, 3, &b);
  // Сравниваем матрицы
  //    1 2 и 1 2 3
  //    4 5   4 5 6
  //          7 8 9

  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[1][0] = 4;
  a.matrix[1][1] = 5;

  b.matrix[0][0] = 1;
  b.matrix[0][1] = 2;
  b.matrix[0][2] = 3;
  b.matrix[1][0] = 4;
  b.matrix[1][1] = 5;
  b.matrix[1][2] = 6;
  b.matrix[2][0] = 7;
  b.matrix[2][1] = 8;
  b.matrix[2][2] = 9;

  ck_assert_int_eq(s21_eq_matrix(&a, &b), 2);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test_eq_matrix_matrices_null) {
  matrix_t a = {0}, b = {0};
  a.matrix = NULL;
  b.matrix = NULL;

  int status = s21_eq_matrix(&a, &b);
  ck_assert_int_eq(status, 0);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

// Тест сравнения сложения матриц со сравнением с ожидаемым результатом
START_TEST(test_sum_matrix_ok) {
  matrix_t a = {0}, b = {0}, result = {0}, expected = {0};

  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);

  a.matrix[0][0] = 30;
  a.matrix[0][1] = 31;
  a.matrix[1][0] = 32;
  a.matrix[1][1] = 33;

  b.matrix[0][0] = 29;
  b.matrix[0][1] = 27;
  b.matrix[1][0] = 25;
  b.matrix[1][1] = 23;

  expected.matrix[0][0] = 59;
  expected.matrix[0][1] = 58;
  expected.matrix[1][0] = 57;
  expected.matrix[1][1] = 56;

  int sum_status = s21_sum_matrix(&a, &b, &result);

  ck_assert_int_eq(sum_status, 0);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected.matrix[i][j]);
    }
  }

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест NULL матриц в функции s21_sum_matrix
START_TEST(test_sum_number_null_pointers) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  int status = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест разных матриц в s21_sum_matrix
START_TEST(test_sum_different_sizes) {
  matrix_t a = {0}, b = {0}, result = {0};

  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 3, &b);

  a.matrix[0][0] = 30;
  a.matrix[0][1] = 31;
  a.matrix[1][0] = 32;
  a.matrix[1][1] = 33;

  b.matrix[0][0] = 29;
  b.matrix[0][1] = 27;
  b.matrix[0][2] = 26;
  b.matrix[1][0] = 25;
  b.matrix[1][1] = 23;
  b.matrix[1][2] = 22;

  int status = s21_sum_matrix(&a, &b, &result);
  ck_assert_int_eq(status, 2);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

// Тест на разные размеры вводных данных и матрицы на выходе
START_TEST(test_sum_different_input_and_result_sizes) {
  matrix_t a = {0}, b = {0}, result = {0};

  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(3, 3, &result);

  a.matrix[0][0] = 1;
  a.matrix[0][1] = 0;
  a.matrix[1][0] = 1;
  a.matrix[1][1] = 0;

  b.matrix[0][0] = 0;
  b.matrix[0][1] = 1;
  b.matrix[1][0] = 0;
  b.matrix[1][1] = 1;

  int status = s21_sum_matrix(&a, &b, &result);
  ck_assert_int_eq(status, 2);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_result_not_initialized) {
  matrix_t a = {0}, b = {0}, result = {0};

  s21_create_matrix(5, 5, &a);
  s21_create_matrix(5, 5, &b);

  a.matrix[0][0] = 432;
  a.matrix[0][1] = 78;
  a.matrix[0][2] = 89;
  a.matrix[0][3] = 112;
  a.matrix[0][4] = 12;
  a.matrix[1][0] = 99;
  a.matrix[1][1] = 1248;
  a.matrix[1][2] = 32;
  a.matrix[1][3] = 565;
  a.matrix[1][4] = 3232;
  a.matrix[2][0] = 329;
  a.matrix[2][1] = 32123;
  a.matrix[2][2] = 88;
  a.matrix[2][3] = 342;
  a.matrix[2][4] = 67;
  a.matrix[3][0] = 890;
  a.matrix[3][1] = 84;
  a.matrix[3][2] = 323;
  a.matrix[3][3] = 989;
  a.matrix[3][4] = 567;
  a.matrix[4][0] = 321;
  a.matrix[4][1] = 25;
  a.matrix[4][2] = 44;
  a.matrix[4][3] = 43;
  a.matrix[4][4] = 889;

  b.matrix[0][0] = 32;
  b.matrix[0][1] = 566;
  b.matrix[0][2] = 55;
  b.matrix[0][3] = 32;
  b.matrix[0][4] = 989;
  b.matrix[1][0] = 151;
  b.matrix[1][1] = 656;
  b.matrix[1][2] = 56;
  b.matrix[1][3] = 692;
  b.matrix[1][4] = 987;
  b.matrix[2][0] = 121;
  b.matrix[2][1] = 848;
  b.matrix[2][2] = 484;
  b.matrix[2][3] = 3694;
  b.matrix[2][4] = 48;
  b.matrix[3][0] = 59;
  b.matrix[3][1] = 559;
  b.matrix[3][2] = 95;
  b.matrix[3][3] = 1010;
  b.matrix[3][4] = 95;
  b.matrix[4][0] = 85;
  b.matrix[4][1] = 111;
  b.matrix[4][2] = 48;
  b.matrix[4][3] = 1;
  b.matrix[4][4] = 84;

  result.matrix = NULL;

  int status = s21_sum_matrix(&a, &b, &result);
  ck_assert_int_eq(status, 0);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

// Тест сравнения вычитания матриц со сравнением с ожидаемым результатом
START_TEST(test_sub_matrix_ok) {
  matrix_t a = {0}, b = {0}, result = {0}, expected = {0};

  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);

  a.matrix[0][0] = 30;
  a.matrix[0][1] = 31;
  a.matrix[1][0] = 32;
  a.matrix[1][1] = 33;

  b.matrix[0][0] = 29;
  b.matrix[0][1] = 27;
  b.matrix[1][0] = 25;
  b.matrix[1][1] = 23;

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 4;
  expected.matrix[1][0] = 7;
  expected.matrix[1][1] = 10;

  int sum_status = s21_sub_matrix(&a, &b, &result);

  ck_assert_int_eq(sum_status, 0);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected.matrix[i][j]);
    }
  }

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест NULL матриц в функции s21_sub_matrix
START_TEST(test_sub_number_null_pointers) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест разных матриц в s21_sub_matrix
START_TEST(test_sub_different_sizes) {
  matrix_t a = {0}, b = {0}, result = {0};

  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 3, &b);

  a.matrix[0][0] = 30;
  a.matrix[0][1] = 31;
  a.matrix[1][0] = 32;
  a.matrix[1][1] = 33;

  b.matrix[0][0] = 29;
  b.matrix[0][1] = 27;
  b.matrix[0][2] = 26;
  b.matrix[1][0] = 25;
  b.matrix[1][1] = 23;
  b.matrix[1][2] = 22;

  int status = s21_sub_matrix(&a, &b, &result);
  ck_assert_int_eq(status, 2);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

// Тест на разные размеры вводных данных и матрицы на выходе
START_TEST(test_sub_different_input_and_result_sizes) {
  matrix_t a = {0}, b = {0}, result = {0};

  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(3, 3, &result);

  a.matrix[0][0] = 1;
  a.matrix[0][1] = 0;
  a.matrix[1][0] = 1;
  a.matrix[1][1] = 0;

  b.matrix[0][0] = 0;
  b.matrix[0][1] = 1;
  b.matrix[1][0] = 0;
  b.matrix[1][1] = 1;

  int status = s21_sub_matrix(&a, &b, &result);
  ck_assert_int_eq(status, 2);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_result_not_initialized) {
  matrix_t a = {0}, b = {0}, result = {0};

  s21_create_matrix(5, 5, &a);
  s21_create_matrix(5, 5, &b);

  a.matrix[0][0] = 432;
  a.matrix[0][1] = 78;
  a.matrix[0][2] = 89;
  a.matrix[0][3] = 112;
  a.matrix[0][4] = 12;
  a.matrix[1][0] = 99;
  a.matrix[1][1] = 1248;
  a.matrix[1][2] = 32;
  a.matrix[1][3] = 565;
  a.matrix[1][4] = 3232;
  a.matrix[2][0] = 329;
  a.matrix[2][1] = 32123;
  a.matrix[2][2] = 88;
  a.matrix[2][3] = 342;
  a.matrix[2][4] = 67;
  a.matrix[3][0] = 890;
  a.matrix[3][1] = 84;
  a.matrix[3][2] = 323;
  a.matrix[3][3] = 989;
  a.matrix[3][4] = 567;
  a.matrix[4][0] = 321;
  a.matrix[4][1] = 25;
  a.matrix[4][2] = 44;
  a.matrix[4][3] = 43;
  a.matrix[4][4] = 889;

  b.matrix[0][0] = 32;
  b.matrix[0][1] = 566;
  b.matrix[0][2] = 55;
  b.matrix[0][3] = 32;
  b.matrix[0][4] = 989;
  b.matrix[1][0] = 151;
  b.matrix[1][1] = 656;
  b.matrix[1][2] = 56;
  b.matrix[1][3] = 692;
  b.matrix[1][4] = 987;
  b.matrix[2][0] = 121;
  b.matrix[2][1] = 848;
  b.matrix[2][2] = 484;
  b.matrix[2][3] = 3694;
  b.matrix[2][4] = 48;
  b.matrix[3][0] = 59;
  b.matrix[3][1] = 559;
  b.matrix[3][2] = 95;
  b.matrix[3][3] = 1010;
  b.matrix[3][4] = 95;
  b.matrix[4][0] = 85;
  b.matrix[4][1] = 111;
  b.matrix[4][2] = 48;
  b.matrix[4][3] = 1;
  b.matrix[4][4] = 84;

  result.matrix = NULL;

  int status = s21_sub_matrix(&a, &b, &result);
  ck_assert_int_eq(status, 0);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

// Успешный тест умножения матрицы на число
START_TEST(test_mult_number_ok) {
  matrix_t a = {0}, result = {0}, expected = {0};
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);

  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[1][0] = 3;
  a.matrix[1][1] = 4;

  double number = 2.0;

  expected.matrix[0][0] = 2;
  expected.matrix[0][1] = 4;
  expected.matrix[1][0] = 6;
  expected.matrix[1][1] = 8;

  s21_mult_number(&a, number, &result);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected.matrix[i][j]);
    }
  }

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Неуспешный тест умножения матрицы на число (разные размеры)
START_TEST(test_mult_number_wrong_sizes) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &result);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  double number = 2.0;

  int status = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(status, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест с неуспешным созданием матрицы
START_TEST(test_mult_number_create_fail) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);

  A.rows = -1;
  A.columns = -1;

  double number = 2.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, 1);

  A.rows = 2;
  A.columns = 2;
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест NULL матриц в функции s21_mult_number
START_TEST(test_mult_number_null_pointers) {
  matrix_t A = {0};
  matrix_t result = {0};
  double number = 2.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_result_not_initialized) {
  matrix_t a = {0}, result = {0};
  double number = 1.87;
  s21_create_matrix(5, 1, &a);

  a.matrix[0][0] = 1;
  a.matrix[1][0] = 2;
  a.matrix[2][0] = 3;
  a.matrix[3][0] = 4;
  a.matrix[4][0] = 5;

  result.matrix = NULL;

  int status = s21_mult_number(&a, number, &result);
  ck_assert_int_eq(status, 0);

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

// Успешный тест умножения матриц
START_TEST(test_mult_matrix_ok) {
  matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = -3;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 5;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = -2;

  B.matrix[0][0] = -7;
  B.matrix[0][1] = 5;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = -1;
  B.matrix[2][0] = 4;
  B.matrix[2][1] = 3;

  expected.matrix[0][0] = -16;
  expected.matrix[0][1] = 16;
  expected.matrix[1][0] = -35;
  expected.matrix[1][1] = 15;

  s21_mult_matrix(&A, &B, &result);
  int status = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(status, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест s21_mul_matrix с NULL матрицами
START_TEST(test_mult_matrix_null_pointers) {
  matrix_t A = {0}, B = {0}, result = {0};
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест перемножения матриц, не выполняющих условие, что количество строк первой
// матрицы равно количеству столбцов второй матрицы
START_TEST(test_mult_matrix_wrong_sizes) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(3, 1, &B);
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Успешный тест транспонирования матрицы
START_TEST(test_transpose_ok) {
  matrix_t A = {0}, result = {0}, expected = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 4;
  expected.matrix[0][2] = 7;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 5;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = 3;
  expected.matrix[2][1] = 6;
  expected.matrix[2][2] = 9;

  s21_transpose(&A, &result);
  int status = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(status, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест транспонирования матрицы с NULL матрицей
START_TEST(test_transpose_null_pointers) {
  matrix_t A = {0}, result = {0};
  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест транспонирования матрицы с несовпадающим по размеру результатом
START_TEST(test_transpose_different_sizes) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(1, 1, &result);

  A.matrix[0][0] = 34;
  A.matrix[0][1] = 98;
  A.matrix[1][0] = 32;
  A.matrix[1][1] = 56;

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_create_matrix_fail) {
  matrix_t A = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int status = s21_transpose(&A, &result);

  ck_assert_int_eq(status, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест для корректного вычисления матрицы алгебраических дополнений
START_TEST(test_calc_complements_ok) {
  matrix_t A = {0}, result = {0}, expected = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  // Матрица A:
  // 1  2  3
  // 0  4  2
  // 5  2  1
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  // Ожидаемая матрица алгебраических дополнений:
  //  0  10 -20
  //  4 -14  8
  // -8  -2  4
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, 0);

  // Сравниваем результат с ожидаемым
  int eq_status = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq_status, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест для неквадратной матрицы
START_TEST(test_calc_complements_not_square) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 3, &A);

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест для матрицы 1x1
START_TEST(test_calc_complements_1x1) {
  matrix_t A = {0}, result = {0}, expected = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &expected);

  A.matrix[0][0] = 5;
  expected.matrix[0][0] =
      1;  // Алгебраическое дополнение для 1x1 матрицы равно 1

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, 0);

  int eq_status = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq_status, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест с NULL указателями
START_TEST(test_calc_complements_null_pointers) {
  matrix_t A = {0};
  int status = s21_calc_complements(NULL, NULL);
  ck_assert_int_eq(status, 1);

  status = s21_calc_complements(&A, NULL);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
}
END_TEST

// Тест для матрицы 2x2
START_TEST(test_calc_complements_2x2) {
  matrix_t A = {0}, result = {0}, expected = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  // Матрица A:
  // 1  3
  // 2  4
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 3;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;

  // Ожидаемая матрица алгебраических дополнений:
  //  4 -2
  // -3  1
  expected.matrix[0][0] = 4;
  expected.matrix[0][1] = -2;
  expected.matrix[1][0] = -3;
  expected.matrix[1][1] = 1;

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, 0);

  int eq_status = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(eq_status, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест с ошибкой выделения памяти
START_TEST(test_calc_complements_memory_fail) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест с ошибкой при создании минора
START_TEST(test_calc_complements_minor_fail) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);

  // Эмулируем ошибку в get_minor
  A.matrix[0][0] = NAN;  // Может вызвать ошибку

  ck_assert_int_eq(s21_calc_complements(&A, &result), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест с ошибкой при вычислении определителя минора
START_TEST(test_calc_complements_minor_det_fail) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);

  // Эмулируем ошибку в determinant
  A.matrix[0][0] = INFINITY;  // Может вызвать ошибку

  ck_assert_int_eq(s21_calc_complements(&A, &result), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест для матрицы 1x1
START_TEST(test_determinant_1x1) {
  matrix_t A = {0};
  double det = 0;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq(det, 5.0);

  s21_remove_matrix(&A);
}
END_TEST

// Тест для матрицы 2x2
START_TEST(test_determinant_2x2) {
  matrix_t A = {0};
  double det = 0;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq(det, -2.0);

  s21_remove_matrix(&A);
}
END_TEST

// Тест для матрицы 3x3
START_TEST(test_determinant_3x3) {
  matrix_t A = {0};
  double det = 0;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq(det, 0.0);  // Определитель вырожденной матрицы

  s21_remove_matrix(&A);
}
END_TEST

// Тест для матрицы 4x4
START_TEST(test_determinant_4x4) {
  matrix_t A = {0};
  double det = 0;
  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 2.0;
  A.matrix[0][3] = -1.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 2.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 3.0;
  A.matrix[2][3] = 0.0;
  A.matrix[3][0] = 0.0;
  A.matrix[3][1] = 0.0;
  A.matrix[3][2] = 0.0;
  A.matrix[3][3] = 4.0;

  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq(det, 12.0);  // 1*1*3*4 = 12

  s21_remove_matrix(&A);
}
END_TEST

// Тест для единичной матрицы
START_TEST(test_determinant_identity) {
  matrix_t A = {0};
  double det = 0;
  s21_create_matrix(3, 3, &A);

  // Вручную создаём единичную матрицу
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = (i == j) ? 1.0 : 0.0;
    }
  }

  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq(det, 1.0);

  s21_remove_matrix(&A);
}
END_TEST

// Тест для нулевой матрицы
START_TEST(test_determinant_zero) {
  matrix_t A = {0};
  double det = 0;
  s21_create_matrix(3, 3, &A);

  // Вручную заполняем матрицу нулями
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 0.0;
    }
  }

  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq(det, 0.0);

  s21_remove_matrix(&A);
}
END_TEST

// Тест для неквадратной матрицы
START_TEST(test_determinant_not_square) {
  matrix_t A = {0};
  double det = 0;
  s21_create_matrix(2, 3, &A);

  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, 2);

  s21_remove_matrix(&A);
}
END_TEST

// Тест с NULL указателями
START_TEST(test_determinant_null_pointers) {
  matrix_t A = {0};
  double det = 0;
  s21_create_matrix(2, 2, &A);

  int status = s21_determinant(NULL, &det);
  ck_assert_int_eq(status, 1);

  status = s21_determinant(&A, NULL);
  ck_assert_int_eq(status, 1);

  s21_remove_matrix(&A);
}
END_TEST

// Тест для матрицы с плавающей точкой
START_TEST(test_determinant_float) {
  matrix_t A = {0};
  double det = 0, expected = 0;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.5;
  A.matrix[0][2] = 3.5;
  A.matrix[1][0] = 4.5;
  A.matrix[1][1] = 5.5;
  A.matrix[1][2] = 6.5;
  A.matrix[2][0] = 7.5;
  A.matrix[2][1] = 8.5;
  A.matrix[2][2] = 9.5;

  // Ручной расчёт определителя
  expected = 1.5 * (5.5 * 9.5 - 6.5 * 8.5) - 2.5 * (4.5 * 9.5 - 6.5 * 7.5) +
             3.5 * (4.5 * 8.5 - 5.5 * 7.5);

  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(det, expected, 1e-9);

  s21_remove_matrix(&A);
}
END_TEST

// Тест для большой матрицы (5x5)
START_TEST(test_determinant_large_matrix) {
  matrix_t A = {0};
  double det = 0;
  s21_create_matrix(5, 5, &A);
  // Заполняем диагональную матрицу
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      A.matrix[i][j] = (i == j) ? (i + 1) : 0;
    }
  }

  // Определитель диагональной матрицы = произведение диагональных элементов
  double expected = 1 * 2 * 3 * 4 * 5;  // 120

  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq(det, expected);

  s21_remove_matrix(&A);
}
END_TEST

// Тест для матрицы с нулевой строкой
START_TEST(test_determinant_zero_row) {
  matrix_t A = {0};
  double det = 0;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 4;
  A.matrix[2][1] = 5;
  A.matrix[2][2] = 6;

  int status = s21_determinant(&A, &det);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq(det, 0.0);

  s21_remove_matrix(&A);
}
END_TEST

// Тест с ошибкой при создании минора
START_TEST(test_determinant_minor_fail) {
  matrix_t A = {0};
  double det;

  s21_create_matrix(3, 2, &A);

  ck_assert_int_eq(s21_determinant(&A, &det), 2);
  s21_remove_matrix(&A);
}
END_TEST

// Тест с NULL указателями
START_TEST(test_get_minor_null_pointers) {
  matrix_t A = {0}, minor = {0};
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(get_minor(NULL, 0, 0, &minor), 1);
  ck_assert_int_eq(get_minor(&A, 0, 0, NULL), 1);
  double **original_matrix = A.matrix;
  A.matrix = NULL;
  ck_assert_int_eq(get_minor(&A, 0, 0, &minor), 1);
  A.matrix = original_matrix;
  s21_remove_matrix(&A);
  s21_remove_matrix(&minor);
}
END_TEST

// Тест с матрицей меньше 2x2
START_TEST(test_get_minor_small_matrix) {
  matrix_t A = {0}, minor = {0};
  s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(get_minor(&A, 0, 0, &minor), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&minor);
}
END_TEST

// Тест с некорректными индексами строки/столбца
START_TEST(test_get_minor_invalid_indices) {
  matrix_t A = {0}, minor = {0};
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(get_minor(&A, -1, 0, &minor), 1);
  ck_assert_int_eq(get_minor(&A, 0, -1, &minor), 1);
  ck_assert_int_eq(get_minor(&A, 3, 0, &minor), 1);
  ck_assert_int_eq(get_minor(&A, 0, 3, &minor), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&minor);
}
END_TEST

// Тест с ошибкой создания минора
START_TEST(test_get_minor_create_fail) {
  matrix_t A = {0}, minor = {0};
  s21_create_matrix(3, 3, &A);
  int original_rows = A.rows;
  A.rows = 1;
  ck_assert_int_eq(get_minor(&A, 0, 0, &minor), 1);
  A.rows = original_rows;
  s21_remove_matrix(&A);
  s21_remove_matrix(&minor);
}
END_TEST

// Тест для успешного вычисления обратной матрицы
START_TEST(test_inverse_matrix_ok) {
  matrix_t A = {0}, result = {0}, expected = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  // Матрица A:
  // 2  5  7
  // 6  3  4
  // 5 -2 -3
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  // Ожидаемая обратная матрица:
  //  1  -1   1
  // -38  41 -34
  //  27 -29  24
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, 0);

  // Проверяем корректность результата
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected.matrix[i][j], 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест для неквадратной матрицы
START_TEST(test_inverse_not_square) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 3, &A);

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест для вырожденной матрицы (определитель = 0)
START_TEST(test_inverse_singular) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);

  // Матрица с определителем 0
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i + j;  // Все строки линейно зависимы
    }
  }

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест с NULL указателями
START_TEST(test_inverse_null_pointers) {
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_inverse_matrix(NULL, NULL), 1);
  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), 1);

  s21_remove_matrix(&A);
}
END_TEST

// Тест для матрицы 1x1
START_TEST(test_inverse_1x1) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.2, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест с ошибкой выделения памяти
START_TEST(test_inverse_memory_fail) {
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  matrix_t *invalid_ptr = NULL;
  ck_assert_int_eq(s21_inverse_matrix(&A, invalid_ptr), 1);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_calc_complements_fail) {
  matrix_t A = {0};
  matrix_t result = {0};

  // Создаем некорректную матрицу (например, с NaN), чтобы s21_calc_complements
  // завершился ошибкой
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = NAN;  // Это вызовет ошибку в calc_complements
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 3;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, INVALID_MATRIX);  // Проверяем, что вернулась ошибка

  // Проверяем, что result не был изменен (остался нулевым)
  ck_assert_ptr_null(result.matrix);
  ck_assert_int_eq(result.rows, 0);
  ck_assert_int_eq(result.columns, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_matrix_suite(void) {
  Suite *s = suite_create("s21_matrix");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_create_matrix_ok);
  tcase_add_test(tc_core, test_create_matrix_null);
  tcase_add_test(tc_core, test_create_matrix_rows_0);
  tcase_add_test(tc_core, test_create_matrix_cols_0);
  tcase_add_test(tc_core, test_create_matrix_size_minus);
  tcase_add_test(tc_core, test_create_matrix_null_pointer);
  tcase_add_test(tc_core, test_eq_matrix_ok);
  tcase_add_test(tc_core, test_eq_matrix_fail_values);
  tcase_add_test(tc_core, test_eq_matrix_fraction_lower);
  tcase_add_test(tc_core, test_eq_matrix_fraction_higher_ok);
  tcase_add_test(tc_core, test_eq_matrix_fraction_higher_fail);
  tcase_add_test(tc_core, test_eq_matrix_diff_sizes);
  tcase_add_test(tc_core, test_eq_matrix_matrices_null);
  tcase_add_test(tc_core, test_sum_matrix_ok);
  tcase_add_test(tc_core, test_sum_number_null_pointers);
  tcase_add_test(tc_core, test_sum_different_sizes);
  tcase_add_test(tc_core, test_sum_different_input_and_result_sizes);
  tcase_add_test(tc_core, test_sum_result_not_initialized);
  tcase_add_test(tc_core, test_sub_matrix_ok);
  tcase_add_test(tc_core, test_sub_number_null_pointers);
  tcase_add_test(tc_core, test_sub_different_sizes);
  tcase_add_test(tc_core, test_sub_different_input_and_result_sizes);
  tcase_add_test(tc_core, test_sub_result_not_initialized);
  tcase_add_test(tc_core, test_mult_number_ok);
  tcase_add_test(tc_core, test_mult_number_wrong_sizes);
  tcase_add_test(tc_core, test_mult_number_create_fail);
  tcase_add_test(tc_core, test_mult_number_null_pointers);
  tcase_add_test(tc_core, test_mult_number_result_not_initialized);
  tcase_add_test(tc_core, test_mult_matrix_ok);
  tcase_add_test(tc_core, test_mult_matrix_null_pointers);
  tcase_add_test(tc_core, test_mult_matrix_wrong_sizes);
  tcase_add_test(tc_core, test_transpose_ok);
  tcase_add_test(tc_core, test_transpose_null_pointers);
  tcase_add_test(tc_core, test_transpose_different_sizes);
  tcase_add_test(tc_core, test_transpose_create_matrix_fail);
  tcase_add_test(tc_core, test_calc_complements_ok);
  tcase_add_test(tc_core, test_calc_complements_not_square);
  tcase_add_test(tc_core, test_calc_complements_1x1);
  tcase_add_test(tc_core, test_calc_complements_null_pointers);
  tcase_add_test(tc_core, test_calc_complements_2x2);
  tcase_add_test(tc_core, test_calc_complements_memory_fail);
  tcase_add_test(tc_core, test_calc_complements_minor_fail);
  tcase_add_test(tc_core, test_calc_complements_minor_det_fail);
  tcase_add_test(tc_core, test_determinant_1x1);
  tcase_add_test(tc_core, test_determinant_2x2);
  tcase_add_test(tc_core, test_determinant_3x3);
  tcase_add_test(tc_core, test_determinant_4x4);
  tcase_add_test(tc_core, test_determinant_identity);
  tcase_add_test(tc_core, test_determinant_zero);
  tcase_add_test(tc_core, test_determinant_not_square);
  tcase_add_test(tc_core, test_determinant_null_pointers);
  tcase_add_test(tc_core, test_determinant_float);
  tcase_add_test(tc_core, test_determinant_large_matrix);
  tcase_add_test(tc_core, test_determinant_zero_row);
  tcase_add_test(tc_core, test_determinant_minor_fail);
  tcase_add_test(tc_core, test_get_minor_null_pointers);
  tcase_add_test(tc_core, test_get_minor_small_matrix);
  tcase_add_test(tc_core, test_get_minor_invalid_indices);
  tcase_add_test(tc_core, test_get_minor_create_fail);
  tcase_add_test(tc_core, test_inverse_matrix_ok);
  tcase_add_test(tc_core, test_inverse_not_square);
  tcase_add_test(tc_core, test_inverse_singular);
  tcase_add_test(tc_core, test_inverse_null_pointers);
  tcase_add_test(tc_core, test_inverse_1x1);
  tcase_add_test(tc_core, test_inverse_memory_fail);
  tcase_add_test(tc_core, test_inverse_matrix_calc_complements_fail);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  Suite *s = s21_matrix_suite();
  SRunner *sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);

  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}