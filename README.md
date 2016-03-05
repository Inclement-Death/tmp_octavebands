# tmp_octavebands
Octave band generator, using C++ template metaprogramming.

Just something I've been messing around with for a couple weeks.

It's pretty much header only (the .hpp files).

Really easy to use.

'''
  // BandFactory<Adjustment octaves [None, Full, TwoThird, Half, Third, Sixth], Output adjustment octaves [true, false], Output octaves [None, Full, TwoThird, Half, Third, Sixth]> 
  typedef BandFactory<AdjustOctaves, false, OutputOctaves>::result OctaveBands;

  int main()
  {
    std::tuple_element<0, OctaveBands>::type band;
    std::cout << band.get_Preferred() << std::endl;
    std::cout << band.get_Center() << std::endl;
    std::cout << band.get_UpperLimit() << std::endl;
    std::cout << band.get_LowerLimit() << std::endl;
    std::cout << band.get_Bandwidth() << std::endl;
    //Process flags can be Adjust, Output, Both.
    std::cout << band.get_ProcessingFlags() << std::endl;
  }
'''
