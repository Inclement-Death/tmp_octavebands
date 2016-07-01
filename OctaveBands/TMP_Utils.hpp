#pragma once

#include "pch.hpp"

//Create instance of...
template<typename T>
struct instance_of
{
  typedef T type;

  instance_of(int i = 0)
  {}
};

//Value as static
template<typename T, T Value>
struct static_parameter{};

template<typename T, T Value>
struct static_value : static_parameter<T, Value>
{
  static const T value = Value;

  operator T () const
  {
    return Value;
  }
};

//Value If

template<bool Condition, 
  typename ResultType, 
  ResultType TrueResult,
  ResultType FalseResult>
struct TMP_If;

template<typename ResultType,
  ResultType TrueResult,
  ResultType FalseResult>
struct TMP_If<true, ResultType, TrueResult, FalseResult>
{
  static const ResultType result = TrueResult;
};

template<typename ResultType,
  ResultType TrueResult,
  ResultType FalseResult>
struct TMP_If<false, ResultType, TrueResult, FalseResult>
{
  static const ResultType result = FalseResult;
};

//Type If

template<bool Condition,
  typename TrueType,
  typename FalseType>
struct TMP_Type_If;

template<typename TrueType,
  typename FalseType>
struct TMP_Type_If<true, TrueType, FalseType>
{
  typedef TrueType result;
};

template<typename TrueResult,
  typename FalseType>
struct TMP_Type_If<false, TrueResult, FalseType>
{
  typedef FalseType result;
};

template <typename T,
  T... Ts>
struct ConstArray
{
  enum { N = sizeof...(Ts) };
  static const T array[N] = { Ts... };
};

//Array from param pack

template<typename... Ts>
constexpr auto make_array(Ts&&... ts)
  ->std::array<std::common_type_t<Ts...>, sizeof...(ts)>
{
  return { std::forward<Ts>(ts)... };
}

template<template<typename...> class F, typename T>
struct unwrap_into;

template<template<typename...> class F, typename... Ts>
struct unwrap_into<F, std::tuple<Ts...>> {
  typedef F<Ts...> type;
};

class NullType {};

//-------------------------------------------------------------------------------------------------------
//                                                                                                       -
// The following was borrowed from: http://blog.mattbierner.com/stupid-template-tricks-short-circuiting/ -
//                                                                                                       -
// You really should read his blog.                                                                      -
//                                                                                                       -
//-------------------------------------------------------------------------------------------------------

//Generic, type only Thunk
template <template<typename...> class T, typename... args>
struct Thunk {
  using type = T<args...>;
};


//Logical and. TMP version of &&

//Example (also goes for logical_or and terniary)
//template <unsigned val>
//struct is_even {
//  //Value style Thunk
//  template <unsigned arg>
//  struct Thunk {
//    using type = is_even<arg>;
//  };
//
//  static const bool value = logical_and<(val > 1), Thunk<val - 2>>::value;
//};

template <bool, typename right>
struct logical_and : right::type { };

template <typename right>
struct logical_and<false, right> : std::false_type { };


//Logical or. TMP version of ||

template <bool, typename right>
struct logical_or : std::true_type { };

template <typename right>
struct logical_or<false, right> : right::type { };


//Terniary

template <bool, typename consequent, typename alternate>
struct ternary : consequent::type { };

template <typename consequent, typename alternate>
struct ternary<false, consequent, alternate> : alternate::type { };
