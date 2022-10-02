/**
 * @file type_helper.hpp
 * @author InGyuChoi (timetraveler930@gmail.com)
 * @brief helper functions for template meta programmings.
 * @version 0.1
 * @date 2022-09-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "type_traits.hpp"

namespace lwm
{
  namespace internal
  {
    template<typename T, typename... TRest>
    struct are_floating_point
    {
      static const bool value = are_floating_point<T>::value && are_floating_point<TRest...>::value;
    };
    template<typename T>
    struct are_floating_point<T> : public is_floating_point<T>
    {
    };
    template<typename T, typename... TRest>
    struct are_fixed_point
    {
      static const bool value = are_fixed_point<T>::value && are_fixed_point<TRest...>::value;
    };
    template<typename T>
    struct are_fixed_point<T> : public is_integral<T>
    {
    };
    template<typename T, typename... TRest>
    struct are_arithmetic
    {
      static const bool value = are_arithmetic<T>::value && are_arithmetic<TRest...>::value;
    };
    template<typename T>
    struct are_arithmetic<T> : public is_arithmetic<T>
    {
    };
    template<typename T, typename T1, typename... TRest>
    struct include_floating_point
    {
      static const bool value = include_floating_point<T, T1>::value || include_floating_point<T, TRest...>::value;
    };
    template<typename T, typename T1>
    struct include_floating_point<T, T1>
    {
      static const bool value = is_floating_point<T>::value || is_floating_point<T1>::value;
    };
    template<typename T, typename T1, typename... TRest>
    struct include_fixed_point
    {
      static const bool value = include_fixed_point<T, T1>::value || include_fixed_point<T, TRest...>::value;
    };
    template<typename T, typename T1>
    struct include_fixed_point<T, T1>
    {
      static const bool value = is_integral<T>::value || is_integral<T1>::value;
    };
    template<typename T, typename T1, typename... TRest>
    struct implicit_cast_floating_point
    {
      typedef typename implicit_cast_floating_point<T, typename implicit_cast_floating_point<T1, TRest...>::type>::type type;
    };
    template<typename T, typename T1>
    struct implicit_cast_floating_point<T, T1>
    {
      typedef conditional_t<
          include_floating_point<T, T1>::value,
          conditional_t<
              are_floating_point<T, T1>::value,
              conditional_t<(sizeof(T) > sizeof(T1)), T, T1>,
              conditional_t<is_floating_point<T>::value, T, T1>>,
          float>
          type;
    };
    template<typename T, typename T1, typename... TRest>
    using implicit_cast_floating_point_t = typename implicit_cast_floating_point<T, T1, TRest...>::type;
    template<typename T, typename... TRest>
    struct include_signed
    {
      static const bool value = include_signed<T>::value || include_signed<TRest...>::value;
    };
    template<typename T>
    struct include_signed<T> : public is_signed<T>
    {
    };
    template<typename T, typename T1, typename... TRest>
    struct implicit_cast_fixed_point
    {
      typedef typename implicit_cast_fixed_point<T, typename implicit_cast_fixed_point<T1, TRest...>::type>::type type;
    };
    template<typename T, typename T1>
    struct implicit_cast_fixed_point<T, T1>
    {
      static_assert(!include_floating_point<T, T1>::value, "implicit_cast_fixed_point includes floating point");
      typedef conditional_t<
          (sizeof(T) >= sizeof(T1)),
          conditional_t<include_signed<T, T1>::value, make_signed_t<T>, T>,
          conditional_t<include_signed<T, T1>::value, make_signed_t<T1>, T1>>
          type;
    };
    template<typename T, typename T1, typename... TRest>
    using implicit_cast_fixed_point_t = typename implicit_cast_fixed_point<T, T1, TRest...>::type;
    template<typename T, typename T1, typename... TRest>
    struct implicit_cast
    {
      typedef typename implicit_cast<T, typename implicit_cast<T1, TRest...>::type>::type type;
    };
    template<typename T, typename T1>
    struct implicit_cast<T, T1> : enable_if<are_arithmetic<T, T1>::value, conditional_t<
          include_floating_point<T, T1>::value,
          implicit_cast_floating_point_t<T, T1>,
          conditional_t<
              (sizeof(T) >= sizeof(T1)),
              conditional_t<include_signed<T, T1>::value, make_signed_t<T>, T>,
              conditional_t<include_signed<T, T1>::value, make_signed_t<T1>, T1>>>>
    {
    };
    template<typename T, typename T1, typename... TRest>
    using implicit_cast_t = typename implicit_cast<T, T1, TRest...>::type;
    template<typename L, typename R>
    struct allowed_cast
    {
      static_assert(
          !(is_unsigned<L>::value && is_signed<R>::value),
          "Allocating unsigned type from singed type is not allowed.");
      typedef L type;
    };
    template<typename L, typename R>
    using allowed_cast_t = typename allowed_cast<L, R>::type;
    template<typename T>
    struct floating_types_holer
    {
      typedef conditional_t<is_same<T, float>::value, double, float>
          type_1;
      typedef conditional_t<
          is_same<T, float>::value,
          long double,
          conditional_t<is_same<T, double>::value, long double, double>>
          type_2; 
    };
    template<typename T>
    using floating_types_holer_1 = typename floating_types_holer<T>::type_1;
    template<typename T>
    using floating_types_holer_2 = typename floating_types_holer<T>::type_2;

    template<typename T, T T1, T T2>
    struct min
    {
      static const T value = (T1 < T2) ? T1:T2;
    };
    template<typename T, T T1, T T2>
    struct max
    {
      static const T value = (T1 > T2) ? T1:T2;
    };
  };  // namespace internal
};    // namespace lwm
