/**
 * @file _MatrixMethods.hpp
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
  template<typename T_>
  enable_if_t<are_floating_point<T_>::value, bool> Matrix<T, M, N>::isAllNan() const
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        if (!isnan(data[i][j]))
          return false;
    return true;
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  enable_if_t<are_floating_point<T_>::value, bool> Matrix<T, M, N>::isAnyNan() const
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        if (isnan(data[i][j]))
          return true;
    return false;
  }

  template<typename T, size_t M, size_t N>
  T Matrix<T, M, N>::max() const
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
  template<typename T, size_t M, size_t N>
  T Matrix<T, M, N>::min() const
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
  template<typename T, size_t M, size_t N>
  template<typename U>
  Matrix<implicit_cast_t<T, U>, M, N> Matrix<T, M, N>::elementWiseMultiply(const Matrix<U, M, N>& other) const
  {
    Matrix<implicit_cast_t<T, U>, M, N> res;
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        res.data[i][j] = other[i][j] * data[i][j];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  Matrix<implicit_cast_t<T, U>, M, N> Matrix<T, M, N>::elementWiseDivide(const Matrix<U, M, N>& other) const
  {
    Matrix<implicit_cast_t<T, U>, M, N> res;
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        res.data[i][j] = data[i][j] / other[i][j];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  enable_if_t<is_floating_point<T_>::value, Matrix<T_, M, N>> Matrix<T, M, N>::abs() const
  {
    Matrix<T_, M, N> res;
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        res.data[i][j] = fabs(data[i][j]);
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U, size_t L>
  void Matrix<T, M, N>::toArray(U (&out)[L], size_t offset) const
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
  template<typename T, size_t M, size_t N>
  template<size_t offset, typename U, size_t L>
  void Matrix<T, M, N>::toArray(U (&out)[L]) const
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
  template<typename T, size_t M, size_t N>
  template<typename U, size_t R, size_t C>
  void Matrix<T, M, N>::toArray(U (&out)[R][C], size_t r, size_t c) const
  {
    static_assert((M <= R) && (N <= C), "toArray matrix size error");
    assert(R > r);
    assert(C > c);
    assert((M <= R - r) && (N <= C - c));
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        out[i + r][j + c] = static_cast<allowed_cast_t<T, U>>(data[i][j]);
  }
  template<typename T, size_t M, size_t N>
  template<size_t offset_r, size_t offset_c, typename U, size_t R, size_t C>
  void Matrix<T, M, N>::toArray(U (&out)[R][C]) const
  {
    static_assert(R > offset_r, "toArray matrix row size error");
    static_assert(C > offset_c, "toArray matrix col size error");
    static_assert((M <= R - offset_r) && (N <= C - offset_c), "toArray matrix size error");
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        out[i + offset_r][j + offset_c] = static_cast<allowed_cast_t<T, U>>(data[i][j]);
  }
  template<typename T, size_t M, size_t N>
  template<size_t c>
  Matrix<T, M, 1> Matrix<T, M, N>::col() const
  {
    static_assert(c < N, "requested column index over the size of column");
    Matrix<T, M, 1> res;
    for (size_t i = 0; i < M; i++)
      res.data[i][0] = data[i][c];
    return res;
  }
  template<typename T, size_t M, size_t N>
  Matrix<T, M, 1> Matrix<T, M, N>::col(size_t c) const
  {
    assert(c < N);
    Matrix<T, M, 1> res;
    for (size_t i = 0; i < M; i++)
      res.data[i][0] = data[i][c];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<size_t c, typename U>
  void Matrix<T, M, N>::setCol(U in)
  {
    static_assert(c < N, "requested column index over the size of column");
    for (size_t i = 0; i < M; i++)
      data[i][c] = static_cast<allowed_cast_t<T, U>>(in);
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  void Matrix<T, M, N>::setCol(size_t c, U in)
  {
    assert(c < N);
    for (size_t i = 0; i < M; i++)
      data[i][c] = static_cast<allowed_cast_t<T, U>>(in);
  }
  template<typename T, size_t M, size_t N>
  template<size_t c, typename U>
  void Matrix<T, M, N>::setCol(const Matrix<U, M, 1>& in)
  {
    static_assert(c < N, "requested col index over the size of row");
    for (size_t i = 0; i < M; i++)
      data[i][c] = static_cast<allowed_cast_t<T, U>>(in.data[i][0]);
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  void Matrix<T, M, N>::setCol(size_t c, const Matrix<U, M, 1>& in)
  {
    assert(c < N);
    for (size_t i = 0; i < M; i++)
      data[i][c] = static_cast<allowed_cast_t<T, U>>(in.data[i][0]);
  }
  template<typename T, size_t M, size_t N>
  template<size_t c, typename U, size_t L>
  void Matrix<T, M, N>::setCol(const U (&in)[L])
  {
    static_assert(c < N, "requested col index over the size of row");
    static_assert(L <= M, "array input length is over the matrix row");
    for (size_t i = 0; i < L; i++)
      data[i][c] = static_cast<allowed_cast_t<T, U>>(in[i]);
  }
  template<typename T, size_t M, size_t N>
  template<typename U, size_t L>
  void Matrix<T, M, N>::setCol(size_t c, const U (&in)[L])
  {
    assert(c < N);
    static_assert(L <= M, "array input length is over the matrix row");
    for (size_t i = 0; i < L; i++)
      data[i][c] = static_cast<allowed_cast_t<T, U>>(in[i]);
  }
  template<typename T, size_t M, size_t N>
  template<size_t r>
  Matrix<T, 1, N> Matrix<T, M, N>::row() const
  {
    static_assert(r < M, "requested row index over the size of row");
    Matrix<T, 1, N> res;
    for (size_t i = 0; i < N; i++)
      res.data[0][i] = data[r][i];
    return res;
  }
  template<typename T, size_t M, size_t N>
  Matrix<T, 1, N> Matrix<T, M, N>::row(size_t r) const
  {
    assert(r < M);
    Matrix<T, 1, N> res;
    for (size_t i = 0; i < N; i++)
      res.data[0][i] = data[r][i];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<size_t r, typename U>
  void Matrix<T, M, N>::setRow(U in)
  {
    static_assert(r < M, "requested row index over the size of column");
    for (size_t i = 0; i < N; i++)
      data[r][i] = static_cast<allowed_cast_t<T, U>>(in);
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  void Matrix<T, M, N>::setRow(size_t r, U in)
  {
    assert(r < M);
    for (size_t i = 0; i < N; i++)
      data[r][i] = static_cast<allowed_cast_t<T, U>>(in);
  }
  template<typename T, size_t M, size_t N>
  template<size_t r, typename U>
  void Matrix<T, M, N>::setRow(const Matrix<U, 1, N>& in)
  {
    static_assert(r < M, "requested row index over the size of column");
    for (size_t i = 0; i < N; i++)
      data[r][i] = static_cast<allowed_cast_t<T, U>>(in.data[0][i]);
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  void Matrix<T, M, N>::setRow(size_t r, const Matrix<U, 1, N>& in)
  {
    assert(r < M);
    for (size_t i = 0; i < N; i++)
      data[r][i] = static_cast<allowed_cast_t<T, U>>(in.data[0][i]);
  }
  template<typename T, size_t M, size_t N>
  template<size_t r, typename U, size_t L>
  void Matrix<T, M, N>::setRow(const U (&in)[L])
  {
    static_assert(r < M, "requested row index over the size of column");
    static_assert(L <= N, "array input length is over the matrix column");
    for (size_t i = 0; i < L; i++)
      data[r][i] = static_cast<allowed_cast_t<T, U>>(in[i]);
  }
  template<typename T, size_t M, size_t N>
  template<typename U, size_t L>
  void Matrix<T, M, N>::setRow(size_t r, const U (&in)[L])
  {
    assert(r < M);
    static_assert(L <= N, "array input length is over the matrix column");
    for (size_t i = 0; i < L; i++)
      data[r][i] = static_cast<allowed_cast_t<T, U>>(in[i]);
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  enable_if_t<M == 1, Matrix<T_, N, 1>> Matrix<T, M, N>::toRowVector() const
  {
    return transpose();
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  enable_if_t<N == 1, Matrix<T_, 1, M>> Matrix<T, M, N>::toColVector() const
  {
    return transpose();
  }
  template<typename T, size_t M, size_t N>
  template<typename U, typename>
  Matrix<U, M, N> Matrix<T, M, N>::cast() const
  {
    Matrix<U, M, N> res;
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        res.data[i][j] = static_cast<U>(data[i][j]);
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<size_t R, size_t C, size_t r, size_t c>
  Matrix<T, R, C> Matrix<T, M, N>::slice() const
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
  template<typename T, size_t M, size_t N>
  Matrix<T, N, M> Matrix<T, M, N>::transpose() const
  {
    Matrix<T, N, M> res;
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        res.data[j][i] = data[i][j];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename U>
  void Matrix<T, M, N>::fill(const U in)
  {
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < N; j++)
        data[i][j] = static_cast<allowed_cast_t<T, U>>(in);
  }
  template<typename T, size_t M, size_t N>
  template<size_t R, size_t C, size_t r, size_t c>
  void Matrix<T, M, N>::size_static_assert()
  {
    static_assert(((M >= (R + r)) && (N >= (C + c))), "Matrix Size Error.");
  }
};  // namespace lwm