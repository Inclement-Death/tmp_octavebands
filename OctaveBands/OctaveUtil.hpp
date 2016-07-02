#pragma once

#include "pch.hpp"

#include "TMP_Utils.hpp"
#include "Fraction.hpp"

namespace OctaveBands
{
//FractionalOctaves::None
    template<FractionalOctaves FractOctaves,
        ProcessingFlags P>
        struct OctaveUtil
    {
        typedef TMP_Fraction<0, 0, 0> OctaveFraction;

        enum
        {
            Flag = P,
            Fract = FractOctaves
        };

        static const std::size_t add = 0;
        static const std::size_t size = 0;
    };

    template<ProcessingFlags P>
    struct OctaveUtil <Full, P>
    {
      //TODO: Replace ConstArray with search function that utilizes add and size (eg. Full = multiplier: 6, size: 11)
        //typedef ConstArray<std::size_t, 0, 6, 12, 18, 24, 30, 36, 42, 48, 54, 60> locations;

        typedef TMP_Fraction<0, 1, 1> OctaveFraction;

        enum
        {
            Flag = P,
            Fract = Full
        };

        static const std::size_t add = 6;
        static const std::size_t size = 11;
    };

    template<ProcessingFlags P>
    struct OctaveUtil <TwoThird, P>
    {
      //TODO: Replace ConstArray with search function that utilizes add and size (eg. Full = multiplier: 6, size: 11)
        //typedef ConstArray<std::size_t, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60> locations;

        typedef TMP_Fraction<0, 2, 3> OctaveFraction;

        enum
        {
            Flag = P,
            Fract = TwoThird
        };

        static const std::size_t add = 4;
        static const std::size_t size = 16;
    };

    template<ProcessingFlags P>
    struct OctaveUtil <Half, P>
    {
      //TODO: Replace ConstArray with search function that utilizes add and size (eg. Full = multiplier: 6, size: 11)
        //typedef ConstArray<std::size_t, 0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54,
        //    57, 60> locations;

        typedef TMP_Fraction<0, 1, 2> OctaveFraction;

        enum
        {
            Flag = P,
            Fract = Half
        };

        static const std::size_t add = 3;
        static const std::size_t size = 21;
    };

    template<ProcessingFlags P>
    struct OctaveUtil <Third, P>
    {
      //TODO: Replace ConstArray with search function that utilizes add and size (eg. Full = multiplier: 6, size: 11)
        //typedef ConstArray<std::size_t, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36,
        //    38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60> locations;

        typedef TMP_Fraction<0, 1, 3> OctaveFraction;

        enum
        {
            Flag = P,
            Fract = Third
        };

        static const std::size_t add = 2;
        static const std::size_t size = 32;
    };

    template<ProcessingFlags P>
    struct OctaveUtil <Sixth, P>
    {
        typedef TMP_Fraction<0, 1, 6> OctaveFraction;

        enum
        {
            Flag = P,
            Fract = Sixth
        };

        static const std::size_t add = 1;
        static const std::size_t size = 62;
    };
}
