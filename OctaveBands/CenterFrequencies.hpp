#pragma once

#include "pch.hpp"

#include "Fraction.hpp"

//TODO: Replace with center frequency generator
struct CenterFrequencies
{
  using value = std::tuple < TMP_Fraction<15, 84893, 100000>, TMP_Fraction<17, 78279, 100000>,
                             TMP_Fraction<19, 95262, 100000>, TMP_Fraction<22, 3872118, 10000000>, TMP_Fraction<25, 11886, 100000>,
                             TMP_Fraction<28, 18383, 100000>, TMP_Fraction<31, 62278, 100000>, TMP_Fraction<35, 48134, 100000>,
                             TMP_Fraction<39, 81072, 100000>, TMP_Fraction<44, 66836, 100000>, TMP_Fraction<50, 11872, 100000>,
                             TMP_Fraction<56, 23413, 100000>, TMP_Fraction<63, 9573, 100000>, TMP_Fraction<70, 79458, 100000>,
                             TMP_Fraction<79, 43282, 100000>, TMP_Fraction<89, 12509, 100000>, TMP_Fraction<100, 0, 0>,
                             TMP_Fraction<112, 20185, 100000>, TMP_Fraction<125, 89254, 100000>, TMP_Fraction<141, 25375, 100000>,
                             TMP_Fraction<158, 48932, 100000>, TMP_Fraction<177, 82794, 100000>, TMP_Fraction<199, 52623, 100000>,
                             TMP_Fraction<223, 87211, 100000>, TMP_Fraction<251, 18864, 100000>, TMP_Fraction<281, 83829, 100000>,
                             TMP_Fraction<316, 22777, 100000>, TMP_Fraction<354, 81339, 100000>, TMP_Fraction<398, 10717, 100000>,
                             TMP_Fraction<446, 68359, 100000>, TMP_Fraction<501, 18723, 100000>, TMP_Fraction<630, 95734, 100000>,
                             TMP_Fraction<707, 94578, 100000>, TMP_Fraction<794, 32823, 100000>, TMP_Fraction<891, 25094, 100000>,
                             TMP_Fraction<1000, 0, 0>, TMP_Fraction<1122, 1845, 100000>, TMP_Fraction<1258, 92541, 100000>,
                             TMP_Fraction<1412, 53754, 100000>, TMP_Fraction<1584, 89319, 100000>, TMP_Fraction<1778, 27941, 100000>,
                             TMP_Fraction<1995, 26231, 100000>, TMP_Fraction<2238, 72114, 100000>, TMP_Fraction<2511, 88643, 100000>,
                             TMP_Fraction<2818, 38293, 100000>, TMP_Fraction<3162, 27766, 100000>, TMP_Fraction<3548, 13389, 100000>,
                             TMP_Fraction<3981, 7171, 100000>, TMP_Fraction<4466, 83592, 100000>, TMP_Fraction<5011, 87234, 100000>,
                             TMP_Fraction<5623, 41325, 100000>, TMP_Fraction<6309, 57344, 100000>, TMP_Fraction<7079, 45784, 100000>,
                             TMP_Fraction<7943, 28235, 100000>, TMP_Fraction<8912, 50938, 100000>, TMP_Fraction<10000, 0, 0>,
                             TMP_Fraction<11200, 18454, 100000>, TMP_Fraction<12589, 25412, 100000>, TMP_Fraction<14125, 37545, 100000>,
                             TMP_Fraction<15848, 93192, 100000 >, TMP_Fraction<17782, 7941, 100000>, TMP_Fraction < 19952, 62315, 100000 >>;

  static const std::size_t size = std::tuple_size<value>::value;
};

template<class Current,
  class Max,
  class OctaveFract>
struct CenterFrequencyGenerator_High
{

};

template<class Max,
  class OctaveFract>
struct CenterFrequencyGenerator_High <Max, Max, OctaveFract>
{

};

template<class Current,
  class Min,
  class OctaveFract>
struct CenterFrequencyGenerator_Low
{

};

template<class Min,
  class OctaveFract>
struct CenterFrequencyGenerator_Low <Min, Min, OctaveFract>
{

};

template<class F>
struct CenterFrequencyGenerator
{

};
