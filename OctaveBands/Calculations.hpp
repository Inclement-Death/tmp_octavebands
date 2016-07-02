#pragma once

#include "pch.hpp"
#include "Enums.hpp"

struct Fraction;

template<size_t W,
    size_t N,
    size_t D,
    class A = Fraction>
    struct TMP_Fraction;

template<size_t W,
    size_t N,
    size_t D,
    size_t FO,
    class A = Fraction>
    struct TMP_Fraction_Ext;

namespace DoubleMath
{
    static constexpr double FRACTION_PRECISION = 100000;

    template<typename T = double>
    static constexpr const T cpow(const T&& base, const T&& exp)
    {
        return (exp > 0) ? (base * cpow(std::forward<const T>(base), std::move(exp - 1.0))) : (1.0);
    };

    static constexpr std::size_t csqrt_impl(std::size_t sq, std::size_t dlt, std::size_t value)
    {
        return sq <= value ?
            csqrt_impl(sq + dlt, dlt + 2, value) : (dlt >> 1) - 1;
    };

    static constexpr std::size_t csqrt(std::size_t value)
    {
        return csqrt_impl(1, 3, value);
    };

    template <typename T = const double>
    static constexpr double cmodf_impl(T a, T b, std::true_type, std::false_type)
    {
        return a % b;
    };

    template <typename T = const double>
    static constexpr T cmodf_impl(T a, T b, std::false_type, std::true_type)
    {
        return std::fmod(a, b);
    };

    template <typename T = const double>
    static constexpr T cmodf(T a, T b)
    {
        return cmodf_impl<T>(a, b,
            std::is_integral<T>(), std::is_floating_point<T>());
    };

    template <typename T = double>
    static constexpr auto ToFraction(T&& f)
    {
        double wholePart;

        return TMP_Fraction<static_cast<long>(wholePart),
            static_cast<long>(cmodf(f, &wholePart) * FRACTION_PRECISION),
            FRACTION_PRECISION>();
    };

    template<typename T = const double>
    static constexpr T const_fabs(T x)
    {
        return x < 0 ? -x : x;
    };

    //Will not work with -ffast-math compiler option
    static constexpr const bool is_nan(const double x)
    {
        return x != x;
    };

    static constexpr const bool is_denormal(const double x)
    {
        return x != 0.0 && const_fabs(x) < std::numeric_limits<double>::min();
    };

    static constexpr bool is_infinite(const double x)
    {
        return x == INFINITY;
    };

    template<typename T>
    static constexpr const bool IsWholeNumber(T&& x)
    {
        return !is_infinite(x) && std::floor(x) == x;
    };

    static constexpr bool IsValidNumber(const double value)
    {
        return !is_nan(value) && !is_denormal(value) && !is_infinite(value);
    };

    static constexpr bool IsSimilar(double value, double comparison, double epsilon)
    {
        return IsValidNumber(value)
            && IsValidNumber(comparison)
            && const_fabs(value - comparison) < epsilon;
    };
};

namespace OctaveBands
{
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
        template<template<size_t, size_t, size_t> class F>
        static constexpr const T PreBandCalc()
        {
            return DoubleMath::cpow(2, static_cast<const T>(F.Numerator) / F.Denominator);
        };

        template<template<size_t, size_t, size_t> class F,
            OctavePosition O>
            static constexpr const T CalcNextOctave(const T currentValue)
        {
            return O == Low
                ? currentValue / PreBandCalc<F>()
                : currentValue * PreBandCalc<F>();
        };
    };
}
