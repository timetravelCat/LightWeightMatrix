#define CATCH_CONFIG_MAIN
#include <LightWeightMatrix/internal/type_helper.hpp>
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

TEMPLATE_PRODUCT_TEST_CASE(
    "implicit_cast testing",
    "[template]",
    lwm::internal::implicit_cast,
    ((double, double), (float, double), (int, double), (unsigned int, double, unsigned int, unsigned short), (unsigned, unsigned, double, unsigned)))
{
  REQUIRE(is_same<typename TestType::type, double>::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "implicit_cast testing",
    "[template]",
    lwm::internal::implicit_cast,
    ((short, short, int), (unsigned int, short, int), (int, short, short), (unsigned int, short, unsigned int, unsigned short), (unsigned, unsigned, short, int)))
{
  REQUIRE(is_same<typename TestType::type, int>::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "allowed_cast testing",
    "[template]",
    lwm::internal::allowed_cast,
    ((float, double), (float, float), (float, long double)))
{
    REQUIRE(is_same<typename TestType::type, float>::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "allowed_cast testing",
    "[template]",
    lwm::internal::allowed_cast,
    ((double, double), (double, float), (double, long double)))
{
    REQUIRE(is_same<typename TestType::type, double>::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "floating_types_holer testing",
    "[template]",
    lwm::internal::floating_types_holer,
    ((float)))
{
    REQUIRE(is_same<typename TestType::type_1, double>::value == true);
    REQUIRE(is_same<typename TestType::type_2, long double>::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "floating_types_holer testing",
    "[template]",
    lwm::internal::floating_types_holer,
    ((double)))
{
    REQUIRE(is_same<typename TestType::type_1, float>::value == true);
    REQUIRE(is_same<typename TestType::type_2, long double>::value == true);
}

TEMPLATE_PRODUCT_TEST_CASE(
    "floating_types_holer testing",
    "[template]",
    lwm::internal::floating_types_holer,
    ((long double)))
{
    REQUIRE(is_same<typename TestType::type_1, float>::value == true);
    REQUIRE(is_same<typename TestType::type_2, double>::value == true);
}

TEST_CASE("type_epsilon testing", "[lwm::internal::type_epsilon]")
{
  REQUIRE(is_same<type_epsilon<int>::type, void>::value == true);
  REQUIRE(is_same<type_epsilon<uint32_t>::type, void>::value == true);
  REQUIRE(is_same<type_epsilon<float>::type, void>::value == false);
  REQUIRE(is_same<type_epsilon<double>::type, void>::value == false);
  REQUIRE(type_epsilon<float>::type::value == FLT_EPSILON);
  REQUIRE(type_epsilon<double>::type::value == DBL_EPSILON);
  REQUIRE(type_epsilon<long double>::type::value == LDBL_EPSILON);
}