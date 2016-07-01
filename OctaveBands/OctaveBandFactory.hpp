#pragma once

#include "pch.hpp"

#include "TMP_Utils.hpp"
#include "PreferredCenters.hpp"
#include "CenterFrequencies.hpp"
#include "OctaveUtil.hpp"
#include "OctaveBand.hpp"
#include "Enums.hpp"

template <size_t Counter,
          size_t Current,
          size_t Max,
          size_t Add,
          FractionalOctaves Fract,
          ProcessingFlags Flags,
          typename... O>
struct BandGen
{
    static const size_t cntr = Counter + 1;
    static const size_t cur = Current + Add;

    using result = typename BandGen<cntr, cur, Max, Add, Fract, Flags, O...,
                                    Factory<Fract, Flags,
                                                      typename tuple_element<cur, PreferredCenters::value>::type,
                                                      typename tuple_element<cur, CenterFrequencies::value>::type>>::result;
};

template <size_t Current,
          size_t Max,
          size_t Add,
          FractionalOctaves Fract,
          ProcessingFlags Flags,
          typename... O>
struct BandGen<Max, Current, Max, Add, Fract, Flags, O...>
{
    static const size_t cntr = Max;
    static const size_t cur = Current;

    using result = tuple<O...>;
};

template <FractionalOctaves Fract,
          bool OutputAdjustmentBands,
          ProcessingFlags Flags>
struct BandFactory_Single
{
    using PrimaryUtil = OctaveUtil<Fract, Flags>;

    using result = typename BandGen<1, 0, PrimaryUtil::size, PrimaryUtil::add, Fract, Flags,
                                    Factory<Fract, Flags,
                                                      tuple_element<0, PreferredCenters::value>::type,
                                                      tuple_element<0, CenterFrequencies::value>::type>>::result;
};

template <FractionalOctaves AdjustFract,
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
    TMP_If<(OutputFract < AdjustFract), ProcessingFlags,
           TMP_If<OutputAdjustmentBands, ProcessingFlags, Both, Adjust>::result, Output>::result;

    using PrimaryUtil = OctaveUtil<PrimaryFract, PrimaryFlags>;
    using SecondaryUtil = OctaveUtil<SecondaryFract, SecondaryFlags>;

    //TODO: generate both primary and secondary at the same time
    using primaryResult = typename BandGen<1, 0, PrimaryUtil::size, PrimaryUtil::add,
                                           PrimaryFract, PrimaryFlags, Factory<PrimaryFract, PrimaryFlags,
                                                                                         tuple_element<0, PreferredCenters::value>::type,
                                                                                         tuple_element<0, CenterFrequencies::value>::type>>::result;

    using result = typename BandGen<1, 0, SecondaryUtil::size, SecondaryUtil::add,
                                    SecondaryFract, SecondaryFlags, primaryResult, Factory<SecondaryFract, SecondaryFlags,
                                                                                                     tuple_element<0, PreferredCenters::value>::type,
                                                                                                     tuple_element<0, CenterFrequencies::value>::type>>::result;
};

template <FractionalOctaves AdjustFract,
          bool OutputAdjustmentBands>
struct BandFactory_Impl<AdjustFract, OutputAdjustmentBands, AdjustFract>
{
    using result = typename BandFactory_Single<AdjustFract, OutputAdjustmentBands, Both>::result;
};

template <FractionalOctaves AdjustFract,
          bool OutputAdjustmentBands>
struct BandFactory_Impl<AdjustFract, OutputAdjustmentBands, None>
{
    using result = typename BandFactory_Single<AdjustFract, OutputAdjustmentBands, Adjust>::result;
};

template <bool OutputAdjustmentBands,
          FractionalOctaves OutputFract>
struct BandFactory_Impl<None, OutputAdjustmentBands, OutputFract>
{
    using result = typename BandFactory_Single<OutputFract, OutputAdjustmentBands, Output>::result;
};

template <bool OutputAdjustmentBands>
struct BandFactory_Impl<None, OutputAdjustmentBands, None>
{
    using result = NullType;
};

template <FractionalOctaves AdjustFract,
          bool OutputAdjustmentBands,
          FractionalOctaves OutputFract>
struct BandFactory
{
    using factory = BandFactory_Impl<AdjustFract, OutputAdjustmentBands, OutputFract>;
    using result = typename factory::result;
};
