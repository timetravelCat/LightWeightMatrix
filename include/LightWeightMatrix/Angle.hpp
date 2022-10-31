/**
 * @file Angle.hpp
 * @author InGyuChoi (timetraveler930@gmail.com)
 * @brief
 * @version 0.5
 * @date 2022-10-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

// #include <float.h>
#include <math.h>

#include "Common.hpp"
#include "Matrix.hpp"
#include "internal/type_helper.hpp"
namespace lwm
{
  enum class ANGLE_RANGE
  {
    MINUS_PI_TO_PI,  //
    ZERO_TO_TWO_PI
  };

  using namespace internal;
  template<typename T, ANGLE_RANGE RANGE = ANGLE_RANGE::MINUS_PI_TO_PI>
  class Angle
  {
   public:
    template<typename U, ANGLE_RANGE RNG>
    friend class Angle;

    explicit Angle() = default;

    static T RAD2DEG(const T& rad)
    {
      return rad * T(180) / PI<T>();
    }
    static T DEG2RAD(const T& deg)
    {
      return deg * PI<T>() / T(180);
    }

    template<typename U, ANGLE_RANGE RNG>
    explicit Angle(const Angle<U, RNG>& other) : val(other.val)
    {
      if (RANGE != RNG)
        wrap();
    }
    template<typename U>
    explicit Angle(U ang) : val(ang)
    {
      wrap();
    }

    template<typename U, ANGLE_RANGE RNG>
    void operator=(const Angle<U, RNG>& other)
    {
      val = other.val;
      if (RANGE != RNG)
        wrap();
    }
    template<typename U>
    void operator=(const U& other)
    {
      val = other;
      wrap();
    }

    template<typename U>
    bool operator==(const Angle<U>& other) const
    {
      return isSame(val, other.val);
    }
    template<typename U>
    bool operator==(const U& other) const
    {
      return isSame(val, other);
    }
    friend bool operator==(T lhs, Angle rhs)
    {
      return isSame(lhs, rhs.val);
    }

    // + - operation for angle class
    template<typename U, ANGLE_RANGE RNG>
    Angle operator+(const Angle<U, RNG>& other) const
    {
      Angle res;
      res.val = val + other.val;
      res.wrap();
      return res;
    }
    template<typename U, ANGLE_RANGE RNG>
    void operator+=(const Angle<U, RNG>& other)
    {
      val += other.val;
      wrap();
    }
    template<typename U, ANGLE_RANGE RNG>
    Angle operator-(const Angle<U, RNG>& other) const
    {
      Angle res;
      res.val = val - other.val;
      res.wrap();
      return res;
    }
    template<typename U, ANGLE_RANGE RNG>
    void operator-=(const Angle<U, RNG>& other)
    {
      val -= other.val;
      wrap();
    }

    template<typename U>
    Angle operator+(const U& other) const
    {
      Angle res;
      res.val = val + other;
      res.wrap();
      return res;
    }
    template<typename U>
    void operator+=(const U& other)
    {
      val += other;
      wrap();
    }
    template<typename U>
    Angle operator-(const U& other) const
    {
      Angle res;
      res.val = val - other;
      res.wrap();
      return res;
    }
    template<typename U>
    void operator-=(const U& other)
    {
      val -= other;
      wrap();
    }

    T& operator()(int dummy = 0)
    {
      (void)dummy;
      return val;
    }
    const T& operator()(int dummy = 0) const
    {
      (void)dummy;
      return val;
    }

    // template<typename U, ANGLE_RANGE RNG>
    // Angle<U, RNG> cast()
    // {
    // }


   private:
    void wrap()
    {
      if (RANGE == ANGLE_RANGE::MINUS_PI_TO_PI)
      {
        val = fmod(val + PI<T>(), PI2<T>());
        if (val < T(0))
          val = val + PI<T>();
        else
          val -= PI<T>();
      }
      else if (RANGE == ANGLE_RANGE::ZERO_TO_TWO_PI)
      {
        val = fmod(val, PI2<T>());
        if (val < T(0))
          val = val + PI2<T>();
      }
    };

    T val{ 0 };
  };
};  // namespace lwm