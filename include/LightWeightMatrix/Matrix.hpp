/**
 * @file Matrix.hpp
 * @author InGyuChoi (timetraveler930@gmail.com)
 * @brief A template based matrix library.
 * @version 0.1
 * @date 2022-09-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string.h>  //used for info

#include "assert.h"
#include "stdio.h"
#include "type_helper.hpp"

namespace lwm
{
  using namespace internal;
  template<size_t N>
  using const_size_t = integral_constant<size_t, N>;
  /**
   * @brief A template based Matrix class
   *
   * @tparam T type
   * @tparam M rows
   * @tparam N cols
   */
  template<typename T, size_t M, size_t N>
  class Matrix
  {
    T data[M][N]{};
    template<size_t R, size_t C, size_t r, size_t c>
    static void size_static_assert()
    {
      static_assert(((M >= (R + r)) && (N >= (C + c))), "Matrix Size Error.");
    }
    template<size_t R, size_t C>
    static void size_assert(const size_t& r, const size_t& c)
    {
      assert((M >= (R + r)) && (N >= (C + c)));
    }

   public:
    Matrix() = default;
    template<typename U>
    explicit Matrix(const U (&in)[M * N])
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in[N * i + j]);
    }
    template<typename U>
    explicit Matrix(const U (&in)[M][N])
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i][j]);
    }
    template<typename U, size_t R, size_t C>
    explicit Matrix(const U (&in)[R][C])
    {
      size_static_assert<R, C, 0, 0>();
      // Todo :: Call SetZero?
      for (size_t i = 0; i < R; i++)
        for (size_t j = 0; j < C; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i][j]);
    };
    template<typename U, size_t R, size_t C>
    explicit Matrix(const U (&in)[R][C], size_t r, size_t c)
    {
      size_assert<R, C>(r, c);
      // Todo :: Call SetZero?
      for (size_t i = r; i < r + R; i++)
        for (size_t j = c; j < c + C; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i][j]);
    };
    template<typename U, size_t R, size_t C, size_t r, size_t c>
    explicit Matrix(const T (&in)[R][C], const_size_t<r>, const_size_t<c>)
    {
      size_static_assert<R, C, r, c>();
      // Todo :: Call SetZero?
      for (size_t i = r; i < r + R; i++)
        for (size_t j = c; j < c + C; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i][j]);
    };
    template<typename U>
    explicit Matrix(const Matrix<U, M, N>& in)
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in.data[i][j]);
    }
    Matrix<T, M, N>& operator=(const Matrix<T, M, N>& in)
    {
      if (this != const_cast<Matrix<T, M, N>*>(&in))
        for (size_t i = 0; i < M; i++)
          for (size_t j = 0; j < N; j++)
            data[i][j] = in.data[i][j];
      return (*this);
    }
    template<typename U>
    Matrix<T, M, N>& operator=(const Matrix<U, M, N>& in)
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in.data[i][j]);
      return (*this);
    }
    template<typename, size_t, size_t>
    friend class Matrix;
  };

};  // namespace lwm