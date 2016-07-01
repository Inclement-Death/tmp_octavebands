#pragma once

#include "pch.hpp"

#include "Calculations.hpp"

class OctaveBand
{
  double m_preferred;
  double m_center;
  ProcessingFlags m_processFlags;
  double m_lowerLimit;
  double m_upperLimit;
  double m_bandwidth;

public:
  constexpr OctaveBand(const double& preferred, const double& center, const ProcessingFlags& processFlags, 
    const double& lower, const double& upper, const double& width) noexcept :
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
class Factory : public O
{
public:
  constexpr Factory() :
    O(Preferred().ToDouble(),
      Center().ToDouble(),
      Flags,
      LimitCalcs<Reference, Lower>::result(Center().ToDouble()),
      LimitCalcs<Reference, Upper>::result(Center().ToDouble()),
      LimitCalcs<Reference, Width>::result(Center().ToDouble()))
  {};
};
