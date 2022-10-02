/**
 * @file Common.hpp
 * @author InGyuChoi (timetraveler930@gmail.com)
 * @brief A common functions for math
 * @version 0.1
 * @date 2022-10-02
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <float.h>
#include <math.h>

#include "internal/type_helper.hpp"

namespace lwm
{
  using namespace lwm::internal;
  template<typename A, typename B>
  enable_if_t<are_fixed_point<A, B>::value, bool> isSame(const A a, const B b)
  {
    return (a == b);
  }
  template<typename A, typename B>
  enable_if_t<are_floating_point<A, B>::value, bool>
  isSame(const A a, const B b, const implicit_cast_floating_point_t<A, B> eps = implicit_cast_floating_point_t<A, B>(1e-4))
  {
    return (fabs(a - b) <= eps) || (isnan(a) && isnan(b)) || (isinf(a) && isinf(b) && isnan(a - b));
  }
  template<typename A, typename B>
  enable_if_t<include_fixed_point<A, B>::value && include_floating_point<A, B>::value, bool> isSame(const A, const B)
  {
    return false;
  }
};  // namespace lwm