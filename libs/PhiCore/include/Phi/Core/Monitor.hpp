#ifndef INCG_PHI_CORE_MONITOR_HPP
#define INCG_PHI_CORE_MONITOR_HPP

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/PhiConfig.hpp"
#include <functional>
#include <mutex>

DETAIL_PHI_BEGIN_NAMESPACE()

/*!
* \brief Stores shared data in its private section.
*        Allows different threads to operate on the shared data
*        by passing in callables that operate on the shared data.
**/
template <typename SharedDataT>
class Monitor final
{
private:
    struct monitor_helper
    {
        monitor_helper(Monitor* monitor) noexcept
            : m_Monitor(monitor)
            , m_Lock(monitor->m_Mutex)
        {}

        PHI_NODISCARD SharedDataT* operator->() noexcept
        {
            return &m_Monitor->m_SharedData;
        }

        Monitor*                     m_Monitor;
        std::unique_lock<std::mutex> m_Lock;
    };

public:
    using this_type    = Monitor<SharedDataT>;
    using element_type = SharedDataT;

    template <typename... ArgsT>
    constexpr Monitor(ArgsT&&... args) noexcept
        : m_SharedData(std::forward<ArgsT>(args)...)
        , m_Mutex()
    {}

    /*!
	* \brief Creates a Monitor.
	* \param shared_data the data to be protected by the Monitor.
	**/
    constexpr explicit Monitor(SharedDataT shared_data) noexcept
        : m_SharedData(std::move(shared_data))
        , m_Mutex()
    {}

    PHI_NODISCARD monitor_helper operator->() noexcept
    {
        return monitor_helper(this);
    }

    /*!
	* \brief Receives a callable and invokes that callable by passing the
	*        shared data to it. The call itself is protected by a mutex.
	* \param callable The callable to be used to operate on the shared data.
	* \return The result of calling the callable passed in with the shared data
	*         as the callable's call operator's argument.
	**/
    template <typename CallableT>
    auto operator()(CallableT&& callable) const -> decltype(auto)
    {
        std::lock_guard<std::mutex> lock_guard{m_Mutex};
        return std::invoke(std::forward<CallableT>(callable), m_SharedData);
    }

    PHI_NODISCARD monitor_helper ManuallyLock() noexcept
    {
        return monitor_helper(this);
    }

    PHI_NODISCARD SharedDataT& GetThreadUnsafeAccess() noexcept
    {
        return m_SharedData;
    }

private:
    mutable element_type m_SharedData; /// the shared data
    mutable std::mutex   m_Mutex;      /// the mutex to guard access to the shared data
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MONITOR_HPP
