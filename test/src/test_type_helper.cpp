#define CATCH_CONFIG_MAIN
#include <LightWeightMatrix/type_helper.hpp>
#include <catch2/catch.hpp>

using namespace lwm::internal;

TEMPLATE_PRODUCT_TEST_CASE(
    "are_floating_point testing",
    "[template]",
    lwm::internal::are_floating_point,
    ((double, float), (float, float), (double, float, float), (double, float, float, double)))
{
  REQUIRE(TestType::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "are_floating_point testing",
    "[template]",
    lwm::internal::are_floating_point,
    ((double, int), (int, float), (int, int, int), (double, long, int, double)))
{
  REQUIRE(TestType::value == false);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "are_fixed_point testing",
    "[template]",
    lwm::internal::are_fixed_point,
    ((int, long), (long, long), (int, int, int), (long long, unsigned, unsigned int, long)))
{
  REQUIRE(TestType::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "are_fixed_point testing",
    "[template]",
    lwm::internal::are_fixed_point,
    ((int, float), (float, double), (float, float, float), (long double, unsigned, unsigned int, long)))
{
  REQUIRE(TestType::value == false);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "include_floating_point testing",
    "[template]",
    lwm::internal::include_floating_point,
    ((double, int), (int, float), (float, double, float), (int, long, int, double)))
{
  REQUIRE(TestType::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "include_floating_point testing",
    "[template]",
    lwm::internal::include_floating_point,
    ((int, int), (int, long), (int, int, int), (long long, long, int, char)))
{
  REQUIRE(TestType::value == false);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "include_fixed_point testing",
    "[template]",
    lwm::internal::include_fixed_point,
    ((double, int), (int, int), (float, long, float), (int, long, int, double)))
{
  REQUIRE(TestType::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "include_fixed_point testing",
    "[template]",
    lwm::internal::include_fixed_point,
    ((float, float), (double, long double), (double, double, double), (long double, float, float, double)))
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

TEMPLATE_PRODUCT_TEST_CASE(
    "implicit_cast_floating_point testing",
    "[template]",
    lwm::internal::implicit_cast_floating_point,
    ((int, int, int), (float, int, float), (long, float, float), (float, float, float)))
{
  REQUIRE(is_same<typename TestType::type, float>::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "implicit_cast_floating_point testing",
    "[template]",
    lwm::internal::implicit_cast_floating_point,
    ((double, int, int, int), (long, double, float, long), (double, double, double, float), (long, int, int, double)))
{
  REQUIRE(is_same<typename TestType::type, double>::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "include_signed testing",
    "[template]",
    lwm::internal::include_signed,
    ((long, int), (unsigned int, int), (long, unsigned long, int), (unsigned int, unsigned int, unsigned, int)))
{
  REQUIRE(TestType::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "include_signed testing",
    "[template]",
    lwm::internal::include_signed,
    ((unsigned, unsigned long),
     (unsigned int, unsigned),
     (unsigned, unsigned long, unsigned int),
     (unsigned int, unsigned int, unsigned, unsigned)))
{
  REQUIRE(TestType::value == false);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "implicit_cast_fixed_point testing",
    "[template]",
    lwm::internal::implicit_cast_fixed_point,
    ((unsigned int, int, char, int), (char, char, short, int), (int, int, int, int), (short, short, unsigned int, short)))
{
  REQUIRE(is_same<typename TestType::type, int>::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "implicit_cast_fixed_point testing",
    "[template]",
    lwm::internal::implicit_cast_fixed_point,
    ((unsigned int, unsigned short, unsigned int, unsigned short), (unsigned, unsigned, unsigned, unsigned)))
{
  REQUIRE(is_same<typename TestType::type, unsigned int>::value == true);
}
