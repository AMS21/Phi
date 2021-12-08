#ifndef INCG_PHI_CORE_MONITOR_HPP
#define INCG_PHI_CORE_MONITOR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/invoke.hpp"
#include "phi/core/move.hpp"
#include "phi/type_traits/invoke_result.hpp"
#include <mutex>

DETAIL_PHI_BEGIN_NAMESPACE()

/*!
* \brief Stores shared data in its private section.
*        Allows different threads to operate on the shared data
*        by passing in callables that operate on the shared data.
**/
template <typename SharedDataT>
class monitor final
{
private:
    struct monitor_helper
    {
        monitor_helper(monitor* monitor) noexcept
            : m_monitor(monitor)
            , m_Lock(monitor->m_Mutex)
        {}

        PHI_NODISCARD SharedDataT* operator->() noexcept
        {
            return &m_monitor->m_SharedData;
        }

        monitor*                     m_monitor;
        std::unique_lock<std::mutex> m_Lock;
    };

public:
    using this_type    = monitor<SharedDataT>;
    using element_type = SharedDataT;

    template <typename... ArgsT>
    constexpr monitor(ArgsT&&... args) noexcept
        : m_SharedData(phi::forward<ArgsT>(args)...)
        , m_Mutex()
    {}

    /*!
	* \brief Creates a monitor.
	* \param shared_data the data to be protected by the monitor.
	**/
    constexpr explicit monitor(SharedDataT shared_data) noexcept
        : m_SharedData(phi::move(shared_data))
        , m_Mutex()
    {}

    PHI_NODISCARD monitor_helper operator->() noexcept
    {
        return monitor_helper(this);
    }

#if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    /*!
	* \brief Receives a callable and invokes that callable by passing the
	*        shared data to it. The call itself is protected by a mutex.
	* \param callable The callable to be used to operate on the shared data.
	* \return The result of calling the callable passed in with the shared data
	*         as the callable's call operator's argument.
	**/
    template <typename CallableT>
    auto operator()(CallableT&& callable) const
    {
        std::lock_guard<std::mutex> lock_guard{m_Mutex};
        return phi::invoke(phi::forward<CallableT>(callable), m_SharedData);
    }
#endif

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
