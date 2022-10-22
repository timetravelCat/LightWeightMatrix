/**
 * @file AxisAngle.hpp
 * @author InGyuChoi (timetraveler930@gmail.com)
 * @brief implementation of axis angle
 * @version 0.6
 * @date 2022-10-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <math.h>

#include "Matrix.hpp"

namespace lwm
{
  template<typename T, size_t M, size_t N>
  class Matrix;

  template<typename T>
  class AxisAngle : public Vector<T, 3>
  {
   public:
    /**
     * @brief Constructors
     */
    using Vector<T, 3>::Vector;
    

   private:
  };
}  // namespace lwm
