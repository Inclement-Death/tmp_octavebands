#pragma once

#include "pch.hpp"

#include "Calculations.hpp"

#define ONE_SIXTH 1.0/6.0
#define ONE_TWELVETH 1.0/12.0

template<FractionalOctaves Octaves>
struct OctaveBandCount
{
  const enum { count = 11 };
  static constexpr const double exp = 0.5;
};

template<>
struct OctaveBandCount<Half>
{
  const enum { count = 22 };
  static constexpr const double exp = 0.25;
};

template<>
struct OctaveBandCount<Third>
{
  const enum { count = 32 };
  static constexpr const double exp = ONE_SIXTH;
};

template<>
struct OctaveBandCount<Sixth>
{
  const enum { count = 63 };
  static constexpr const double exp = ONE_TWELVETH;
};

class OctaveBand
{
  double m_preferred;
  double m_center;
  ProcessingFlags m_processFlags;
  double m_lowerLimit;
  double m_upperLimit;
  double m_bandwidth;

public:
  constexpr OctaveBand(const double preferred, const double center, const ProcessingFlags processFlags, 
    const double lower, const double upper, const double width) noexcept :
    m_preferred(std::forward<const double>(preferred)),
    m_center(std::forward<const double>(center)),
    m_processFlags(processFlags),
    m_lowerLimit(lower),
    m_upperLimit(upper),
    m_bandwidth(width)
  {};

  constexpr double get_Preferred() const
  {
    return m_preferred;
  };

  constexpr double get_Center() const
  {
    return m_center;
  };

  constexpr const ProcessingFlags&& get_ProcessFlags() const noexcept
  {
    return std::forward<const ProcessingFlags>(m_processFlags);
  };

  const double&& get_UpperLimit() const noexcept
  {
    return std::forward<const double>(m_upperLimit);
  };

  const double&& get_LowerLimit() const noexcept
  {
    return std::forward<const double>(m_lowerLimit);
  };

  const double&& get_Bandwidth() const noexcept
  {
    return std::forward<const double>(m_bandwidth);
  };
};

template<FractionalOctaves Reference,
  ProcessingFlags Flags,
  class Preferred,
  class Center,
  class O = OctaveBand>
class OctaveBandCreator : public O
{
public:
  constexpr OctaveBandCreator() :
    O(Preferred().ToDouble(),
      Center().ToDouble(),
      Flags,
      LimitCalcs<Reference, Lower>::result(std::move(Center().ToDouble())),
      LimitCalcs<Reference, Upper>::result(std::move(Center().ToDouble())),
      LimitCalcs<Reference, Width>::result(std::move(Center().ToDouble())))
  {};
};
