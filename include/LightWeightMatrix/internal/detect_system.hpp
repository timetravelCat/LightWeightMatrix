/**
 * @file detect_compiler.hpp
 * @author InGyuChoi (timetraveler930@gmail.com)
 * @brief detect compiler version & cpp standard
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <limits.h>

#define LWM_PLATFORM_16BIT (UINT16_MAX == UINTPTR_MAX)
#define LWM_PLATFORM_32BIT (UINT32_MAX == UINTPTR_MAX)
#define LWM_PLATFORM_64BIT (UINT64_MAX == UINTPTR_MAX)

#if (CHAR_BIT == 8)
  #define LWM_USING_8BIT_TYPES     1
  #define LWM_NOT_USING_8BIT_TYPES 0
#else
  #define LWM_USING_8BIT_TYPES     0
  #define LWM_NOT_USING_8BIT_TYPES 1
#endif

#if defined(LWM_NO_64BIT_TYPES)
  #define LWM_USING_64BIT_TYPES     0
  #define LWM_NOT_USING_64BIT_TYPES 1
#else
  #define LWM_USING_64BIT_TYPES     1
  #define LWM_NOT_USING_64BIT_TYPES 0
#endif

#if !defined(LWM_COMPILER_TYPE_DETECTED) && !defined(LWM_COMPILER_ARM5)
#if defined(__CC_ARM)
#define LWM_COMPILER_ARM5
#define LWM_COMPILER_TYPE_DETECTED
#endif
#endif

#if !defined(LWM_COMPILER_TYPE_DETECTED) && !defined(LWM_COMPILER_ARM6)
#if defined(__ARMCOMPILER_VERSION) && (__ARMCOMPILER_VERSION >= 6000000L) && (__ARMCOMPILER_VERSION < 7000000L)
#define LWM_COMPILER_ARM6
#define LWM_COMPILER_TYPE_DETECTED 1
#endif
#endif

#if !defined(LWM_COMPILER_TYPE_DETECTED) && !defined(LWM_COMPILER_ARM7)
#if defined(__ARMCOMPILER_VERSION) && (__ARMCOMPILER_VERSION >= 7000000L) && (__ARMCOMPILER_VERSION < 8000000L)
#define LWM_COMPILER_ARM7
#define LWM_COMPILER_TYPE_DETECTED
#endif
#endif

#if !defined(LWM_COMPILER_TYPE_DETECTED) && !defined(LWM_COMPILER_GCC)
#if defined(__GNUC__) && !defined(__clang__) && !defined(__llvm__)
#define LWM_COMPILER_GCC
#define LWM_COMPILER_TYPE_DETECTED
#endif
#endif

#if !defined(LWM_COMPILER_TYPE_DETECTED) && !defined(LWM_COMPILER_CLANG)
#if defined(__clang__) || defined(__llvm__)
#define LWM_COMPILER_CLANG
#define LWM_COMPILER_TYPE_DETECTED
#if __AVR__ == 1
#define LWM_CROSS_COMPILING_TO_AVR
#endif
#endif
#endif

#if !defined(LWM_COMPILER_TYPE_DETECTED) && !defined(LWM_COMPILER_GREEN_HILLS)
#if defined(__ghs__)
#define LWM_COMPILER_GREEN_HILLS
#define LWM_COMPILER_TYPE_DETECTED
#endif
#endif

#if !defined(LWM_COMPILER_TYPE_DETECTED) && !defined(LWM_COMPILER_IAR)
#if defined(__IAR_SYSTEMS_ICC__)
#define LWM_COMPILER_IAR
#define LWM_COMPILER_TYPE_DETECTED
#endif
#endif

#if !defined(LWM_COMPILER_TYPE_DETECTED) && !defined(LWM_COMPILER_INTEL)
#if defined(__INTEL_COMPILER)
#define LWM_COMPILER_INTEL
#define LWM_COMPILER_TYPE_DETECTED
#endif
#endif

#if !defined(LWM_COMPILER_TYPE_DETECTED) && !defined(LWM_COMPILER_TEXAS_INSTRUMENTS)
#if defined(__TI_COMPILER_VERSION__)
#define LWM_COMPILER_TEXAS_INSTRUMENTS
#define LWM_COMPILER_TYPE_DETECTED
#endif
#endif

#if !defined(LWM_COMPILER_TYPE_DETECTED) && !defined(LWM_COMPILER_ICCAVR)
#if defined(__ICCAVR__)
#define LWM_COMPILER_ICCAVR
#define LWM_COMPILER_TYPE_DETECTED
#endif
#endif

#if !defined(LWM_COMPILER_TYPE_DETECTED) && !defined(LWM_COMPILER_MICROSOFT)
#if defined(_MSC_VER)
#define LWM_COMPILER_MICROSOFT
#define LWM_COMPILER_TYPE_DETECTED
#endif
#endif

#if !defined(LWM_COMPILER_TYPE_DETECTED)
#define LWM_COMPILER_GENERIC
#endif


#if defined(LWM_COMPILER_GCC)
#define LWM_USING_GCC_COMPILER 1
#else
#define LWM_USING_GCC_COMPILER 0
#endif

#if defined(LWM_COMPILER_ICCAVR)
#define LWM_USING_ICCAVR_COMPILER 1
#else
#define LWM_USING_ICCAVR_COMPILER 0
#endif

#if defined(LWM_COMPILER_MICROSOFT)
#define LWM_USING_MICROSOFT_COMPILER 1
#else
#define LWM_USING_MICROSOFT_COMPILER 0
#endif

#if defined(LWM_COMPILER_ARM5)
#define LWM_USING_ARM5_COMPILER 1
#else
#define LWM_USING_ARM5_COMPILER 0
#endif

#if defined(LWM_COMPILER_ARM6)
#define LWM_USING_ARM6_COMPILER 1
#else
#define LWM_USING_ARM6_COMPILER 0
#endif

#if defined(LWM_COMPILER_ARM7)
#define LWM_USING_ARM7_COMPILER 1
#else
#define LWM_USING_ARM7_COMPILER 0
#endif

#if defined(LWM_COMPILER_CLANG)
#define LWM_USING_CLANG_COMPILER 1
#else
#define LWM_USING_CLANG_COMPILER 0
#endif

#if defined(LWM_COMPILER_GREEN_HILLS)
#define LWM_USING_GREEN_HILLS_COMPILER 1
#else
#define LWM_USING_GREEN_HILLS_COMPILER 0
#endif

#if defined(LWM_COMPILER_IAR)
#define LWM_USING_IAR_COMPILER 1
#else
#define LWM_USING_IAR_COMPILER 0
#endif

#if defined(LWM_COMPILER_INTEL)
#define LWM_USING_INTEL_COMPILER 1
#else
#define LWM_USING_INTEL_COMPILER 0
#endif

#if defined(LWM_COMPILER_TEXAS_INSTRUMENTS)
#define LWM_USING_TEXAS_INSTRUMENTS_COMPILER 1
#else
#define LWM_USING_TEXAS_INSTRUMENTS_COMPILER 0
#endif

#if defined(LWM_COMPILER_GENERIC)
#define LWM_USING_GENERIC_COMPILER 1
#else
#define LWM_USING_GENERIC_COMPILER 0
#endif

#if !defined(LWM_COMPILER_VERSION) && !defined(LWM_COMPILER_FULL_VERSION)
#if defined(LWM_COMPILER_GCC)
#define LWM_COMPILER_VERSION      __GNUC__
#define LWM_COMPILER_FULL_VERSION ((__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + __GNUC_PATCHLEVEL__)
#elif defined(LWM_COMPILER_ICCAVR)
#define LWM_COMPILER_VERSION      __VER__
#define LWM_COMPILER_FULL_VERSION __VER__
#elif defined(LWM_COMPILER_MICROSOFT)
#define LWM_COMPILER_VERSION      _MSC_VER
#define LWM_COMPILER_FULL_VERSION _MSC_FULL_VER
#elif defined(LWM_COMPILER_ARM5)
#define LWM_COMPILER_VERSION      __ARMCC_VERSION
#define LWM_COMPILER_FULL_VERSION __ARMCC_VERSION
#elif defined(LWM_COMPILER_ARM6)
#define LWM_COMPILER_VERSION      __ARMCOMPILER_VERSION
#define LWM_COMPILER_FULL_VERSION __ARMCOMPILER_VERSION
#elif defined(LWM_COMPILER_ARM7)
#define LWM_COMPILER_VERSION      __ARMCOMPILER_VERSION
#define LWM_COMPILER_FULL_VERSION __ARMCOMPILER_VERSION
#elif defined(LWM_COMPILER_CLANG)
#define LWM_COMPILER_VERSION      __clang_version__
#define LWM_COMPILER_FULL_VERSION ((__clang_major__ * 10000) + (__clang_minor__ * 100) + __clang_patchlevel__)
#elif defined(LWM_COMPILER_GREEN_HILLS)
#define LWM_COMPILER_VERSION      __GHS_VERSION_NUMBER__
#define LWM_COMPILER_FULL_VERSION __GHS_VERSION_NUMBER__
#elif defined(LWM_COMPILER_IAR)
#define LWM_COMPILER_VERSION      __VER__
#define LWM_COMPILER_FULL_VERSION __VER__
#elif defined(LWM_COMPILER_INTEL)
#define LWM_COMPILER_VERSION      __INTEL_COMPILER
#define LWM_COMPILER_FULL_VERSION __INTEL_COMPILER
#elif defined(LWM_COMPILER_TEXAS_INSTRUMENTS)
#define LWM_COMPILER_VERSION      __TI_COMPILER_VERSION__
#define LWM_COMPILER_FULL_VERSION __TI_COMPILER_VERSION__
#else
#define LWM_COMPILER_VERSION      0
#define LWM_COMPILER_FULL_VERSION 0
#endif
#endif

#if !defined(LWM_CPP23_SUPPORTED)
  #define LWM_CPP23_SUPPORTED 0
#endif

#if LWM_CPP23_SUPPORTED
  #define LWM_CPP11_SUPPORTED 1
  #define LWM_CPP14_SUPPORTED 1
  #define LWM_CPP17_SUPPORTED 1
  #define LWM_CPP20_SUPPORTED 1
#endif

// Determine C++20 support
#if !defined(LWM_CPP20_SUPPORTED)
  #if defined(__cplusplus)
    #if defined(LWM_COMPILER_MICROSOFT)
      #if defined(_MSVC_LANG)
        #define LWM_CPP20_SUPPORTED (_MSVC_LANG >= 202002L)
      #else
        #define LWM_CPP20_SUPPORTED (_MSC_VER >= 1929)
      #endif
    #elif defined(LWM_COMPILER_ARM5)
      #define LWM_CPP20_SUPPORTED 0
    #else
      #define LWM_CPP20_SUPPORTED (__cplusplus >= 202002L)
    #endif
  #else
    #define LWM_CPP20_SUPPORTED 0
  #endif
#endif

#if LWM_CPP20_SUPPORTED
  #define LWM_CPP11_SUPPORTED 1
  #define LWM_CPP14_SUPPORTED 1
  #define LWM_CPP17_SUPPORTED 1
#endif

// Determine C++17 support
#if !defined(LWM_CPP17_SUPPORTED)
  #if defined(__cplusplus)
    #if defined(LWM_COMPILER_MICROSOFT)
      #if defined(_MSVC_LANG)
        #define LWM_CPP17_SUPPORTED (_MSVC_LANG >= 201703L)
      #else
        #define LWM_CPP17_SUPPORTED (_MSC_VER >= 1914)
      #endif
    #elif defined(LWM_COMPILER_ARM5)
      #define LWM_CPP17_SUPPORTED 0
    #else
      #define LWM_CPP17_SUPPORTED (__cplusplus >= 201703L)
    #endif
  #else
    #define LWM_CPP17_SUPPORTED 0
  #endif
#endif

#if LWM_CPP17_SUPPORTED
  #define LWM_CPP11_SUPPORTED 1
  #define LWM_CPP14_SUPPORTED 1
#endif

// Determine C++14 support
#if !defined(LWM_CPP14_SUPPORTED)
  #if defined(__cplusplus)
    #if defined(LWM_COMPILER_MICROSOFT)
      #if defined(_MSVC_LANG)
        #define LWM_CPP14_SUPPORTED (_MSVC_LANG >= 201402L)
      #else
        #define LWM_CPP14_SUPPORTED (_MSC_VER >= 1900)
      #endif
    #elif defined(LWM_COMPILER_ARM5)
      #define LWM_CPP14_SUPPORTED 0
    #else
      #define LWM_CPP14_SUPPORTED (__cplusplus >= 201402L)
    #endif
  #else
    #define LWM_CPP14_SUPPORTED 0
  #endif
#endif

#if LWM_CPP14_SUPPORTED
  #define LWM_CPP11_SUPPORTED 1
#endif

// Determine C++11 support
#if !defined(LWM_CPP11_SUPPORTED)
  #if defined(__cplusplus)
    #if defined(LWM_COMPILER_MICROSOFT)
      #if defined(_MSVC_LANG)
        #define LWM_CPP11_SUPPORTED (_MSVC_LANG >= 201103L)
      #else
        #define LWM_CPP11_SUPPORTED (_MSC_VER >= 1700)
      #endif
    #elif defined(LWM_COMPILER_ARM5)
      #define LWM_CPP11_SUPPORTED 0
    #else
      #define LWM_CPP11_SUPPORTED (__cplusplus >= 201103L)
    #endif
  #else
    #define LWM_CPP11_SUPPORTED 0
  #endif
#endif

// Helper macros
#define LWM_CPP11_NOT_SUPPORTED (!LWM_CPP11_SUPPORTED)
#define LWM_CPP14_NOT_SUPPORTED (!LWM_CPP14_SUPPORTED)
#define LWM_CPP17_NOT_SUPPORTED (!LWM_CPP17_SUPPORTED)
#define LWM_CPP20_NOT_SUPPORTED (!LWM_CPP20_SUPPORTED)
#define LWM_CPP23_NOT_SUPPORTED (!LWM_CPP23_SUPPORTED)

#if !defined(LWM_NO_NULLPTR_SUPPORT)
  #define LWM_NO_NULLPTR_SUPPORT LWM_CPP11_NOT_SUPPORTED
#endif

#if !defined(LWM_NO_SMALL_CHAR_SUPPORT)
  #define LWM_NO_SMALL_CHAR_SUPPORT LWM_CPP20_NOT_SUPPORTED
#endif

#if !defined(LWM_NO_LARGE_CHAR_SUPPORT)
#define LWM_NO_LARGE_CHAR_SUPPORT LWM_CPP11_NOT_SUPPORTED
#endif

#if !defined(LWM_CPP11_TYPE_TRAITS_IS_TRIVIAL_SUPPORTED)
  #define LWM_CPP11_TYPE_TRAITS_IS_TRIVIAL_SUPPORTED LWM_CPP14_SUPPORTED
#endif

// 'Using' macros
#define LWM_USING_CPP11 (LWM_CPP11_SUPPORTED == 1)
#define LWM_USING_CPP14 (LWM_CPP14_SUPPORTED == 1)
#define LWM_USING_CPP17 (LWM_CPP17_SUPPORTED == 1)
#define LWM_USING_CPP20 (LWM_CPP20_SUPPORTED == 1)
#define LWM_USING_CPP23 (LWM_CPP23_SUPPORTED == 1)

// Language standard
#if LWM_USING_CPP23
  #define LWM_LANGUAGE_STANDARD 23
#elif LWM_USING_CPP20
  #define LWM_LANGUAGE_STANDARD 20
#elif LWM_USING_CPP17
  #define LWM_LANGUAGE_STANDARD 17
#elif LWM_USING_CPP14
  #define LWM_LANGUAGE_STANDARD 14
#elif LWM_USING_CPP11
  #define LWM_LANGUAGE_STANDARD 11
#else
  #define LWM_LANGUAGE_STANDARD 3
#endif

#include <math.h>
#if !defined(NAN) || defined(__CROSSWORKS_ARM) || defined(LWM_COMPILER_ARM5) || defined(ARDUINO)
  #define LWM_NO_CPP_NAN_SUPPORT
#endif

#define LWM_USING_EXCEPTIONS 0

#if LWM_NO_NULLPTR_SUPPORT
  #define LWM_HAS_NULLPTR 0
#else
  #define LWM_HAS_NULLPTR 1
#endif

