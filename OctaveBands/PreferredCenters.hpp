#pragma once

#include "pch.hpp"

#include "Fraction.hpp"
#include "ParamPack.hpp"

namespace OctaveBands
{
    //TODO: Use Renard Series to calculate these values and DoubleMath::ToFraction to create fractional representations of double values.
    struct PreferredCenters
    {
        using value = ParamPack < TMP_Fraction_Ext<16, 0, 0, Full | Half | Third | Sixth>,
            TMP_Fraction_Ext<18, 0, 0, Sixth>,
            TMP_Fraction_Ext<20, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<22, 2, 5, Half | Sixth>,
            TMP_Fraction_Ext<25, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<28, 0, 0, Sixth>,
            TMP_Fraction_Ext<31, 1, 2, Full | Half | Third | Sixth>,
            TMP_Fraction_Ext<35, 1, 2, Sixth>,
            TMP_Fraction_Ext<40, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<45, 0, 0, Half | Sixth>,
            TMP_Fraction_Ext<50, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<56, 0, 0, Sixth>,
            TMP_Fraction_Ext<63, 0, 0, Full | Half | Third | Sixth>,
            TMP_Fraction_Ext<71, 0, 0, Sixth>,
            TMP_Fraction_Ext<80, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<90, 0, 0, Half | Sixth>,
            TMP_Fraction_Ext<100, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<112, 0, 0, Sixth>,
            TMP_Fraction_Ext<125, 0, 0, Full | Half | Third | Sixth>,
            TMP_Fraction_Ext<140, 0, 0, Sixth>,
            TMP_Fraction_Ext<160, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<180, 0, 0, Half | Sixth>,
            TMP_Fraction_Ext<200, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<224, 0, 0, Sixth>,
            TMP_Fraction_Ext<250, 0, 0, Full | Half | Third | Sixth>,
            TMP_Fraction_Ext<280, 0, 0, Sixth>,
            TMP_Fraction_Ext<315, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<355, 0, 0, Half | Sixth>,
            TMP_Fraction_Ext<400, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<450, 0, 0, Sixth>,
            TMP_Fraction_Ext<500, 0, 0, Full | Half | Third | Sixth>,
            TMP_Fraction_Ext<630, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<710, 0, 0, Half | Sixth>,
            TMP_Fraction_Ext<800, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<900, 0, 0, Sixth>,
            TMP_Fraction_Ext<1000, 0, 0, Full | Half | Third | Sixth>,
            TMP_Fraction_Ext<1120, 0, 0, Sixth>,
            TMP_Fraction_Ext<1250, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<1400, 0, 0, Half | Sixth>,
            TMP_Fraction_Ext<1600, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<1800, 0, 0, Sixth>,
            TMP_Fraction_Ext<2000, 0, 0, Full | Half | Third | Sixth>,
            TMP_Fraction_Ext<2240, 0, 0, Sixth>,
            TMP_Fraction_Ext<2500, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<2800, 0, 0, Half | Sixth>,
            TMP_Fraction_Ext<3150, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<3550, 0, 0, Sixth>,
            TMP_Fraction_Ext<4000, 0, 0, Full | Half | Third | Sixth>,
            TMP_Fraction_Ext<4500, 0, 0, Sixth>,
            TMP_Fraction_Ext<5000, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<5600, 0, 0, Half | Sixth>,
            TMP_Fraction_Ext<6300, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<7100, 0, 0, Sixth>,
            TMP_Fraction_Ext<8000, 0, 0, Full | Half | Third | Sixth>,
            TMP_Fraction_Ext<9000, 0, 0, Sixth>,
            TMP_Fraction_Ext<10000, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<11200, 0, 0, Half | Sixth>,
            TMP_Fraction_Ext<12500, 0, 0, Third | Sixth>,
            TMP_Fraction_Ext<14000, 0, 0, Sixth>,
            TMP_Fraction_Ext<16000, 0, 0, Full | Half | Third | Sixth>,
            TMP_Fraction_Ext<18000, 0, 0, Sixth>,
            TMP_Fraction_Ext<20000, 0, 0, Third | Sixth >> ;

        static const size_t size = value::size;
    };
}
