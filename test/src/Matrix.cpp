#define CATCH_CONFIG_MAIN
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
    matrix.toArray(res, 1);
    // matrix.toArray(res, constexpr_size_t(1));
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
    matrix.toArray(res2, constexpr_size_t(1), constexpr_size_t(2));
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
    REQUIRE(matrix2(0, 0) == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[0]));
    REQUIRE(matrix2(0, 1) == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[1]));
    REQUIRE(matrix2(0, 2) == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[2]));
    REQUIRE(matrix2(1, 0) == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[3]));
    REQUIRE(matrix2(1, 1) == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[4]));
    REQUIRE(matrix2[0][0] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[0]));
    REQUIRE(matrix2[0][1] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[1]));
    REQUIRE(matrix2[0][2] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[2]));
    REQUIRE(matrix2[1][0] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[3]));
    REQUIRE(matrix2[1][1] == static_cast<lwm::internal::allowed_cast_t<float, double>>(arr2[4]));

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
  SECTION("fill")
  {
    Matrix<double, 2, 3> matrix;
    matrix.fill(10.0f);
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 3; j++)
        REQUIRE(matrix[i][j] == 10.0);

    // Compile time error
    // Matrix<uint32_t, 2, 3> matrix2;
    // matrix2.fill(10.0);
  }
  SECTION("transpose & cast")
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
        REQUIRE(sliced[i][j] == matrix1[i + 1][j + 1]);

    // auto rowvec = matrix1.row<0>();
    // auto rowvec2 = matrix1.row<1>();
    // // auto rowvec2 = matrix1.row<2>();
    // for (size_t i = 0; i < 3; i++)
    //   REQUIRE(rowvec[0][i] == matrix1[0][i]);
    // for (size_t i = 0; i < 3; i++)
    //   REQUIRE(rowvec2[0][i] == matrix1[1][i]);

    // auto colvec1 = matrix1.col<0>();
    // auto colvec2 = matrix1.col<1>();
    // auto colvec3 = matrix1.col<2>();
    // // auto colvec3 = matrix1.col<3>();
    // for (size_t i = 0; i < 2; i++)
    // {
    //   REQUIRE(colvec1[i][0] == matrix1[i][0]);
    //   REQUIRE(colvec2[i][0] == matrix1[i][1]);
    //   REQUIRE(colvec3[i][0] == matrix1[i][2]);
    // }
  }
  SECTION("Vector Accessor & Operator TEST when N==1")
  {
    // for double type testing
    double arr[4] = { 1.0, 2.0, 3.0, 4.0 };
    const double const_arr[4] = { 1.0, 2.0, 3.0, 4.0 };
    Matrix<double, 4, 1> test{ arr };
    Matrix<double, 5, 1> test_comp{ arr };
    Matrix<double, 5, 2> test_comp_ref{ const_arr };

    const Matrix<double, 4, 1> const_test{ arr };
    const Matrix<double, 5, 1> const_test_comp{ arr };
    const Matrix<double, 5, 2> const_test_comp_ref{ arr };
    
    // for int type testing
    int arr_int[4] = { 1, 2, 3, 4 };
    const int const_arr_int[4] = { 1, 2, 3, 4 };

    Matrix<int, 4, 1> test_int{ arr_int };
    Matrix<int, 5, 1> test_int_comp{ arr_int };
    Matrix<int, 5, 2> test_int_comp_ref{ const_arr_int };

    const Matrix<int, 4, 1> const_test_int{ arr_int };
    const Matrix<int, 5, 1> const_test_int_comp{ arr_int };
    const Matrix<int, 5, 2> const_test_int_comp_ref{ const_arr_int };
    

    for (int i = 0; i < 4; i++)
    {
      // ==
      REQUIRE(test_comp[i] == static_cast<double>(i+1));
      REQUIRE(const_test_comp[i] == static_cast<double>(i+1));
      REQUIRE(test[i] == test_comp[i]);
      REQUIRE(test[i] == const_test_comp[i]);
      REQUIRE(const_test_comp[i] == const_test[i]);
      REQUIRE(const_test_comp[i] == test_comp[i]);
      REQUIRE(test[i] == arr[i]);
      REQUIRE(test[i] == const_arr[i]);
      REQUIRE(test_comp[i] == arr[i]);
      REQUIRE(test_comp[i] == const_arr[i]);
      REQUIRE(static_cast<double>(i+1) == test[i]);
      REQUIRE(static_cast<double>(i+1) == const_test[i]);
      REQUIRE(arr[i] == test[i]);
      REQUIRE(arr[i] == const_test[i]);
      REQUIRE(const_arr[i] == test[i]);
      REQUIRE(const_arr[i] == const_test[i]);

      REQUIRE((test_comp[i] != static_cast<double>(i+1)) == false);
      REQUIRE((const_test_comp[i] != static_cast<double>(i+1)) == false);
      REQUIRE((test[i] != test_comp[i]) == false);
      REQUIRE((test[i] != const_test_comp[i]) == false);
      REQUIRE((const_test_comp[i] != const_test[i]) == false);
      REQUIRE((const_test_comp[i] != test_comp[i]) == false);
      REQUIRE((test[i] != arr[i]) == false);
      REQUIRE((test[i] != const_arr[i]) == false);
      REQUIRE((test_comp[i] != arr[i]) == false);
      REQUIRE((test_comp[i] != const_arr[i]) == false);
      REQUIRE((static_cast<double>(i+1) != test[i]) == false);
      REQUIRE((static_cast<double>(i+1) != const_test[i]) == false);
      REQUIRE((arr[i] != test[i]) == false);
      REQUIRE((arr[i] != const_test[i]) == false);
      REQUIRE((const_arr[i] != test[i]) == false);
      REQUIRE((const_arr[i] != const_test[i]) == false);

      // = 
      (test_comp[i] = static_cast<double>(i+1));
      REQUIRE(test_comp[i] == static_cast<double>(i+1));
      test[i] = test_comp[i];
      REQUIRE(test[i] == test_comp[i]);
      test[i] = const_test_comp[i];
      REQUIRE(test[i] == const_test_comp[i]);
      test[i] = arr[i];
      REQUIRE(test[i] == arr[i]);
      test[i] = const_arr[i];
      REQUIRE(test[i] == const_arr[i]);

      arr[i] = test[i].value();
      // arr[i] = test[i]; -> not possible.
      REQUIRE(test[i] == arr[i]);
      arr[i] = const_test[i].value();
      REQUIRE(test[i] == const_arr[i]);

      // +

      REQUIRE((test[i] + 1.0) == (arr[i] + 1.0));
      REQUIRE((test(i) + 1.0) == (arr[i] + 1.0));
      REQUIRE((arr[i] + 1.0) == (test[i] + 1.0));
      REQUIRE((arr[i] + 1.0) == (test(i) + 1.0));
      REQUIRE((const_test[i] + 1.0) == (const_arr[i] + 1.0));
      REQUIRE((const_test(i) + 1.0) == (const_arr[i] + 1.0));
      REQUIRE((const_arr[i] + 1.0) == (const_test[i] + 1.0));
      REQUIRE((const_arr[i] + 1.0) == (const_test(i) + 1.0));

      REQUIRE((1.0 + test[i]) == (1.0 + arr[i]));
      REQUIRE((1.0 + test(i)) == (1.0 + arr[i]));
      REQUIRE((1.0 + arr[i]) == (1.0 + test[i]));
      REQUIRE((1.0 + arr[i]) == (1.0 + test(i)));
      REQUIRE((1.0 + const_test[i]) == (1.0 + const_arr[i]));
      REQUIRE((1.0 + const_test(i)) == (1.0 + const_arr[i]));
      REQUIRE((1.0 + const_arr[i]) == (1.0 + const_test[i]));
      REQUIRE((1.0 + const_arr[i]) == (1.0 + const_test(i)));

      REQUIRE((arr[i] + test[i]) == (arr[i] + arr[i]));
      REQUIRE((arr[i] + test(i)) == (arr[i] + arr[i]));
      REQUIRE((arr[i] + arr[i]) == (arr[i] + test[i]));
      REQUIRE((arr[i] + arr[i]) == (arr[i] + test(i)));
      REQUIRE((const_arr[i] + const_test[i]) == (const_arr[i] + const_arr[i]));
      REQUIRE((const_arr[i] + const_test(i)) == (const_arr[i] + const_arr[i]));
      REQUIRE((const_arr[i] + const_arr[i]) == (const_arr[i] + const_test[i]));
      REQUIRE((const_arr[i] + const_arr[i]) == (const_arr[i] + const_test(i)));

      REQUIRE((test_comp[i] + test[i]) == (test_comp[i] + arr[i]));
      REQUIRE((test_comp[i] + test(i)) == (test_comp[i] + arr[i]));
      REQUIRE((test_comp[i] + const_test[i]) == (test_comp[i] + const_arr[i]));
      REQUIRE((test_comp[i] + const_test(i)) == (test_comp[i] + const_arr[i]));
      REQUIRE((test_comp[i] + const_test[i]) == (arr[i] + const_arr[i]));
      REQUIRE((test_comp[i] + const_test(i)) == (arr[i] + const_arr[i]));
      REQUIRE((const_test[i] + const_test[i]) == (const_test[i] + const_arr[i]));
      REQUIRE((const_test[i] + const_test(i)) == (const_test[i] + const_arr[i]));

      // -
      REQUIRE((test[i] - 1.0) == (arr[i] - 1.0));
      REQUIRE((test(i) - 1.0) == (arr[i] - 1.0));
      REQUIRE((arr[i] - 1.0) == (test[i] - 1.0));
      REQUIRE((arr[i] - 1.0) == (test(i) - 1.0));
      REQUIRE((const_test[i] - 1.0) == (const_arr[i] - 1.0));
      REQUIRE((const_test(i) - 1.0) == (const_arr[i] - 1.0));
      REQUIRE((const_arr[i] - 1.0) == (const_test[i] - 1.0));
      REQUIRE((const_arr[i] - 1.0) == (const_test(i) - 1.0));

      REQUIRE((1.0 - test[i]) == (1.0 - arr[i]));
      REQUIRE((1.0 - test(i)) == (1.0 - arr[i]));
      REQUIRE((1.0 - arr[i]) == (1.0 - test[i]));
      REQUIRE((1.0 - arr[i]) == (1.0 - test(i)));
      REQUIRE((1.0 - const_test[i]) == (1.0 - const_arr[i]));
      REQUIRE((1.0 - const_test(i)) == (1.0 - const_arr[i]));
      REQUIRE((1.0 - const_arr[i]) == (1.0 - const_test[i]));
      REQUIRE((1.0 - const_arr[i]) == (1.0 - const_test(i)));

      REQUIRE((arr[i] - test[i]) == (arr[i] - arr[i]));
      REQUIRE((arr[i] - test(i)) == (arr[i] - arr[i]));
      REQUIRE((arr[i] - arr[i]) == (arr[i] - test[i]));
      REQUIRE((arr[i] - arr[i]) == (arr[i] - test(i)));
      REQUIRE((const_arr[i] - const_test[i]) == (const_arr[i] - const_arr[i]));
      REQUIRE((const_arr[i] - const_test(i)) == (const_arr[i] - const_arr[i]));
      REQUIRE((const_arr[i] - const_arr[i]) == (const_arr[i] - const_test[i]));
      REQUIRE((const_arr[i] - const_arr[i]) == (const_arr[i] - const_test(i)));

      REQUIRE((test_comp[i] - test[i]) == (test_comp[i] - arr[i]));
      REQUIRE((test_comp[i] - test(i)) == (test_comp[i] - arr[i]));
      REQUIRE((test_comp[i] - const_test[i]) == (test_comp[i] - const_arr[i]));
      REQUIRE((test_comp[i] - const_test(i)) == (test_comp[i] - const_arr[i]));
      REQUIRE((const_test[i] - const_test[i]) == (const_test[i] - const_arr[i]));
      REQUIRE((const_test[i] - const_test(i)) == (const_test[i] - const_arr[i]));

      // *
      REQUIRE((test[i] * 2.1) == (arr[i] * 2.1));
      REQUIRE((test(i) * 2.1) == (arr[i] * 2.1));
      REQUIRE((arr[i] * 2.1) == (test[i] * 2.1));
      REQUIRE((arr[i] * 2.1) == (test(i) * 2.1));
      REQUIRE((const_test[i] * 2.1) == (const_arr[i] * 2.1));
      REQUIRE((const_test(i) * 2.1) == (const_arr[i] * 2.1));
      REQUIRE((const_arr[i] * 2.1) == (const_test[i] * 2.1));
      REQUIRE((const_arr[i] * 2.1) == (const_test(i) * 2.1));

      REQUIRE((2.1 * test[i]) == (2.1 * arr[i]));
      REQUIRE((2.1 * test(i)) == (2.1 * arr[i]));
      REQUIRE((2.1 * arr[i]) == (2.1 * test[i]));
      REQUIRE((2.1 * arr[i]) == (2.1 * test(i)));
      REQUIRE((2.1 * const_test[i]) == (2.1 * const_arr[i]));
      REQUIRE((2.1 * const_test(i)) == (2.1 * const_arr[i]));
      REQUIRE((2.1 * const_arr[i]) == (2.1 * const_test[i]));
      REQUIRE((2.1 * const_arr[i]) == (2.1 * const_test(i)));

      REQUIRE((arr[i] * test[i]) == (arr[i] * arr[i]));
      REQUIRE((arr[i] * test(i)) == (arr[i] * arr[i]));
      REQUIRE((arr[i] * arr[i]) == (arr[i] * test[i]));
      REQUIRE((arr[i] * arr[i]) == (arr[i] * test(i)));
      REQUIRE((const_arr[i] * const_test[i]) == (const_arr[i] * const_arr[i]));
      REQUIRE((const_arr[i] * const_test(i)) == (const_arr[i] * const_arr[i]));
      REQUIRE((const_arr[i] * const_arr[i]) == (const_arr[i] * const_test[i]));
      REQUIRE((const_arr[i] * const_arr[i]) == (const_arr[i] * const_test(i)));
    
      
      REQUIRE((test_comp[i] * test[i]) == (test_comp[i] * arr[i]));
      REQUIRE((test_comp[i] * test(i)) == (test_comp[i] * arr[i]));
      REQUIRE((test_comp[i] * const_test[i]) == (test_comp[i] * const_arr[i]));
      REQUIRE((test_comp[i] * const_test(i)) == (test_comp[i] * const_arr[i]));
      REQUIRE((const_test[i] * const_test[i]) == (const_test[i] * const_arr[i]));
      REQUIRE((const_test[i] * const_test(i)) == (const_test[i] * const_arr[i]));

      // /
      REQUIRE((test[i] / 2.1) == (arr[i] / 2.1));
      REQUIRE((test(i) / 2.1) == (arr[i] / 2.1));
      REQUIRE((arr[i] / 2.1) == (test[i] / 2.1));
      REQUIRE((arr[i] / 2.1) == (test(i) / 2.1));
      REQUIRE((const_test[i] / 2.1) == (const_arr[i] / 2.1));
      REQUIRE((const_test(i) / 2.1) == (const_arr[i] / 2.1));
      REQUIRE((const_arr[i] / 2.1) == (const_test[i] / 2.1));
      REQUIRE((const_arr[i] / 2.1) == (const_test(i) / 2.1));

      REQUIRE((2.1 / test[i]) == (2.1 / arr[i]));
      REQUIRE((2.1 / test(i)) == (2.1 / arr[i]));
      REQUIRE((2.1 / arr[i]) == (2.1 / test[i]));
      REQUIRE((2.1 / arr[i]) == (2.1 / test(i)));
      REQUIRE((2.1 / const_test[i]) == (2.1 / const_arr[i]));
      REQUIRE((2.1 / const_test(i)) == (2.1 / const_arr[i]));
      REQUIRE((2.1 / const_arr[i]) == (2.1 / const_test[i]));
      REQUIRE((2.1 / const_arr[i]) == (2.1 / const_test(i)));

      REQUIRE((arr[i] / test[i]) == (arr[i] / arr[i]));
      REQUIRE((arr[i] / test(i)) == (arr[i] / arr[i]));
      REQUIRE((arr[i] / arr[i]) == (arr[i] / test[i]));
      REQUIRE((arr[i] / arr[i]) == (arr[i] / test(i)));
      REQUIRE((const_arr[i] / const_test[i]) == (const_arr[i] / const_arr[i]));
      REQUIRE((const_arr[i] / const_test(i)) == (const_arr[i] / const_arr[i]));
      REQUIRE((const_arr[i] / const_arr[i]) == (const_arr[i] / const_test[i]));
      REQUIRE((const_arr[i] / const_arr[i]) == (const_arr[i] / const_test(i)));

      REQUIRE((test_comp[i] / test[i]) == (test_comp[i] / arr[i]));
      REQUIRE((test_comp[i] / test(i)) == (test_comp[i] / arr[i]));
      REQUIRE((test_comp[i] / const_test[i]) == (test_comp[i] / const_arr[i]));
      REQUIRE((test_comp[i] / const_test(i)) == (test_comp[i] / const_arr[i]));
      REQUIRE((const_test[i] / const_test[i]) == (const_test[i] / const_arr[i]));
      REQUIRE((const_test[i] / const_test(i)) == (const_test[i] / const_arr[i]));

      // %
      REQUIRE((test_int[i] % 2) == (arr_int[i] % 2));
      REQUIRE((test_int(i) % 2) == (arr_int[i] % 2));
      REQUIRE((arr_int[i] % 2) == (test_int[i] % 2));
      REQUIRE((arr_int[i] % 2) == (test_int(i) % 2));
      REQUIRE((const_test_int[i] % 2) == (const_arr_int[i] % 2));
      REQUIRE((const_test_int(i) % 2) == (const_arr_int[i] % 2));
      REQUIRE((const_arr_int[i] % 2) == (const_test_int[i] % 2));
      REQUIRE((const_arr_int[i] % 2) == (const_test_int(i) % 2));

      REQUIRE((2 % test_int[i]) == (2 % arr_int[i]));
      REQUIRE((2 % test_int(i)) == (2 % arr_int[i]));
      REQUIRE((2 % arr_int[i]) == (2 % test_int[i]));
      REQUIRE((2 % arr_int[i]) == (2 % test_int(i)));
      REQUIRE((2 % const_test_int[i]) == (2 % const_arr_int[i]));
      REQUIRE((2 % const_test_int(i)) == (2 % const_arr_int[i]));
      REQUIRE((2 % const_arr_int[i]) == (2 % const_test_int[i]));
      REQUIRE((2 % const_arr_int[i]) == (2 % const_test_int(i)));

      REQUIRE((arr_int[i] % test_int[i]) == (arr_int[i] % arr_int[i]));
      REQUIRE((arr_int[i] % test_int(i)) == (arr_int[i] % arr_int[i]));
      REQUIRE((arr_int[i] % arr_int[i]) == (arr_int[i] % test_int[i]));
      REQUIRE((arr_int[i] % arr_int[i]) == (arr_int[i] % test_int(i)));
      REQUIRE((const_arr_int[i] % const_test_int[i]) == (const_arr_int[i] % const_arr_int[i]));
      REQUIRE((const_arr_int[i] % const_test_int(i)) == (const_arr_int[i] % const_arr_int[i]));
      REQUIRE((const_arr_int[i] % const_arr_int[i]) == (const_arr_int[i] % const_test_int[i]));
      REQUIRE((const_arr_int[i] % const_arr_int[i]) == (const_arr_int[i] % const_test_int(i)));
      
      REQUIRE((test_int_comp[i] % test_int[i]) == (test_int_comp[i] % arr_int[i]));
      REQUIRE((test_int_comp[i] % test_int(i)) == (test_int_comp[i] % arr_int[i]));
      REQUIRE((test_int_comp[i] % const_test_int[i]) == (test_int_comp[i] % const_arr_int[i]));
      REQUIRE((test_int_comp[i] % const_test_int(i)) == (test_int_comp[i] % const_arr_int[i]));
      REQUIRE((const_test_int[i] % const_test_int[i]) == (const_test_int[i] % const_arr_int[i]));
      REQUIRE((const_test_int[i] % const_test_int(i)) == (const_test_int[i] % const_arr_int[i]));

      // ++, --
      REQUIRE((test[i]++) == (arr[i]++));
      REQUIRE((test(i)++) == (arr[i]++));
      REQUIRE((arr[i]++) == (test[i]++));
      REQUIRE((arr[i]++) == (test(i)++));
      // REQUIRE((const_test[i]++) == (arr[i]++));
      // REQUIRE((arr[i]++) == (const_test[i]++));

      REQUIRE((++test[i]) == (++arr[i]));
      REQUIRE((++test(i)) == (++arr[i]));
      REQUIRE((++arr[i]) == (++test[i]));
      REQUIRE((++arr[i]) == (++test(i)));


      // -
      // REQUIRE((test[i] - 1.0) == (arr[i] - 1.0));
      // REQUIRE((test(i) - 1.0) == (arr[i] - 1.0));
      // *
      // REQUIRE((test[i] * 2.1) == (arr[i] * 2.1));
      // REQUIRE((test(i) * 2.1) == (arr[i] * 2.1));
      // /
      // REQUIRE((test[i] / 2.1) == (arr[i] / 2.1));
      // REQUIRE((test(i) / 2.1) == (arr[i] / 2.1));
      // % 
      // REQUIRE((test_int[i] % 2) == (arr_int[i] % 2));
      // REQUIRE((test_int(i) % 2) == (arr_int[i] % 2));
      // ++
      // REQUIRE((++arr_int[i]) == (++test_int[i]));
      // REQUIRE((++arr_int[i]) == (++test_int(i)));
      // REQUIRE((arr_int[i]++) == (test_int[i]++));
      // REQUIRE((arr_int[i]++) == (test_int(i)++));
      // REQUIRE((++test_int[i]) == (++arr_int[i]));
      // REQUIRE((++test_int(i)) == (++arr_int[i]));
      // REQUIRE((test_int[i]++) == (arr_int[i]++));
      // REQUIRE((test_int(i)++) == (arr_int[i]++));
      // --
      // REQUIRE((--arr_int[i]) == (--test_int[i]));
      // REQUIRE((--arr_int[i]) == (--test_int(i)));
      // REQUIRE((arr_int[i]--) == (test_int[i]--));
      // REQUIRE((arr_int[i]--) == (test_int(i)--));
      // REQUIRE((--test_int[i]) == (--arr_int[i]));
      // REQUIRE((--test_int(i)) == (--arr_int[i]));
      // REQUIRE((test_int[i]--) == (arr_int[i]--));
      // REQUIRE((test_int(i)--) == (arr_int[i]--));

      // +=
      // test[i] += 1.0;
      // arr[i] += 1.0;
      // REQUIRE(test[i] == arr[i]);
      // REQUIRE(arr[i] == test[i]); // => How to do?, if rvalue && (NorM ==1) => overloading 

      // -=
      // test[i] -= 1.0;
      // arr[i] -= 1.0;
      // REQUIRE(test[i] == arr[i]);
      // REQUIRE(arr[i] == test[i]); // => How to do?, if rvalue && (NorM ==1) => overloading 

      // *=
      // test[i] *= 2.1;
      // arr[i] *= 2.1;
      // REQUIRE(test[i] == arr[i]);
      // REQUIRE(arr[i] == test[i]); // => How to do?, if rvalue && (NorM ==1) => overloading 

      // /=
      // test[i] /= 2.1;
      // arr[i] /= 2.1;
      // REQUIRE(test[i] == arr[i]);
      // REQUIRE(arr[i] == test[i]); // => How to do?, if rvalue && (NorM ==1) => overloading 

      // %=
      // test_int[i] %= 3;
      // arr_int[i] %= 3;
      // REQUIRE(test_int[i] == arr_int[i]);
      // REQUIRE(arr_int[i] == test_int[i]); // => How to do?, if rvalue && (NorM ==1) => overloading 

      // ==, !=
      // REQUIRE(test_int[i] == arr_int[i]); 
      // REQUIRE(arr_int[i] == test_int[i]);  // => How to do?, if rvalue && (NorM ==1) => overloading 

      // arr[i] += 1.0;
      // !=
      // REQUIRE(test[i] != arr[i]); 

      // >, >=
      // REQUIRE(test[i] < arr[i]); 
      
      // !=

      // >
      
      // <

      // >=

      // <=

      // &&

      // ||

      // !
      
      // ^

      // ~

      // <<

      // >>


    }

    // Matrix<double, 2, 2> test2{ { {1.0, 2.0}, {3.0, 4.0}} };
    // if(test2[0] == 1.0)
    // {

    // }
  }
}