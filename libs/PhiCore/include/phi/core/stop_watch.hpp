#ifndef INCG_PHI_CORE_STOP_WATCH_HPP
#define INCG_PHI_CORE_STOP_WATCH_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include <chrono>
#include <ratio>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ClockT = std::chrono::high_resolution_clock>
class stop_watch
{
public:
    using this_type       = stop_watch<ClockT>;
    using clock_type      = ClockT;
    using time_point_type = std::chrono::time_point<ClockT>;

    stop_watch() PHI_NOEXCEPT : m_BeginTimePoint(ClockT::now())
    {}

    template <typename StorageT = double, typename PeriodT = std::milli>
    PHI_NODISCARD std::chrono::duration<StorageT, PeriodT> get_elapsed() const PHI_NOEXCEPT
    {
        const std::chrono::time_point<ClockT> current_time_point = ClockT::now();

        auto elapsed_time = current_time_point - m_BeginTimePoint;

        return std::chrono::duration_cast<std::chrono::duration<StorageT, PeriodT>>(elapsed_time);
    }

private:
    time_point_type m_BeginTimePoint;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_STOP_WATCH_HPP
