#pragma once

#include "pch.hpp"

#include "TMP_Utils.hpp"
#include "PreferredCenters.hpp"
#include "CenterFrequencies.hpp"
#include "OctaveUtil.hpp"
#include "OctaveBand.hpp"

template <std::size_t Counter, 
  std::size_t Current,
  std::size_t Max,
  std::size_t Add,
  FractionalOctaves Fract,
  ProcessingFlags Flags,
  typename... O>
struct BandGen
{
  static const std::size_t cntr = Counter + 1;
  static const std::size_t cur = Current + Add;

  typedef typename BandGen<cntr, cur, Max, Add, Fract, Flags, O...,
    OctaveBandCreator<Fract, Flags, 
      typename std::tuple_element<cur, PreferredCenters::result>::type, 
      typename std::tuple_element<cur, CenterFrequencies::result>::type>>::result result;
};

template<std::size_t Current,
  std::size_t Max,
  std::size_t Add,
  FractionalOctaves Fract,
  ProcessingFlags Flags,
  typename... O>
struct BandGen<Max, Current, Max, Add, Fract, Flags, O...>
{
  static const std::size_t cntr = Max;
  static const std::size_t cur = Current;

  typedef std::tuple<O...> result;
};

template<FractionalOctaves Fract,
  bool OutputAdjustmentBands,
  ProcessingFlags Flags>
struct BandFactory_Single
{
  typedef OctaveUtil<Fract, Flags> PrimaryUtil;

  typedef typename BandGen <1, 0, PrimaryUtil::size, PrimaryUtil::add, Fract, Flags,
    OctaveBandCreator<Fract, Flags, 
    typename std::tuple_element<0, PreferredCenters::result>::type, 
    typename std::tuple_element<0, CenterFrequencies::result>::type>>::result result;
};

template<FractionalOctaves AdjustFract,
  bool OutputAdjustmentBands,
  FractionalOctaves OutputFract>
struct BandFactory_Impl 
{
  static const FractionalOctaves PrimaryFract =
    TMP_If<(OutputFract > AdjustFract), FractionalOctaves, 
      OutputFract, AdjustFract>::result;

  static const FractionalOctaves SecondaryFract =
    TMP_If<(OutputFract < AdjustFract), FractionalOctaves, 
      AdjustFract, OutputFract>::result;

  static const ProcessingFlags PrimaryFlags =
    TMP_If<(OutputFract > AdjustFract), ProcessingFlags, Output,
      TMP_If<OutputAdjustmentBands, ProcessingFlags, Both, Adjust>::result>::result;

  static const ProcessingFlags SecondaryFlags =
    TMP_If < (OutputFract < AdjustFract), ProcessingFlags,
      TMP_If<OutputAdjustmentBands, ProcessingFlags, Both, Adjust>::result, Output>::result;

  typedef OctaveUtil<PrimaryFract, PrimaryFlags> PrimaryUtil;
  typedef OctaveUtil<SecondaryFract, SecondaryFlags> SecondaryUtil;

  //TODO: generate both primary and secondary at the same time
  typedef typename BandGen <1, 0, PrimaryUtil::size, PrimaryUtil::add,
    PrimaryFract, PrimaryFlags, OctaveBandCreator<PrimaryFract, PrimaryFlags,
      std::tuple_element<0, PreferredCenters::result>::type,
      std::tuple_element<0, CenterFrequencies::result>::type>>::result primaryResult;

  typedef typename BandGen <1, 0, SecondaryUtil::size, SecondaryUtil::add,
    SecondaryFract, SecondaryFlags, OctaveBandCreator<SecondaryFract, SecondaryFlags,
    std::tuple_element<0, PreferredCenters::result>::type,
    std::tuple_element<0, CenterFrequencies::result>::type >>::result result;
};

template<FractionalOctaves AdjustFract,
  bool OutputAdjustmentBands>
struct BandFactory_Impl<AdjustFract, OutputAdjustmentBands, AdjustFract>
{
  typedef typename BandFactory_Single<AdjustFract, OutputAdjustmentBands, Both>::result result;
};

template<FractionalOctaves AdjustFract, 
  bool OutputAdjustmentBands>
struct BandFactory_Impl<AdjustFract, OutputAdjustmentBands, None>
{
  typedef typename BandFactory_Single<AdjustFract, OutputAdjustmentBands, Adjust>::result result;
};

template<bool OutputAdjustmentBands,
  FractionalOctaves OutputFract>
struct BandFactory_Impl<None, OutputAdjustmentBands, OutputFract>
{
  typedef typename BandFactory_Single<OutputFract, OutputAdjustmentBands, Display>::result result;
};

template<bool OutputAdjustmentBands>
struct BandFactory_Impl<None, OutputAdjustmentBands, None>
{
  typedef NullType result;
};

template<FractionalOctaves AdjustFract,
  bool OutputAdjustmentBands,
  FractionalOctaves OutputFract>
struct BandFactory
{
  typedef typename BandFactory_Impl<AdjustFract, OutputAdjustmentBands, OutputFract>::result result;
};
