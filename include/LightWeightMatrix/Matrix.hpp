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

#define constexpr_size_t(x) lwm::const_size_t<x>()

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
    constexpr static size_t SIZE{ M * N };
    Matrix() = default;

    // check initializer_list supported or not. (compiler-dependent.)
    // initialization using initializer_list
    // Hadamard(elementwise) product / elementwise devide
    // operator* / operator+ / operator- / += / -= / *= / ...
    // get info string / transpose
    // slice / row / col / serRow, setCol/ ... / Zero, / setAll / Identity, swap? abs ? max, min / nan check ...

    /**
     * @brief Copy to 1D array Type.
     *
     * @tparam U type of array.
     * @tparam L Length of array.
     * @param offset offset of copied array.
     */
    template<typename U, size_t L>
    void toArray(U (&out)[L], size_t offset = size_t(0)) const
    {
      static_assert((L >= SIZE), "matrix constructor from array size error");
      assert(offset <= L);
      assert((L - offset >= SIZE));
      size_t m{ 0 }, n{ 0 };
      for (size_t i = offset; i < offset + SIZE; i++)
      {
        out[i] = static_cast<allowed_cast_t<T, U>>(data[m][n]);
        if (++n == N)
        {
          m++;
          n = 0;
        }
      }
    }
    /**
     * @brief Copy to 1D array Type, supports compile time size checking
     *
     * @tparam U type of array.
     * @tparam L Length of array.
     * @tparam type_ enabled only if unsigned constexpr_cast_size_t type.
     */
    template<
        typename U,
        size_t L,
        typename type_,
        typename = enable_if_t<is_same<const_size_t<type_::value>, type_>::value, type_>>
    void toArray(U (&out)[L], type_) const
    {
      static_assert((L >= SIZE), "toArray : matrix constructor from array size error");
      static_assert(type_::value <= L, "toArray : matrix constructor from array size error");
      static_assert((L - type_::value >= SIZE), "toArray : matrix constructor from array size error");
      size_t m{ 0 }, n{ 0 };
      for (size_t i = type_::value; i < type_::value + SIZE; i++)
      {
        out[i] = static_cast<allowed_cast_t<T, U>>(data[m][n]);
        if (++n == N)
        {
          m++;
          n = 0;
        }
      }
    }
    /**
     * @brief Copy To 2D array.
     *
     * @tparam U type of array
     * @tparam R row size of array
     * @tparam C col size of array
     * @param r_ row offset of array.
     * @param c_ col offset of array
     */
    template<typename U, size_t R, size_t C>
    void toArray(U (&out)[R][C], size_t r = size_t(0), size_t c = size_t(0)) const
    {
      static_assert((M <= R) && (N <= C), "toArray matrix size error");
      assert(R > r);
      assert(C > c);
      assert((M <= R - r) && (N <= C - c));
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          out[i + r][j + c] = static_cast<allowed_cast_t<T, U>>(data[i][j]);
    }
    /**
     * @brief Copy To 2D array, supports compile time size check.
     */
    template<
        typename U,
        size_t R,
        size_t C,
        typename r,
        typename c,
        typename = enable_if_t<is_same<const_size_t<r::value>, r>::value && is_same<const_size_t<c::value>, c>::value, void>>
    void toArray(U (&out)[R][C], r, c) const
    {
      static_assert(R > r::value, "toArray matrix row size error");
      static_assert(C > c::value, "toArray matrix col size error");
      static_assert((M <= R - r::value) && (N <= C - c::value), "toArray matrix size error");
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          out[i + r::value][j + c::value] = static_cast<allowed_cast_t<T, U>>(data[i][j]);
    }
    /**
     * @brief Construct a new Matrix object from 1D array.
     *
     * @tparam U type of 1D array.
     * @tparam L length of 1D array, supports compile-time checking for size.
     * @param offset container copied from this value.
     */
    template<typename U, size_t L>
    explicit Matrix(const U (&in)[L], size_t offset = size_t(0))
    {
      static_assert((L <= SIZE), "matrix constructor from array size error");
      assert((L + offset <= SIZE));
      size_t m{ offset / N }, n{ offset % N };
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
     * @brief Construct a new Matrix object from 1D array, supports compile-time size check.
     *
     * @tparam U type of 1D array.
     * @tparam L length of 1D array, supports compile-time checking for size.
     * @tparam type_ container copied from this value const_size_t<value>()
     */
    template<
        typename U,
        size_t L,
        typename type_,
        typename = enable_if_t<is_same<const_size_t<type_::value>, type_>::value, type_>>
    explicit Matrix(const U (&in)[L], type_)
    {
      static_assert((L + type_::value <= SIZE), "matrix constructor from array size error");
      assert((L + type_::value <= SIZE));
      size_t m{ type_::value / N }, n{ type_::value % N };
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
    template<typename U, size_t R, size_t C>
    explicit Matrix(const U (&in)[R][C], size_t r = size_t(0), size_t c = size_t(0))
    {
      size_static_assert<R, C, 0, 0>();
      size_assert<R, C>(r, c);
      // Todo :: Call SetZero?
      for (size_t i = r; i < r + R; i++)
        for (size_t j = c; j < c + C; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i - r][j - c]);
    }
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
    }
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
   private:
    template<bool isConst>
    class accessor
    {
      conditional_t<isConst, const data_array&, data_array&> data_;

     public:
      accessor() = delete;
      explicit accessor(const accessor&) = delete;
      explicit accessor(conditional_t<isConst, const data_array&, data_array&> data) : data_{ data }
      {
      }

      inline T& operator[](size_t j)
      {
        assert(j < N);
        return data_[j];
      }
      template<typename U, typename = enable_if_t<is_same<const_size_t<U::value>, U>::value>>
      inline T& operator[](U)
      {
        static_assert(U::value < N, "[] access col size error");
        return data_[U::value];
      }
      inline T& operator()(size_t j)
      {
        assert(j < N);
        return data_[j];
      }
      template<typename U, typename = enable_if_t<is_same<const_size_t<U::value>, U>::value>>
      inline T& operator()(U)
      {
        static_assert(U::value < N, "() access col size error");
        return data_[U::value];
      }
    };
   public:
    /**
     * @brief Accessors by [row][col], it dose not support column size checking.
     */
    inline accessor<true> operator[](size_t i) const
    {
      assert(i < M);
      return accessor<true>{ data[i] };
    }
    /**
     * @brief const Accessors by [row][col], supports compile time size check
     */
    template<typename U, typename = enable_if_t<is_same<const_size_t<U::value>, U>::value>>
    inline accessor<true> operator[](U) const
    {
      static_assert(U::value < M, "[] access row size error");
      return accessor<true>{ data[U::value] };
    }
    /**
     * @brief Accessors by [row][col], it dose not support column size checking.
     */
    inline accessor<false> operator[](size_t i)
    {
      assert(i < M);
      return accessor<false>{ data[i] };
    }
    /**
     * @brief Accessors by [row][col], supports compile time size check
     */
    template<typename U, typename = enable_if_t<is_same<const_size_t<U::value>, U>::value>>
    inline accessor<false> operator[](U)
    {
      static_assert(U::value < M, "[] access row size error");
      return accessor<false>{ data[U::value] };
    }
    /**
     * @brief Accessors by [row][col], it dose not support column size checking.
     */
    inline accessor<true> operator()(size_t i) const
    {
      assert(i < M);
      return accessor<true>{ data[i] };
    }
    /**
     * @brief const Accessors by [row][col], supports compile time size check
     */
    template<typename U, typename = enable_if_t<is_same<const_size_t<U::value>, U>::value>>
    inline accessor<true> operator()(U) const
    {
      static_assert(U::value < M, "() access row size error");
      return accessor<true>{ data[U::value] };
    }
    /**
     * @brief Accessors by (row)(col), it dose not support column size checking.
     */
    inline accessor<false> operator()(size_t i)
    {
      assert(i < M);
      return accessor<false>{ data[i] };
    }
    /**
     * @brief Accessors by (row)(col), supports compile time size check
     */
    template<typename U, typename = enable_if_t<is_same<const_size_t<U::value>, U>::value>>
    inline accessor<false> operator()(U) 
    {
      static_assert(U::value < M, "() access row size error");
      return accessor<false>{ data[U::value] };
    }

   private:
    template<size_t R, size_t C, size_t r, size_t c>
    static void size_static_assert()
    {
      static_assert(((M >= (R + r)) && (N >= (C + c))), "Matrix Size Error.");
    }
    template<
        size_t R,
        size_t C,
        typename type_ = size_t,
        typename = enable_if_t<are_fixed_point<type_>::value && is_unsigned<type_>::value>>
    static void size_assert(const type_& r, const type_& c)
    {
      assert((M >= (R + static_cast<size_t>(r))) && (N >= (C + static_cast<size_t>(c))));
    }
  };
};  // namespace lwm