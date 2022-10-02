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

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "Common.hpp"
#include "internal/type_helper.hpp"

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
  template<typename T, size_t M, size_t N, typename = enable_if_t<(M > 0) && (N > 0)>>
  class Matrix
  {
   protected:
    T data[M][N]{};
    typedef T data_array[N];
    template<typename, size_t, size_t, typename>
    friend class Matrix;

   public:
    constexpr static size_t SIZE{ M * N };
    Matrix() = default;

    // static methods of constants, starts with Upper case.
    static Matrix Zero()
    {
      return Matrix();
    }
    template<typename T_ = T>
    static enable_if_t<is_floating_point<T_>::value, Matrix> NaN()
    {
      Matrix res;
      res.fill(NAN);
      return res;
    }
    static Matrix Constant(T value)
    {
      Matrix res;
      res.fill(value);
      return res;
    }
    static Matrix Identity()
    {
      Matrix res;
      for (size_t i = 0; i < internal::min<size_t, M, N>::value; i++)
        res.data[i][i] = static_cast<T>(1);
      return res;
    }

    /**
     * @brief Mathmatical operations
     */
    template<typename U, size_t P>
    Matrix<implicit_cast_t<T, U>, M, P> operator*(const Matrix<U, N, P>& other) const
    {
      Matrix<implicit_cast_t<T, U>, M, P> res;
      for (size_t i = 0; i < M; i++)
        for (size_t k = 0; k < P; k++)
          for (size_t j = 0; j < N; j++)
            res.data[i][k] += data[i][j] * other.data[j][k];
      return res;
    }
    template<typename U, size_t P>
    void operator*=(const Matrix<U, N, P>& other)
    {
      (*this) = (*this) * other;
    }
    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> operator*(U other) const
    {
      Matrix<implicit_cast_t<T, U>, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[i][j] = data[i][j] * other;
      return res;
    }
    template<typename U>
    void operator*=(U other)
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] = data[i][j] * other;
    }
    template<typename U>
    friend Matrix<implicit_cast_t<T, U>, M, N> operator*(U other, const Matrix& m)
    {
      Matrix<implicit_cast_t<T, U>, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[i][j] = m.data[i][j] * other;
      return res;
    }

    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> operator/(U other) const
    {
      Matrix<implicit_cast_t<T, U>, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[i][j] = data[i][j] / other;
      return res;
    }
    template<typename U>
    void operator/=(U other)
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] /= other;
    }

    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> operator+(const Matrix<U, M, N>& other) const
    {
      Matrix<implicit_cast_t<T, U>, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[i][j] = data[i][j] + other.data[i][j];
      return res;
    }
    template<typename U>
    void operator+=(const Matrix<U, M, N>& other)
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] += other.data[i][j];
    }
    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> operator+(U other) const
    {
      Matrix<implicit_cast_t<T, U>, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[i][j] = data[i][j] + other;
      return res;
    }
    template<typename U>
    void operator+=(U other)
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] += other;
    }
    template<typename U>
    friend Matrix<implicit_cast_t<T, U>, M, N> operator+(U other, const Matrix& m)
    {
      Matrix<implicit_cast_t<T, U>, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res[i][j] = m.data[i][j] + other;
      return res;
    }

    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> operator-(const Matrix<U, M, N>& other) const
    {
      Matrix<implicit_cast_t<T, U>, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[i][j] = data[i][j] - other.data[i][j];
      return res;
    }
    template<typename U>
    void operator-=(const Matrix<U, M, N>& other)
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] -= other.data[i][j];
    }
    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> operator-(U other) const
    {
      Matrix<implicit_cast_t<T, U>, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[i][j] = data[i][j] - other;
      return res;
    }
    template<typename U>
    void operator-=(U other)
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] -= other;
    }
    template<typename U>
    friend Matrix<implicit_cast_t<T, U>, M, N> operator-(U other, const Matrix& m)
    {
      Matrix<implicit_cast_t<T, U>, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[i][j] = other - m.data[i][j];
      return res;
    }

    template<typename U>
    bool operator==(const Matrix<U, M, N>& other) const
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          if (!isSame(data[i][j], other.data[i][j]))
            return false;
      return true;
    }
    template<typename U>
    bool operator!=(const Matrix<U, M, N>& other) const
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          if (!isSame(data[i][j], other.data[i][j]))
            return true;
      return false;
    }

    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> elementWiseMultiply(const Matrix<U, M, N>& other) const
    {
      Matrix<implicit_cast_t<T, U>, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[i][j] = other[i][j] * data[i][j];
      return res;
    }
    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> elementWiseDivide(const Matrix<U, M, N>& other) const
    {
      Matrix<implicit_cast_t<T, U>, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[i][j] = data[i][j] / other[i][j];
      return res;
    }

    template<typename T_ = T>
    enable_if_t<is_signed<T_>::value, Matrix<T_, M, N>> abs() const
    {
      Matrix<T_, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[i][j] = fabs(data[i][j]);
      return res;
    }
    template<typename T_ = T>
    enable_if_t<are_floating_point<T_>::value, bool> isAllNan() const
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          if (!isnan(data[i][j]))
            return false;
      return true;
    }
    template<typename T_ = T>
    enable_if_t<are_floating_point<T_>::value, bool> isAnyNan() const
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          if (isnan(data[i][j]))
            return true;
      return false;
    }

    T max() const
    {
      T max_val = data[0][0];
      for (size_t i = 0; i < M; i++)
      {
        for (size_t j = 0; j < N; j++)
        {
          T val = data[i][j];
          if (val > max_val)
          {
            max_val = val;
          }
        }
      }
      return max_val;
    }
    T min() const
    {
      T min_val = data[0][0];
      for (size_t i = 0; i < M; i++)
      {
        for (size_t j = 0; j < N; j++)
        {
          T val = data[i][j];
          if (val < min_val)
          {
            min_val = val;
          }
        }
      }
      return min_val;
    }

    /**
     * @brief get info char array
     */
    // struct MatrixInfo
    // {
    //     // char info[func(M*N)]
    // };

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
    template<size_t offset, typename U, size_t L>
    void toArray(U (&out)[L]) const
    {
      static_assert((L >= SIZE), "toArray : matrix constructor from array size error");
      static_assert(offset <= L, "toArray : matrix constructor from array size error");
      static_assert((L - offset >= SIZE), "toArray : matrix constructor from array size error");
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
    template<size_t offset_r, size_t offset_c, typename U, size_t R, size_t C>
    void toArray(U (&out)[R][C]) const
    {
      static_assert(R > offset_r, "toArray matrix row size error");
      static_assert(C > offset_c, "toArray matrix col size error");
      static_assert((M <= R - offset_r) && (N <= C - offset_c), "toArray matrix size error");
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          out[i + offset_r][j + offset_c] = static_cast<allowed_cast_t<T, U>>(data[i][j]);
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

    // Todo : Specialization when N == 1 or M == 1
    // template<typename U, size_t L, typename = enable_if<N==1>>
    // explicit Matrix(const U (&in)[L], size_t offset = size_t(0))
    // {
    // static_assert((L <= SIZE), "matrix constructor from array size error");
    // assert((L + offset <= SIZE));
    // size_t m{ offset / N }, n{ offset % N };
    // for (size_t i = 0; i < L; i++)
    // {
    //   data[m][n] = static_cast<allowed_cast_t<T, U>>(in[i]);
    //   if (++n == N)
    //   {
    //     m++;
    //     n = 0;
    //   }
    // }
    // }

    // if M or N => disable [] () operator by template or virtual or overloading in Matrix class
    // Override or redefine [], (), when N or M == 1

    /**
     * @brief Compile time, get column of Matrix
     *
     * @tparam c index of column
     */
    template<size_t c>
    Matrix<T, M, 1> col() const
    {
      static_assert(c < N, "requested column index over the size of column");
      Matrix<T, M, 1> res;
      for (size_t i = 0; i < M; i++)
        res.data[i][0] = data[i][c];
      return res;
    }
    Matrix<T, M, 1> col(size_t c) const
    {
      assert(c < N);
      Matrix<T, M, 1> res;
      for (size_t i = 0; i < M; i++)
        res.data[i][0] = data[i][c];
      return res;
    }
    template<size_t c, typename U>
    void setCol(U in)
    {
      static_assert(c < N, "requested column index over the size of column");
      for (size_t i = 0; i < M; i++)
        data[i][c] = static_cast<allowed_cast_t<T, U>>(in);
    }
    template<typename U>
    void setCol(size_t c, U in)
    {
      assert(c < N);
      for (size_t i = 0; i < M; i++)
        data[i][c] = static_cast<allowed_cast_t<T, U>>(in);
    }
    template<size_t c, typename U>
    void setCol(const Matrix<U, M, 1>& in)
    {
      static_assert(c < N, "requested col index over the size of row");
      for (size_t i = 0; i < M; i++)
        data[i][c] = static_cast<allowed_cast_t<T, U>>(in.data[i][0]);
    }
    template<typename U>
    void setCol(size_t c, const Matrix<U, M, 1>& in)
    {
      assert(c < N);
      for (size_t i = 0; i < M; i++)
        data[i][c] = static_cast<allowed_cast_t<T, U>>(in.data[i][0]);
    }
    template<size_t c, typename U, size_t L>
    void setCol(const U (&in)[L])
    {
      static_assert(c < N, "requested col index over the size of row");
      static_assert(L <= M, "array input length is over the matrix row");
      for (size_t i = 0; i < L; i++)
        data[i][c] = static_cast<allowed_cast_t<T, U>>(in[i]);
    }
    template<typename U, size_t L>
    void setCol(size_t c, const U (&in)[L])
    {
      assert(c < N);
      static_assert(L <= M, "array input length is over the matrix row");
      for (size_t i = 0; i < L; i++)
        data[i][c] = static_cast<allowed_cast_t<T, U>>(in[i]);
    }

    /**
     * @brief Compile time, get row of Matrix
     *
     * @tparam r index of row
     */
    template<size_t r>
    Matrix<T, 1, N> row() const
    {
      static_assert(r < M, "requested row index over the size of row");
      Matrix<T, 1, N> res;
      for (size_t i = 0; i < N; i++)
        res.data[0][i] = data[r][i];
      return res;
    }
    Matrix<T, 1, N> row(size_t r) const
    {
      assert(r < M);
      Matrix<T, 1, N> res;
      for (size_t i = 0; i < N; i++)
        res.data[0][i] = data[r][i];
      return res;
    }
    template<size_t r, typename U>
    void setRow(U in)
    {
      static_assert(r < M, "requested row index over the size of column");
      for (size_t i = 0; i < N; i++)
        data[r][i] = static_cast<allowed_cast_t<T, U>>(in);
    }
    template<typename U>
    void setRow(size_t r, U in)
    {
      assert(r < M);
      for (size_t i = 0; i < N; i++)
        data[r][i] = static_cast<allowed_cast_t<T, U>>(in);
    }
    template<size_t r, typename U>
    void setRow(const Matrix<U, 1, N>& in)
    {
      static_assert(r < M, "requested row index over the size of column");
      for (size_t i = 0; i < N; i++)
        data[r][i] = static_cast<allowed_cast_t<T, U>>(in.data[0][i]);
    }
    template<typename U>
    void setRow(size_t r, const Matrix<U, 1, N>& in)
    {
      assert(r < M);
      for (size_t i = 0; i < N; i++)
        data[r][i] = static_cast<allowed_cast_t<T, U>>(in.data[0][i]);
    }
    template<size_t r, typename U, size_t L>
    void setRow(const U (&in)[L])
    {
      static_assert(r < M, "requested row index over the size of column");
      static_assert(L <= N, "array input length is over the matrix column");
      for (size_t i = 0; i < L; i++)
        data[r][i] = static_cast<allowed_cast_t<T, U>>(in[i]);
    }
    template<typename U, size_t L>
    void setRow(size_t r, const U (&in)[L])
    {
      assert(r < M);
      static_assert(L <= N, "array input length is over the matrix column");
      for (size_t i = 0; i < L; i++)
        data[r][i] = static_cast<allowed_cast_t<T, U>>(in[i]);
    }

    /**
     * @brief Compile time matrix slice API.
     *
     * @tparam R size of target matrix row
     * @tparam C size of target matrix col
     * @tparam r copy row location
     * @tparam c copy col location
     * @return Matrix<T, R, C>
     */
    template<size_t R, size_t C, size_t r = 0, size_t c = 0>
    Matrix<T, R, C> slice() const
    {
      static_assert(R >= 1, "row size can not be zero.");
      static_assert(C >= 1, "col size can not be zero.");
      size_static_assert<R, C, r, c>();
      Matrix<T, R, C> res;
      for (size_t i = 0; i < R; i++)
        for (size_t j = 0; j < C; j++)
          res.data[i][j] = data[i + r][j + c];
      return res;
    }
    /**
     * @brief Return Transposed Matrix
     *
     * @return Matrix<T, N, M>
     */
    Matrix<T, N, M> transpose() const
    {
      Matrix<T, N, M> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[j][i] = data[i][j];
      return res;
    }
    /**
     * @brief fill operation
     */
    template<typename U>
    void fill(const U in)
    {
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          data[i][j] = static_cast<allowed_cast_t<T, U>>(in);
    }
    Matrix(const Matrix&) = default;
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
     * @brief Explicit conversion to different type
     */
    template<typename U>
    operator Matrix<U, M, N>() const
    {
      Matrix<U, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res[i][j] = static_cast<allowed_cast_t<U, T>>(data[i][j]);
      return res;
    }
    /**
     * @brief Cast operator to other type.
     */
    template<typename U, typename = enable_if_t<!is_same<U, T>::value>>
    Matrix<U, M, N> cast() const
    {
      Matrix<U, M, N> res;
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
          res.data[i][j] = static_cast<U>(data[i][j]);
      return res;
    }

    // if N or M == 1 => enable operator()(size_t i)
    template<typename T_ = T>
    inline const enable_if_t<M == 1 && N == 1, T_>& operator()() const
    {
      return data[0][0];
    }
    template<typename T_ = T>
    inline enable_if_t<M == 1 && N == 1, T_>& operator()()
    {
      return data[0][0];
    }
    template<typename T_ = T>
    inline const enable_if_t<M == 1 && N != 1, T_>& operator()(size_t i) const
    {
      assert(i < N);
      return data[0][i];
    }
    template<typename T_ = T>
    inline enable_if_t<M == 1 && N != 1, T_>& operator()(size_t i)
    {
      assert(i < N);
      return data[0][i];
    }
    template<typename U, typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M == 1 && N != 1, T>>
    inline const res& operator()(U) const
    {
      static_assert(U::value < N, "() access row size error");
      return data[0][U::value];
    }
    template<typename U, typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M == 1 && N != 1, T>>
    inline res& operator()(U)
    {
      static_assert(U::value < N, "() access row size error");
      return data[0][U::value];
    }
    template<typename dummy = void, typename T_ = T>
    inline const enable_if_t<M != 1 && N == 1, T_>& operator()(size_t i) const
    {
      assert(i < M);
      return data[i][0];
    }
    template<typename dummy = void, typename T_ = T>
    inline enable_if_t<M != 1 && N == 1, T_>& operator()(size_t i)
    {
      assert(i < M);
      return data[i][0];
    }
    template<
        typename dummy = void,
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N == 1, T>>
    inline const res& operator()(U) const
    {
      static_assert(U::value < M, "() access column size error");
      return data[U::value][0];
    }
    template<
        typename dummy = void,
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N == 1, T>>
    inline res& operator()(U)
    {
      static_assert(U::value < M, "() access column size error");
      return data[U::value][0];
    }
    template<typename T_ = T>
    inline const enable_if_t<M == 1 && N != 1, T_>& operator[](size_t i) const
    {
      assert(i < N);
      return data[0][i];
    }
    template<typename T_ = T>
    inline enable_if_t<M == 1 && N != 1, T_>& operator[](size_t i)
    {
      assert(i < N);
      return data[0][i];
    }
    template<typename U, typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M == 1 && N != 1, T>>
    inline const res& operator[](U) const
    {
      static_assert(U::value < N, "() access row size error");
      return data[0][U::value];
    }
    template<typename U, typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M == 1 && N != 1, T>>
    inline res& operator[](U)
    {
      static_assert(U::value < N, "() access row size error");
      return data[0][U::value];
    }
    template<typename dummy = void, typename T_ = T>
    inline const enable_if_t<M != 1 && N == 1, T_>& operator[](size_t i) const
    {
      assert(i < M);
      return data[i][0];
    }
    template<typename dummy = void, typename T_ = T>
    inline enable_if_t<M != 1 && N == 1, T_>& operator[](size_t i)
    {
      assert(i < M);
      return data[i][0];
    }
    template<
        typename dummy = void,
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N == 1, T>>
    inline const res& operator[](U) const
    {
      static_assert(U::value < M, "() access column size error");
      return data[U::value][0];
    }
    template<
        typename dummy = void,
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N == 1, T>>
    inline res& operator[](U)
    {
      static_assert(U::value < M, "() access column size error");
      return data[U::value][0];
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

   protected:
    template<bool isConst>
    class accessor
    {
     protected:
      template<typename U, size_t R, size_t C, typename>
      friend class Matrix;

     public:
      typedef conditional_t<isConst, const T, T> T_;
      conditional_t<isConst, const data_array&, data_array&> data_;
      accessor() = delete;
      explicit accessor(const accessor&) = delete;
      explicit accessor(conditional_t<isConst, const data_array&, data_array&> data) : data_{ data }
      {
      }

      inline T_& operator[](size_t j)
      {
        assert(j < N);
        return data_[j];
      }
      template<typename U, typename = enable_if_t<is_same<const_size_t<U::value>, U>::value>>
      inline T_& operator[](U)
      {
        static_assert(U::value < N, "[] access col size error");
        return data_[U::value];
      }
      inline T_& operator()(size_t j)
      {
        assert(j < N);
        return data_[j];
      }
      template<typename U, typename = enable_if_t<is_same<const_size_t<U::value>, U>::value>>
      inline T_& operator()(U)
      {
        static_assert(U::value < N, "() access col size error");
        return data_[U::value];
      }
    };

   public:
    /**
     * @brief Accessors by [row][col], it dose not support column size checking.
     */
    template<typename T_ = accessor<true>>
    inline enable_if_t<M != 1 && N != 1, T_> operator[](size_t i) const
    {
      assert(i < M);
      return accessor<true>{ data[i] };
    }
    /**
     * @brief const Accessors by [row][col], supports compile time size check
     */
    template<
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N != 1, accessor<true>>>
    inline res operator[](U) const
    {
      static_assert(U::value < M, "[] access row size error");
      return accessor<true>{ data[U::value] };
    }
    /**
     * @brief Accessors by [row][col], it dose not support column size checking.
     */
    template<typename T_ = accessor<false>>
    inline enable_if_t<M != 1 && N != 1, T_> operator[](size_t i)
    {
      assert(i < M);
      return T_{ data[i] };
    }
    /**
     * @brief Accessors by [row][col], supports compile time size check
     */
    template<
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N != 1, accessor<false>>>
    inline res operator[](U)
    {
      static_assert(U::value < M, "[] access row size error");
      return res{ data[U::value] };
    }
    /**
     * @brief Accessors by [row][col], it dose not support column size checking.
     */
    template<typename T_ = accessor<true>>
    inline enable_if_t<M != 1 && N != 1, T_> operator()(size_t i) const
    {
      assert(i < M);
      return accessor<true>{ data[i] };
    }
    /**
     * @brief const Accessors by [row][col], supports compile time size check
     */
    template<
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N != 1, accessor<true>>>
    inline res operator()(U) const
    {
      static_assert(U::value < M, "() access row size error");
      return accessor<true>{ data[U::value] };
    }
    /**
     * @brief Accessors by (row)(col), it dose not support column size checking.
     */
    template<typename T_ = accessor<false>>
    inline enable_if_t<M != 1 && N != 1, T_> operator()(size_t i)
    {
      assert(i < M);
      return T_{ data[i] };
    }
    /**
     * @brief Accessors by (row)(col), supports compile time size check
     */
    template<
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N != 1, accessor<false>>>
    inline res operator()(U)
    {
      static_assert(U::value < M, "() access row size error");
      return res{ data[U::value] };
    }

   protected:
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