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
    REQUIRE(Angle<float>::DEG2RAD(1.0f) == PI<float>()/float(180));
    REQUIRE(Angle<float>::RAD2DEG(1.0f) == float(180)/PI<float>());
  }
}