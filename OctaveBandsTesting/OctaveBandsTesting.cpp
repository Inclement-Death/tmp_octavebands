// OctaveBandsTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "../OctaveBands/OctaveBandFactory.hpp"
#include <map>

const OctaveBands::FractionalOctaves AdjustOctaves = OctaveBands::Full;
const OctaveBands::FractionalOctaves DisplayOctaves = OctaveBands::Third;

typedef OctaveBands::BandFactory<AdjustOctaves, false, DisplayOctaves>::factory Factory;
typedef Factory::result Bands;
typedef Factory::primaryResult Primary;
typedef Factory::secondaryResult Secondary;

int main()
{
    map<uint32_t, OctaveBands::OctaveBand> bandMap;
    auto bands = Bands().As_Array<OctaveBands::OctaveBand>();

    for (size_t i = 0; i < Bands::size; ++i)
    {
        auto band = bands[i];

        if (bandMap.find(band.get_PreferredAsWholeNumber()) == bandMap.end())
        {
            auto bandPair = make_pair<uint32_t, 
                OctaveBands::OctaveBand>(band.get_PreferredAsWholeNumber(), move(band));

            bandMap.emplace(bandPair);
        }
    }

    //NOTE: Testing output

    cout << "Sizes: -----------------------------------------------" << endl;

    cout << "  total size:     " << Bands::size << endl;
    cout << "  primary size:   " << Primary::size << endl;
    cout << "  secondary size: " << Secondary::size << endl;

    cout << "Contents: --------------------------------------------" << endl;

    for (pair<int, OctaveBands::OctaveBand> bandPair : bandMap)
    {
        auto band = bandPair.second;

        cout << "    Preferred Whole: " << band.get_PreferredAsWholeNumber() << endl;
        cout << "    Preferred:       " << band.get_Preferred() << endl;
        cout << "    Process Flags:   " << band.get_ProcessFlags() << endl;
    }

    return 0;
}

