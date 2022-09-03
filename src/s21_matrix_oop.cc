#include "s21_matrix_oop.h"

#include <iostream>

S21Matrix::S21Matrix() { this->zerro_padding(); }
// Default constructor
S21Matrix::~S21Matrix() { this->clear_matrix(); }
// Destructor
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 && cols <= 0) {
    throw std::out_of_range("Invalid size of rows or columns");
  }
  this->rows_ = rows;
  this->cols_ = cols;
  this->create_matrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = new double *[other.rows_ * other.cols_];
  /* standard cpp function: copies memory of o.rows_ * o.cols_ * sizeof(double)
  from o.p pointer to _p pointer */
  std::memcpy(matrix_, other.matrix_,
              other.rows_ * other.cols_ * sizeof(double));
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

int S21Matrix::get_rows() { return this->rows_; }
int S21Matrix::get_columns() { return this->cols_; }

void S21Matrix::set_rows(int rows) {
  if (rows <= 0) {
    throw std::length_error("Rows is less or equal 0");
  }
  S21Matrix temp(rows, this->cols_);
  int min_rows = (rows < this->rows_) ? rows : this->rows_;

  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < this->cols_; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  this->clear_matrix();
  *this = temp;
}

void S21Matrix::set_columns(int columns) {
  if (columns <= 0) {
    throw std::length_error("Rows is less or equal 0");
  }
  S21Matrix temp(this->rows_, columns);
  if (columns < this->cols_) {
    this->cols_ = columns;
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = temp;
}

void S21Matrix::create_matrix() {
  this->matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 1;
    }
  }
}

void S21Matrix::zerro_padding() {
  this->rows_ = this->cols_ = 0;
  this->matrix_ = nullptr;
}

void S21Matrix::clear_matrix() {
  if (!this->matrix_) {
    for (int i = 0; i < this->rows_; i++) {
      delete matrix_[i];
    }
    delete matrix_;
  }
}

void S21Matrix::print_matrix() {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        std::cout << matrix_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  } else {
    std::cout << "Matrix is empty" << std::endl;
  }
}

void S21Matrix::number_padding(double x) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = x;
    }
  }
}

void S21Matrix::copy_matrix(const S21Matrix &other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = new double *[other.rows_ * other.cols_];
  /* standard cpp function: copies memory of o.rows_ * o.cols_ * sizeof(double)
  from o.p pointer to _p pointer */
  std::memcpy(matrix_, other.matrix_,
              other.rows_ * other.cols_ * sizeof(double));
}

void S21Matrix::sum_matrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  } else if (this->matrix_ == nullptr && other.matrix_ == nullptr) {
    throw std::out_of_range("Incorrect input, matrix empty");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::sub_matrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  } else if (this->matrix_ == nullptr && other.matrix_ == nullptr) {
    throw std::out_of_range("Incorrect input, matrix empty");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}
bool S21Matrix::eq_matrix(const S21Matrix &other) {
  bool result = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  } else if (this->matrix_ == nullptr && other.matrix_ == nullptr) {
    throw std::out_of_range("Incorrect input, matrix empty");
  } else if ((this->rows_ < 0 || this->cols_ < 0) &&
             (other.rows_ < 0 || other.cols_ < 0)) {
    throw std::out_of_range("Incorrect input, size cannot be less than zero");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (std::fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-07)
          result = false;
      }
    }
  }
  return result;
}

void S21Matrix::mul_number(const double num) {
  if (this->matrix_ == nullptr) {
    throw std::out_of_range("Empty matrix");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] *= num;
      }
    }
  }
}

void S21Matrix::mul_matrix(const S21Matrix &other) {
  if (this->rows_ != other.cols_) {
    throw std::out_of_range(
        "the number of rows of the first matrix must be equal to the number of "
        "columns of the second matrix");
  } else if (!this->matrix_ || !other.matrix_) {
    throw std::out_of_range("Incorrect input, matrix empty");
  } else {
    S21Matrix result(this->rows_, other.cols_);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        for (int k = 0; k < this->cols_; k++) {
          result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    *this = result;
  }
}

S21Matrix S21Matrix::transpose() {
  if (!this->matrix_) {
    throw std::out_of_range("Incorrect input, matrix empty");
  } else {
    S21Matrix result(this->rows_, this->cols_);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        for (int k = 0; k < this->cols_; k++) {
          result.matrix_[i][j] = this->matrix_[j][i];
        }
      }
    }
    *this = result;
  }
  return *this;
}

S21Matrix S21Matrix::get_matrix_minor(const S21Matrix &other_matrix, int rows,
                                      int cols) {
  for (int i = 0; i < other_matrix.rows_; i++) {
    for (int j = 0; j < other_matrix.cols_; j++) {
      if (i != rows && j != cols) {
        if (j > cols && i > rows) {
          matrix_[i - 1][j - 1] = other_matrix.matrix_[i][j];
        } else if (j < cols && i < rows) {
          matrix_[i][j] = other_matrix.matrix_[i][j];
        } else if (j > cols && i < rows) {
          matrix_[i][j - 1] = other_matrix.matrix_[i][j];
        } else if (j < cols && i > rows) {
          matrix_[i - 1][j] = other_matrix.matrix_[i][j];
        }
      }
    }
  }
  return *this;
}

double S21Matrix::determinant() {
  if (this->rows_ != this->cols_) {
    throw std::out_of_range("Size of rows must be equal size of columns");
  } else if (!this->matrix_) {
    throw std::out_of_range("Incorrect input, matrix empty");
  } else {
    double result = 0.0;
    if (rows_ == 1 && cols_ == 1) { //Условие выхода из рекурсии
      result = matrix_[0][0];
    } else if (rows_ == 2 && cols_ == 2) {
      result =
          matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * this->matrix_[1][0];
    } else {
      for (int j = 0; j < cols_; j++) { //Матрица без строки и столбца
        S21Matrix tmpMatrix(rows_ - 1, cols_ - 1);
        tmpMatrix.get_matrix_minor(*this, 0, j);
        result += matrix_[0][j] * pow(-1, j) * tmpMatrix.determinant();
      }
    }
    return result;
  }
}

S21Matrix S21Matrix::calc_complements() {
  S21Matrix resultMatrix(rows_, cols_);
  S21Matrix tmpMatrix(rows_ - 1, cols_ - 1);
  if (rows_ != cols_) {
    throw std::out_of_range("Size of rows must be equal size of columns");
  } else if (!matrix_) {
    throw std::out_of_range("Incorrect input, matrix empty");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        tmpMatrix.get_matrix_minor(*this, i, j);
        resultMatrix.matrix_[i][j] = tmpMatrix.determinant() * pow(-1, i + j);
      }
    }
  }
  return resultMatrix;
}

S21Matrix S21Matrix::inverse_matrix() {
  if (rows_ != cols_) {
    throw std::logic_error("\nRows and columns must match\n");
  } else if (determinant() == 0.0) {
    throw std::logic_error("\ndeterminant value can't be equal to 0\n");
  }
  const double determinant = 1 / this->determinant();
  S21Matrix tmpMatrix(calc_complements());
  S21Matrix resultMatrix(tmpMatrix.transpose());
  resultMatrix.mul_number(determinant);
  return resultMatrix;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->eq_matrix(other);
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  sum_matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  sub_matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  mul_matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  mul_number(num);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res(rows_, cols_);
  res.sum_matrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res(rows_, cols_);
  res.sub_matrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res(rows_, cols_);
  res.mul_matrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(rows_, cols_);
  res.mul_number(num);
  return res;
}

double &S21Matrix::operator()(int i, int j) {
  if (i >= this->rows_ || j >= this->cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Incorrect index!");
  }
  return this->matrix_[i][j];
}