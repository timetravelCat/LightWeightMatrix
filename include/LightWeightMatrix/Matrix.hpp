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
#include <stdlib.h>
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
   * @tparam T type of data, only primitive types are allowed.
   * @tparam M rows
   * @tparam N cols
   */
  template<typename T, size_t M, size_t N>
  class Matrix
  {
   protected:
    T data[M][N]{};
    typedef T data_array[N];
    template<typename, size_t, size_t>
    friend class Matrix;

   public:
    constexpr static size_t SIZE{ M * N };
    Matrix() = default;

    /**
     * @brief returns Static Zero Matrix.
     *
     * @return Matrix [M][N] initialized with Zero
     */
    static Matrix Zero();
    /**
     * @brief returns NaN Matrix.
     *
     * @return Matrix [M][N] initialized with NaN, enabled in only floating types.
     */
    template<typename T_ = T>
    static enable_if_t<is_floating_point<T_>::value, Matrix> NaN();
    /**
     * @brief returns Matrix filled with value.
     *
     * @param value
     * @return Matrix [M][N]
     */
    static Matrix Constant(T value);
    /**
     * @brief returns Identity Matrix. even if this is not a square matrix.
     *
     * @return Matrix [N][N]
     */
    static Matrix Identity();
    /**
     * @brief returns abs matrix.
     *
     * @return returns abs Matrix. enabled only type is floating point.
     */
    template<typename T_ = T>
    inline enable_if_t<is_floating_point<T_>::value, Matrix<T_, M, N>> abs() const;
    /**
     * @brief Check values are all NaN or not.
     *
     * @return Returns all value is nan or not. enabled only type is floating point.
     */
    template<typename T_ = T>
    inline enable_if_t<are_floating_point<T_>::value, bool> isAllNan() const;
    /**
     * @brief Check NaN value is contained or not.
     *
     * @return Returns any value is nan or not. enabled only type is floating point.
     */
    template<typename T_ = T>
    inline enable_if_t<are_floating_point<T_>::value, bool> isAnyNan() const;
    /**
     * @brief Returns Maximum value in Matrix.
     *
     * @return T maximum value
     */
    inline T max() const;
    /**
     * @brief Returns Minimum value in Matrix.
     *
     * @return T minimum value
     */
    inline T min() const;
    /**
     * @brief Returns element wise multiply between matrix.
     *
     * @return Matrix [M][N] with implicit casted between input matrix.
     */
    template<typename U>
    inline Matrix<implicit_cast_t<T, U>, M, N> elementWiseMultiply(const Matrix<U, M, N>& other) const;
    /**
     * @brief Returns element wise divide between matrix.
     *
     * @return Matrix [M][N] with implicit casted between input matrix.
     */
    template<typename U>
    inline Matrix<implicit_cast_t<T, U>, M, N> elementWiseDivide(const Matrix<U, M, N>& other) const;
    /**
     * @brief Copy to 1D array Type, copy from signed type to unsigned is not allowed.
     *
     * @tparam L Length of array.
     * @param offset offset of copied array, index of copy point.
     */
    template<typename U, size_t L>
    inline void toArray(U (&out)[L], size_t offset = size_t(0)) const;
    /**
     * @brief Copy to 1D array Type, supports compile time size checking, copy from signed type to unsigned is not allowed.
     *
     * @tparam L Length of array.
     * @tparam offset offset of copied array, index of copy point. supports compile time size check.
     */
    template<size_t offset, typename U, size_t L>
    inline void toArray(U (&out)[L]) const;
    /**
     * @brief Copy To 2D array. copy from signed type to unsigned is not allowed.
     *
     * @tparam U type of array
     * @tparam R row size of array
     * @tparam C col size of array
     * @param r row offset of array, index of copy point.
     * @param c col offset of array, index of copy point.
     */
    template<typename U, size_t R, size_t C>
    inline void toArray(U (&out)[R][C], size_t r = size_t(0), size_t c = size_t(0)) const;
    /**
     * @brief Copy To 2D array. copy from signed type to unsigned is not allowed.
     *
     * @tparam U type of array
     * @tparam R row size of array
     * @tparam C col size of array
     * @tparam r row offset of array, index of copy point. compile time size check enabled.
     * @tparam c col offset of array, index of copy point. compile time size check enabled.
     */
    template<size_t offset_r, size_t offset_c, typename U, size_t R, size_t C>
    inline void toArray(U (&out)[R][C]) const;
    /**
     * @brief Get column of Matrix, compile time size check enabled.
     *
     * @tparam c index of column
     */
    template<size_t c>
    inline Matrix<T, M, 1> col() const;
    /**
     * @brief Get column of Matrix
     *
     * @tparam c index of column
     */
    inline Matrix<T, M, 1> col(size_t c) const;
    /**
     * @brief Get row of Matrix, compile time size check enabled.
     *
     * @tparam r index of row
     */
    template<size_t r>
    inline Matrix<T, 1, N> row() const;
    /**
     * @brief Get row of Matrix
     *
     * @tparam r index of row
     */
    inline Matrix<T, 1, N> row(size_t r) const;

    /**
     * @brief Set column from value or column Matrix.
     */
    template<size_t c, typename U>
    inline void setCol(U in);
    template<typename U>
    inline void setCol(size_t c, U in);
    template<size_t c, typename U>
    inline void setCol(const Matrix<U, M, 1>& in);
    template<typename U>
    inline void setCol(size_t c, const Matrix<U, M, 1>& in);
    template<size_t c, typename U, size_t L>
    inline void setCol(const U (&in)[L]);
    template<typename U, size_t L>
    inline void setCol(size_t c, const U (&in)[L]);
    /**
     * @brief Set row from value or row Matrix.
     */
    template<size_t r, typename U>
    inline void setRow(U in);
    template<typename U>
    inline void setRow(size_t r, U in);
    template<size_t r, typename U>
    inline void setRow(const Matrix<U, 1, N>& in);
    template<typename U>
    inline void setRow(size_t r, const Matrix<U, 1, N>& in);
    template<size_t r, typename U, size_t L>
    inline void setRow(const U (&in)[L]);
    template<typename U, size_t L>
    inline void setRow(size_t r, const U (&in)[L]);

    /**
     * @brief Swap Row
     */
    inline void swapRow(const size_t& a, const size_t& b);
    /**
     * @brief Swap Col
     */
    inline void swapCol(const size_t& a, const size_t& b);

    /**
     * @brief if ColumnVector, converts to row vector (transpose)
     */
    template<typename T_ = T>
    inline enable_if_t<M == 1, Matrix<T_, N, 1>> toRowVector() const;
    /**
     * @brief if RowVector, converts to col vector (transpose)
     */
    template<typename T_ = T>
    inline enable_if_t<N == 1, Matrix<T_, 1, M>> toColVector() const;

    /**
     * @brief Explict cast operation. any type is allowed.
     */
    template<typename U, typename = enable_if_t<!is_same<U, T>::value>>
    inline Matrix<U, M, N> cast() const;
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
    inline Matrix<T, R, C> slice() const;
    /**
     * @brief Return Transposed Matrix
     *
     * @return Matrix<T, N, M>
     */
    inline Matrix<T, N, M> transpose() const;
    /**
     * @brief fill operation
     */
    template<typename U>
    inline void fill(const U in);
    /**
     * @brief return trace of Matrix.
     */
    template<typename T_ = T>
    enable_if_t<M == N, T_> trace() const;
    /**
     * @brief Returns inverse of the matrix 1x1. if not valid, return NaN matrix.
     */
    template<typename T_ = T, enable_if_t<M == N && is_floating_point<T_>::value && M == 1, void*> = nullptr>
    Matrix inv() const;
    /**
     * @brief Returns inverse of the matrix 1x1. if not valid, return NaN matrix.
     */
    template<typename T_ = T, enable_if_t<M == N && is_floating_point<T_>::value && M == 2, void*> = nullptr>
    Matrix inv() const;
    /**
     * @brief Returns inverse of the matrix 1x1. if not valid, return NaN matrix.
     */
    template<typename T_ = T, enable_if_t<M == N && is_floating_point<T_>::value && M == 3, void*> = nullptr>
    Matrix inv() const;
    /**
     * @brief Returns inverse of the matrix 1x1. if not valid, return NaN matrix.
     */
    template<typename T_ = T, enable_if_t<M == N && is_floating_point<T_>::value && (M > 3), void*> = nullptr>
    Matrix inv() const;
    template<typename T_ = T, enable_if_t<M == N && is_floating_point<T_>::value, void*> = nullptr>
    Matrix inv(size_t rank) const;
    /**
     * @brief return column vector composed of diagonal members
     */
    template<typename T_ = T, enable_if_t<M == N && is_floating_point<T_>::value, void*> = nullptr>
    Matrix<T, M, 1> diag() const;
    /**
     * @brief return CholeskyDecomposition with Rank. return lower triangular matrix
     */
    template<typename T_ = T, enable_if_t<M == N && is_floating_point<T_>::value, void*> = nullptr>
    Matrix choleskyDecomposition(size_t& rank) const;
    /**
     * @brief Fast Computation of Moore-Penrose Inverse Matrices, 8(2), 25–29. http://arxiv.org/abs/0804.4809
     */
    Matrix<T, N, M> pinv() const;

    /**
     * @brief rotation matrix functions
     */
    template<size_t M_ = M, enable_if_t<(M_ == 3) && (N == 3), void*> = nullptr>
    Matrix<T, M_, 1> vee() const;
    /**
     * @brief 1D functions
     */
    using Vector = conditional_t<N == 1, Matrix<T, M, 1>, Matrix<T, 1, N>>;

    template<size_t M_ = M, size_t N_ = N, enable_if_t<((M_ == 1 && N_ > 1) || (N_ == 1 && M_ > 1)), void*> = nullptr>
    inline T dot(const Vector& in) const;
    template<size_t M_ = M, size_t N_ = N, enable_if_t<((M_ == 1 && N_ > 1) || (N_ == 1 && M_ > 1)), void*> = nullptr>
    inline T norm() const;
    template<size_t M_ = M, size_t N_ = N, enable_if_t<((M_ == 1 && N_ > 1) || (N_ == 1 && M_ > 1)), void*> = nullptr>
    inline T normSquared() const;
    template<size_t M_ = M, size_t N_ = N, enable_if_t<((M_ == 1 && N_ > 1) || (N_ == 1 && M_ > 1)), void*> = nullptr>
    inline Vector unit(const T eps = T(1e-5)) const;
    template<size_t M_ = M, size_t N_ = N, enable_if_t<((M_ == 1 && N_ > 1) || (N_ == 1 && M_ > 1)), void*> = nullptr>
    inline Vector normalized(const T eps = T(1e-5)) const;
    template<size_t M_ = M, size_t N_ = N, enable_if_t<((M_ == 2 && N_ == 1) || (N_ == 2 && M_ == 1)), void*> = nullptr>
    inline T cross(const Vector& r) const;
    template<size_t M_ = M, size_t N_ = N, enable_if_t<((M_ == 3 && N_ == 1) || (N_ == 3 && M_ == 1)), void*> = nullptr>
    inline Vector cross(const Vector& r) const;
    template<size_t M_ = M, size_t N_ = N, enable_if_t<((M_ == 3 && N_ == 1) || (N_ == 3 && M_ == 1)), void*> = nullptr>
    inline Matrix<T, 3, 3> hat() const;
    template<size_t M_ = M, size_t N_ = N, enable_if_t<((M_ == 3 && N_ == 3)), void*> = nullptr>
    inline Matrix normalized(const T eps = T(1e-5)) const;

    /**
     * @brief Mathmatical operations
     */
    template<typename U, size_t P>
    Matrix<implicit_cast_t<T, U>, M, P> operator*(const Matrix<U, N, P>& other) const;
    template<typename U, size_t P>
    void operator*=(const Matrix<U, N, P>& other);
    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> operator*(U other) const;
    template<typename U>
    void operator*=(U other);
    template<typename U, typename T_, size_t M_, size_t N_>
    friend Matrix<implicit_cast_t<T, U>, M, N> operator*(U other, const Matrix& m);
    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> operator/(U other) const;
    template<typename U>
    void operator/=(U other);
    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> operator+(const Matrix<U, M, N>& other) const;
    template<typename U>
    void operator+=(const Matrix<U, M, N>& other);
    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> operator+(U other) const;
    template<typename U>
    void operator+=(U other);
    template<typename U, typename T_, size_t M_, size_t N_>
    friend Matrix<implicit_cast_t<T_, U>, M_, N_> operator+(U other, const Matrix<T_, M_, N_>& m);
    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> operator-(const Matrix<U, M, N>& other) const;
    template<typename U>
    void operator-=(const Matrix<U, M, N>& other);
    template<typename U>
    Matrix<implicit_cast_t<T, U>, M, N> operator-(U other) const;
    template<typename U>
    void operator-=(U other);
    template<typename U, typename T_, size_t M_, size_t N_>
    friend Matrix<implicit_cast_t<T_, U>, M_, N_> operator-(U other, const Matrix<T_, M_, N_>& m);
    template<typename U>
    bool operator==(const Matrix<U, M, N>& other) const;
    template<typename U>
    bool operator!=(const Matrix<U, M, N>& other) const;

    /**
     * @brief copy from 1D array, copy from signed to unsigned is not allowed.
     */
    template<typename U, size_t L>
    Matrix<T, M, N>& operator=(const U (&in)[L]);
    /**
     * @brief copy from 2D array, copy from signed to unsigned is not allowed.
     */
    template<typename U, size_t R, size_t C>
    Matrix<T, M, N>& operator=(const U (&in)[R][C]);
    /**
     * @brief Copy from Matrix.
     */
    template<typename U>
    Matrix<T, M, N>& operator=(const Matrix<U, M, N>& in);

    // /**
    //  * @brief get info char array
    //  */
    // struct Info
    // {
    //     char str[func(M*N)]
    // };
    // [][][][] //4자리수까지 지원? => point 까지 포함되어있을 수 있음.
    // []1 \t 2\ t3 \t4 \n
    // []1 \t 2\ t3 \t4 \n
    // []1 \t 2\ t3 \t4 \n\0

    /**
     * @brief Construct a new Matrix object from 1D array.
     *
     * @tparam U type of 1D array.
     * @tparam L length of 1D array, supports compile-time checking for size.
     * @param offset container copied from this value.
     */
    template<typename U, size_t L>
    explicit Matrix(const U (&in)[L], size_t offset = size_t(0));

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

    /**
     * @brief Construct a new Matrix object, filled with Zeros.
     */
    Matrix(const Matrix&) = default;
    /**
     * @brief Construct a new Matrix object from 1D array, supports compile-time size check.
     *
     * @tparam U type of 1D array.
     * @tparam L length of 1D array, supports compile-time size check.
     * @tparam type_ container copied from this value const_size_t<value>()
     */
    template<
        typename U,
        size_t L,
        typename type_,
        typename = enable_if_t<is_same<const_size_t<type_::value>, type_>::value, type_>>
    explicit Matrix(const U (&in)[L], type_);

    template<typename U>
    explicit Matrix(const U (&in)[M][N]);
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
    explicit Matrix(const U (&in)[R][C], size_t r = size_t(0), size_t c = size_t(0));

    /**
     * @brief Construct a new Matrix object, supports compile-time size check.
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
    explicit Matrix(const U (&in)[R][C], r, c);
    /**
     * @brief Copy Constructor from other type of Matrix Object.
     *
     * @tparam U type of Matrix object.
     */
    template<typename U>
    explicit Matrix(const Matrix<U, M, N>& in);
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
     * @brief matrix accessors [m][n] or (m)(n) or [l](if vector) or (l)(if vector) or (m, n)
     */

    template<typename T_ = T>
    inline const enable_if_t<M == 1 && N == 1, T_>& operator()() const;
    template<typename T_ = T>
    inline enable_if_t<M == 1 && N == 1, T_>& operator()();
    template<typename T_ = T>
    inline const enable_if_t<M == 1 && N != 1, T_>& operator()(size_t i) const;
    template<typename T_ = T>
    inline enable_if_t<M == 1 && N != 1, T_>& operator()(size_t i);
    template<typename U, typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M == 1 && N != 1, T>>
    inline const res& operator()(U) const;
    template<typename U, typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M == 1 && N != 1, T>>
    inline res& operator()(U);
    template<typename dummy = void, typename T_ = T>
    inline const enable_if_t<M != 1 && N == 1, T_>& operator()(size_t i) const;
    template<typename dummy = void, typename T_ = T>
    inline enable_if_t<M != 1 && N == 1, T_>& operator()(size_t i);
    template<
        typename dummy = void,
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N == 1, T>>
    inline const res& operator()(U) const;
    template<
        typename dummy = void,
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N == 1, T>>
    inline res& operator()(U);
    template<typename T_ = T>
    inline const enable_if_t<M == 1 && N != 1, T_>& operator[](size_t i) const;
    template<typename T_ = T>
    inline enable_if_t<M == 1 && N != 1, T_>& operator[](size_t i);
    template<typename U, typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M == 1 && N != 1, T>>
    inline const res& operator[](U) const;
    template<typename U, typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M == 1 && N != 1, T>>
    inline res& operator[](U);
    template<typename dummy = void, typename T_ = T>
    inline const enable_if_t<M != 1 && N == 1, T_>& operator[](size_t i) const;
    template<typename dummy = void, typename T_ = T>
    inline enable_if_t<M != 1 && N == 1, T_>& operator[](size_t i);
    template<
        typename dummy = void,
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N == 1, T>>
    inline const res& operator[](U) const;
    template<
        typename dummy = void,
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N == 1, T>>
    inline res& operator[](U);
    inline const T& operator()(size_t i, size_t j) const;
    inline T& operator()(size_t i, size_t j);

   protected:
    template<bool isConst>
    class accessor
    {
     protected:
      template<typename U, size_t R, size_t C>
      friend class Matrix;

     public:
      typedef conditional_t<isConst, const T, T> T_;
      conditional_t<isConst, const data_array&, data_array&> data_;
      // accessor() = delete;
      // explicit accessor(const accessor&) = delete;
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
    template<typename T_ = accessor<true>>
    inline enable_if_t<M != 1 && N != 1, T_> operator[](size_t i) const;
    template<
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N != 1, accessor<true>>>
    inline res operator[](U) const;
    template<typename T_ = accessor<false>>
    inline enable_if_t<M != 1 && N != 1, T_> operator[](size_t i);
    template<
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N != 1, accessor<false>>>
    inline res operator[](U);
    template<typename T_ = accessor<true>>
    inline enable_if_t<M != 1 && N != 1, T_> operator()(size_t i) const;
    template<
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N != 1, accessor<true>>>
    inline res operator()(U) const;
    template<typename T_ = accessor<false>>
    inline enable_if_t<M != 1 && N != 1, T_> operator()(size_t i);
    template<
        typename U,
        typename res = enable_if_t<is_same<const_size_t<U::value>, U>::value && M != 1 && N != 1, accessor<false>>>
    inline res operator()(U);

   protected:
    template<size_t R, size_t C, size_t r, size_t c>
    static void size_static_assert();
  };

  template<size_t M, size_t N>
  using Matrixi = Matrix<int, M, N>;
  template<size_t M, size_t N>
  using Matrixui = Matrix<unsigned int, M, N>;
  template<size_t M, size_t N>
  using Matrixf = Matrix<float, M, N>;
  template<size_t M, size_t N>
  using Matrixd = Matrix<double, M, N>;
  template<size_t M, size_t N>
  using Matrixld = Matrix<long double, M, N>;

  template<typename T, size_t N>
  using SquareMatrix = Matrix<T, N, N>;
  template<size_t N>
  using SquareMatrixi = SquareMatrix<int, N>;
  template<size_t N>
  using SquareMatrixui = SquareMatrix<unsigned int, N>;
  template<size_t N>
  using SquareMatrixf = SquareMatrix<float, N>;
  template<size_t N>
  using SquareMatrixd = SquareMatrix<double, N>;
  template<size_t N>
  using SquareMatrixld = SquareMatrix<long double, N>;

  template<typename T, size_t N>
  using RowVector = Matrix<T, 1, N>;
  template<size_t N>
  using RowVectori = RowVector<int, N>;
  template<size_t N>
  using RowVectorui = RowVector<unsigned int, N>;
  template<size_t N>
  using RowVectorf = RowVector<float, N>;
  template<size_t N>
  using RowVectord = RowVector<double, N>;
  template<size_t N>
  using RowVectorld = RowVector<long double, N>;

  template<typename T, size_t N>
  using ColVector = Matrix<T, N, 1>;
  template<size_t N>
  using ColVectori = ColVector<int, N>;
  template<size_t N>
  using ColVectorui = ColVector<unsigned int, N>;
  template<size_t N>
  using ColVectorf = ColVector<float, N>;
  template<size_t N>
  using ColVectord = ColVector<double, N>;
  template<size_t N>
  using ColVectorld = ColVector<long double, N>;

  template<typename T, size_t N>
  using Vector = ColVector<T, N>;
  template<size_t N>
  using Vectori = Vector<int, N>;
  template<size_t N>
  using Vectorui = Vector<unsigned int, N>;
  template<size_t N>
  using Vectorf = Vector<float, N>;
  template<size_t N>
  using Vectord = Vector<double, N>;
  template<size_t N>
  using Vectorld = Vector<long double, N>;

  template<typename T>
  using Vector2 = ColVector<T, 2>;
  using Vector2i = Vector<int, 2>;
  using Vector2ui = Vector<unsigned int, 2>;
  using Vector2f = Vector<float, 2>;
  using Vector2d = Vector<double, 2>;
  using Vector2ld = Vector<long double, 2>;

  template<typename T>
  using Vector3 = ColVector<T, 3>;
  using Vector3i = Vector<int, 3>;
  using Vector3ui = Vector<unsigned int, 3>;
  using Vector3f = Vector<float, 3>;
  using Vector3d = Vector<double, 3>;
  using Vector3ld = Vector<long double, 3>;

  template<typename T>
  using RotationMatrix = SquareMatrix<T, 3>;
  using RotationMatrixf = RotationMatrix<float>;
  using RotationMatrixd = RotationMatrix<double>;
  using RotationMatrixld = RotationMatrix<long double>;

  template<typename T>
  using DirectionCosineMatrix = RotationMatrix<T>;
  using DirectionCosineMatrixf = DirectionCosineMatrix<float>;
  using DirectionCosineMatrixd = DirectionCosineMatrix<double>;
  using DirectionCosineMatrixld = DirectionCosineMatrix<long double>;

  template<typename T>
  using DCM = DirectionCosineMatrix<T>;
  using DCMf = DCM<float>;
  using DCMd = DCM<double>;
  using DCMld = DCM<long double>;

};  // namespace lwm

#include "internal/_MatrixAccessors.hpp"
#include "internal/_MatrixConstructors.hpp"
#include "internal/_MatrixMethods.hpp"
#include "internal/_MatrixOperations.hpp"
#include "internal/_MatrixStaticMethods.hpp"