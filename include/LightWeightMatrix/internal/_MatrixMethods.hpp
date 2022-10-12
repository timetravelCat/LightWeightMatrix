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
  void Matrix<T, M, N>::swapRow(const size_t& a, const size_t& b)
  {
    assert(a < M);
    assert(b < M);

    if (a == b)
      return;

    for (size_t j = 0; j < N; j++)
    {
      const T tmp = data[a][j];
      data[a][j] = data[b][j];
      data[b][j] = tmp;
    }
  }

  template<typename T, size_t M, size_t N>
  void Matrix<T, M, N>::swapCol(const size_t& a, const size_t& b)
  {
    assert(a < N);
    assert(b < N);

    if (a == b)
      return;

    for (size_t i = 0; i < M; i++)
    {
      const T tmp = data[i][a];
      data[i][a] = data[i][b];
      data[i][b] = tmp;
    }
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
  template<typename T_>
  enable_if_t<M == N, T_> Matrix<T, M, N>::trace() const
  {
    T res = T(0);
    for (size_t i = 0; i < M; i++)
      res += data[i][i];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename T_, enable_if_t<M == N && is_floating_point<T_>::value && M == 1, void*>>
  Matrix<T, M, N> Matrix<T, M, N>::inv() const
  {
    if (!isFinite(data[0][0]) || isEpsilon(data[0][0]))
      return Matrix<T, M, N>{ { NAN } };
    return Matrix<T, M, N>{ { T(1.0) / data[0][0] } };
  }
  template<typename T, size_t M, size_t N>
  template<typename T_, enable_if_t<M == N && is_floating_point<T_>::value && M == 2, void*>>
  Matrix<T, M, N> Matrix<T, M, N>::inv() const
  {
    const T det = data[0][0] * data[1][1] - data[1][0] * data[0][1];
    if (!isFinite(det) || isEpsilon(det))
      return Matrix<T, M, N>::NaN();
    return Matrix<T, M, N>{ { data[1][1] / det, -data[0][1] / det, -data[1][0] / det, data[0][0] / det } };
  }
  template<typename T, size_t M, size_t N>
  template<typename T_, enable_if_t<M == N && is_floating_point<T_>::value && M == 3, void*>>
  Matrix<T, M, N> Matrix<T, M, N>::inv() const
  {
    const T det = data[0][0] * (data[1][1] * data[2][2] - data[2][1] * data[1][2]) -
                  data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
                  data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    if (!isFinite(det) || isEpsilon(det))
      return Matrix<T, M, N>::NaN();
    Matrix<T, M, N> res;
    res.data[0][0] = (data[1][1] * data[2][2] - data[2][1] * data[1][2]) / det;
    res.data[0][1] = (data[0][2] * data[2][1] - data[0][1] * data[2][2]) / det;
    res.data[0][2] = (data[0][1] * data[1][2] - data[0][2] * data[1][1]) / det;
    res.data[1][0] = (data[1][2] * data[2][0] - data[1][0] * data[2][2]) / det;
    res.data[1][1] = (data[0][0] * data[2][2] - data[0][2] * data[2][0]) / det;
    res.data[1][2] = (data[1][0] * data[0][2] - data[0][0] * data[1][2]) / det;
    res.data[2][0] = (data[1][0] * data[2][1] - data[2][0] * data[1][1]) / det;
    res.data[2][1] = (data[2][0] * data[0][1] - data[0][0] * data[2][1]) / det;
    res.data[2][2] = (data[0][0] * data[1][1] - data[1][0] * data[0][1]) / det;
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename T_, enable_if_t<M == N && is_floating_point<T_>::value && (M > 3), void*>>
  Matrix<T, M, N> Matrix<T, M, N>::inv() const
  {
    Matrix<T, M, N> L = Matrix<T, M, N>::Identity();
    Matrix<T, M, N> U = (*this);
    Matrix<T, M, N> P = Matrix<T, M, N>::Identity();

    for (size_t n = 0; n < M; n++)
    {
      if (isEpsilon(U(n, n)))
      {
        for (size_t i = n + 1; i < M; i++)
        {
          if (!isEpsilon(U(i, n)))
          {
            U.swapRow(i, n);
            P.swapRow(i, n);
            L.swapRow(i, n);
            L.swapCol(i, n);
            break;
          }
        }
      }

      if (isEpsilon(U(n, n)))
        return Matrix<T, M, N>::NaN();

      for (size_t i = (n + 1); i < M; i++)
      {
        L(i, n) = U(i, n) / U(n, n);
        for (size_t k = n; k < M; k++)
        {
          U(i, k) -= L(i, n) * U(n, k);
        }
      }
    }

    for (size_t c = 0; c < M; c++)
      for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < i; j++)
          P(i, c) -= L(i, j) * P(j, c);

    for (size_t c = 0; c < M; c++)
    {
      for (size_t k = 0; k < M; k++)
      {
        size_t i = M - 1 - k;
        for (size_t j = i + 1; j < M; j++)
        {
          P(i, c) -= U(i, j) * P(j, c);
        }
        P(i, c) /= U(i, i);
      }
    }
    for (size_t i = 0; i < M; i++)
      for (size_t j = 0; j < M; j++)
        if (!isFinite(P(i, j)))
          return Matrix<T, M, N>::NaN();

    return P;
  }
  template<typename T, size_t M, size_t N>
  template<typename T_, enable_if_t<M == N && is_floating_point<T_>::value, void*>>
  Matrix<T, M, N> Matrix<T, M, N>::inv(size_t rank) const
  {
    Matrix<T, M, N> L = Matrix<T, M, N>::Identity();
    Matrix<T, M, N> U = (*this);
    Matrix<T, M, N> P = Matrix<T, M, N>::Identity();

    for (size_t n = 0; n < rank; n++)
    {
      if (isEpsilon(U(n, n)))
      {
        for (size_t i = n + 1; i < rank; i++)
        {
          if (!isEpsilon(U(i, n)))
          {
            U.swapRow(i, n);
            P.swapRow(i, n);
            L.swapRow(i, n);
            L.swapCol(i, n);
            break;
          }
        }
      }

      if (isEpsilon(U(n, n)))
        return Matrix<T, M, N>::NaN();

      for (size_t i = (n + 1); i < rank; i++)
      {
        L(i, n) = U(i, n) / U(n, n);
        for (size_t k = n; k < rank; k++)
        {
          U(i, k) -= L(i, n) * U(n, k);
        }
      }
    }

    for (size_t c = 0; c < rank; c++)
      for (size_t i = 0; i < rank; i++)
        for (size_t j = 0; j < i; j++)
          P(i, c) -= L(i, j) * P(j, c);

    for (size_t c = 0; c < rank; c++)
    {
      for (size_t k = 0; k < rank; k++)
      {
        size_t i = rank - 1 - k;
        for (size_t j = i + 1; j < rank; j++)
        {
          P(i, c) -= U(i, j) * P(j, c);
        }
        P(i, c) /= U(i, i);
      }
    }
    for (size_t i = 0; i < rank; i++)
      for (size_t j = 0; j < rank; j++)
        if (!isFinite(P(i, j)))
          return Matrix<T, M, N>::NaN();

    return P;
  }
  template<typename T, size_t M, size_t N>
  template<typename T_, enable_if_t<M == N && is_floating_point<T_>::value, void*>>
  Matrix<T, M, 1> Matrix<T, M, N>::diag() const
  {
    Matrix<T, M, 1> res;
    for (size_t i = 0; i < M; i++)
      res.data[i][0] = data[i][i];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<typename T_, enable_if_t<M == N && is_floating_point<T_>::value, void*>>
  Matrix<T, M, N> Matrix<T, M, N>::choleskyDecomposition(size_t& rank) const
  {
    const T tol = M * epsilon<T>() * diag().max();
    Matrix<T, N, N> L;

    size_t r = 0;
    for (size_t k = 0; k < N; k++)
    {
      if (r == 0)
      {
        for (size_t i = k; i < N; i++)
          L.data[i][r] = data[i][k];
      }
      else
      {
        for (size_t i = k; i < N; i++)
        {
          T LL = T();
          for (size_t j = 0; j < r; j++)
            LL += L.data[i][j] * L.data[k][j];

          L.data[i][r] = data[i][k] - LL;
        }
      }
      if (L.data[k][r] > tol)
      {
        L.data[k][r] = sqrt(L.data[k][r]);
        if (k < N - 1)
          for (size_t i = k + 1; i < N; i++)
            L.data[i][r] = L.data[i][r] / L.data[k][r];

        r = r + 1;
      }
    }

    // Return rank
    rank = r;

    return L;
  }
  template<typename T, size_t M, size_t N>
  Matrix<T, N, M> Matrix<T, M, N>::pinv() const
  {
    if (M <= N)
    {
      size_t rank;
      Matrix<T, M, M> A = (*this) * transpose();
      Matrix<T, M, M> L = A.choleskyDecomposition(rank);

      A = L.transpose() * L;
      Matrix<T, M, M> X = A.inv(rank);
      if (X.isAnyNan())
        return Matrix<T, N, M>::NaN();  // LCOV_EXCL_LINE -- this can only be hit from numerical issues

      // doing an intermediate assignment reduces stack usage
      A = X * X * L.transpose();
      return transpose() * (L * A);
    }
    else
    {
      size_t rank;
      Matrix<T, N, N> A = transpose() * (*this);
      Matrix<T, N, N> L = A.choleskyDecomposition(rank);

      A = L.transpose() * L;
      Matrix<T, N, N> X = A.inv(rank);
      if (X.isAnyNan())
        return Matrix<T, N, M>::NaN();  // LCOV_EXCL_LINE -- this can only be hit from numerical issues

      // doing an intermediate assignment reduces stack usage
      A = X * X * L.transpose();
      return (L * A) * transpose();
    }
  }
  template<typename T, size_t M, size_t N>
  template<size_t M_, enable_if_t<(M_ == 3) && (N == 3), void*>>
  Matrix<T, M_, 1> Matrix<T, M, N>::vee() const
  {
    Matrix<T, M_, 1> res;
    res.data[0][0] = -data[1][2];
    res.data[1][0] = data[0][2];
    res.data[2][0] = -data[0][1];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<size_t M_, size_t N_, enable_if_t<((M_ == 1 && N_ > 1) || (N_ == 1 && M_ > 1)), void*>>
  inline T Matrix<T, M, N>::dot(const Matrix<T, M, N>::Vector& in) const
  {
    T res{ 0 };
    for (size_t i = 0; i < SIZE; i++)
      res += (*this)[i] * in[i];
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<size_t M_, size_t N_, enable_if_t<((M_ == 1 && N_ > 1) || (N_ == 1 && M_ > 1)), void*>>
  inline T Matrix<T, M, N>::norm() const
  {
    return sqrt(dot(*this));
  }
  template<typename T, size_t M, size_t N>
  template<size_t M_, size_t N_, enable_if_t<((M_ == 1 && N_ > 1) || (N_ == 1 && M_ > 1)), void*>>
  inline T Matrix<T, M, N>::normSquared() const
  {
    return (dot(*this));
  }
  template<typename T, size_t M, size_t N>
  template<size_t M_, size_t N_, enable_if_t<((M_ == 1 && N_ > 1) || (N_ == 1 && M_ > 1)), void*>>
  inline typename Matrix<T, M, N>::Vector Matrix<T, M, N>::unit(const T eps) const
  {
    const T n = norm();
    if (n < eps)
      return NaN();
    return (*this) / n;
  }
  template<typename T, size_t M, size_t N>
  template<size_t M_, size_t N_, enable_if_t<((M_ == 1 && N_ > 1) || (N_ == 1 && M_ > 1)), void*>>
  inline typename Matrix<T, M, N>::Vector Matrix<T, M, N>::normalized(const T eps) const
  {
    return unit(eps);
  }
  template<typename T, size_t M, size_t N>
  template<size_t M_, size_t N_, enable_if_t<((M_ == 2 && N_ == 1) || (N_ == 2 && M_ == 1)), void*>>
  inline T Matrix<T, M, N>::cross(const typename Matrix<T, M, N>::Vector& r) const
  {
    const Matrix<T, M, N>::Vector& l{ *this };
    return l[0] * r[1] - l[1] * r[0];
  }
  template<typename T, size_t M, size_t N>
  template<size_t M_, size_t N_, enable_if_t<((M_ == 3 && N_ == 1) || (N_ == 3 && M_ == 1)), void*>>
  inline typename Matrix<T, M, N>::Vector Matrix<T, M, N>::cross(const typename Matrix<T, M, N>::Vector& r) const
  {
    const typename Matrix<T, M, N>::Vector& l{ *this };
    return Matrix<T, M, N>::Vector{ { l[1] * r[2] - l[2] * r[1], -l[0] * r[2] + l[2] * r[0], l[0] * r[1] - l[1] * r[0] } };
  }
  template<typename T, size_t M, size_t N>
  template<size_t M_, size_t N_, enable_if_t<((M_ == 3 && N_ == 1) || (N_ == 3 && M_ == 1)), void*>>
  inline Matrix<T, 3, 3> Matrix<T, M, N>::hat() const
  {
    Matrix<T, 3, 3> res;
    res.data[0][0] = 0;
    res.data[0][1] = -(*this)[2];
    res.data[0][2] = (*this)[1];
    res.data[1][0] = (*this)[2];
    res.data[1][1] = 0;
    res.data[1][2] = -(*this)[0];
    res.data[2][0] = -(*this)[1];
    res.data[2][1] = (*this)[0];
    res.data[2][2] = 0;
    return res;
  }
  template<typename T, size_t M, size_t N>
  template<size_t M_, size_t N_, enable_if_t<((M_ == 3 && N_ == 3)), void*>>
  inline Matrix<T, M, N> Matrix<T, M, N>::normalized(const T eps) const
  {
    Matrix<T, M, N> res;
    for (size_t i = 0; i < 3; i++)
      res.setRow(i, row(i).normalized(eps));
    return res;
  }

  template<typename T, size_t M, size_t N>
  template<size_t R, size_t C, size_t r, size_t c>
  void Matrix<T, M, N>::size_static_assert()
  {
    static_assert(((M >= (R + r)) && (N >= (C + c))), "Matrix Size Error.");
  }
};  // namespace lwm