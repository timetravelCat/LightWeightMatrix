#define CATCH_CONFIG_MAIN
#include <float.h>
#include <math.h>

#include <LightWeightMatrix/Angle.hpp>
#include <catch2/catch.hpp>

using namespace lwm;
using namespace lwm::internal;

TEST_CASE("Angle", "[lwm::Angle]")
{
  SECTION("Constructors")
  {
    REQUIRE(Angle<float>::DEG2RAD(1.0f) == PI<float>() / float(180));
    REQUIRE(Angle<float>::RAD2DEG(1.0f) == float(180) / PI<float>());

    REQUIRE(Angle<float>{ Angle<float>{ 0.1f } } == 0.1f);
    // REQUIRE(Angle<float>{Angle<double>{0.1}} == 0.1f);
    REQUIRE(Angle<float>{ Angle<float, ANGLE_RANGE::ZERO_TO_TWO_PI>{ 0.1f } } == 0.1f);
    // REQUIRE(Angle<float>{Angle<double, ANGLE_RANGE::ZERO_TO_TWO_PI>{0.1}} == 0.1f);
  }

  SECTION("Compare")
  {
    Angle<float, ANGLE_RANGE::MINUS_PI_TO_PI> ang{ 0.1f };
    REQUIRE((ang == 0.1f));
    // REQUIRE((ang == 0.1));
    REQUIRE((0.1f == ang));
    // REQUIRE((0.1 == ang));
    REQUIRE(ang == Angle<float, ANGLE_RANGE::MINUS_PI_TO_PI>{ 0.1f });
    // REQUIRE(ang == Angle<double, ANGLE_RANGE::MINUS_PI_TO_PI>{0.1});
  }

  SECTION("+ - operations")
  {
    Angle<float, ANGLE_RANGE::MINUS_PI_TO_PI> ang1{ 0.1f };
    Angle<float, ANGLE_RANGE::ZERO_TO_TWO_PI> ang2{ 0.2f };
    auto ang3 = ang1 + ang2;
    REQUIRE((ang3 == 0.1f + 0.2f));
    ang3 -= ang1;
    REQUIRE((ang3 == 0.1f + 0.2f - 0.1f));
    ang3 += 0.1f;
    REQUIRE((ang3 == 0.1f + 0.2f - 0.1f + 0.1f));

    auto ang4 = ang2 - ang1;
    REQUIRE((ang4 == 0.2f - 0.1f));
    ang4 += ang1;
    REQUIRE((ang4 == 0.2f - 0.1f + 0.1f));
    ang4 -= 0.1f;
    REQUIRE((ang4 == 0.2f - 0.1f + 0.1f - 0.1f));

    REQUIRE((ang4() == 0.2f - 0.1f + 0.1f - 0.1f));
  }
  SECTION("cast operations")
  {
    Angle<float, ANGLE_RANGE::MINUS_PI_TO_PI> ang1{ 0.1f };
    REQUIRE(ang1.cast<double>() == static_cast<double>(0.1f));
    REQUIRE(ang1.cast<ANGLE_RANGE::ZERO_TO_TWO_PI>() == 0.1f);
  }
}