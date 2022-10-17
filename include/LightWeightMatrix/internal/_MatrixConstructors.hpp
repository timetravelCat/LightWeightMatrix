/**
 * @file _MatrixConstructors.hpp
 * @author InGyuChoi (timetraveler930@gmail.com)
 * @brief implements constructor of Matrix Class.
 * @version 0.1
 * @date 2022-10-02
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

namespace lwm
{
  using namespace internal;
  template<typename T, size_t M, size_t N>
  template<typename U, size_t L>
  Matrix<T, M, N>::Matrix(const U (&in)[L], size_t offset)
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
  template<typename T, size_t M, size_t N>
  template<typename U, size_t L, typename type_, typename>
  Matrix<T, M, N>::Matrix(const U (&in)[L], type_)
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
  template<typename T, size_t M, size_t N>
  template<typename U>
  Matrix<T, M, N>::Matrix(const U (&in)[M][N])
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i][j]);
  }
  template<typename T, size_t M, size_t N>
  template<typename U, size_t R, size_t C>
  Matrix<T, M, N>::Matrix(const U (&in)[R][C], size_t r, size_t c)
  {
    size_static_assert<R, C, 0, 0>();
    assert((M >= (R + r)) && (N >= (C + c)));
    for (size_t i = r; i < r + R; i++)
      for (size_t j = c; j < c + C; j++)
        data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i - r][j - c]);
  }
  template<typename T, size_t M, size_t N>
  template<typename U, size_t R, size_t C, typename r, typename c, typename>
  Matrix<T, M, N>::Matrix(const U (&in)[R][C], r, c)
  {
    size_static_assert<R, C, r::value, c::value>();
    for (size_t i = r::value; i < r::value + R; i++)
      for (size_t j = c::value; j < c::value + C; j++)
        data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i - r::value][j - c::value]);
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  Matrix<T, M, N>::Matrix(const Matrix<U, M, N>& in)
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        data[i][j] = static_cast<allowed_cast_t<T, U>>(in.data[i][j]);
  }
};  // namespace lwm