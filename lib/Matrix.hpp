#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstring>
#include <stdexcept>
#include <vector>

#include "Tuple.hpp"

template<std::size_t ROWS, std::size_t COLS>
struct Matrix
{
  float data[ROWS][COLS]{};
  float* operator[](std::size_t row) { return data[row]; }
  float const* operator[](std::size_t row) const { return data[row]; }

  static Matrix Identity();
};

template<std::size_t ROWS, std::size_t COLS>
inline bool operator==(const Matrix<ROWS, COLS>& A, const Matrix<ROWS, COLS>& B)
{
  for (auto row = 0; row < ROWS; ++row) {
    for (auto col = 0; col < COLS; ++col) {
      if (std::abs(A[row][col] - B[row][col]) >= EPSILON) {
        return false;
      }
    }
  }
  return true;
}

inline Matrix<4, 4> operator*(const Matrix<4, 4>& A, const Matrix<4, 4>& B)
{
  Matrix<4, 4> R;
  for (auto row = 0; row < 4; ++row) {
    for (auto col = 0; col < 4; ++col) {
      R[row][col] = A[row][0] * B[0][col] + //
                    A[row][1] * B[1][col] + //
                    A[row][2] * B[2][col] + //
                    A[row][3] * B[3][col];
    }
  }
  return R;
}

inline Tuple operator*(const Matrix<4, 4>& A, const Tuple& b)
{
  return Tuple(A[0][0] * b.x + A[0][1] * b.y + A[0][2] * b.z + A[0][3] * b.w,
               A[1][0] * b.x + A[1][1] * b.y + A[1][2] * b.z + A[1][3] * b.w,
               A[2][0] * b.x + A[2][1] * b.y + A[2][2] * b.z + A[2][3] * b.w,
               A[3][0] * b.x + A[3][1] * b.y + A[3][2] * b.z + A[3][3] * b.w);
}

template<>
inline Matrix<4, 4> Matrix<4, 4>::Identity()
{
  Matrix<4, 4> R = {
    1, 0, 0, 0, //
    0, 1, 0, 0, //
    0, 0, 1, 0, //
    0, 0, 0, 1  //
  };
  return R;
}

template<std::size_t ROWS, std::size_t COLS>
inline Matrix<ROWS, COLS> transpose(const Matrix<ROWS, COLS>& A)
{
  Matrix<ROWS, COLS> R;
  for (auto row = 0; row < ROWS; ++row) {
    for (auto col = 0; col < COLS; ++col) {
      R[row][col] = A[col][row];
    }
  }
  return R;
}

template<std::size_t ROWS, std::size_t COLS>
inline float determinant(const Matrix<ROWS, COLS>& A)
{
  float result{};
  for (auto col = 0; col < COLS; ++col) {
    result += A[0][col] * cofactor(A, 0, col);
  }
  return result;
}

inline float determinant(const Matrix<2, 2>& A)
{
  return (A[0][0] * A[1][1]) - (A[0][1] * A[1][0]);
}

template<std::size_t ROWS, std::size_t COLS>
inline Matrix<ROWS - 1, COLS - 1> submatrix(const Matrix<ROWS, COLS>& A,
                                            std::size_t i,
                                            std::size_t j)
{
  Matrix<ROWS - 1, COLS - 1> R{};

  for (auto row = 0; row < ROWS - 1; ++row) {
    for (auto col = 0; col < COLS - 1; ++col) {
      R[row][col] = A[row < i ? row : row + 1] //
                     [col < j ? col : col + 1];
    }
  }

  return R;
}

template<std::size_t ROWS, std::size_t COLS>
inline float minor(const Matrix<ROWS, COLS>& A, std::size_t i, std::size_t j)
{
  return determinant(submatrix(A, i, j));
}

template<std::size_t ROWS, std::size_t COLS>
inline float cofactor(const Matrix<ROWS, COLS>& A,
                      std::size_t row,
                      std::size_t col)
{
  if ((row + col) % 2 == 0) {
    return minor(A, row, col);
  } else {
    return -(minor(A, row, col));
  }
}

template<std::size_t ROWS, std::size_t COLS>
inline bool isInvertible(const Matrix<ROWS, COLS>& A)
{
  return !determinant(A) == 0;
}

#endif // MATRIX_HPP

template<std::size_t ROWS, std::size_t COLS>
inline Matrix<ROWS, COLS> inverse(const Matrix<ROWS, COLS>& A)
{
  if (isInvertible(A)) {
    Matrix<ROWS, COLS> R;

    for (auto row = 0; row < ROWS; ++row) {
      for (auto col = 0; col < COLS; ++col) {
        auto c = cofactor(A, row, col);

        // note that "col, row" here, instead of "row, col",
        // accomplishes the transpose operation!
        R[col][row] = c / determinant(A);
      }
    }

    return R;

  } else {
    throw std::runtime_error("A is not invertible");
  }
}
