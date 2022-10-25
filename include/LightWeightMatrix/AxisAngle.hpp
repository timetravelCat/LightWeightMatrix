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
#include "Quaternion.hpp"

namespace lwm
{
  template<typename T, size_t M, size_t N>
  class Matrix;

  template<typename T>
  class Quaternion;

  template<typename T>
  class AxisAngle : public Vector<T, 3>
  {
   public:
    /**
     * @brief Constructors
     */
    using Vector<T, 3>::Vector;

    template<typename U>
    explicit AxisAngle(U x, U y, U z)
    {
      this->data[0][0] = x;
      this->data[1][0] = y;
      this->data[2][0] = z;
    }

    template<typename U>
    explicit AxisAngle(const Vector<U, 3>& other) : Vector<T, 3>(other)
    {
    }

    template<typename U>
    void operator=(const Vector<U, 3>& other)
    {
      this->data[0][0] = other[0];
      this->data[1][0] = other[1];
      this->data[2][0] = other[2];
    }

    template<typename U>
    void operator=(const AxisAngle<U>& other)
    {
      this->data[0][0] = other[0];
      this->data[1][0] = other[1];
      this->data[2][0] = other[2];
    }

    // Euler Angle Constructor

    // Quaternion constructor
    template<typename U>
    explicit AxisAngle(const Quaternion<U>& q)
    {
      AxisAngle& v = *this;
      T mag = q.imag().norm();
      if (fabs(mag) >= epsilon<T>())
        v = q.imag() * T(T(2) * atan2(mag, q(0)) / mag);
      else
        v = q.imag() * T(T(2) * T(sign(q(0))));
    }

    // Rotation Matrix Constructor
    template<typename U>
    explicit AxisAngle(const RotationMatrix<U>& mat)
    {
      *this = AxisAngle<T>{ Quaternion<U>{ mat } };
    }

    template<typename U>
    explicit AxisAngle(const Vector3<U>& axis, U angle)
    {
      (*this) = axis * angle;
    }

    Vector3<T> axis()
    {
      return this->template unit();
    }

    T angle()
    {
      return this->template norm();
    }

   private:
  };
}  // namespace lwm
