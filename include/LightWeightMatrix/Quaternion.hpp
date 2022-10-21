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

    template<typename U>
    void operator=(const Quaternion<U>& other)
    {
      Quaternion& q = *this;
      q[0] = other[0];
      q[1] = other[1];
      q[2] = other[2];
      q[3] = other[3];
    }

    // Rotation Matrix Constructor
    template<typename U>
    explicit Quaternion(const RotationMatrix<U>& R)
    {
      Quaternion& q = *this;
      T t = R.trace();
      if (t > T(0))
      {
        t = sqrt(T(1) + t);
        q[0] = T(0.5) * t;
        t = T(0.5) / t;
        q[1] = (R(2, 1) - R(1, 2)) * t;
        q[2] = (R(0, 2) - R(2, 0)) * t;
        q[3] = (R(1, 0) - R(0, 1)) * t;
      }
      else if (R(0, 0) > R(1, 1) && R(0, 0) > R(2, 2))
      {
        t = sqrt(T(1) + R(0, 0) - R(1, 1) - R(2, 2));
        q[1] = T(0.5) * t;
        t = T(0.5) / t;
        q[0] = (R(2, 1) - R(1, 2)) * t;
        q[2] = (R(1, 0) + R(0, 1)) * t;
        q[3] = (R(0, 2) + R(2, 0)) * t;
      }
      else if (R(1, 1) > R(2, 2))
      {
        t = sqrt(T(1) - R(0, 0) + R(1, 1) - R(2, 2));
        q[2] = T(0.5) * t;
        t = T(0.5) / t;
        q[0] = (R(0, 2) - R(2, 0)) * t;
        q[1] = (R(1, 0) + R(0, 1)) * t;
        q[3] = (R(2, 1) + R(1, 2)) * t;
      }
      else
      {
        t = sqrt(T(1) - R(0, 0) - R(1, 1) + R(2, 2));
        q[3] = T(0.5) * t;
        t = T(0.5) / t;
        q[0] = (R(1, 0) - R(0, 1)) * t;
        q[1] = (R(0, 2) + R(2, 0)) * t;
        q[2] = (R(2, 1) + R(1, 2)) * t;
      }
    }

    // Euler Angle Constructor
    // Axis Angle Constructor

    // Other Methods
    template<typename U>
    Quaternion<implicit_cast_t<T, U>> operator*(const Quaternion<U>& p) const
    {
      const Quaternion& q = *this;
      return Quaternion<implicit_cast_t<T, U>>{ q(0) * p(0) - q(1) * p(1) - q(2) * p(2) - q(3) * p(3),
                                                q(1) * p(0) + q(0) * p(1) - q(3) * p(2) + q(2) * p(3),
                                                q(2) * p(0) + q(3) * p(1) + q(0) * p(2) - q(1) * p(3),
                                                q(3) * p(0) - q(2) * p(1) + q(1) * p(2) + q(0) * p(3) };
    }

    template<typename U>
    void operator*=(const Quaternion<U>& other)
    {
      Quaternion& self = *this;
      self = self * other;
    }

    static Quaternion exp(const Vector3<T>& u)
    {
        const T tol = T(0.2);           // ensures an error < 10^-10

        T u_norm = u.norm();
        T sinc_u, cos_u;

        if (u_norm < tol) {
            T u2 = u_norm * u_norm;
            T u4 = u2 * u2;
            T u6 = u4 * u2;

            const T c2 = T(1.0 / 2.0);      // 1 / 2!
            const T c3 = T(1.0 / 6.0);      // 1 / 3!
            const T c4 = T(1.0 / 24.0);     // 1 / 4!
            const T c5 = T(1.0 / 120.0);    // 1 / 5!
            const T c6 = T(1.0 / 720.0);    // 1 / 6!
            const T c7 = T(1.0 / 5040.0);   // 1 / 7!

            // compute the first 4 terms of the Taylor serie
            sinc_u = T(1.0) - u2 * c3 + u4 * c5 - u6 * c7;
            cos_u = T(1.0) - u2 * c2 + u4 * c4 - u6 * c6;
        } else {
            sinc_u = T(sin(u_norm) / u_norm);
            cos_u = T(cos(u_norm));
        }
        const Vector<T, 3> v = sinc_u * u;
        return Quaternion{cos_u, v(0), v(1), v(2)};
    };

    Vector3<T> log() const 
    {
      const Quaternion& q = *this;
      const T ang = acos(q(0));
      if(abs(ang) < epsilon<T>())
        return Vector3<T>::Zero();
      return imag()*ang/sin(ang);
    }

    Quaternion inv() const
    {
      const Quaternion& q = *this;
      return Quaternion(q(0) , -q(1), -q(2), -q(3));
    }

    Quaternion normalized() const
    {
      const Quaternion& q = *this;
      T normSq = q.dot(q);
      return Quaternion(q(0) / normSq, q(1) / normSq, q(2) / normSq, q(3) / normSq);
    }

    T real() const 
    {
      const Quaternion& q = *this;
      return q(0);
    }

    Vector3<T> imag() const
    {
      return this->template slice<3, 1, 1, 0>();
    }

    template<typename U>
    Vector3<U> rotate(const Vector3<U> &vec) const 
    {
        const Quaternion& q = *this;
        Quaternion v(T(0), vec(0), vec(1), vec(2));
        return (q*v*q.inv()).imag();
    }

    template<typename U>
    Vector3<U> rotateReverse(const Vector3<U> &vec) const 
    {
        const Quaternion& q = *this;
        Quaternion v(T(0), vec(0), vec(1), vec(2));
        return (q.inv()*v*q).imag();
    }

   private:
  };
};  // namespace lwm
