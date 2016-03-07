#pragma once

#include "pch.hpp"

#include "Fraction.hpp"

//TODO: Use Renard Series to calculate these values and DoubleMath::ToFraction to create fractional representations of double values.
struct PreferredCenters
{
  typedef std::tuple < TMP_Fraction<16, 0, 0>, TMP_Fraction<18, 0, 0>, TMP_Fraction<20, 0, 0>,
    TMP_Fraction<22, 2, 5>, TMP_Fraction<25, 0, 0>, TMP_Fraction<28, 0, 0>, TMP_Fraction<31, 1, 2>,
    TMP_Fraction<35, 1, 2>, TMP_Fraction<40, 0, 0>, TMP_Fraction<45, 0, 0>, TMP_Fraction<50, 0, 0>,
    TMP_Fraction<56, 0, 0>, TMP_Fraction<63, 0, 0>, TMP_Fraction<71, 0, 0>, TMP_Fraction<80, 0, 0>,
    TMP_Fraction<90, 0, 0>, TMP_Fraction<100, 0, 0>, TMP_Fraction<112, 0, 0>, TMP_Fraction<125, 0, 0>,
    TMP_Fraction<140, 0, 0>, TMP_Fraction<160, 0, 0>, TMP_Fraction<180, 0, 0>, TMP_Fraction<200, 0, 0>,
    TMP_Fraction<224, 0, 0>, TMP_Fraction<250, 0, 0>, TMP_Fraction<280, 0, 0>, TMP_Fraction<315, 0, 0>,
    TMP_Fraction<355, 0, 0>, TMP_Fraction<400, 0, 0>, TMP_Fraction<450, 0, 0>, TMP_Fraction<500, 0, 0>,
    TMP_Fraction<630, 0, 0>, TMP_Fraction<710, 0, 0>, TMP_Fraction<800, 0, 0>, TMP_Fraction<900, 0, 0>,
    TMP_Fraction<1000, 0, 0>, TMP_Fraction<1120, 0, 0>, TMP_Fraction<1250, 0, 0>, TMP_Fraction<1400, 0, 0>,
    TMP_Fraction<1600, 0, 0>, TMP_Fraction<1800, 0, 0>, TMP_Fraction<2000, 0, 0>, TMP_Fraction<2240, 0, 0>,
    TMP_Fraction<2500, 0, 0>, TMP_Fraction<2800, 0, 0>, TMP_Fraction<3150, 0, 0>, TMP_Fraction<3550, 0, 0>,
    TMP_Fraction<4000, 0, 0>, TMP_Fraction<4500, 0, 0>, TMP_Fraction<5000, 0, 0>, TMP_Fraction<5600, 0, 0>,
    TMP_Fraction<6300, 0, 0>, TMP_Fraction<7100, 0, 0>, TMP_Fraction<8000, 0, 0>, TMP_Fraction<9000, 0, 0>,
    TMP_Fraction<10000, 0, 0>, TMP_Fraction<11200, 0, 0>, TMP_Fraction<12500, 0, 0>, TMP_Fraction<14000, 0, 0>,
    TMP_Fraction<16000, 0, 0 >, TMP_Fraction<18000, 0, 0>, TMP_Fraction < 20000, 0, 0 >> result;

  static const std::size_t size = std::tuple_size<result>::value;
};
