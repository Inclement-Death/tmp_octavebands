#pragma once

#include "pch.hpp"

#include "DoubleMath.hpp"

template<FractionalOctaves FractOctave,
  LimitCalcType CalcType>
struct LimitCalcs
{
  static constexpr double result(const double center)
  {
    return center / std::pow(10.0, 3.0 / (10.0 * (2.0 * FractOctave)));
  }
};

template<FractionalOctaves FractOctave>
struct LimitCalcs <FractOctave, Upper>
{
  static constexpr double result(const double center)
  {
    return std::pow(10.0, 3.0 / (10.0 * (2.0 * FractOctave))) * center;
  }
};

template<FractionalOctaves FractOctave>
struct LimitCalcs<FractOctave, Width>
{
  static constexpr double result(const double center)
  {
    return (std::pow(10.0, 3.0 / (10.0 * (2.0 * FractOctave))) * center) - (center / std::pow(10.0, 3.0 / (10.0 * (2.0 * FractOctave))));
  }
};

template<typename T = double>
struct OctaveBandCalculations
{
  template<template<long, long, long> class F>
  static constexpr const T PreBandCalc()
  {
    return DoubleMath::cpow(2, static_cast<const T>(F.Numerator) / F.Denominator);
  };

  template<template<long, long, long> class F,
    OctavePosition O>
  static constexpr const T CalcNextOctave(const T currentValue)
  {
    return O == Low
      ? currentValue / PreBandCalc<F>()
      : currentValue * PreBandCalc<F>();
  };
};
