#pragma once

#include "pch.hpp"

#include "TMP_Utils.hpp"
#include "PreferredCenters.hpp"
#include "CenterFrequencies.hpp"
#include "OctaveUtil.hpp"
#include "OctaveBand.hpp"
#include "Enums.hpp"
#include "ParamPack.hpp"

namespace OctaveBands
{
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
            typename pack_element<cur, PreferredCenters::value>::type,
            typename pack_element<cur, CenterFrequencies::value>::type>>::result;
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

        using result = ParamPack<O...>;
    };

    template <FractionalOctaves Fract,
        bool OutputAdjustmentBands,
        ProcessingFlags Flags>
        struct BandFactory_Single
    {
        using PrimaryUtil = OctaveUtil<Fract, Flags>;

        using result = typename BandGen<1, 0, PrimaryUtil::size, PrimaryUtil::add, Fract, Flags,
            Factory<Fract, Flags,
            pack_element<0, PreferredCenters::value>::type,
            pack_element<0, CenterFrequencies::value>::type>>::result;
    };

    template <FractionalOctaves AdjustFract,
        bool OutputAdjustmentBands,
        FractionalOctaves OutputFract>
        struct BandFactory_Impl
    {
        //static const FractionalOctaves PrimaryFract =
        //TMP::TMP_If<(OutputFract > AdjustFract), FractionalOctaves,
        //    OutputFract, AdjustFract>::result;

        //static const FractionalOctaves SecondaryFract =
        //TMP::TMP_If<(OutputFract < AdjustFract), FractionalOctaves,
        //    AdjustFract, OutputFract>::result;

        static const ProcessingFlags PrimaryFlags =
            TMP::TMP_If<(OutputFract > AdjustFract), ProcessingFlags, Output,
                        TMP::TMP_If<OutputAdjustmentBands, ProcessingFlags, Both, Adjust>::result>::result;

        static const ProcessingFlags SecondaryFlags =
            TMP::TMP_If<(OutputFract < AdjustFract), ProcessingFlags,
                        TMP::TMP_If<OutputAdjustmentBands, ProcessingFlags, Both, Adjust>::result, Output>::result;

        using PrimaryUtil = OctaveUtil<AdjustFract, PrimaryFlags>;
        using SecondaryUtil = OctaveUtil<OutputFract, SecondaryFlags>;

        //TODO: generate both primary and secondary at the same time
        using primaryResult = typename BandGen<1, 0, PrimaryUtil::size - 1, PrimaryUtil::add,
            AdjustFract, PrimaryFlags, Factory<AdjustFract, PrimaryFlags,
            pack_element<0, PreferredCenters::value>::type,
            pack_element<0, CenterFrequencies::value>::type>>::result;

        using secondaryResult = typename BandGen<1, 0, SecondaryUtil::size - 1, SecondaryUtil::add,
            OutputFract, SecondaryFlags, Factory<OutputFract, SecondaryFlags,
            pack_element<0, PreferredCenters::value>::type,
            pack_element<0, CenterFrequencies::value>::type>>::result;

        using result = typename paramPack_concat<primaryResult, secondaryResult>::type;
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
        using result = TMP::NullType;
    };

    template <FractionalOctaves AdjustFract,
        bool OutputAdjustmentBands,
        FractionalOctaves OutputFract>
        struct BandFactory
    {
        using factory = BandFactory_Impl<AdjustFract, OutputAdjustmentBands, OutputFract>;
        using result = typename factory::result;
    };
}
