#define CATCH_CONFIG_MAIN
#include <float.h>
#include <math.h>

#include <LightWeightMatrix/Quaternion.hpp>
#include <catch2/catch.hpp>

using namespace lwm;
using namespace lwm::internal;

TEST_CASE("Quaternion", "[lwm::Quaternion]")
{
  SECTION("Constructors")
  {
    Quaternion<float> quat;
    REQUIRE(quat(0) == 1.0f);

    Quaternion<float> quat2{ { 0.0f, 1.0f, 0.0f, 0.0f } };
    REQUIRE(quat2(1) == 1.0f);

    Vector<float, 4> vec1{ { 0.0f, 0.0f, 1.0f, 0.0f } };
    Quaternion<float> quat3{ vec1 };
    REQUIRE(quat3(2) == 1.0f);

    Vector<double, 4> vec2{ { 0.0f, 0.0f, 0.0f, 1.0f } };
    Quaternion<float> quat4{ vec2 };
    REQUIRE(quat4(3) == float(1.0));

    Quaternion<float> quat5{ quat3 };
    Quaternion<float> quat6{ quat4 };
    REQUIRE(quat5(2) == float(1.0));
    REQUIRE(quat6(3) == float(1.0));

    quat6 = quat5;
    REQUIRE(quat6(2) == float(1.0));
    quat6 = vec1;
    REQUIRE(quat6(2) == float(1.0));

    Quaternion<float> quat7{ 0.0f, 0.0f, 0.0f, 1.0f };
    REQUIRE(quat7(3) == 1.0f);

    RotationMatrixf rotmat = RotationMatrixf::Identity();
    Quaternion<float> quat8{ rotmat };
    REQUIRE(quat8(0) == 1.0f);
    REQUIRE(quat8(1) == 0.0f);
    REQUIRE(quat8(2) == 0.0f);
    REQUIRE(quat8(3) == 0.0f);

    Quaternion<float> quat9 = quat8*Quaternion<float>{0.0f, 1.0f, 0.0f, 0.0f};
    REQUIRE(quat9(0) == 0.0f);
    REQUIRE(quat9(1) == 1.0f);
    REQUIRE(quat9(2) == 0.0f);
    REQUIRE(quat9(3) == 0.0f);

    auto quat10 = Quaternion<float>::exp(Vector3<float>{{0.0, 0.0, M_PI/2.0}});
    REQUIRE(isSame(quat10(0), 0.0f) == true);
    REQUIRE(isSame(quat10(1), 0.0f) == true);
    REQUIRE(isSame(quat10(2), 0.0f) == true);
    REQUIRE(quat10(3) == 1.0f);

    auto vec0 = quat10.log();
    REQUIRE(isSame(vec0(0), 0.0f) == true);
    REQUIRE(isSame(vec0(1), 0.0f) == true);
    REQUIRE(isSame(vec0(2), float(M_PI/2.0)) == true);

    auto quat11 = quat9.inv();
    REQUIRE(quat11(0) == 0.0f);
    REQUIRE(quat11(1) == -1.0f);
    REQUIRE(quat11(2) == 0.0f);
    REQUIRE(quat11(3) == 0.0f);

    auto quat12 = quat9.normalized();
    REQUIRE(quat12(0) == 0.0f);
    REQUIRE(quat12(1) == 1.0f);
    REQUIRE(quat12(2) == 0.0f);
    REQUIRE(quat12(3) == 0.0f);

    float real = quat9.real();
    REQUIRE(real == 0.0f);

    Vector3<float> imag = quat9.imag();
    REQUIRE(imag(0) == 1.0f);
    REQUIRE(imag(1) == 0.0f);
    REQUIRE(imag(2) == 0.0f);

    auto rotvec0 = quat9.rotate(imag);
    REQUIRE(rotvec0(0) == 1.0f);
    REQUIRE(rotvec0(1) == 0.0f);
    REQUIRE(rotvec0(2) == 0.0f);

    auto rotvec1 = quat9.rotateReverse(imag);
    REQUIRE(rotvec1(0) == 1.0f);
    REQUIRE(rotvec1(1) == 0.0f);
    REQUIRE(rotvec1(2) == 0.0f);
  }
}