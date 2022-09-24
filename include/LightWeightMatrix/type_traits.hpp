/**
 * @file type_traits.hpp
 * @author InGyuChoi (timetraveler930@gmail.com)
 * @brief partial type_traits without libc++
 * @details a lightweight replacement of c++ <type_traits>, requires c++11
 * @version 0.1
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <stdint.h>
#include <stdlib.h>

namespace lwm
{
  namespace internal
  {
    template<typename...>
    using void_t = void;
    template<typename T, const T VALUE>
    struct integral_constant
    {
      static const T value = VALUE;

      typedef T value_type;
      typedef integral_constant<T, VALUE> type;

      operator value_type() const
      {
        return value;
      }
    };
    typedef integral_constant<bool, false> false_type;
    typedef integral_constant<bool, true> true_type;
    template<typename T, const T VALUE>
    const T integral_constant<T, VALUE>::value;
    template<bool B>
    using bool_constant = integral_constant<bool, B>;
    template<typename T>
    struct negation : bool_constant<!bool(T::value)>
    {
    };
    template<typename T>
    struct remove_reference
    {
      typedef T type;
    };
    template<typename T>
    struct remove_reference<T&>
    {
      typedef T type;
    };
    template<typename T>
    struct remove_reference<T&&>
    {
      typedef T type;
    };
    template<typename T>
    using remove_reference_t = typename remove_reference<T>::type;
    template<typename T>
    struct remove_pointer
    {
      typedef T type;
    };
    template<typename T>
    struct remove_pointer<T*>
    {
      typedef T type;
    };
    template<typename T>
    struct remove_pointer<const T*>
    {
      typedef const T type;
    };
    template<typename T>
    struct remove_pointer<volatile T*>
    {
      typedef volatile T type;
    };
    template<typename T>
    struct remove_pointer<const volatile T*>
    {
      typedef const volatile T type;
    };
    template<typename T>
    struct remove_pointer<T* const>
    {
      typedef T type;
    };
    template<typename T>
    struct remove_pointer<const T* const>
    {
      typedef const T type;
    };
    template<typename T>
    struct remove_pointer<volatile T* const>
    {
      typedef volatile T type;
    };
    template<typename T>
    struct remove_pointer<const volatile T* const>
    {
      typedef const volatile T type;
    };
    template<typename T>
    using remove_pointer_t = typename remove_pointer<T>::type;
    template<typename T>
    struct add_pointer
    {
      typedef typename remove_reference<T>::type* type;
    };
    template<typename T>
    using add_pointer_t = typename add_pointer<T>::type;
    template<typename T>
    struct is_const : false_type
    {
    };
    template<typename T>
    struct is_const<const T> : true_type
    {
    };
    template<typename T>
    struct is_const<const volatile T> : true_type
    {
    };
    template<typename T>
    struct remove_const
    {
      typedef T type;
    };
    template<typename T>
    struct remove_const<const T>
    {
      typedef T type;
    };
    template<typename T>
    using remove_const_t = typename remove_const<T>::type;
    template<typename T>
    struct add_const
    {
      typedef const T type;
    };
    template<typename T>
    struct add_const<const T>
    {
      typedef const T type;
    };
    template<typename T>
    using add_const_t = typename add_const<T>::type;
    template<typename T>
    struct is_volatile : false_type
    {
    };
    template<typename T>
    struct is_volatile<volatile T> : true_type
    {
    };
    template<typename T>
    struct is_volatile<const volatile T> : true_type
    {
    };
    template<typename T>
    struct remove_volatile
    {
      typedef T type;
    };
    template<typename T>
    struct remove_volatile<volatile T>
    {
      typedef T type;
    };
    template<typename T>
    struct add_volatile
    {
      typedef volatile T type;
    };
    template<typename T>
    struct add_volatile<volatile T>
    {
      typedef volatile T type;
    };
    template<typename T>
    using add_volatile_t = typename add_volatile<T>::type;
    template<typename T>
    struct remove_cv
    {
      typedef typename remove_volatile<typename remove_const<T>::type>::type type;
    };
    template<typename T>
    using remove_cv_t = typename remove_cv<T>::type;
    template<typename T>
    struct add_cv
    {
      typedef typename add_volatile<typename add_const<T>::type>::type type;
    };
    template<typename T>
    using add_cv_t = typename add_cv<T>::type;
    template<typename T>
    struct remove_cvref
    {
      typedef typename remove_cv<typename remove_reference<T>::type>::type type;
    };
    template<typename T>
    using remove_cvref_t = typename remove_cvref<T>::type;
    template<typename T>
    struct is_integral : false_type
    {
    };
    template<>
    struct is_integral<bool> : true_type
    {
    };
    template<>
    struct is_integral<char> : true_type
    {
    };
    template<>
    struct is_integral<unsigned char> : true_type
    {
    };
    template<>
    struct is_integral<signed char> : true_type
    {
    };
    template<>
    struct is_integral<wchar_t> : true_type
    {
    };
    template<>
    struct is_integral<short> : true_type
    {
    };
    template<>
    struct is_integral<unsigned short> : true_type
    {
    };
    template<>
    struct is_integral<int> : true_type
    {
    };
    template<>
    struct is_integral<unsigned int> : true_type
    {
    };
    template<>
    struct is_integral<long> : true_type
    {
    };
    template<>
    struct is_integral<unsigned long> : true_type
    {
    };
    template<>
    struct is_integral<long long> : true_type
    {
    };
    template<>
    struct is_integral<unsigned long long> : true_type
    {
    };
    template<typename T>
    struct is_integral<const T> : is_integral<T>
    {
    };
    template<typename T>
    struct is_integral<volatile T> : is_integral<T>
    {
    };
    template<typename T>
    struct is_integral<const volatile T> : is_integral<T>
    {
    };
    template<typename T>
    struct is_signed : false_type
    {
    };
    template<>
    struct is_signed<char> : bool_constant<(char(255) < 0)>
    {
    };
    template<>
    struct is_signed<wchar_t> : public bool_constant<static_cast<bool>(wchar_t(-1) < wchar_t(0))>
    {
    };
    template<>
    struct is_signed<signed char> : true_type
    {
    };
    template<>
    struct is_signed<short> : true_type
    {
    };
    template<>
    struct is_signed<int> : true_type
    {
    };
    template<>
    struct is_signed<long> : true_type
    {
    };
    template<>
    struct is_signed<long long> : true_type
    {
    };
    template<>
    struct is_signed<float> : true_type
    {
    };
    template<>
    struct is_signed<double> : true_type
    {
    };
    template<>
    struct is_signed<long double> : true_type
    {
    };
    template<typename T>
    struct is_signed<const T> : is_signed<T>
    {
    };
    template<typename T>
    struct is_signed<volatile T> : is_signed<T>
    {
    };
    template<typename T>
    struct is_signed<const volatile T> : is_signed<T>
    {
    };
    template<typename T>
    struct is_unsigned : false_type
    {
    };
    template<>
    struct is_unsigned<bool> : true_type
    {
    };
    template<>
    struct is_unsigned<char> : bool_constant<(char(255) > 0)>
    {
    };
    template<>
    struct is_unsigned<unsigned char> : true_type
    {
    };
    template<>
    struct is_unsigned<wchar_t> : public bool_constant<(wchar_t(-1) > wchar_t(0))>
    {
    };
    template<>
    struct is_unsigned<unsigned short> : true_type
    {
    };
    template<>
    struct is_unsigned<unsigned int> : true_type
    {
    };
    template<>
    struct is_unsigned<unsigned long> : true_type
    {
    };
    template<>
    struct is_unsigned<unsigned long long> : true_type
    {
    };
    template<typename T>
    struct is_unsigned<const T> : is_unsigned<T>
    {
    };
    template<typename T>
    struct is_unsigned<volatile T> : is_unsigned<T>
    {
    };
    template<typename T>
    struct is_unsigned<const volatile T> : is_unsigned<T>
    {
    };
    template<typename T>
    struct is_floating_point : false_type
    {
    };
    template<>
    struct is_floating_point<float> : true_type
    {
    };
    template<>
    struct is_floating_point<double> : true_type
    {
    };
    template<>
    struct is_floating_point<long double> : true_type
    {
    };
    template<typename T>
    struct is_floating_point<const T> : is_floating_point<T>
    {
    };
    template<typename T>
    struct is_floating_point<volatile T> : is_floating_point<T>
    {
    };
    template<typename T>
    struct is_floating_point<const volatile T> : is_floating_point<T>
    {
    };
    template<typename T1, typename T2>
    struct is_same : public false_type
    {
    };
    template<typename T>
    struct is_same<T, T> : public true_type
    {
    };
    template<typename T>
    struct is_void : false_type
    {
    };
    template<>
    struct is_void<void> : true_type
    {
    };
    template<typename T>
    struct is_arithmetic : bool_constant<is_integral<T>::value || is_floating_point<T>::value>
    {
    };
    template<typename T>
    struct is_fundamental : bool_constant<is_arithmetic<T>::value || is_void<T>::value>
    {
    };
    template<typename T>
    struct is_compound : bool_constant<!is_fundamental<T>::value>
    {
    };
    template<typename T>
    struct is_array : false_type
    {
    };
    template<typename T>
    struct is_array<T[]> : true_type
    {
    };
    template<typename T, size_t MAXN>
    struct is_array<T[MAXN]> : true_type
    {
    };
    template<typename T>
    struct is_pointer_helper : false_type
    {
    };
    template<typename T>
    struct is_pointer_helper<T*> : true_type
    {
    };
    template<typename T>
    struct is_pointer : is_pointer_helper<typename remove_cv<T>::type>
    {
    };
    template<typename T>
    struct is_lvalue_reference_helper : false_type
    {
    };
    template<typename T>
    struct is_lvalue_reference_helper<T&> : true_type
    {
    };
    template<typename T>
    struct is_lvalue_reference : is_lvalue_reference_helper<typename remove_cv<T>::type>
    {
    };
    template<typename T>
    struct is_rvalue_reference_helper : false_type
    {
    };
    template<typename T>
    struct is_rvalue_reference_helper<T&&> : true_type
    {
    };
    template<typename T>
    struct is_rvalue_reference : is_rvalue_reference_helper<typename remove_cv<T>::type>
    {
    };
    template<typename T>
    struct is_reference : integral_constant<bool, is_lvalue_reference<T>::value || is_rvalue_reference<T>::value>
    {
    };
    template<typename T>
    struct is_pod : bool_constant<is_fundamental<T>::value || is_pointer<T>::value>
    {
    };
    template<bool B, typename T, typename F>
    struct conditional
    {
      typedef T type;
    };
    template<typename T, typename F>
    struct conditional<false, T, F>
    {
      typedef F type;
    };
    template<bool B, typename T, typename F>
    using conditional_t = typename conditional<B, T, F>::type;
    template<typename T>
    struct make_signed
    {
      typedef T type;
    };
    template<>
    struct make_signed<char>
    {
      typedef signed char type;
    };
    template<>
    struct make_signed<unsigned char>
    {
      typedef signed char type;
    };
    template<>
    struct make_signed<wchar_t>
    {
      typedef conditional<
          sizeof(wchar_t) == sizeof(int16_t),
          int16_t,
          conditional<sizeof(wchar_t) == sizeof(int32_t), int32_t, void>::type>::type type;
    };
    template<>
    struct make_signed<unsigned short>
    {
      typedef short type;
    };
    template<>
    struct make_signed<unsigned int>
    {
      typedef int type;
    };
    template<>
    struct make_signed<unsigned long>
    {
      typedef long type;
    };
    template<>
    struct make_signed<unsigned long long>
    {
      typedef long long type;
    };
    template<typename T>
    struct make_signed<const T> : add_const<typename make_signed<T>::type>
    {
    };
    template<typename T>
    struct make_signed<volatile T> : add_volatile<typename make_signed<T>::type>
    {
    };
    template<typename T>
    struct make_signed<const volatile T> : add_const<typename add_volatile<typename make_signed<T>::type>::type>
    {
    };
    template<typename T>
    using make_signed_t = typename make_signed<T>::type;
    template<typename T>
    struct make_unsigned
    {
      typedef T type;
    };
    template<>
    struct make_unsigned<char>
    {
      typedef unsigned char type;
    };
    template<>
    struct make_unsigned<signed char>
    {
      typedef unsigned char type;
    };
    template<>
    struct make_unsigned<short>
    {
      typedef unsigned short type;
    };
    template<>
    struct make_unsigned<wchar_t>
    {
      typedef conditional<
          sizeof(wchar_t) == sizeof(uint16_t),
          uint16_t,
          conditional<sizeof(wchar_t) == sizeof(uint32_t), uint32_t, void>::type>::type type;
    };
    template<>
    struct make_unsigned<int>
    {
      typedef unsigned int type;
    };
    template<>
    struct make_unsigned<long>
    {
      typedef unsigned long type;
    };
    template<>
    struct make_unsigned<long long>
    {
      typedef unsigned long long type;
    };
    template<typename T>
    struct make_unsigned<const T> : add_const<typename make_unsigned<T>::type>
    {
    };
    template<typename T>
    struct make_unsigned<volatile T> : add_volatile<typename make_unsigned<T>::type>
    {
    };
    template<typename T>
    struct make_unsigned<const volatile T> : add_const<typename add_volatile<typename make_unsigned<T>::type>::type>
    {
    };
    template<typename T>
    using make_unsigned_t = typename make_unsigned<T>::type;
    template<bool B, typename T = void>
    struct enable_if
    {
    };
    template<typename T>
    struct enable_if<true, T>
    {
      typedef T type;
    };
    template<bool B, typename T = void>
    using enable_if_t = typename enable_if<B, T>::type;
    template<typename T, unsigned MAXN = 0U>
    struct extent : integral_constant<size_t, 0U>
    {
    };
    template<typename T>
    struct extent<T[], 0> : integral_constant<size_t, 0U>
    {
    };
    template<typename T, unsigned MAXN>
    struct extent<T[], MAXN> : integral_constant<size_t, extent<T, MAXN - 1>::value>
    {
    };
    template<typename T, unsigned MAXN>
    struct extent<T[MAXN], 0> : integral_constant<size_t, MAXN>
    {
    };
    template<typename T, unsigned I, unsigned MAXN>
    struct extent<T[I], MAXN> : integral_constant<size_t, extent<T, MAXN - 1>::value>
    {
    };
    template<typename T>
    struct remove_all_extents
    {
      typedef T type;
    };
    template<typename T>
    struct remove_all_extents<T[]>
    {
      typedef typename remove_all_extents<T>::type type;
    };
    template<typename T, size_t MAXN>
    struct remove_all_extents<T[MAXN]>
    {
      typedef typename remove_all_extents<T>::type type;
    };
    template<typename T>
    using remove_all_extents_t = typename remove_all_extents<T>::type;
    template<typename T>
    struct rank : integral_constant<size_t, 0>
    {
    };
    template<typename T>
    struct rank<T[]> : public integral_constant<size_t, rank<T>::value + 1>
    {
    };
    template<typename T, size_t MAXN>
    struct rank<T[MAXN]> : public integral_constant<size_t, rank<T>::value + 1>
    {
    };
    template<typename T>
    struct decay
    {
      typedef typename remove_reference<T>::type U;
      typedef
          typename conditional<is_array<U>::value, typename remove_extent<U>::type*, typename remove_cv<U>::type>::type type;
    };
    template<typename T>
    using decay_t = typename decay<T>::type;
    template<
        typename TBase,
        typename TDerived,
        const bool IsFundamental =
            (is_fundamental<TBase>::value || is_fundamental<TDerived>::value || is_array<TDerived>::value)>
    struct is_base_of
    {
     private:
      template<typename T>
      struct dummy
      {
      };
      struct internal : TDerived, dummy<int>
      {
      };

      static TBase* check(TBase*)
      {
        return (TBase*)0;
      }

      template<typename T>
      static char check(dummy<T>*)
      {
        return 0;
      }

     public:
      static const bool value = (sizeof(check((internal*)0)) == sizeof(TBase*));
    };

    template<typename TBase, typename TDerived>
    struct is_base_of<TBase, TDerived, true>
    {
      static const bool value = false;
    };
    namespace private_type_traits
    {
      template<typename T>
      char test(int T::*);

      struct dummy
      {
        char c[2];
      };
      template<typename T>
      dummy test(...);
    }  // namespace private_type_traits
    template<typename T>
    struct is_class : bool_constant<sizeof(private_type_traits::test<T>(0)) == 1U>
    {
    };
    template<typename T>
    struct add_lvalue_reference
    {
      typedef T& type;
    };
    template<typename T>
    struct add_lvalue_reference<T&>
    {
      typedef T& type;
    };
    template<>
    struct add_lvalue_reference<void>
    {
      typedef void type;
    };
    template<>
    struct add_lvalue_reference<const void>
    {
      typedef const void type;
    };
    template<>
    struct add_lvalue_reference<volatile void>
    {
      typedef volatile void type;
    };
    template<>
    struct add_lvalue_reference<const volatile void>
    {
      typedef const volatile void type;
    };
    template<typename T>
    using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
    template<typename T>
    struct add_rvalue_reference
    {
      using type = T&&;
    };
    template<typename T>
    struct add_rvalue_reference<T&>
    {
      using type = T&;
    };
    template<>
    struct add_rvalue_reference<void>
    {
      using type = void;
    };
    template<>
    struct add_rvalue_reference<const void>
    {
      using type = const void;
    };
    template<>
    struct add_rvalue_reference<volatile void>
    {
      using type = volatile void;
    };
    template<>
    struct add_rvalue_reference<const volatile void>
    {
      using type = const volatile void;
    };
    template<typename T>
    using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
    template<typename T>
    typename add_rvalue_reference<T>::type declval() noexcept;
    namespace private_type_traits
    {
      template<typename T, typename = int>
      struct is_convertible_to_int : false_type
      {
      };
      template<typename T>
      struct is_convertible_to_int<T, decltype(static_cast<int>(declval<T>()))> : true_type
      {
      };
      template<typename>
      using true_type_for = true_type;
      template<typename T>
      auto returnable(int) -> true_type_for<T()>;
      template<typename>
      auto returnable(...) -> false_type;
      template<typename TFrom, typename TTo>
      auto nonvoid_convertible(int) -> true_type_for<decltype(declval<void (&)(TTo)>()(declval<TFrom>()))>;
      template<typename, typename>
      auto nonvoid_convertible(...) -> false_type;
      template<typename TFrom, typename TTo>
      struct is_convertible : bool_constant<
                                  (decltype(private_type_traits::returnable<TTo>(0))::value &&
                                   decltype(private_type_traits::nonvoid_convertible<TFrom, TTo>(0))::value) ||
                                  (is_void<TFrom>::value && is_void<TTo>::value)>
      {
      };
    }  // namespace private_type_traits
    template<typename T>
    struct is_enum : integral_constant<
                         bool,
                         private_type_traits::is_convertible_to_int<T>::value && !is_class<T>::value &&
                             !is_arithmetic<T>::value && !is_reference<T>::value>
    {
    };
    template<bool B, typename T, T TRUE_VALUE, T FALSE_VALUE>
    struct conditional_integral_constant;
    template<typename T, T TRUE_VALUE, T FALSE_VALUE>
    struct conditional_integral_constant<true, T, TRUE_VALUE, FALSE_VALUE>
    {
      static_assert(is_integral<T>::value, "Not an integral type");
      static const T value = TRUE_VALUE;
    };
    template<typename T, T TRUE_VALUE, T FALSE_VALUE>
    struct conditional_integral_constant<false, T, TRUE_VALUE, FALSE_VALUE>
    {
      static_assert(is_integral<T>::value, "Not an integral type");
      static const T value = FALSE_VALUE;
    };
    template<typename T, typename T1, typename... TRest>
    struct is_one_of
    {
      static const bool value = is_same<T, T1>::value || is_one_of<T, TRest...>::value;
    };
    template<typename T, typename T1>
    struct is_one_of<T, T1>
    {
      static const bool value = is_same<T, T1>::value;
    };
    template<typename T>
    struct types
    {
     private:
      typedef typename remove_reference<typename remove_cv<T>::type>::type type_t;

     public:
      typedef type_t type;
      typedef type_t& reference;
      typedef const type_t& const_reference;
      typedef type_t* pointer;
      typedef const type_t* const_pointer;
      typedef const type_t* const const_pointer_const;
      typedef type_t&& rvalue_reference;
    };
    template<typename T>
    struct types<T*>
    {
     private:
      typedef typename remove_reference<typename remove_cv<T>::type>::type type_t;

     public:
      typedef type_t type;
      typedef type_t& reference;
      typedef const type_t& const_reference;
      typedef type_t* pointer;
      typedef const type_t* const_pointer;
      typedef const type_t* const const_pointer_const;
      typedef type_t&& rvalue_reference;
    };
    template<typename T>
    struct types<T* const>
    {
     private:
      typedef typename remove_reference<typename remove_cv<T>::type>::type type_t;

     public:
      typedef type_t type;
      typedef type_t& reference;
      typedef const type_t& const_reference;
      typedef type_t* pointer;
      typedef const type_t* const_pointer;
      typedef const type_t* const const_pointer_const;
      typedef type_t&& rvalue_reference;
    };
    // References.
    template<typename T>
    struct types<T&>
    {
     private:
      typedef typename remove_reference<typename remove_cv<T>::type>::type type_t;

     public:
      typedef type_t type;
      typedef type_t& reference;
      typedef const type_t& const_reference;
      typedef type_t* pointer;
      typedef const type_t* const_pointer;
      typedef const type_t* const const_pointer_const;
      typedef type_t&& rvalue_reference;
    };
    // rvalue References.
    template<typename T>
    struct types<T&&>
    {
     private:
      typedef typename remove_reference<typename remove_cv<T>::type>::type type_t;

     public:
      typedef type_t type;
      typedef type_t& reference;
      typedef const type_t& const_reference;
      typedef type_t* pointer;
      typedef const type_t* const_pointer;
      typedef const type_t* const const_pointer_const;
      typedef type_t&& rvalue_reference;
    };
    template<typename T>
    using types_t = typename types<T>::type;
    template<typename T>
    using types_r = typename types<T>::reference;
    template<typename T>
    using types_cr = typename types<T>::const_reference;
    template<typename T>
    using types_rr = typename types<T>::rvalue_reference;
    template<typename T>
    using types_p = typename types<T>::pointer;
    template<typename T>
    using types_cp = typename types<T>::const_pointer;
    template<typename T>
    using types_cpc = typename types<T>::const_pointer_const;
    template<typename T>
    struct size_of : integral_constant<size_t, sizeof(T)>
    {
    };
    template<>
    struct size_of<void> : integral_constant<size_t, 1U>
    {
    };
    template<typename T, typename T1, typename... TRest>
    struct are_all_same
    {
      static const bool value = is_same<T, T1>::value && are_all_same<T, TRest...>::value;
    };
    template<typename T, typename T1>
    struct are_all_same<T, T1>
    {
      static const bool value = is_same<T, T1>::value;
    };
    template<typename...>
    struct conjunction : public true_type
    {
    };
    template<typename T1, typename... Tn>
    struct conjunction<T1, Tn...> : public conditional_t<bool(T1::value), conjunction<Tn...>, T1>
    {
    };
    template<typename T>
    struct conjunction<T> : public T
    {
    };
    template<typename...>
    struct disjunction : public false_type
    {
    };
    template<typename T1, typename... Tn>
    struct disjunction<T1, Tn...> : public conditional_t<bool(T1::value), T1, disjunction<Tn...>>
    {
    };
    template<typename T1>
    struct disjunction<T1> : public T1
    {
    };
    template<typename T1, typename T2>
    struct is_assignable
        : public bool_constant<
              (is_arithmetic<T1>::value || is_pointer<T1>::value) && (is_arithmetic<T2>::value || is_pointer<T2>::value)>
    {
    };
    template<typename T, typename... TArgs>
    struct is_constructible : public bool_constant<is_arithmetic<T>::value || is_pointer<T>::value>
    {
    };
    template<typename T>
    struct is_copy_constructible : public bool_constant<is_arithmetic<T>::value || is_pointer<T>::value>
    {
    };
    template<typename T>
    struct is_move_constructible : public bool_constant<is_arithmetic<T>::value || is_pointer<T>::value>
    {
    };
    template<typename T>
    struct is_trivially_constructible : public bool_constant<is_arithmetic<T>::value || is_pointer<T>::value>
    {
    };
    template<typename T>
    struct is_trivially_copy_constructible : public bool_constant<is_arithmetic<T>::value || is_pointer<T>::value>
    {
    };
    template<typename T>
    struct is_trivially_destructible : public bool_constant<is_arithmetic<T>::value || is_pointer<T>::value>
    {
    };
    template<typename T>
    struct is_trivially_copy_assignable : public bool_constant<is_arithmetic<T>::value || is_pointer<T>::value>
    {
    };
    template<typename T>
    struct is_trivially_copyable : public bool_constant<is_arithmetic<T>::value || is_pointer<T>::value>
    {
    };
    template<typename T1, typename T2>
    struct is_lvalue_assignable : public is_assignable<
                                      typename add_lvalue_reference<T1>::type,
                                      typename add_lvalue_reference<typename add_const<T2>::type>::type>
    {
    };
    template<typename...>
    struct common_type
    {
    };
    template<typename T>
    struct common_type<T> : common_type<T, T>
    {
    };
    namespace private_common_type
    {
      template<typename T1, typename T2>
      using conditional_result_t = decltype(false ? declval<T1>() : declval<T2>());
      template<typename, typename, typename = void>
      struct decay_conditional_result
      {
      };
      template<typename T1, typename T2>
      struct decay_conditional_result<T1, T2, void_t<conditional_result_t<T1, T2>>> : decay<conditional_result_t<T1, T2>>
      {
      };
      template<typename T1, typename T2, typename = void>
      struct common_type_2_impl : decay_conditional_result<const T1&, const T2&>
      {
      };
      template<typename T1, typename T2>
      struct common_type_2_impl<T1, T2, void_t<conditional_result_t<T1, T2>>> : decay_conditional_result<T1, T2>
      {
      };
    }  // namespace private_common_type
    template<typename T1, typename T2>
    struct common_type<T1, T2>
        : conditional<
              is_same<T1, typename decay<T1>::type>::value && is_same<T2, typename decay<T2>::type>::value,
              private_common_type::common_type_2_impl<T1, T2>,
              common_type<typename decay<T2>::type, typename decay<T2>::type>>::type
    {
    };
    namespace private_common_type
    {
      template<typename AlwaysVoid, typename T1, typename T2, typename... TRest>
      struct common_type_multi_impl
      {
      };

      template<typename T1, typename T2, typename... TRest>
      struct common_type_multi_impl<void_t<typename common_type<T1, T2>::type>, T1, T2, TRest...>
          : common_type<typename common_type<T1, T2>::type, TRest...>
      {
      };
    }  // namespace private_common_type
    template<typename T1, typename T2, typename... TRest>
    struct common_type<T1, T2, TRest...> : private_common_type::common_type_multi_impl<void, T1, T2, TRest...>
    {
    };
    template<typename... T>
    using common_type_t = typename common_type<T...>::type;
    template<typename T>
    struct unsigned_type
    {
      typedef typename conditional<
          sizeof(T) == sizeof(unsigned char),
          unsigned char,
          typename conditional<
              sizeof(T) == sizeof(unsigned short),
              unsigned short,
              typename conditional<
                  sizeof(T) == sizeof(unsigned int),
                  unsigned int,
                  typename conditional<sizeof(T) == sizeof(unsigned long), unsigned long, unsigned long long>::type>::type>::
              type>::type type;
    };
    template<typename T>
    using unsigned_type_t = typename unsigned_type<T>::type;
    template<typename T>
    struct signed_type
    {
      typedef typename conditional<
          sizeof(T) == sizeof(char),
          char,
          typename conditional<
              sizeof(T) == sizeof(short),
              short,
              typename conditional<
                  sizeof(T) == sizeof(int),
                  int,
                  typename conditional<sizeof(T) == sizeof(long), long, long long>::type>::type>::type>::type type;
    };
    template<typename T>
    using signed_type_t = typename signed_type<T>::type;
  }  // namespace internal
};   // namespace lwm