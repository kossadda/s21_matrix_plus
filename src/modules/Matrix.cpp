/**
 * @file Matrix.cpp
 * @author kossadda (https://github.com/kossadda)
 * @brief Module containing descriptions of S21Matrix class methods
 * @version 1.0
 * @date 2024-04-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./include/Matrix.h"

/// @brief Default constructor (creates a 3x3 matrix)
S21Matrix::S21Matrix() : rows_(DEFAULT), cols_(DEFAULT), matrix_(Alloc()) {}

/**
 * @brief Parameterized constructor
 *
 * @param[in] rows number of matrix rows
 * @param[in] cols number of matrix columns
 */
S21Matrix::S21Matrix(int r, int c) : rows_(r), cols_(c), matrix_(Alloc()) {}

/// @brief Destructor
S21Matrix::~S21Matrix() { Remove(); }

/**
 * @brief Copy constructor
 *
 * @param[in] other Object to be copied
 */
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(Alloc()) {
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
}

/// @brief Allocates memory for a matrix with the current fields rows_ and cols_
double* S21Matrix::Alloc() {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("Constructor: invalid matrix size");

  try {
    return new double[rows_ * cols_]{};
  } catch (const std::bad_alloc& e) {
    throw std::runtime_error("Memory allocation failed");
  }
}

/// @brief Clears the memory allocated in field matrix_
void S21Matrix::Remove() {
  if (matrix_) {
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

/**
 * @brief Checks the validity of the matrix
 *
 * @retval NO (false) - if wrong size or matrix contains nan or inf values
 * @retval YES (true) - correct matrix
 */
bool S21Matrix::IsCorrect() const {
  bool correct = (rows_ && cols_) ? YES : NO;

  if (correct) {
    for (int i = 0; i < rows_ * cols_; ++i) {
      if (std::isnan(matrix_[i]) || std::isinf(matrix_[i])) {
        correct = NO;
      }
    }
  }

  return correct;
}

/**
 * @brief Compare size and valid of both matrix
 *
 * @param[in] other second matrix
 * @retval YES (true) - correct matrix
 * @retval NO (false) - if different size or contains nan or inf
 */
bool S21Matrix::CompareIsRight(const S21Matrix& other) const {
  return (rows_ != other.rows_ || cols_ != other.cols_ || !IsCorrect() ||
          !other.IsCorrect())
             ? NO
             : YES;
}

/**
 * @brief Fill matrix with values
 *
 * @param[in] values the array where the numbers are entered from
 */
void S21Matrix::Fill(const double* values) {
  std::copy(values, values + rows_ * cols_, matrix_);
}

/**
 * @brief Get array element
 *
 * @param[in] row element row
 * @param[in] col element col
 * @return double - array element
 */
double S21Matrix::GetCell(const int row, const int col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::invalid_argument("GetCell: invalid cell");
  }
  return matrix_[row * cols_ + col];
}

/**
 * @brief Checks matrices for equality with each other
 *
 * @param[in] other comparison matrix
 * @retval true  - the matrices are equal
 * @retval false - the matrices are not equal
 */
bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool equal = CompareIsRight(other);

  if (equal) {
    for (int i = 0; i < rows_ * cols_ && equal; i++) {
      if (std::abs(matrix_[i] - other.matrix_[i]) > PRECISION) {
        equal = NO;
      }
    }
  }

  return equal;
}

/**
 * @brief Checks matrices for equality with each other via operator ==
 *
 * @param[in] other comparison matrix
 * @retval true - the matrices are equal
 * @retval false - the matrices are not equal
 */
bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

/**
 * @brief Checks matrices for non-equality with each other via operator !=
 *
 * @param[in] other comparison matrix
 * @retval true  - the matrices are not equal
 * @retval false - the matrices are equal
 */
bool S21Matrix::operator!=(const S21Matrix& other) const {
  return !EqMatrix(other);
}


/**
 * @brief An assignment operator = that replaces the current matrix with the
 * input one
 *
 * @param other assignable matrix
 */
void S21Matrix::operator=(const S21Matrix& other) {
  if(this != &other && other.rows_ && other.cols_) {
    Remove();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = Alloc();
    std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
  }
}

// /**
//  * @brief Adds the second matrix to the current one
//  *
//  * @param[in] other added matrix
//  */
// void S21Matrix::SumMatrix(const S21Matrix& other) {
//   if (ValidEqualSize(other) && !IsNanOrInf() && !other.IsNanOrInf()) {
//     for (int i = 0; i < rows_; i++) {
//       for (int j = 0; j < cols_; j++) {
//         matrix_[i][j] += other.matrix_[i][j];
//       }
//     }
//   }
// }

// /**
//  * @brief Subtracts another matrix from the current one
//  *
//  * @param[in] other subtractable matrix
//  */
// void S21Matrix::SubMatrix(const S21Matrix& other) {
//   if (ValidEqualSize(other) && !IsNanOrInf() && !other.IsNanOrInf()) {
//     for (int i = 0; i < rows_; i++) {
//       for (int j = 0; j < cols_; j++) {
//         matrix_[i][j] -= other.matrix_[i][j];
//       }
//     }
//   }
// }

//   return status;
// }

// /**
//  * @brief Adds the second matrix to the current one via operator +
//  *
//  * @param[in] other added matrix
//  * @return S21Matrix - result of addition
//  */
// S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
//   S21Matrix result(*this);
//   result.SumMatrix(other);

//   return result;
// }

// /**
//  * @brief Subtracts another matrix from the current one via operator -
//  *
//  * @param[in] other subtractable matrix
//  * @return S21Matrix - result of addition
//  */
// S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
//   S21Matrix result(*this);
//   result.SubMatrix(other);

//   return result;
// }

// /**
//  * @brief Adds the second matrix to the current one via operator +=
//  *
//  * @param[in] other added matrix
//  */
// void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }

// /**
//  * @brief Subtracts another matrix from the current one via operator -=
//  *
//  * @param other subtractable matrix
//  */
// void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }

/// @brief Print the matrix of the current object
void S21Matrix::Print() const {
  for (int i = 0; i < rows_ * cols_; i++) {
    if (i && i % cols_ == 0) std::cout << std::endl;
    std::cout << matrix_[i] << " ";
  }
  std::cout << std::endl;
}