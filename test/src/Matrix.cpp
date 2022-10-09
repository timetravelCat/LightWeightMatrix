#define CATCH_CONFIG_MAIN
#include <float.h>
#include <math.h>

#include <LightWeightMatrix/Matrix.hpp>
#include <catch2/catch.hpp>

using namespace lwm;
using namespace lwm::internal;

TEST_CASE("Matrix", "[lwm::Matrix]")
{
  SECTION("toArray")
  {
    float arr[6] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
    lwm::Matrix<float, 2, 3> matrix{ arr };

    // Compile time error
    // float res[5];
    // matrix.toArray(res, size_t(1));

    float res[9];
    // matrix.toArray(res, 1);
    matrix.toArray<1>(res);
    REQUIRE(matrix(0, 0) == res[1 + 0]);
    REQUIRE(matrix(0, 1) == res[1 + 1]);
    REQUIRE(matrix(0, 2) == res[1 + 2]);
    REQUIRE(matrix(1, 0) == res[1 + 3]);
    REQUIRE(matrix(1, 1) == res[1 + 4]);
    REQUIRE(matrix(1, 2) == res[1 + 5]);

    // Compile time error
    // float temp[9];
    // matrix.toArray(temp, constexpr_size_t(4));

    // Compile time error
    // float res2_[2][3];
    // matrix.toArray(res2, constexpr_size_t(1), constexpr_size_t(0));

    float res2[3][5];
    matrix.toArray<1, 2>(res2);
    REQUIRE(matrix(0, 0) == res2[1 + 0][2 + 0]);
    REQUIRE(matrix(0, 1) == res2[1 + 0][2 + 1]);
    REQUIRE(matrix(0, 2) == res2[1 + 0][2 + 2]);
    REQUIRE(matrix(1)(0) == res2[1 + 1][2 + 0]);
    REQUIRE(matrix(1)(1) == res2[1 + 1][2 + 1]);
    REQUIRE(matrix(1)(2) == res2[1 + 1][2 + 2]);

    float res3[3][5];
    matrix.toArray(res3, size_t(1), size_t(2));
    REQUIRE(matrix(0)(0) == res3[1 + 0][2 + 0]);
    REQUIRE(matrix(0)(1) == res3[1 + 0][2 + 1]);
    REQUIRE(matrix(0)(2) == res3[1 + 0][2 + 2]);
    REQUIRE(matrix(1)(0) == res3[1 + 1][2 + 0]);
    REQUIRE(matrix(1)(1) == res3[1 + 1][2 + 1]);
    REQUIRE(matrix(1)(2) == res3[1 + 1][2 + 2]);

    // Compile time error
    // const auto& test = matrix[(0)][constexpr_size_t(10)];
    // matrix[constexpr_size_t(10)][constexpr_size_t(0)];
    // const auto& test = matrix(0)(constexpr_size_t(10));
    // matrix(constexpr_size_t(10))(constexpr_size_t(0));
  }
  SECTION("Constructor 1) explicit Matrix(const U (&in)[L])")
  {
    // Compile-time errors, error by casting type
    // float arr1_temp[5] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    // lwm::Matrix<uint32_t, 2, 3> matrix_temp{arr1_temp};
    // double arr2_temp[7] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };
    // lwm::Matrix<float, 2, 3> matrix_temp{arr2_temp};

    float arr[5] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
    // lwm::Matrix<float, 2, 3> matrix{ arr, 1 };
    lwm::Matrix<float, 2, 3> matrix{ arr, constexpr_size_t(1) };

    // matrix = arr;
    // REQUIRE(matrix(0, 0) == arr[0]);
    REQUIRE(matrix(0, 1) == arr[0]);
    REQUIRE(matrix(0, 2) == arr[1]);
    REQUIRE(matrix(1, 0) == arr[2]);
    REQUIRE(matrix(1, 1) == arr[3]);
    REQUIRE(matrix(1, 2) == arr[4]);
    // REQUIRE(matrix[0][0] == arr[0]);
    REQUIRE(matrix[0][1] == arr[0]);
    REQUIRE(matrix[0][2] == arr[1]);
    REQUIRE(matrix[1][0] == arr[2]);
    REQUIRE(matrix[1][1] == arr[3]);
    REQUIRE(matrix[1][2] == arr[4]);

    double arr2[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    lwm::Matrix<float, 2, 3> matrix2{ arr2 };
    matrix2 = arr2;
    REQUIRE(
        matrix2(constexpr_size_t(0), constexpr_size_t(0)) ==
        static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[0]));
    REQUIRE(
        matrix2(constexpr_size_t(0), constexpr_size_t(1)) ==
        static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[1]));
    REQUIRE(
        matrix2(constexpr_size_t(0), constexpr_size_t(2)) ==
        static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[2]));
    REQUIRE(
        matrix2(constexpr_size_t(1), constexpr_size_t(0)) ==
        static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[3]));
    REQUIRE(
        matrix2(constexpr_size_t(1), constexpr_size_t(1)) ==
        static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[4]));
    REQUIRE(
        matrix2[constexpr_size_t(0)][constexpr_size_t(0)] ==
        static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[0]));
    REQUIRE(
        matrix2[constexpr_size_t(0)][constexpr_size_t(1)] ==
        static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[1]));
    REQUIRE(
        matrix2[constexpr_size_t(0)][constexpr_size_t(2)] ==
        static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[2]));
    REQUIRE(
        matrix2[constexpr_size_t(1)][constexpr_size_t(0)] ==
        static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[3]));
    REQUIRE(
        matrix2[constexpr_size_t(1)][constexpr_size_t(1)] ==
        static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[4]));

    double arr3[1] = { 1.0 };
    lwm::Matrix<float, 2, 3> matrix3{ arr3 };
    matrix3 = arr3;
    REQUIRE(matrix3(0, 0) == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr3[0]));
    REQUIRE(matrix3[0][0] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr3[0]));

    int arr4[5] = { 1, 2, 3, 4, 5 };
    lwm::Matrix<float, 2, 3> matrix4{ arr4 };
    matrix4 = arr4;
    REQUIRE(matrix4(0, 0) == static_cast<lwm::internal::allowed_cast_t<float, int>>(arr4[0]));
    REQUIRE(matrix4(0, 1) == static_cast<lwm::internal::allowed_cast_t<float, int>>(arr4[1]));
    REQUIRE(matrix4(0, 2) == static_cast<lwm::internal::allowed_cast_t<float, int>>(arr4[2]));
    REQUIRE(matrix4(1, 0) == static_cast<lwm::internal::allowed_cast_t<float, int>>(arr4[3]));
    REQUIRE(matrix4(1, 1) == static_cast<lwm::internal::allowed_cast_t<float, int>>(arr4[4]));
    REQUIRE(matrix4[0][0] == static_cast<lwm::internal::allowed_cast_t<float, int>>(arr4[0]));
    REQUIRE(matrix4[0][1] == static_cast<lwm::internal::allowed_cast_t<float, int>>(arr4[1]));
    REQUIRE(matrix4[0][2] == static_cast<lwm::internal::allowed_cast_t<float, int>>(arr4[2]));
    REQUIRE(matrix4[1][0] == static_cast<lwm::internal::allowed_cast_t<float, int>>(arr4[3]));
    REQUIRE(matrix4[1][1] == static_cast<lwm::internal::allowed_cast_t<float, int>>(arr4[4]));
  }
  SECTION(
      "Constructor 2) explicit const U (&in)[M][N], Matrix(const U (&in)[R][C], type_ r_ = type_(0), type_ c_ = type_(0))")
  {
    float arr[2][3] = { { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f } };
    lwm::Matrix<float, 2, 3> matrix{ arr };
    matrix = arr;
    REQUIRE(matrix(0, 0) == arr[0][0]);
    REQUIRE(matrix(0, 1) == arr[0][1]);
    REQUIRE(matrix(0, 2) == arr[0][2]);
    REQUIRE(matrix(1, 0) == arr[1][0]);
    REQUIRE(matrix(1, 1) == arr[1][1]);
    REQUIRE(matrix(1, 2) == arr[1][2]);

    double arr2[2][3] = { { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 } };
    matrix = arr2;
    REQUIRE(matrix[0][0] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[0][0]));
    REQUIRE(matrix[0][1] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[0][1]));
    REQUIRE(matrix[0][2] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[0][2]));
    REQUIRE(matrix[1][0] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[1][0]));
    REQUIRE(matrix[1][1] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[1][1]));
    REQUIRE(matrix[1][2] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[1][2]));

    // check Compile time error
    // double arr3[3][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};

    double arr3[2][2] = { { 1.0, 2.0 }, { 3.0, 4.0 } };
    lwm::Matrix<float, 2, 3> matrix2{ arr3, uint16_t(0), uint16_t(0) };
    matrix2 = arr3;
    REQUIRE(matrix2[0][0] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr3[0][0]));
    REQUIRE(matrix2[0][1] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr3[0][1]));
    REQUIRE(matrix2[1][0] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr3[1][0]));
    REQUIRE(matrix2[1][1] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr3[1][1]));

    double arr4[2][2] = { { 1.0, 2.0 }, { 3.0, 4.0 } };
    lwm::Matrix<float, 4, 5> matrix3{ arr4, size_t(1), size_t(1) };
    REQUIRE(matrix3[1][1] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr4[0][0]));
    REQUIRE(matrix3[1][2] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr4[0][1]));
    REQUIRE(matrix3[2][1] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr4[1][0]));
    REQUIRE(matrix3[2][2] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr4[1][1]));

    // check Compile time error
    // float arr5[2][2] = { { 1.0, 2.0 }, { 3.0, 4.0 } };
    // lwm::Matrix<float, 4, 5> matrix4{ arr5, lwm::const_size_t<3>(),  lwm::const_size_t<2>()};

    float arr5[2][2] = { { 1.0, 2.0 }, { 3.0, 4.0 } };

    lwm::Matrix<float, 4, 5> matrix4{ arr5, lwm::const_size_t<1>(), lwm::const_size_t<1>() };
    REQUIRE(matrix3[1][1] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr4[0][0]));
    REQUIRE(matrix3[1][2] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr4[0][1]));
    REQUIRE(matrix3[2][1] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr4[1][0]));
    REQUIRE(matrix3[2][2] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr4[1][1]));
  }
  SECTION("Accessors(), []")
  {
    lwm::Matrix<float, 2, 2> matrix_;
    matrix_[0][1] = 2.0f;
    matrix_(1, 1) = 2.0f;
    REQUIRE(matrix_[0][1] == 2.0f);
    REQUIRE(matrix_[1][1] == 2.0f);
  }
  SECTION("fill, setRow, setCol, swap")
  {
    Matrix<double, 2, 3> matrix;
    matrix.fill(10.0f);
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 3; j++)
        REQUIRE(matrix[i][j] == 10.0);

    matrix.fill(10.0);
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 3; j++)
        REQUIRE(matrix[i][j] == 10.0);

    matrix.setRow(0, 1.0);
    for (int j = 0; j < 3; j++)
      REQUIRE(matrix[0][j] == 1.0);
    matrix.setRow(1, 2.0);
    for (int j = 0; j < 3; j++)
      REQUIRE(matrix[1][j] == 2.0);

    matrix.setRow<0>(1.0);
    for (int j = 0; j < 3; j++)
      REQUIRE(matrix[0][j] == 1.0);
    matrix.setRow<1>(2.0);
    for (int j = 0; j < 3; j++)
      REQUIRE(matrix[1][j] == 2.0);
    // matrix.setRow<2>(2.0f);

    matrix.setCol<0>(1.0);
    for (int j = 0; j < 2; j++)
      REQUIRE(matrix[j][0] == 1.0);
    matrix.setCol<1>(2.0);
    for (int j = 0; j < 2; j++)
      REQUIRE(matrix[j][1] == 2.0);
    matrix.setCol<2>(3.0);
    for (int j = 0; j < 2; j++)
      REQUIRE(matrix[j][2] == 3.0);
    // matrix.setCol<3>(2.0f);

    Matrix<double, 1, 3> row{ { 4.0, 5.0, 6.0 } };
    matrix.setRow<0>(row);
    matrix.setRow<1>(row);
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 3; j++)
        REQUIRE(matrix[i][j] == row[j]);
    // matrix.setRow<2>(row);

    Matrix<double, 1, 3> row2{ { 7.0, 8.0, 9.0 } };
    matrix.setRow(0, row2);
    matrix.setRow(1, row2);
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 3; j++)
        REQUIRE(matrix[i][j] == row2[j]);
    // matrix.setRow(2, row2);

    matrix.setRow<0>({ 1.0, 1.0, 1.0 });
    for (int j = 0; j < 3; j++)
      REQUIRE(matrix[0][j] == 1.0);
    matrix.setRow<1>({ 2.0, 2.0, 2.0 });
    for (int j = 0; j < 3; j++)
      REQUIRE(matrix[1][j] == 2.0);
    matrix.setRow(0, { 3.0, 3.0, 3.0 });
    for (int j = 0; j < 3; j++)
      REQUIRE(matrix[0][j] == 3.0);
    matrix.setRow(1, { 4.0, 4.0, 4.0 });
    for (int j = 0; j < 3; j++)
      REQUIRE(matrix[1][j] == 4.0);

    matrix.setRow<0>({ 1.0, 1.0, 1.0 });
    for (int j = 0; j < 3; j++)
      REQUIRE(matrix[0][j] == 1.0);
    matrix.setRow<1>({ 2.0, 2.0, 2.0 });
    for (int j = 0; j < 3; j++)
      REQUIRE(matrix[1][j] == 2.0);
    matrix.setRow(0, { 3.0, 3.0, 3.0 });
    for (int j = 0; j < 3; j++)
      REQUIRE(matrix[0][j] == 3.0);
    matrix.setRow(1, { 4.0, 4.0, 4.0 });
    for (int j = 0; j < 3; j++)
      REQUIRE(matrix[1][j] == 4.0);

    Matrix<double, 2, 1> col{ { 4.0, 5.0 } };
    matrix.setCol<0>(col);
    matrix.setCol<1>(col);
    matrix.setCol<2>(col);
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 2; j++)
        REQUIRE(matrix[j][i] == col[j]);

    Matrix<double, 2, 1> col2{ { 7.0, 8.0 } };
    matrix.setCol(0, col2);
    matrix.setCol(1, col2);
    matrix.setCol(2, col2);
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 2; j++)
        REQUIRE(matrix[j][i] == col2[j]);

    matrix.setCol<0>({ 1.0, 1.0 });
    for (int j = 0; j < 2; j++)
      REQUIRE(matrix[j][0] == 1.0);
    matrix.setCol<1>({ 2.0, 2.0 });
    for (int j = 0; j < 2; j++)
      REQUIRE(matrix[j][1] == 2.0);
    matrix.setCol(0, { 3.0, 3.0 });
    for (int j = 0; j < 2; j++)
      REQUIRE(matrix[j][0] == 3.0);
    matrix.setCol(1, { 4.0, 4.0 });
    for (int j = 0; j < 2; j++)
      REQUIRE(matrix[j][1] == 4.0);

    Matrix<double, 2, 2> swap_test{ { 1.0, 2.0, 3.0, 4.0 } };
    swap_test.swapCol(0, 1);
    REQUIRE(swap_test[0][0] == 2.0);
    REQUIRE(swap_test[0][1] == 1.0);
    REQUIRE(swap_test[1][0] == 4.0);
    REQUIRE(swap_test[1][1] == 3.0);
    swap_test.swapCol(0, 1);
    REQUIRE(swap_test[0][0] == 1.0);
    REQUIRE(swap_test[0][1] == 2.0);
    REQUIRE(swap_test[1][0] == 3.0);
    REQUIRE(swap_test[1][1] == 4.0);
    swap_test.swapRow(0, 1);
    REQUIRE(swap_test[0][0] == 3.0);
    REQUIRE(swap_test[0][1] == 4.0);
    REQUIRE(swap_test[1][0] == 1.0);
    REQUIRE(swap_test[1][1] == 2.0);
  }
  SECTION("transpose & cast & toRowVector, to toColVector")
  {
    float arr[2][3] = { { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f } };
    Matrix<float, 2, 3> matrix{ arr };

    Matrix<float, 3, 2> transposed = matrix.transpose();
    Matrix<float, 3, 2> transposed_;
    transposed_ = matrix.transpose();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 3; j++)
        REQUIRE(transposed[j][i] == matrix[i][j]);

    Matrix<double, 3, 2> transposed2{ matrix.transpose() };
    Matrix<double, 3, 2> transposed2_;
    transposed2_ = matrix.transpose();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 3; j++)
        REQUIRE(transposed2[j][i] == static_cast<double>(matrix[i][j]));

    Matrix<double, 3, 2> transposed3 = matrix.transpose();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 3; j++)
        REQUIRE(transposed3[j][i] == static_cast<double>(matrix[i][j]));

    Matrix<uint32_t, 2, 3> casted = matrix.cast<uint32_t>();
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 3; j++)
        REQUIRE(casted[i][j] == static_cast<uint32_t>(matrix[i][j]));

    Matrix<int, 1, 3> test{ { 1, 2, 3 } };
    Matrix<int, 3, 1> test2 = test.toRowVector();
    REQUIRE(test2[0] == 1);
    REQUIRE(test2[1] == 2);
    REQUIRE(test2[2] == 3);
    Matrix<int, 1, 3> test3 = test2.toColVector();
    REQUIRE(test3[0] == 1);
    REQUIRE(test3[1] == 2);
    REQUIRE(test3[2] == 3);
  }
  SECTION("slice")
  {
    float arr[6] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
    Matrix<float, 2, 3> matrix1{ { { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f } } };
    Matrix<float, 2, 3> matrix2{ arr };
    for (size_t i = 0; i < 2; i++)
      for (size_t j = 0; j < 3; j++)
        REQUIRE(matrix2[i][j] == matrix1[i][j]);

    auto sliced = matrix2.slice<1, 2, 1, 1>();
    for (size_t i = 0; i < 1; i++)
      for (size_t j = 0; j < 2; j++)
        REQUIRE(sliced[j] == matrix1[i + 1][j + 1]);

    auto rowvec = matrix1.row<0>();
    auto rowvec2 = matrix1.row<1>();
    // auto rowvec2 = matrix1.row<2>();
    for (size_t i = 0; i < 3; i++)
      REQUIRE(rowvec[i] == matrix1[0][i]);
    for (size_t i = 0; i < 3; i++)
      REQUIRE(rowvec2[i] == matrix1[1][i]);

    auto rowvec3 = matrix1.row(0);
    auto rowvec4 = matrix1.row(1);
    // auto rowvec2 = matrix1.row<2>();
    for (size_t i = 0; i < 3; i++)
      REQUIRE(rowvec3[i] == matrix1[0][i]);
    for (size_t i = 0; i < 3; i++)
      REQUIRE(rowvec4[i] == matrix1[1][i]);

    auto colvec1 = matrix1.col<0>();
    auto colvec2 = matrix1.col<1>();
    auto colvec3 = matrix1.col<2>();
    // auto colvec3 = matrix1.col<3>();
    for (size_t i = 0; i < 2; i++)
    {
      REQUIRE(colvec1[i] == matrix1[i][0]);
      REQUIRE(colvec2[i] == matrix1[i][1]);
      REQUIRE(colvec3[i] == matrix1[i][2]);
    }

    auto colvec4 = matrix1.col(0);
    auto colvec5 = matrix1.col(1);
    auto colvec6 = matrix1.col(2);
    // auto colvec3 = matrix1.col<3>();
    for (size_t i = 0; i < 2; i++)
    {
      REQUIRE(colvec4[i] == matrix1[i][0]);
      REQUIRE(colvec5[i] == matrix1[i][1]);
      REQUIRE(colvec6[i] == matrix1[i][2]);
    }
  }
  SECTION("Vector Accessor & Operator TEST when N==1 or M == 1")
  {
    Matrix<int, 1, 1> value{ { 7 } };
    Matrix<int, 1, 6> value2{ { 1, 2, 3, 4, 5, 6 } };
    Matrix<int, 6, 1> value3{ { 1, 2, 3, 4, 5, 6 } };

    REQUIRE(value2(constexpr_size_t(0)) == 1);
    REQUIRE(value2(constexpr_size_t(1)) == 2);
    REQUIRE(value2(constexpr_size_t(2)) == 3);
    REQUIRE(value2(constexpr_size_t(3)) == 4);
    REQUIRE(value2(constexpr_size_t(4)) == 5);
    REQUIRE(value2(constexpr_size_t(5)) == 6);
    REQUIRE(value3(constexpr_size_t(0)) == 1);
    REQUIRE(value3(constexpr_size_t(1)) == 2);
    REQUIRE(value3(constexpr_size_t(2)) == 3);
    REQUIRE(value3(constexpr_size_t(3)) == 4);
    REQUIRE(value3(constexpr_size_t(4)) == 5);
    REQUIRE(value3(constexpr_size_t(5)) == 6);

    for (int i = 0; i < 4; i++)
    {
      REQUIRE(value() == 7);
      REQUIRE(value2(i) == (i + 1));
      REQUIRE(value3(i) == (i + 1));
      REQUIRE((i + 1) == value2(i));
      REQUIRE((i + 1) == value3(i));

      REQUIRE((i + 1) == value2[i]);
      REQUIRE((i + 1) == value3[i]);
      REQUIRE(value2[i] == (i + 1));
      REQUIRE(value3[i] == (i + 1));

      REQUIRE(value(0, 0) == 7);
      // REQUIRE(test_int[i][0] == const_test_int[i][0]);
    }
  }
  SECTION("static functions")
  {
    auto test = Matrix<int, 3, 3>::Zero();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        REQUIRE(test(i, j) == 0);

    auto test2 = Matrix<double, 3, 3>::Zero();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        REQUIRE(test2(i, j) == 0.0);

    // Matrix<int, 3,3>::NaN();
    auto test3 = Matrix<float, 3, 3>::NaN();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        REQUIRE(isnan(test3[i][j]));

    auto test4 = Matrix<float, 3, 4>::Identity();
    for (int i = 0; i < 3; i++)
      REQUIRE(test4[i][i] == 1.0f);
  }
  SECTION("mathmatical operations")
  {
    Matrix<int, 2, 1> mat_l1{ { 1, 2 } };
    Matrix<int, 1, 2> mat_l2{ { 3, 4 } };
    Matrix<int, 2, 2> mat = mat_l1 * mat_l2;
    REQUIRE(mat[0][0] == 3);
    REQUIRE(mat[0][1] == 4);
    REQUIRE(mat[1][0] == 6);
    REQUIRE(mat[1][1] == 8);

    Matrix<int, 2, 1> mat__l1{ { 1, 2 } };
    Matrix<double, 1, 2> mat__l2{ { 3.0, 4.0 } };
    Matrix<double, 2, 2> mat_ = (mat__l1 * mat__l2);
    REQUIRE(mat_[0][0] == 1.0 * 3.0);
    REQUIRE(mat_[0][1] == 1.0 * 4.0);
    REQUIRE(mat_[1][0] == 2.0 * 3.0);
    REQUIRE(mat_[1][1] == 2.0 * 4.0);

    Matrix<int, 2, 1> mat___l1{ { 1.0, 2.0 } };
    Matrix<double, 1, 2> mat___l2{ { 3.0, 4.0 } };
    Matrix<float, 2, 2> mat__ = (mat___l1 * mat___l2).cast<float>();
    REQUIRE(mat__[0][0] == static_cast<float>(1.0 * 3.0));
    REQUIRE(mat__[0][1] == static_cast<float>(1.0 * 4.0));
    REQUIRE(mat__[1][0] == static_cast<float>(2.0 * 3.0));
    REQUIRE(mat__[1][1] == static_cast<float>(2.0 * 4.0));

    // mat__ += 1.0f;
    // mat__ += Matrix<double, 2,2>::Constant(1.0).cast<float>();
    mat__ = 1.0f + mat__;
    REQUIRE(mat__[0][0] == static_cast<float>(1.0 * 3.0 + 1.0));
    REQUIRE(mat__[0][1] == static_cast<float>(1.0 * 4.0 + 1.0));
    REQUIRE(mat__[1][0] == static_cast<float>(2.0 * 3.0 + 1.0));
    REQUIRE(mat__[1][1] == static_cast<float>(2.0 * 4.0 + 1.0));

    // mat__ -= 1.0f;
    mat__ -= Matrix<double, 2, 2>::Constant(1.0).cast<float>();
    REQUIRE(mat__[0][0] == static_cast<float>(1.0 * 3.0));
    REQUIRE(mat__[0][1] == static_cast<float>(1.0 * 4.0));
    REQUIRE(mat__[1][0] == static_cast<float>(2.0 * 3.0));
    REQUIRE(mat__[1][1] == static_cast<float>(2.0 * 4.0));

    // mat__ *= 2.0f;
    // mat__ *= Matrix<double, 2,2>::Identity().cast<float>()*2.0f;
    mat__ *= 2.0f * Matrix<double, 2, 2>::Identity().cast<float>();
    REQUIRE(mat__[0][0] == static_cast<float>(1.0 * 3.0 * 2.0));
    REQUIRE(mat__[0][1] == static_cast<float>(1.0 * 4.0 * 2.0));
    REQUIRE(mat__[1][0] == static_cast<float>(2.0 * 3.0 * 2.0));
    REQUIRE(mat__[1][1] == static_cast<float>(2.0 * 4.0 * 2.0));

    mat__ /= 2.0f;
    REQUIRE(mat__[0][0] == static_cast<float>(1.0 * 3.0));
    REQUIRE(mat__[0][1] == static_cast<float>(1.0 * 4.0));
    REQUIRE(mat__[1][0] == static_cast<float>(2.0 * 3.0));
    REQUIRE(mat__[1][1] == static_cast<float>(2.0 * 4.0));

    Matrix<float, 2, 2> mat___ = Matrix<double, 2, 2>::Constant(2.0);
    Matrix<float, 2, 2> mat____ = mat___.elementWiseMultiply(Matrix<double, 2, 2>::Constant(2.0).cast<float>());
    REQUIRE(mat____[0][0] == 4.0f);
    REQUIRE(mat____[0][1] == 4.0f);
    REQUIRE(mat____[1][0] == 4.0f);
    REQUIRE(mat____[1][1] == 4.0f);

    Matrix<double, 2, 2> test_mat{ { -1.0, 3.0, 4.0, 2.0 } };
    Matrix<double, 2, 2> test_mat_abs = test_mat.abs();
    REQUIRE(test_mat_abs[0][0] == 1.0);
    REQUIRE(test_mat_abs[0][1] == 3.0);
    REQUIRE(test_mat_abs[1][0] == 4.0);
    REQUIRE(test_mat_abs[1][1] == 2.0);
    REQUIRE(test_mat.max() == 4.0);
    REQUIRE(test_mat.min() == -1.0);

    Matrix<float, 2, 2> test_mat_nan1{ { -1.0f, 2.0f, 4.0f, 2.0f } };
    REQUIRE(test_mat_nan1.max() == 4.0f);
    REQUIRE(test_mat_nan1.min() == -1.0f);
    REQUIRE(!test_mat_nan1.isAllNan());
    test_mat_nan1[0][0] = NAN;
    REQUIRE(!test_mat_nan1.isAllNan());
    REQUIRE(test_mat_nan1.isAnyNan());

    Matrix<float, 2, 2> test_mat_nan2{ { -NAN, NAN, NAN, NAN } };
    REQUIRE(test_mat_nan2.isAllNan());
    REQUIRE(test_mat_nan2.isAnyNan());
  }
  SECTION("Trace, inverse")
  {
    Matrix<double, 4, 4> wow = Matrix<double, 4, 4>::Constant(2.0);
    wow[0][0] = 3.0;
    wow[1][1] = 5.0;
    REQUIRE(wow.trace() == 2.0 + 2.0 + 3.0 + 5.0);

    Matrix<double, 1, 1> test{ { 3.0 } };
    REQUIRE(test.inv()() == 1.0 / 3.0);
    test() = NAN;
    REQUIRE(isnan(test.inv()()));
    test() = INFINITY;
    REQUIRE(isnan(test.inv()()));

    Matrix<double, 2, 2> test2{ { 1.0, 2.0, 3.0, 4.0 } };
    Matrix<double, 2, 2> test2_inv = test2.inv();
    double det = test2[0][0] * test2[1][1] - test2[1][0] * test2[0][1];
    REQUIRE((test2_inv[0][0] == test2[1][1] / det));
    REQUIRE((test2_inv[0][1] == -test2[0][1] / det));
    REQUIRE((test2_inv[1][0] == -test2[1][0] / det));
    REQUIRE((test2_inv[1][1] == test2[0][0] / det));

    Matrix<double, 2, 2> test3{ { nan(""), 2.0, 3.0, 4.0 } };
    test3 = test3.inv();
    REQUIRE(isnan(test3[0][0]));
    REQUIRE(isnan(test3[0][1]));
    REQUIRE(isnan(test3[1][0]));
    REQUIRE(isnan(test3[1][1]));
  }
  SECTION("diag, cholesky decomposition, Moore-Penrose Inverse")
  {
    Matrix<double, 3UL, 1UL> diag = Matrix<double, 3, 3>{ { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 } }.diag();
    REQUIRE(diag[0] == 1.0);
    REQUIRE(diag[1] == 5.0);
    REQUIRE(diag[2] == 9.0);

    size_t rank;
    Matrix<double, 3UL, 3UL> cholesky =
        Matrix<double, 3UL, 3UL>{ { 4.0, 12.0, -16.0, 12.0, 37.0, -43.0, -16.0, -43.0, 98.0 } }.choleskyDecomposition(rank);

    REQUIRE(rank == 3);
    REQUIRE(cholesky[0][0] == 2.0);
    REQUIRE(cholesky[0][1] == 0.0);
    REQUIRE(cholesky[0][2] == 0.0);
    REQUIRE(cholesky[1][0] == 6.0);
    REQUIRE(cholesky[1][1] == 1.0);
    REQUIRE(cholesky[1][2] == 0.0);
    REQUIRE(cholesky[2][0] == -8.0);
    REQUIRE(cholesky[2][1] == 5.0);
    REQUIRE(cholesky[2][2] == 3.0);

    Matrix<double, 3, 2> pinv = Matrix<double, 2, 3>{ { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 } }.pinv();

    REQUIRE(isSame(pinv[0][0], -17.0 / 18.0));
    REQUIRE(isSame(pinv[0][1], 8.0 / 18.0));
    REQUIRE(isSame(pinv[1][0], -2.0 / 18.0));
    REQUIRE(isSame(pinv[1][1], 2.0 / 18.0));
    REQUIRE(isSame(pinv[2][0], 13.0 / 18.0));
    REQUIRE(isSame(pinv[2][1], -4.0 / 18.0));
  }

  SECTION("Rotation Matrix")
  {
    Matrix<double, 3UL, 3UL> rotmat{ { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 } };
    auto vee = rotmat.vee();
    REQUIRE(vee[0] == -rotmat[1][2]);
    REQUIRE(vee[1] == rotmat[0][2]);
    REQUIRE(vee[2] == -rotmat[0][1]);
  }
  SECTION("Vector Operations")
  {
     Matrix<double, 3UL, 1UL> l{{1.0, 2.0, 3.0}};
     Matrix<double, 3UL, 1UL> r{{2.0, 3.0, 4.0}};
     REQUIRE(l.dot(r) == 1.0*2.0+2.0*3.0+3.0*4.0);
     REQUIRE(l.norm() == sqrt(1.0*1.0+2.0*2.0+3.0*3.0));
     REQUIRE(l.normSquared() == (1.0*1.0+2.0*2.0+3.0*3.0));


    Matrix<double, 3UL, 1UL> mat = Matrix<double, 3UL, 1UL>::Zero();
    REQUIRE(isnan(mat.unit()[0]));
    mat = l.unit();
    REQUIRE(mat[0] == l[0]/l.norm());
    REQUIRE(mat[1] == l[1]/l.norm());
    REQUIRE(mat[2] == l[2]/l.norm());
  }

}
