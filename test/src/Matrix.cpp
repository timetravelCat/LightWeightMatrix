#define CATCH_CONFIG_MAIN
#include <LightWeightMatrix/Matrix.hpp>
#include <catch2/catch.hpp>

using namespace lwm;
using namespace lwm::internal;

TEST_CASE("Matrix", "[lwm::Matrix]")
{
  SECTION("Constructor 1) explicit Matrix(const U (&in)[L])")
  {
    // Compile-time errors, error by casting type
    // float arr1_temp[5] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    // lwm::Matrix<uint32_t, 2, 3> matrix_temp{arr1_temp};
    // double arr2_temp[7] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };
    // lwm::Matrix<float, 2, 3> matrix_temp{arr2_temp};

    float arr[6] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
    lwm::Matrix<float, 2, 3> matrix{ arr };
    matrix = arr;
    REQUIRE(matrix(0, 0) == arr[0]);
    REQUIRE(matrix(0, 1) == arr[1]);
    REQUIRE(matrix(0, 2) == arr[2]);
    REQUIRE(matrix(1, 0) == arr[3]);
    REQUIRE(matrix(1, 1) == arr[4]);
    REQUIRE(matrix(1, 2) == arr[5]);
    REQUIRE(matrix[0][0] == arr[0]);
    REQUIRE(matrix[0][1] == arr[1]);
    REQUIRE(matrix[0][2] == arr[2]);
    REQUIRE(matrix[1][0] == arr[3]);
    REQUIRE(matrix[1][1] == arr[4]);
    REQUIRE(matrix[1][2] == arr[5]);

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
    lwm::Matrix<float, 2, 3> matrix2{ arr3, int(0), int(0) };
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
  SECTION("reserving bigger changes capacity but not size")
  {
  }
  SECTION("reserving smaller does not change size or capacity")
  {
  }
}