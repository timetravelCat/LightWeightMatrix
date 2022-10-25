#define CATCH_CONFIG_MAIN
#include <float.h>
#include <math.h>

#include <LightWeightMatrix/AxisAngle.hpp>
#include <catch2/catch.hpp>

using namespace lwm;
using namespace lwm::internal;

TEST_CASE("AxisAngle", "[lwm::AxisAngle]")
{
  SECTION("Constructors")
  {
    AxisAngle<float> axisAngle{1.0f, 1.0f, 1.0f};
    AxisAngle<float> axisAngle2{{1.0f, 1.0f, 1.0f}};
    
    REQUIRE(axisAngle[0] == 1.0f);
    REQUIRE(axisAngle[1] == 1.0f);
    REQUIRE(axisAngle[2] == 1.0f);
    REQUIRE(axisAngle[0] == 1.0f);
    REQUIRE(axisAngle[1] == 1.0f);
    REQUIRE(axisAngle[2] == 1.0f);

    Vector3f vec{{1.0f, 1.0f, 1.0f}};
    AxisAngle<float> axisAngle3{vec};
    REQUIRE(axisAngle3[0] == 1.0f);
    REQUIRE(axisAngle3[1] == 1.0f);
    REQUIRE(axisAngle3[2] == 1.0f);

    AxisAngle<float> axisAngle4; axisAngle4 = vec;
    REQUIRE(axisAngle4[0] == 1.0f);
    REQUIRE(axisAngle4[1] == 1.0f);
    REQUIRE(axisAngle4[2] == 1.0f);

    AxisAngle<float> axisAngle5{vec};
    REQUIRE(axisAngle5[0] == 1.0f);
    REQUIRE(axisAngle5[1] == 1.0f);
    REQUIRE(axisAngle5[2] == 1.0f);

    Quaternion<float> quat;
    AxisAngle<float> axisAngle6{quat};
    REQUIRE(axisAngle6[0] == 0.0f);
    REQUIRE(axisAngle6[1] == 0.0f);
    REQUIRE(axisAngle6[2] == 0.0f);

    AxisAngle<float> axisAngle7{Vector3f{{0.0f, 0.0f, 0.0f}}, 0.0f};
    REQUIRE(axisAngle7(0) == 0.0f);
    REQUIRE(axisAngle7(1) == 0.0f);
    REQUIRE(axisAngle7(2) == 0.0f);

    AxisAngle<float> axisAngle8{0.0f, 0.0f, 0.0f};
    REQUIRE(isnan(axisAngle8.unit()(0)));
    REQUIRE(isnan(axisAngle8.unit()(1)));
    REQUIRE(isnan(axisAngle8.unit()(2)));

    REQUIRE(axisAngle8.norm() == 0.0f);
  }
}