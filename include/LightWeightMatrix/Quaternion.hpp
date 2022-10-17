/**
 * @file Quaternion.hpp
 * @author InGyuChoi (timetraveler930@gmail.com)
 * @brief
 * @version 0.2
 * @date 2022-10-17
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
  class Quaternion : public Vector<T, 4>
  {
   public:
    /**
     * @brief Constructors
     */
    using Vector<T, 4>::Vector;
    Quaternion()
    {
      Quaternion& q = *this;
      q[0] = 1;
      q[1] = 0;
      q[2] = 0;
      q[3] = 0;
    };

    template<typename U>
    explicit Quaternion(U w, U x, U y, U z)
    {
      Quaternion& q = *this;
      q[0] = w;
      q[1] = x;
      q[2] = y;
      q[3] = z;
    }

    template<typename U>
    explicit Quaternion(const Vector<U, 4>& other) : Vector<T, 4>(other)
    {
    }

    template<typename U>
    void operator=(const Vector<U, 4>& other)
    {
      Quaternion& q = *this;
      q[0] = other[0];
      q[1] = other[1];
      q[2] = other[2];
      q[3] = other[3];
    }

    // Rotation Matrix Constructor

    // Euler Angle Constructor

    // Axis Angle Constructor

   private:
  };
};  // namespace lwm
