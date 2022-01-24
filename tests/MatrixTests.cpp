// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

SCENARIO("Constructing and inspecting a 4x4 matrix")
{
  GIVEN("the following 4x4 matrix M:\
    |  1   |  2   |  3   |  4   |\
    |  5.5 |  6.5 |  7.5 |  8.5 |\
    |  9   | 10   | 11   | 12   |\
    | 13.5 | 14.5 | 15.5 | 16.5 |")
  {

    mat4 M = {
      1,    2,    3,    4,   //
      5.5,  6.5,  7.5,  8.5, //
      9,    10,   11,   12,  //
      13.5, 14.5, 15.5, 16.5 //
    };

    THEN("\
        M[0,0] == 1 &&\
        M[0,3] == 4 &&\
        M[1,0] == 5.5 &&\
        M[1,2] == 7.5 &&\
        M[2,2] == 11 &&\
        M[3,0] == 13.5 &&\
        M[3,2] == 15.5")
    {

      CHECK(M[0][0] == 1);
      CHECK(M[0][3] == 4);
      CHECK(M[1][0] == 5.5);
      CHECK(M[1][2] == 7.5);
      CHECK(M[2][2] == 11);
      CHECK(M[3][0] == 13.5);
      CHECK(M[3][2] == 15.5);
    }
  }
}

SCENARIO("A 2x2 matrix ought to be representable")
{
  GIVEN("the following 2x2 matrix M:\
    | -3 |  5 |\
    |  1 | -2 |")
  {

    // clang-format off
    Matrix<2, 2> M{
      -3,  5,
       1, -2
    };
    // clang-format on

    THEN("\
        M[0,0] == -3 &&\
        M[0,1] == 5 &&\
        M[1,0] == 1 &&\
        M[1,1] == -2")
    {

      CHECK(M[0][0] == -3);
      CHECK(M[0][1] == 5);
      CHECK(M[1][0] == 1);
      CHECK(M[1][1] == -2);
    }
  }
}

SCENARIO("A 3x3 matrix ought to be representable")
{
  GIVEN("the following 3x3 matrix M:\
    | -3 |  5 |  0 |\
    |  1 | -2 | -7 |\
    |  0 |  1 |  1 |")
  {

    // clang-format off
    Matrix<3, 3> M{
      -3,  5,  0,
       1, -2, -7,
       0,  1,  1
    };
    // clang-format on

    THEN("\
        M[0,0] == -3 &&\
        M[1,1] == -2 &&\
        M[2,2] ==  1")
    {

      CHECK(M[0][0] == -3);
      CHECK(M[1][1] == -2);
      CHECK(M[2][2] == 1);
    }
  }
}

SCENARIO("Matrix equality with identitical matrices")
{
  GIVEN("the following matrix A:\
    \n| 1 | 2 | 3 | 4 |\
    \n| 5 | 6 | 7 | 8 |\
    \n| 9 | 8 | 7 | 6 |\
    \n| 5 | 4 | 3 | 2 |\
    And the following matrix B:\
    \n| 1 | 2 | 3 | 4 |\
    \n| 5 | 6 | 7 | 8 |\
    \n| 9 | 8 | 7 | 6 |\
    \n| 5 | 4 | 3 | 2 |")
  {

    mat4 A = {
      1, 2, 3, 4, //
      5, 6, 7, 8, //
      9, 8, 7, 6, //
      5, 4, 3, 2  //
    };

    mat4 B = {
      1, 2, 3, 4, //
      5, 6, 7, 8, //
      9, 8, 7, 6, //
      5, 4, 3, 2  //
    };

    THEN("A == B") { CHECK(A == B); }
  }
}

SCENARIO("Matrix equality with different matrices")
{
  GIVEN("the following matrix A:\
    | 1 | 2 | 3 | 4 |\
    | 5 | 6 | 7 | 8 |\
    | 9 | 8 | 7 | 6 |\
    | 5 | 4 | 3 | 2 |\
    And the following matrix B:\
    | 2 | 3 | 4 | 5 |\
    | 6 | 7 | 8 | 9 |\
    | 8 | 7 | 6 | 5 |\
    | 4 | 3 | 2 | 1 |")
  {

    mat4 A = {
      1, 2, 3, 4, //
      5, 6, 7, 8, //
      9, 8, 7, 6, //
      5, 4, 3, 2  //
    };

    mat4 B = {
      1, 2, 3, 4, //
      5, 6, 7, 8, //
      8, 7, 6, 5, //
      4, 3, 2, 1  //
    };

    THEN("A != B") { CHECK(A != B); }
  }
}

SCENARIO("Multiplying two matrices")
{
  GIVEN("the following matrix A:\
    \n| 1 | 2 | 3 | 4 |\
    \n| 5 | 6 | 7 | 8 |\
    \n| 9 | 8 | 7 | 6 |\
    \n| 5 | 4 | 3 | 2 |\n\n\
    And the following matrix B:\
    \n| -2 | 1 | 2 |  3 |\
    \n|  3 | 2 | 1 | -1 |\
    \n|  4 | 3 | 6 |  5 |\
    \n|  1 | 2 | 7 |  8 |\n")
  {

    mat4 A = {
      1, 2, 3, 4, //
      5, 6, 7, 8, //
      9, 8, 7, 6, //
      5, 4, 3, 2  //
    };

    mat4 B = {
      -2, 1, 2, 3,  //
      3,  2, 1, -1, //
      4,  3, 6, 5,  //
      1,  2, 7, 8   //
    };

    THEN("A * B is the following 4x4 matrix:\
    \n| 20 | 22 |  50 |  48 |\
    \n| 44 | 54 | 114 | 108 |\
    \n| 40 | 58 | 110 | 102 |\
    \n| 16 | 26 |  46 |  42 |\n")
    {

      mat4 R = {
        20, 22, 50,  48,  //
        44, 54, 114, 108, //
        40, 58, 110, 102, //
        16, 26, 46,  42   //
      };

      CHECK(A * B == R);
    }
  }
}

SCENARIO("A matrix multiplied by a tuple")
{
  GIVEN("the following matrix A:\
    \n| 1 | 2 | 3 | 4 |\
    \n| 2 | 4 | 4 | 2 |\
    \n| 8 | 6 | 4 | 1 |\
    \n| 0 | 0 | 0 | 1 |\n\
    \n\
    And b = tuple(1, 2, 3, 1)")
  {

    mat4 A = {
      1, 2, 3, 4, //
      2, 4, 4, 2, //
      8, 6, 4, 1, //
      0, 0, 0, 1  //
    };

    auto b = Tuple(1, 2, 3, 1);

    THEN("A * b == tuple(18, 24, 33, 1)")
    {
      CHECK(A * b == Tuple(18, 24, 33, 1));
    }
  }
}

SCENARIO("Multiplying a matrix by the identity matrix")
{
  GIVEN("the following matrix A:\
    \n| 0 | 1 |  2 |  4 |\
    \n| 1 | 2 |  4 |  8 |\
    \n| 2 | 4 |  8 | 16 |\
    \n| 4 | 8 | 16 | 32 |\n")
  {

    mat4 A = {
      0, 1, 2,  4,  //
      1, 2, 4,  8,  //
      2, 4, 8,  16, //
      4, 8, 16, 32  //
    };

    THEN("A * identity_matrix == A")
    {
      CHECK(A * mat4::Identity() == A);
    }
  }
}

SCENARIO("Multiplying the identity matrix by a tuple")
{
  GIVEN("a = tuple(1, 2, 3, 4)")
  {
    auto a = Tuple(1, 2, 3, 4);

    THEN("identity_matrix * a == a")
    {
      CHECK(mat4::Identity() * a == a);
    }
  }
}

SCENARIO("Transposing a matrix")
{
  GIVEN("the following matrix A:\
    \n| 0 | 9 | 3 | 0 |\
    \n| 9 | 8 | 0 | 8 |\
    \n| 1 | 8 | 5 | 3 |\
    \n| 0 | 0 | 5 | 8 |\n")
  {

    mat4 A = {
      0, 9, 3, 0, //
      9, 8, 0, 8, //
      1, 8, 5, 3, //
      0, 0, 5, 8  //
    };

    THEN("transpose(A) is the following matrix:\
    \n| 0 | 9 | 1 | 0 |\
    \n| 9 | 8 | 8 | 0 |\
    \n| 3 | 0 | 5 | 5 |\
    \n| 0 | 8 | 3 | 8 |\n")
    {
      mat4 T = {
        0, 9, 1, 0, //
        9, 8, 8, 0, //
        3, 0, 5, 5, //
        0, 8, 3, 8  //
      };

      CHECK(transpose(A) == T);
    }
  }
}

SCENARIO("Transposing the identity matrix")
{
  GIVEN("A = transpose(identity_matrix)")
  {
    auto A = transpose(mat4::Identity());

    THEN("A == identity_matrix") { CHECK(A == mat4::Identity()); }
  }
}

SCENARIO("Calculating the determinant of a 2x2 matrix")
{
  GIVEN("the following 2x2 matrix M:\
    \n|  1 | 5 |\
    \n| -3 | 2 |\n")
  {

    // clang-format off
    Matrix<2, 2> A = {
       1, 5,
      -3, 2
    };
    // clang-format on

    THEN("determinant(A) == 17") { CHECK(determinant(A) == 17); }
  }
}

SCENARIO("A submatrix of a 3x3 matrix is a 2x2 matrix")
{
  GIVEN("the following 3x3 matrix A:\
    \n|  1 |  5 |  0 |\
    \n| -3 |  2 |  7 |\
    \n|  0 |  6 | -3 |\n")
  {

    // clang-format off
    Matrix<3, 3> A = {
       1,  5,  0,
      -3,  2,  7,
       0,  6, -3
    };
    // clang-format on

    THEN("submatrix(A, 0, 2) is the following 2x2 matrix:\
    \n| -3 | 2 |\
    \n|  0 | 6 |\n")
    {

      // clang-format off
      Matrix<2, 2> R = {
        -3,  2,
         0,  6
      };
      // clang-format on

      CHECK(submatrix(A, 0, 2) == R);
    }
  }
}

SCENARIO("A submatrix of a 4x4 matrix is a 3x3 matrix")
{
  GIVEN("the following 4x4 matrix A:\
    \n| -6 |  1 |  1 |  6 |\
    \n| -8 |  5 |  8 |  6 |\
    \n| -1 |  0 |  8 |  2 |\
    \n| -7 |  1 | -1 |  1 |\n")
  {

    mat4 A = {
      -6, 1, 1,  6, //
      -8, 5, 8,  6, //
      -1, 0, 8,  2, //
      -7, 1, -1, 1  //
    };

    THEN("submatrix(A, 2, 1) is the following 3x3 matrix:\
    \n| -6 |  1 |  6 |\
    \n| -8 |  8 |  6 |\
    \n| -7 | -1 |  1 |\n")
    {

      // clang-format off
      Matrix<3, 3> R = {
        -6,  1,  6,
        -8,  8,  6,
        -7, -1,  1
      };
      // clang-format on

      CHECK(submatrix(A, 2, 1) == R);
    }
  }
}

SCENARIO("Calculating a minor of a 3x3 matrix")
{
  GIVEN("the following 3x3 matrix A:\
    \n| 3 |  5 |  0 |\
    \n| 2 | -1 | -7 |\
    \n| 6 | -1 |  5 |\n\
    And B = submatrix(A, 1, 0)")
  {
    // clang-format off
    Matrix<3, 3> A = {
       3,  5,  0,
       2, -1, -7,
       6, -1,  5
    };
    // clang-format on

    auto B = submatrix(A, 1, 0);

    THEN("determinant(B) == 25 && minor(A, 1, 0) == 25")
    {
      CHECK(determinant(B) == 25);
      CHECK(minor(A, 1, 0) == 25);
    }
  }
}

SCENARIO("Calculating a cofactor of a 3x3 matrix")
{
  GIVEN("the following 3x3 matrix A:\
    \n| 3 |  5 |  0 |\
    \n| 2 | -1 | -7 |\
    \n| 6 | -1 |  5 |\n\
    And B = submatrix(A, 1, 0)")
  {
    // clang-format off
    Matrix<3, 3> A = {
       3,  5,  0,
       2, -1, -7,
       6, -1,  5
    };
    // clang-format on

    THEN("minor(A, 0, 0) == -12 &&\
      cofactor(A, 0, 0) == -12 &&\
      minor(A, 1, 0) == 25 &&\
      cofactor(A, 1, 0) == -25")
    {
      CHECK(minor(A, 0, 0) == -12);
      CHECK(cofactor(A, 0, 0) == -12);
      CHECK(minor(A, 1, 0) == 25);
      CHECK(cofactor(A, 1, 0) == -25);
    }
  }
}

SCENARIO("Calculating the determinant of a 3x3 matrix")
{
  GIVEN("the following 3x3 matrix A:\
    \n|  1 |  2 |  6 |\
    \n| -5 |  8 | -4 |\
    \n|  2 |  6 |  4 |\n")
  {
    // clang-format off
    Matrix<3, 3> A = {
       1,  2,  6,
      -5,  8, -4,
       2,  6,  4
    };
    // clang-format on

    THEN("cofactor(A, 0, 0) == 56 &&\n\
            cofactor(A, 0, 1) == 12 &&\n\
            cofactor(A, 0, 2) == -46 &&\n\
            determinant(A) == -196")
    {
      CHECK(cofactor(A, 0, 0) == 56);
      CHECK(cofactor(A, 0, 1) == 12);
      CHECK(cofactor(A, 0, 2) == -46);
      CHECK(determinant(A) == -196);
    }
  }
}

SCENARIO("Calculating the determinant of a 4x4 matrix")
{
  GIVEN("the following 4x4 matrix A:\
    \n| -2 | -8 |  3 |  5 |\
    \n| -3 |  1 |  7 |  3 |\
    \n|  1 |  2 | -9 |  6 |\
    \n| -6 |  7 |  7 | -9 |\n")
  {
    mat4 A = {
      -2, -8, 3,  5, //
      -3, 1,  7,  3, //
      1,  2,  -9, 6, //
      -6, 7,  7,  -9 //
    };

    THEN("cofactor(A, 0, 0) == 690 &&\n\
            cofactor(A, 0, 1) == 447 &&\n\
            cofactor(A, 0, 2) == 210 &&\n\
            cofactor(A, 0, 3) == 51 &&\n\
            determinant(A) == -4071")
    {
      CHECK(cofactor(A, 0, 0) == 690);
      CHECK(cofactor(A, 0, 1) == 447);
      CHECK(cofactor(A, 0, 2) == 210);
      CHECK(cofactor(A, 0, 3) == 51);
      CHECK(determinant(A) == -4071);
    }
  }
}

SCENARIO("Testing an invertible matrix for invertibility")
{
  GIVEN("the following 4x4 matrix A:\
    \n|  6 |  4 | 4 |  4 |\
    \n|  5 |  5 | 7 |  6 |\
    \n|  4 | -9 | 3 | -7 |\
    \n|  9 |  1 | 7 | -6 |\n")
  {
    mat4 A = {
      6, 4,  4, 4,  //
      5, 5,  7, 6,  //
      4, -9, 3, -7, //
      9, 1,  7, -6  //
    };

    THEN("determinant(A) == -2120 && A is invertible")
    {
      CHECK(determinant(A) == -2120);
      CHECK(isInvertible(A));
    }
  }
}

SCENARIO("Testing a noninvertible matrix for invertibility")
{
  GIVEN("the following 4x4 matrix A:\
    \n| -4 |  2 | -2 | -3 |\
    \n|  9 |  6 |  2 |  6 |\
    \n|  0 | -5 |  1 | -5 |\
    \n|  0 |  0 |  0 |  0 |\n")
  {
    mat4 A = {
      -4, 2,  -2, -3, //
      9,  6,  2,  6,  //
      0,  -5, 1,  -5, //
      0,  0,  0,  0   //
    };

    THEN("determinant(A) == 0 && A is not invertible")
    {
      CHECK(determinant(A) == 0);
      CHECK(!isInvertible(A));
    }
  }
}

SCENARIO("Calculating the inverse of a matrix")
{
  GIVEN("the following 4x4 matrix A:\
    \n| -5 |  2 |  6 | -8 |\
    \n|  1 | -5 |  1 |  8 |\
    \n|  7 |  7 | -6 | -7 |\
    \n|  1 | -3 |  7 |  4 |\n\
    AND B = inverse(A)\n")
  {
    mat4 A = {
      -5, 2,  6,  -8, //
      1,  -5, 1,  8,  //
      7,  7,  -6, -7, //
      1,  -3, 7,  4   //
    };

    auto B = inverse(A);

    THEN("determinant(A) == 532 &&\n\
            cofactor(A, 2, 3) == -160 &&\n\
            B[3,2] == -160/532 &&\n\
            cofactor(A, 3, 2) == 105 &&\n\
            B[2,3] == 105/532 &&\n\
            B is the following 4x4 matrix:\
            \n|  0.21805 |  0.45113 |  0.24060 | -0.04511 |\
            \n| -0.80827 | -1.45677 | -0.44361 |  0.52068 |\
            \n| -0.07895 | -0.22368 | -0.05263 |  0.19737 |\
            \n| -0.52256 | -0.81391 | -0.30075 |  0.30639 |")
    {
      CHECK(determinant(A) == 532);
      CHECK(cofactor(A, 2, 3) == -160);
      CHECK(B[3][2] == -160.0f / 532.0f);
      CHECK(cofactor(A, 3, 2) == 105);
      CHECK(B[2][3] == 105.0f / 532.0f);

      mat4 R = {
        0.21805,  0.45113,  0.24060,  -0.04511, //
        -0.80827, -1.45677, -0.44361, 0.52068,  //
        -0.07895, -0.22368, -0.05263, 0.19737,  //
        -0.52256, -0.81391, -0.30075, 0.30639   //
      };

      CHECK(B == R);
    }
  }
}

SCENARIO("Calculating the inverse of another matrix")
{
  GIVEN("the following 4x4 matrix A:\
    \n|  8 | -5 |  9 |  2 |\
    \n|  7 |  5 |  6 |  1 |\
    \n| -6 |  0 |  9 |  6 |\
    \n| -3 |  0 | -9 | -4 |")
  {
    mat4 A = {
      8,  -5, 9,  2, //
      7,  5,  6,  1, //
      -6, 0,  9,  6, //
      -3, 0,  -9, -4 //
    };

    THEN("inverse(A) is the following 4x4 matrix:\
            \n| -0.15385 | -0.15385 | -0.28205 | -0.53846 |\
            \n| -0.07692 |  0.12308 |  0.02564 |  0.03077 |\
            \n|  0.35897 |  0.35897 |  0.43590 |  0.92308 |\
            \n| -0.69231 | -0.69231 | -0.76923 | -1.92308 |")
    {
      mat4 R = {
        -0.15385, -0.15385, -0.28205, -0.53846, //
        -0.07692, 0.12308,  0.02564,  0.03077,  //
        0.35897,  0.35897,  0.43590,  0.92308,  //
        -0.69231, -0.69231, -0.76923, -1.92308, //
      };
      CHECK(R == inverse(A));
    }
  }
}

SCENARIO("Calculating the inverse of a third matrix")
{
  GIVEN("the following 4x4 matrix A:\
    \n|  9 |  3 |  0 |  9 |\
    \n| -5 | -2 | -6 | -3 |\
    \n| -4 |  9 |  6 |  4 |\
    \n| -7 |  6 |  6 |  2 |\n")
  {
    mat4 A = {
      9,  3,  0,  9,  //
      -5, -2, -6, -3, //
      -4, 9,  6,  4,  //
      -7, 6,  6,  2   //
    };

    THEN("inverse(A) is the following 4x4 matrix:\
            \n| -0.04074 | -0.07778 |  0.14444 | -0.22222 |\
            \n| -0.07778 |  0.03333 |  0.36667 | -0.33333 |\
            \n| -0.02901 | -0.14630 | -0.10926 |  0.12963 |\
            \n|  0.17778 |  0.06667 | -0.26667 |  0.33333 |")
    {
      mat4 R = {
        -0.04074, -0.07778, 0.14444,  -0.22222, //
        -0.07778, 0.03333,  0.36667,  -0.33333, //
        -0.02901, -0.14630, -0.10926, 0.12963,  //
        0.17778,  0.06667,  -0.26667, 0.33333,  //
      };
      CHECK(R == inverse(A));
    }
  }
}

SCENARIO("Multiplying a product by its inverse")
{

  GIVEN("the following 4x4 matrix A:\
    \n|  3 | -9 |  7 |  3 |\
    \n|  3 | -8 |  2 | -9 |\
    \n| -4 |  4 |  4 |  1 |\
    \n| -6 |  5 | -1 |  1 |\n\
    AND the following 4x4 matrix B:\
    \n|  8 |  2 |  2 |  2 |\
    \n|  3 | -1 |  7 |  0 |\
    \n|  7 |  0 |  5 |  4 |\
    \n|  6 | -2 |  0 |  5 |\n\
    AND c = A * B")
  {
    mat4 A = {
      3,  -9, 7,  3,  //
      3,  -8, 2,  -9, //
      -4, 4,  4,  1,  //
      -6, 5,  -1, 1   //
    };

    mat4 B = {
      8, 2,  2, 2, //
      3, -1, 7, 0, //
      7, 0,  5, 4, //
      6, -2, 0, 5  //
    };

    auto C = A * B;

    THEN("C * inverse(B) == A") { CHECK(C * inverse(B) == A); }
  }
}

SCENARIO("Calculating the product of a matrix by its inverse")
{
  GIVEN("the following 4x4 matrix A:\
    \n|  9 |  3 |  0 |  9 |\
    \n| -5 | -2 | -6 | -3 |\
    \n| -4 |  9 |  6 |  4 |\
    \n| -7 |  6 |  6 |  2 |\n")
  {
    mat4 A = {
      9,  3,  0,  9,  //
      -5, -2, -6, -3, //
      -4, 9,  6,  4,  //
      -7, 6,  6,  2   //
    };

    THEN("A * inverse(A) == identity_matrix")
    {
      CHECK(A * inverse(A) == mat4::Identity());
    }
  }
}
