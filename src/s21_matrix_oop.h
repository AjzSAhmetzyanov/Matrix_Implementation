#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <cmath>
#include <cstring>
#include <iostream>

class S21Matrix {
private:
  // Attributes
  int rows_, cols_; // Rows and columns
  double **matrix_; // Pointer to the memory where the matrix is allocated

public:
  S21Matrix();  // Default constructor
  ~S21Matrix(); // Destructor
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);

  void zerro_padding();
  void create_matrix();
  void clear_matrix();
  void print_matrix();
  void number_padding(double x);
  void copy_matrix(const S21Matrix &other);
  S21Matrix get_matrix_minor(const S21Matrix &other_matrix, int rows, int cols);
  int get_rows();
  int get_columns();
  void set_rows(int rows);
  void set_columns(int columns);

  S21Matrix &operator=(const S21Matrix &other);
  bool operator==(const S21Matrix &other);
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(const S21Matrix &other);
  S21Matrix operator*=(const double num);
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  double &operator()(int i, int j);

  bool eq_matrix(const S21Matrix &other);
  void sum_matrix(const S21Matrix &other);
  void sub_matrix(const S21Matrix &other);
  void mul_number(const double num);
  void mul_matrix(const S21Matrix &other);
  S21Matrix transpose();
  S21Matrix calc_complements();
  double determinant();
  S21Matrix inverse_matrix();
};

#endif // __S21MATRIX_H__