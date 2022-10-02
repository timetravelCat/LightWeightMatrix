/**
 * @file _MatrixStaticMethods.hpp
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
  Matrix<T, M, N> Matrix<T, M, N>::Zero()
  {
    return Matrix<T, M, N>();
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  enable_if_t<is_floating_point<T_>::value, Matrix<T, M, N>> Matrix<T, M, N>::NaN()
  {
    Matrix<T, M, N> res;
    res.fill(NAN);
    return res;
  }
  template<typename T, size_t M, size_t N>
  Matrix<T, M, N> Matrix<T, M, N>::Constant(T value)
  {
    Matrix<T, M, N> res;
    res.fill(value);
    return res;
  }
  template<typename T, size_t M, size_t N>
  Matrix<T, M, N> Matrix<T, M, N>::Identity()
  {
    Matrix<T, M, N> res;
    for (size_t i = 0; i < internal::min<size_t, M, N>::value; i++)
      res.data[i][i] = static_cast<T>(1);
    return res;
  }
};  // namespace lwm