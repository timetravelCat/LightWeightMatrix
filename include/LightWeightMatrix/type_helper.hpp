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
  };  // namespace internal
};    // namespace lwm
