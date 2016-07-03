// tmp_octavebands.cpp : Defines the exported functions for the static library.
//
#pragma once




#include "tmp_octavebands.h"
#include "../OctaveBands/OctaveBandFactory.hpp"
#include <tuple>

const FractionalOctaves AdjustOctaves = Full;
const FractionalOctaves DisplayOctaves = Half;

typedef BandFactory<AdjustOctaves, false, DisplayOctaves>::result Bands;

int fnGetOctaveBands(void)
{
  auto total = std::tuple_size<Bands>::value;

  for (size_t i = 0; i < total - 1; ++i)
  {
    
  }

  return total;
}

// This is the constructor of a class that has been exported.
// see tmp_octavebands.h for the class definition
Ctmp_octavebands::Ctmp_octavebands()
{
  return;
}
