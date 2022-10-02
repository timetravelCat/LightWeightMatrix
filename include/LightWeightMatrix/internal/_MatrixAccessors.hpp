/**
 * @file _MatrixAccessors.hpp
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
  inline const enable_if_t<M == 1 && N == 1, T_>& Matrix<T, M, N>::operator()() const
  {
    return data[0][0];
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  inline enable_if_t<M == 1 && N == 1, T_>& Matrix<T, M, N>::operator()()
  {
    return data[0][0];
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  inline const enable_if_t<M == 1 && N != 1, T_>& Matrix<T, M, N>::operator()(size_t i) const
  {
    assert(i < N);
    return data[0][i];
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  inline enable_if_t<M == 1 && N != 1, T_>& Matrix<T, M, N>::operator()(size_t i)
  {
    assert(i < N);
    return data[0][i];
  }
  template<typename T, size_t M, size_t N>
  template<typename U, typename res>
  inline const res& Matrix<T, M, N>::operator()(U) const
  {
    static_assert(static_cast<int>(U::value) < N, "() access row size error");
    return data[0][U::value];
  }
  template<typename T, size_t M, size_t N>
  template<typename U, typename res>
  inline res& Matrix<T, M, N>::operator()(U)
  {
    static_assert(static_cast<int>(U::value) < N, "() access row size error");
    return data[0][U::value];
  }
  template<typename T, size_t M, size_t N>
  template<typename dummy, typename T_>
  inline const enable_if_t<M != 1 && N == 1, T_>& Matrix<T, M, N>::operator()(size_t i) const
  {
    assert(i < M);
    return data[i][0];
  }
  template<typename T, size_t M, size_t N>
  template<typename dummy, typename T_>
  inline enable_if_t<M != 1 && N == 1, T_>& Matrix<T, M, N>::operator()(size_t i)
  {
    assert(i < M);
    return data[i][0];
  }
  template<typename T, size_t M, size_t N>
  template<typename dummy, typename U, typename res>
  inline const res& Matrix<T, M, N>::operator()(U) const
  {
    static_assert(static_cast<int>(U::value) < M, "() access column size error");
    return data[U::value][0];
  }
  template<typename T, size_t M, size_t N>
  template<typename dummy, typename U, typename res>
  inline res& Matrix<T, M, N>::operator()(U)
  {
    static_assert(static_cast<int>(U::value) < M, "() access column size error");
    return data[U::value][0];
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  inline const enable_if_t<M == 1 && N != 1, T_>& Matrix<T, M, N>::operator[](size_t i) const
  {
    assert(i < N);
    return data[0][i];
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  inline enable_if_t<M == 1 && N != 1, T_>& Matrix<T, M, N>::operator[](size_t i)
  {
    assert(i < N);
    return data[0][i];
  }
  template<typename T, size_t M, size_t N>
  template<typename U, typename res>
  inline const res& Matrix<T, M, N>::operator[](U) const
  {
    static_assert(static_cast<int>(U::value) < N, "() access row size error");
    return data[0][U::value];
  }
  template<typename T, size_t M, size_t N>
  template<typename U, typename res>
  inline res& Matrix<T, M, N>::operator[](U)
  {
    static_assert(static_cast<int>(U::value) < N, "() access row size error");
    return data[0][U::value];
  }
  template<typename T, size_t M, size_t N>
  template<typename dummy, typename T_>
  inline const enable_if_t<M != 1 && N == 1, T_>& Matrix<T, M, N>::operator[](size_t i) const
  {
    assert(i < M);
    return data[i][0];
  }
  template<typename T, size_t M, size_t N>
  template<typename dummy, typename T_>
  inline enable_if_t<M != 1 && N == 1, T_>& Matrix<T, M, N>::operator[](size_t i)
  {
    assert(i < M);
    return data[i][0];
  }
  template<typename T, size_t M, size_t N>
  template<typename dummy, typename U, typename res>
  inline const res& Matrix<T, M, N>::operator[](U) const
  {
    static_assert(static_cast<int>(U::value) < M, "() access column size error");
    return data[U::value][0];
  }
  template<typename T, size_t M, size_t N>
  template<typename dummy, typename U, typename res>
  inline res& Matrix<T, M, N>::operator[](U)
  {
    static_assert(static_cast<int>(U::value) < M, "() access column size error");
    return data[U::value][0];
  }
  template<typename T, size_t M, size_t N>
  inline const T& Matrix<T, M, N>::operator()(size_t i, size_t j) const
  {
    assert(i < M);
    assert(j < N);

    return data[i][j];
  }
  template<typename T, size_t M, size_t N>
  inline T& Matrix<T, M, N>::operator()(size_t i, size_t j)
  {
    assert(i < M);
    assert(j < N);

    return data[i][j];
  }

  template<typename T, size_t M, size_t N>
  template<typename T_>
  inline enable_if_t<M != 1 && N != 1, T_> Matrix<T, M, N>::operator[](size_t i) const
  {
    assert(i < M);
    return accessor<true>{ data[i] };
  }
  template<typename T, size_t M, size_t N>
  template<typename U, typename res>
  inline res Matrix<T, M, N>::operator[](U) const
  {
    static_assert(static_cast<int>(U::value) < M, "[] access row size error");
    return accessor<true>{ data[U::value] };
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  inline enable_if_t<M != 1 && N != 1, T_> Matrix<T, M, N>::operator[](size_t i)
  {
    assert(i < M);
    return T_{ data[i] };
  }
  template<typename T, size_t M, size_t N>
  template<typename U, typename res>
  inline res Matrix<T, M, N>::operator[](U)
  {
    static_assert(static_cast<int>(U::value) < M, "[] access row size error");
    return res{ data[U::value] };
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  inline enable_if_t<M != 1 && N != 1, T_> Matrix<T, M, N>::operator()(size_t i) const
  {
    assert(i < M);
    return accessor<true>{ data[i] };
  }
  template<typename T, size_t M, size_t N>
  template<typename U, typename res>
  inline res Matrix<T, M, N>::operator()(U) const
  {
    static_assert(static_cast<int>(U::value) < M, "() access row size error");
    return accessor<true>{ data[U::value] };
  }
  template<typename T, size_t M, size_t N>
  template<typename T_>
  inline enable_if_t<M != 1 && N != 1, T_> Matrix<T, M, N>::operator()(size_t i)
  {
    assert(i < M);
    return T_{ data[i] };
  }
  template<typename T, size_t M, size_t N>
  template<typename U, typename res>
  inline res Matrix<T, M, N>::operator()(U)
  {
    static_assert(static_cast<int>(U::value) < M, "() access row size error");
    return res{ data[U::value] };
  }
};  // namespace lwm