#define CATCH_CONFIG_MAIN
#include <LightWeightMatrix/type_helper.hpp>
#include <catch2/catch.hpp>

using namespace lwm::internal;

TEMPLATE_PRODUCT_TEST_CASE(
    "are_floating_type testing",
    "[template]",
    lwm::internal::are_floating_point,
    ((double, float), (float, float), (double, float, float), (double, float, float, double)))
{
  REQUIRE(TestType::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "are_floating_type testing",
    "[template]",
    lwm::internal::are_floating_point,
    ((double, int), (int, float), (int, int, int), (double, long, int, double)))
{
  REQUIRE(TestType::value == false);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "include_floating_type testing",
    "[template]",
    lwm::internal::include_floating_point,
    ((double, int), (int, float), (float, double, float), (int, long, int, double)))
{
  REQUIRE(TestType::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "include_floating_type testing",
    "[template]",
    lwm::internal::include_floating_point,
    ((int, int), (int, long), (int, int, int), (long long, long, int, char)))
{
  REQUIRE(TestType::value == false);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "implicit_cast_floating_point testing",
    "[template]",
    lwm::internal::implicit_cast_floating_point,
    ((int, int), (int, long), (float, float), (float, char)))
{
  REQUIRE(is_same<typename TestType::type, float>::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "implicit_cast_floating_point testing",
    "[template]",
    lwm::internal::implicit_cast_floating_point,
    ((int, double), (float, double), (double, double), (double, long)))
{
  REQUIRE(is_same<typename TestType::type, double>::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "implicit_cast_floating_point testing",
    "[template]",
    lwm::internal::implicit_cast_floating_point,
    ((int, long double), (float, long double), (long double, long double), (long double, long)))
{
  REQUIRE(is_same<typename TestType::type, long double>::value == true);
}