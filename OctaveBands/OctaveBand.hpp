#pragma once

#include "pch.hpp"

#include "Calculations.hpp"
#include <sstream>

namespace OctaveBands
{
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

        constexpr double get_Preferred() const noexcept
        {
            return m_preferred;
        };

        constexpr uint32_t get_PreferredAsWholeNumber() const noexcept
        {
            return static_cast<uint32_t>(m_preferred + 0.5);
        }

        constexpr double get_Center() const noexcept
        {
            return m_center;
        };

        constexpr ProcessingFlags get_ProcessFlags() const noexcept
        {
            return m_processFlags;
        };

        constexpr double get_UpperLimit() const noexcept
        {
            return m_upperLimit;
        };

        constexpr double get_LowerLimit() const noexcept
        {
            return m_lowerLimit;
        };

        constexpr double get_Bandwidth() const noexcept
        {
            return m_bandwidth;
        };

        bool operator<(const OctaveBand& lhs) const
        {
            return m_preferred < lhs.get_Preferred();
        }

        bool operator>(const OctaveBand& lhs) const
        {
            return m_preferred > lhs.get_Preferred();
        }

        bool operator==(const OctaveBand& lhs) const
        {
            return m_preferred == lhs.get_Preferred()
                && m_processFlags == lhs.get_ProcessFlags();
        }

        bool operator<=(const OctaveBand& lhs) const
        {
            return m_preferred < lhs.get_Preferred()
                && (m_preferred == lhs.get_Preferred()
                    && m_processFlags == lhs.get_ProcessFlags());
        }

        bool operator>=(const OctaveBand& lhs) const
        {
            return m_preferred > lhs.get_Preferred()
                && (m_preferred == lhs.get_Preferred()
                    && m_processFlags == lhs.get_ProcessFlags());
        }

        bool operator!=(const OctaveBand& lhs) const
        {
            return !(DoubleMath::IsSimilar(m_preferred, lhs.get_Preferred(), 0.05)
                && m_processFlags == lhs.get_ProcessFlags());
        }

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
}
