#include <gtest/gtest.h>

#include "s21_matrix_oop.h"
TEST(test_eq_matrix, test1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix2.number_padding(2);
  ASSERT_EQ(matrix2.eq_matrix(matrix1), false);
}

TEST(sub_matrix, test2) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix1(2, 2);
  S21Matrix matrix_res(2, 2);
  matrix.number_padding(1);
  matrix1.number_padding(2);
  matrix_res.number_padding(3);
  matrix_res.sub_matrix(matrix1);
  ASSERT_EQ(matrix_res.eq_matrix(matrix), true);
}

TEST(sum_matrix, test3) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix1(2, 2);
  S21Matrix matrix_res(2, 2);
  matrix.number_padding(3);
  matrix1.number_padding(2);
  matrix_res.number_padding(1);
  matrix_res.sum_matrix(matrix1);
  ASSERT_EQ(matrix_res.eq_matrix(matrix), true);
}

TEST(mul_matrix, test4) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix1(2, 2);
  S21Matrix matrix_res(2, 2);
  matrix.number_padding(3);
  matrix1.number_padding(1);
  matrix_res.number_padding(1);
  matrix_res.mul_matrix(matrix1);
  ASSERT_EQ(matrix_res.eq_matrix(matrix), true);
}

TEST(trans, test5) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix1(2, 2);
  matrix1 = matrix.transpose();
  ASSERT_EQ(matrix1.eq_matrix(matrix), true);
}

TEST(det, test6) {
  S21Matrix matrix(3, 3);
  double matrix_res = 0;
  matrix.number_padding(1);
  double a = matrix.determinant();
  EXPECT_EQ(a, matrix_res);
}

TEST(calc, test7) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix1(2, 2);
  matrix.number_padding(0);
  matrix1 = matrix.calc_complements();
  ASSERT_EQ(matrix1.eq_matrix(matrix), true);
}

TEST(inverse, test8) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 3;
  matrix(1, 0) = 1;
  matrix(1, 1) = 2;
  matrix2(0, 0) = -2;
  matrix2(0, 1) = 3;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = -1;
  matrix1 = matrix.inverse_matrix();
  ASSERT_EQ(matrix1.eq_matrix(matrix2), true);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
// #include <iostream>
// #include "s21_matrix_oop.h"

// int main() {
//   S21Matrix matrix(3, 3);
//   S21Matrix matrix1(matrix);
//   S21Matrix matrix2(matrix);
//   matrix2 = matrix + matrix1;
//   // ma==
//     // matrix.number_padding();
//     // matrix.calc_complements();
//     matrix.print_matrix();
//     //std::cout << matrix2 << std::endl;
//     return 0;
// }