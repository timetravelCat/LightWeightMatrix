/**
 * @file EulerAngle.hpp
 * @author InGyuChoi (timetraveler930@gmail.com)
 * @brief
 * @version 0.6
 * @date 2022-11-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <math.h>

#include "Angle.hpp"
#include "AxisAngle.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

namespace lwm
{
  using namespace internal;

  template<typename T, size_t M, size_t N>
  class Matrix;

  template<typename T>
  class Quaternion;

  template<typename T>
  class AxisAngle;

  enum class EulerAngleType
  {
    ZYX
    // Todo support other useful type?
  };

  template<typename T, EulerAngleType O>  // Order
  class EulerAngle
  {
   public:
   private:
    Angle<T> angle[3];
  };
};  // namespace lwm