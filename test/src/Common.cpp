#define CATCH_CONFIG_MAIN
#include <LightWeightMatrix/Common.hpp>
#include <catch2/catch.hpp>

using namespace lwm;
using namespace lwm::internal;

TEST_CASE("Common.cpp")
{
  SECTION("isSame")
  {
    // if different type, return false
    REQUIRE(!isSame(1, 3.0));
    REQUIRE(!isSame(1, 1.0));

    // if fixed point
    REQUIRE(isSame(1, 1));
    REQUIRE(!isSame(1, 2));
    // REQUIRE(isSame(1, size_t(1)));
    // REQUIRE(!isSame(1, size_t(2)));

    // if floating point
    // REQUIRE(isSame(nanf(""), nan("")));
    // REQUIRE(isSame(1.0, 1.0f));
    REQUIRE(isSame(1.0, 1.0));
    REQUIRE(!isSame(1.1, 1.0));
    REQUIRE(isSame(INFINITY, INFINITY));
    REQUIRE(isSame(-INFINITY, -INFINITY));
    REQUIRE(!isSame(INFINITY, -INFINITY));

    REQUIRE(isFinite(1.0));
    REQUIRE(!isFinite(nanf("")));
    REQUIRE(!isFinite(INFINITY));
    REQUIRE(!isFinite(double(INFINITY)));
    REQUIRE(!isFinite(NAN));
    REQUIRE(!isFinite(double(NAN)));
    
    REQUIRE(isEpsilon(LDBL_EPSILON));
    REQUIRE(isEpsilon(FLT_EPSILON));
    REQUIRE(isEpsilon(FLT_EPSILON/2.0f));
    REQUIRE(!isEpsilon(FLT_EPSILON*2.0f));
    REQUIRE(isEpsilon(DBL_EPSILON));


  } 
}