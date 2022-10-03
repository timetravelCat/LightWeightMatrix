/**
 * @file _MatrixOperations.hpp
 * @author InGyuChoi (timetraveler930@gmail.com)
 * @brief
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
  template<typename U, size_t P>
  Matrix<implicit_cast_t<T, U>, M, P> Matrix<T, M, N>::operator*(const Matrix<U, N, P>& other) const
  {
    Matrix<implicit_cast_t<T, U>, M, P> res;
    for (size_t i = 0; i < M; i++)
      for (size_t k = 0; k < P; k++)
        for (size_t j = 0; j < N; j++)
          res.data[i][k] += data[i][j] * other.data[j][k];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U, size_t P>
  void Matrix<T, M, N>::operator*=(const Matrix<U, N, P>& other)
  {
    (*this) = (*this) * other;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  Matrix<implicit_cast_t<T, U>, M, N> Matrix<T, M, N>::operator*(U other) const
  {
    Matrix<implicit_cast_t<T, U>, M, N> res;
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        res.data[i][j] = data[i][j] * other;
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  void Matrix<T, M, N>::operator*=(U other)
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        data[i][j] = data[i][j] * other;
  }
  template<typename U, typename T_, size_t M_, size_t N_>
  Matrix<implicit_cast_t<T_, U>, M_, N_> operator*(U other, const Matrix<T_, M_, N_>& m)
  {
    Matrix<implicit_cast_t<T_, U>, M_, N_> res;
    for (size_t i = 0; i < M_; i++)
      for (size_t j = 0; j < N_; j++)
        res(i, j) = m(i, j) * other;
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  Matrix<implicit_cast_t<T, U>, M, N> Matrix<T, M, N>::operator/(U other) const
  {
    Matrix<implicit_cast_t<T, U>, M, N> res;
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        res.data[i][j] = data[i][j] / other;
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  void Matrix<T, M, N>::operator/=(U other)
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        data[i][j] /= other;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  Matrix<implicit_cast_t<T, U>, M, N> Matrix<T, M, N>::operator+(const Matrix<U, M, N>& other) const
  {
    Matrix<implicit_cast_t<T, U>, M, N> res;
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        res.data[i][j] = data[i][j] + other.data[i][j];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  void Matrix<T, M, N>::operator+=(const Matrix<U, M, N>& other)
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        data[i][j] += other.data[i][j];
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  Matrix<implicit_cast_t<T, U>, M, N> Matrix<T, M, N>::operator+(U other) const
  {
    Matrix<implicit_cast_t<T, U>, M, N> res;
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        res.data[i][j] = data[i][j] + other;
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  void Matrix<T, M, N>::operator+=(U other)
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        data[i][j] += other;
  }
  template<typename U, typename T_, size_t M_, size_t N_>
  Matrix<implicit_cast_t<T_, U>, M_, N_> operator+(U other, const Matrix<T_, M_, N_>& m)
  {
    Matrix<implicit_cast_t<T_, U>, M_, N_> res;
    for (size_t i = 0; i < M_; i++)
      for (size_t j = 0; j < N_; j++)
        res[i][j] = m.data[i][j] + other;
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  Matrix<implicit_cast_t<T, U>, M, N> Matrix<T, M, N>::operator-(const Matrix<U, M, N>& other) const
  {
    Matrix<implicit_cast_t<T, U>, M, N> res;
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        res.data[i][j] = data[i][j] - other.data[i][j];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  void Matrix<T, M, N>::operator-=(const Matrix<U, M, N>& other)
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        data[i][j] -= other.data[i][j];
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  Matrix<implicit_cast_t<T, U>, M, N> Matrix<T, M, N>::operator-(U other) const
  {
    Matrix<implicit_cast_t<T, U>, M, N> res;
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        res.data[i][j] = data[i][j] - other;
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  void Matrix<T, M, N>::operator-=(U other)
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        data[i][j] -= other;
  }
  template<typename U, typename T_, size_t M_, size_t N_>
  Matrix<implicit_cast_t<T_, U>, M_, N_> operator-(U other, const Matrix<T_, M_, N_>& m)
  {
    Matrix<implicit_cast_t<T_, U>, M_, N_> res;
    for (size_t i = 0; i < M_; i++)
      for (size_t j = 0; j < N_; j++)
        res.data[i][j] = other - m.data[i][j];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  bool Matrix<T, M, N>::operator==(const Matrix<U, M, N>& other) const
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        if (!isSame(data[i][j], other.data[i][j]))
          return false;
    return true;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  bool Matrix<T, M, N>::operator!=(const Matrix<U, M, N>& other) const
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        if (!isSame(data[i][j], other.data[i][j]))
          return true;
    return false;
  }
  template<typename T, size_t M, size_t N>
  template<typename U, size_t L>
  Matrix<T, M, N>& Matrix<T, M, N>::operator=(const U (&in)[L])
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
  template<typename T, size_t M, size_t N>
  template<typename U, size_t R, size_t C>
  Matrix<T, M, N>& Matrix<T, M, N>::operator=(const U (&in)[R][C])
  {
    size_static_assert<R, C, 0, 0>();
    for (size_t i = 0; i < R; i++)
      for (size_t j = 0; j < C; j++)
        data[i][j] = static_cast<allowed_cast_t<T, U>>(in[i][j]);
    return (*this);
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  Matrix<T, M, N>& Matrix<T, M, N>::operator=(const Matrix<U, M, N>& in)
  {
    if (memcmp(data, in.data, sizeof(T)) == 0)
      return (*this);
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        data[i][j] = static_cast<allowed_cast_t<T, U>>(in.data[i][j]);
    
    return (*this);
  }
};  // namespace lwm