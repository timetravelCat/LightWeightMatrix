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
  using const_size_t = typename integral_constant<size_t, N>::type;
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
    typedef T data_array[N];
    template<typename, size_t, size_t>
    friend class Matrix;

   public:
    Matrix() = default;

    /**
     * @brief Construct a new Matrix object
     *
     * @tparam U type of 1D array.
     * @tparam L length of 1D array, supports compile-time checking for size.
     */
    template<typename U, size_t L>
    explicit Matrix(const U (&in)[L])
    {
      size_t m{ 0 }, n{ 0 };
      for (size_t i = 0; i < L; i++)
      {
        data[m][n] = static_cast<allowed_cast_t<T, U>>(in[i]);
        if (++n == N)
        {
          m++;
          n = 0;
        }
      }
    }
    /**
     * @brief Construct a new Matrix object
     *
     * @tparam U type of 1D array.
     * @tparam L length of 1D array, supports compile-time checking for size.
     */
    template<typename U, size_t L>
    Matrix<T, M, N>& operator=(const U (&in)[L])
    {
      size_t m{ 0 }, n{ 0 };
      for (size_t i = 0; i < L; i++)
      {
        data[m][n] = static_cast<allowed_cast_t<T, U>>(in[i]);
        if (++n == N)
        {
          m++;
          n = 0;
        }
      }
      return (*this);
    }
    /**
     * @brief Construct a new Matrix object
     *
     * @tparam U type of 2D array.
     */
    template<typename U>
    explicit Matrix(const U (&in)[M][N])
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i][j]);
    }
    /**
     * @brief Construct a new Matrix object, do not supports assert from size of array, recommend to use const_size_t type.
     *
     * @tparam U type of 2D array.
     * @tparam R row of input array
     * @tparam C col of input array
     * @param r first row index of data.
     * @param c first col index of data.
     */
    template<typename U, size_t R, size_t C, typename type_ = size_t, typename = enable_if_t<are_fixed_point<type_>::value>>
    explicit Matrix(const U (&in)[R][C], type_ r_ = type_(0), type_ c_ = type_(0))
    {
      const size_t r = static_cast<size_t>(r_);
      const size_t c = static_cast<size_t>(c_);
      size_static_assert<R, C, 0, 0>();
      size_assert<R, C>(r, c);
      // Todo :: Call SetZero?
      for (size_t i = r; i < r + R; i++)
        for (size_t j = c; j < c + C; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i - r][j - c]);
    };
    /**
     * @brief Corresponding copy constructor of the constructor Matrix(const U (&in)[R][C])
     *
     * @tparam U type of 2D array.
     * @tparam R row of input array.
     * @tparam C col of input array
     */
    template<typename U, size_t R, size_t C>
    Matrix<T, M, N>& operator=(const U (&in)[R][C])
    {
      size_static_assert<R, C, 0, 0>();
      // Todo :: Call SetZero?
      for (size_t i = 0; i < R; i++)
        for (size_t j = 0; j < C; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i][j]);
      return (*this);
    }
    /**
     * @brief Construct a new Matrix object, supports static assert from sizes of array and start index of row and col.
     *
     * @tparam U type of 2D array.
     * @tparam R row of input array
     * @tparam C col of input array
     * @param r first row index of data.
     * @param c first col index of data.
     */
    template<
        typename U,
        size_t R,
        size_t C,
        typename r,
        typename c,
        typename = enable_if_t<is_same<const_size_t<r::value>, r>::value && is_same<const_size_t<c::value>, c>::value, void>>
    explicit Matrix(const U (&in)[R][C], r, c)
    {
      size_static_assert<R, C, r::value, c::value>();
      // Todo :: Call SetZero?
      for (size_t i = r::value; i < r::value + R; i++)
        for (size_t j = c::value; j < c::value + C; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i - r::value][j - c::value]);
    };
    /**
     * @brief Copy Constructor from other type of Matrix Object.
     *
     * @tparam U type of Matrix object.
     */
    template<typename U>
    explicit Matrix(const Matrix<U, M, N>& in)
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in.data[i][j]);
    }
    /**
     * @brief Copy constructor(operator=) from same type of Matrix object.
     *
     * @param in Matrix object
     * @return Matrix<T, M, N>& current Matrix object.
     */
    Matrix<T, M, N>& operator=(const Matrix<T, M, N>& in)
    {
      if (this != const_cast<Matrix<T, M, N>*>(&in))
        for (size_t i = 0; i < M; i++)
          for (size_t j = 0; j < N; j++)
            data[i][j] = in.data[i][j];
      return (*this);
    }
    /**
     * @brief Copy constructor(operator=) from other type of Matrix object.
     *
     * @tparam U type of Matrix object
     * @return Matrix<T, M, N>& current Matrix object.
     */
    template<typename U>
    Matrix<T, M, N>& operator=(const Matrix<U, M, N>& in)
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in.data[i][j]);
      return (*this);
    }

    /**
     * @brief Accessors by()
     *
     * @param i rows
     * @param j cols
     * @return const T& data[i][j]
     */
    inline const T& operator()(size_t i, size_t j) const
    {
      assert(i < M);
      assert(j < N);

      return data[i][j];
    }
    /**
     * @brief  Accessors by()
     * 
     * @param i rows
     * @param j cols
     * @return T& 
     */
    inline T& operator()(size_t i, size_t j)
    {
      assert(i < M);
      assert(j < N);

      return data[i][j];
    }
    /**
     * @brief Accessors by [][], it dose not support column size checking.
     *
     * @param i rows
     * @return const T*&
     */
    inline const data_array& operator[](size_t i) const
    {
      assert(i < M);
      return data[i];
    }
    /**
     * @brief Accessors by [][], it dose not support column size checking.
     *
     * @param i rows
     * @return const T*&
     */
    inline data_array& operator[](size_t i) 
    {
      assert(i < M);
      return data[i];
    }
   private:
    template<size_t R, size_t C, size_t r, size_t c>
    static void size_static_assert()
    {
      static_assert(((M >= (R + r)) && (N >= (C + c))), "Matrix Size Error.");
    }
    template<size_t R, size_t C, typename type_ = size_t, typename = enable_if_t<are_fixed_point<type_>::value>>
    static void size_assert(const type_& r, const type_& c)
    {
      assert((M >= (R + static_cast<size_t>(r))) && (N >= (C + static_cast<size_t>(c))));
    }
  };
};  // namespace lwm