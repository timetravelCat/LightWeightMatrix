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

    Quaternion<float> quat2{{0.0f, 1.0f, 0.0f, 0.0f}};
    REQUIRE(quat2(1) == 1.0f);

    Vector<float, 4> vec1{{0.0f, 0.0f, 1.0f, 0.0f}};
    Quaternion<float> quat3{vec1};
    REQUIRE(quat3(2) == 1.0f);

    Vector<double, 4> vec2{{0.0f, 0.0f, 0.0f, 1.0f}};
    Quaternion<float> quat4{vec2};
    REQUIRE(quat4(3) == float(1.0));

    Quaternion<float> quat5{quat3};
    Quaternion<float> quat6{quat4};
    REQUIRE(quat5(2) == float(1.0));
    REQUIRE(quat6(3) == float(1.0));

    quat6 = quat5;
    REQUIRE(quat6(2) == float(1.0));
    quat6 = vec1;
    REQUIRE(quat6(2) == float(1.0));
    
    Quaternion<float> quat7{0.0f, 0.0f, 0.0f, 1.0f};
    REQUIRE(quat7(3) == 1.0f);

    // Vector<float, 4> vector{{0.0f, 1.0f, 0.0f, 0.0f}};
    // Quaternion<float> quat2 = vector;
    // REQUIRE(quat2(0) == 0.0f);
    // REQUIRE(quat2(1) == 1.0f);
    // REQUIRE(quat2(2) == 0.0f);
    // REQUIRE(quat2(3) == 0.0f);
  }
}