#ifndef INCG_PHI_CORE_STOP_WATCH_HPP
#define INCG_PHI_CORE_STOP_WATCH_HPP

#include "Phi/Core/Types.hpp"
#include "Phi/PhiConfig.hpp"
#include <chrono>
#include <ratio>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ClockT = std::chrono::high_resolution_clock>
class StopWatch
{
public:
    using this_type       = StopWatch<ClockT>;
    using clock_type      = ClockT;
    using time_point_type = std::chrono::time_point<ClockT>;

    StopWatch() noexcept
        : m_BeginTimePoint(ClockT::now())
    {}

    template <typename StorageT = double, typename PeriodT = std::milli>
    [[nodiscard]] std::chrono::duration<StorageT, PeriodT> getElapsed() const noexcept
    {
        const std::chrono::time_point<ClockT> current_time_point = ClockT::now();

        const std::chrono::duration elapsed_time = current_time_point - m_BeginTimePoint;

        return std::chrono::duration_cast<std::chrono::duration<StorageT, PeriodT>>(elapsed_time);
    }

private:
    time_point_type m_BeginTimePoint;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_STOP_WATCH_HPP
