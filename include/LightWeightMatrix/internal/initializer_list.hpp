/**
 * @file initializer_list.hpp
 * @author InGyuChoi (timetraveler930@gmail.com)
 * @brief replacement of libc++ std::initializer_list
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#if !defined(_INITIALIZER_LIST)

#include "detect_system.hpp"

#ifdef LWM_CPP11_SUPPORTED

#define _INITIALIZER_LIST

// Use the LWM's std::initializer_list
namespace std
{
#if defined(LWM_COMPILER_MICROSOFT)

  ///**************************************************************************
  /// A definition of initializer_list that is compatible with the Microsoft compiler
  ///**************************************************************************
  template<typename T>
  class initializer_list
  {
   public:
    using value_type = T;
    using reference = const T&;
    using const_reference = const T&;
    using size_type = size_t;
    using iterator = const T*;
    using const_iterator = const T*;

    //*************************************************************************
    /// Default constructor
    //*************************************************************************
    constexpr initializer_list() noexcept : pfirst(nullptr), plast(nullptr)
    {
    }

    //*************************************************************************
    /// Constructor
    //*************************************************************************
    constexpr initializer_list(const T* pfirst_, const T* plast_) noexcept : pfirst(pfirst_), plast(plast_)
    {
    }

    //*************************************************************************
    /// Get the beginning of the list.
    //*************************************************************************
    constexpr const T* begin() const noexcept
    {
      return pfirst;
    }

    //*************************************************************************
    /// Get the end of the list.
    //*************************************************************************
    constexpr const T* end() const noexcept
    {
      return plast;
    }

    //*************************************************************************
    /// Get the size of the list.
    //*************************************************************************
    constexpr size_t size() const noexcept
    {
      return static_cast<size_t>(plast - pfirst);
    }

   private:
    const T* pfirst;
    const T* plast;
  };

  //*************************************************************************
  /// Get the beginning of the list.
  //*************************************************************************
  template<typename T>
  constexpr const T* begin(initializer_list<T> init) noexcept
  {
    return init.begin();
  }

  //*************************************************************************
  /// Get the end of the list.
  //*************************************************************************
  template<typename T>
  constexpr const T* end(initializer_list<T> init) noexcept
  {
    return init.end();
  }

#else defined(LWM_COMPILER_GCC) || defined(LWM_COMPILER_CLANG) || defined(LWM_COMPILER_ARM6) ||           \
    defined(LWM_COMPILER_ARM7) || defined(LWM_COMPILER_IAR) || defined(LWM_COMPILER_TEXAS_INSTRUMENTS) || \
    defined(LWM_COMPILER_INTEL)

  ///**************************************************************************
  /// A definition of initializer_list that is compatible with Clang, GCC and other compilers.
  ///**************************************************************************
  template<class T>
  class initializer_list
  {
   public:
    using value_type = T;
    using reference = const T&;
    using const_reference = const T&;
    using size_type = size_t;
    using iterator = const T*;
    using const_iterator = const T*;

    //*************************************************************************
    /// Default constructor
    //*************************************************************************
    constexpr initializer_list() noexcept : pfirst(nullptr), length(0)
    {
    }

    //*************************************************************************
    /// Get the beginning of the list.
    //*************************************************************************
    constexpr const T* begin() const noexcept
    {
      return pfirst;
    }

    //*************************************************************************
    /// Get the end of the list.
    //*************************************************************************
    constexpr const T* end() const noexcept
    {
      return pfirst + length;
    }

    //*************************************************************************
    /// Get the size of the list.
    //*************************************************************************
    constexpr size_t size() const noexcept
    {
      return length;
    }

   private:
    //*************************************************************************
    /// Constructor
    //*************************************************************************
    constexpr initializer_list(const T* pfirst_, size_t length_) noexcept : pfirst(pfirst_), length(length_)
    {
    }

    const T* pfirst;
    size_t length;
  };

  //*************************************************************************
  /// Get the beginning of the list.
  //*************************************************************************
  template<class T>
  constexpr const T* begin(initializer_list<T> init) noexcept
  {
    return init.begin();
  }

  //*************************************************************************
  /// Get the end of the list.
  //*************************************************************************
  template<class T>
  constexpr const T* end(initializer_list<T> init) noexcept
  {
    return init.end();
  }
#endif
}  // namespace std

#endif
#endif  // !_INITIALIZER_LIST