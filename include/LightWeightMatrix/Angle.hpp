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
#include "Matrix.hpp"
#include "Common.hpp"
#include "internal/type_helper.hpp"
namespace lwm
{
  enum class Range
  {
    MINUS_PI_TO_PI, //
    ZERO_TO_TWO_PI
  };



  using namespace internal;
  template<typename T>
  class Angle
  {
   public:
    static T RAD2DEG(const T& rad) {return rad*T(180)/PI<T>();}
    static T DEG2RAD(const T& deg) {return deg*PI<T>()/T(180);}
    // static T RAD2DEG(const T& rad) {return M_PIf}

    // https://github.com/ros/angles/blob/ros2/angles/include/angles/angles.h
    // https://softwareengineering.stackexchange.com/questions/272084/well-defined-mathematical-operations-for-bearing-angle-class
    // Static Methods
    // RAD2DEG
    // DEG2RAD
    // Wrap Functions 
    
   private:
  };
};  // namespace lwm