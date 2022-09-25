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
    template<typename T, typename T1, typename... TRest>
    struct are_floating_point
    {
      static const bool value = are_floating_point<T, T1>::value && are_floating_point<T, TRest...>::value;
    };
    template<typename T, typename T1>
    struct are_floating_point<T, T1>
    {
      static const bool value = is_floating_point<T>::value && is_floating_point<T1>::value;
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
    struct implicit_cast_floating_point
    {
      // Todo 
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

    template<typename T, typename T1>
    using implicit_cast_floating_point_t = typename implicit_cast_floating_point<T, T1>::type;
    
  };  // namespace internal
};    // namespace lwm
