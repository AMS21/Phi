#ifndef INCG_PHI_CORE_SCOPEGUARD_HPP
#define INCG_PHI_CORE_SCOPEGUARD_HPP

#include "Phi/PhiConfig.hpp"

#include <type_traits>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ActionT>
class ScopeGuard
{
private:
    static_assert(!std::is_reference_v<ActionT> && !std::is_const_v<ActionT> &&
                          !std::is_volatile_v<ActionT>,
                  "phi::ScopeGuard should store its callable by value");

public:
    constexpr explicit ScopeGuard(ActionT action) noexcept
        : m_Action(std::move(action))
    {}

    ScopeGuard(ScopeGuard&&)      = delete;
    ScopeGuard(const ScopeGuard&) = delete;

    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ScopeGuard& operator=(ScopeGuard&&) = delete;

    ~ScopeGuard() noexcept
    {
        m_Action();
    }

private:
    ActionT m_Action;
};

template <typename ActionT>
[[nodiscard]] constexpr ScopeGuard<
        typename std::remove_cv_t<typename std::remove_reference_t<ActionT>>>
make_scope_guard(ActionT&& action) noexcept
{
    return ScopeGuard<typename std::remove_cv_t<typename std::remove_reference_t<ActionT>>>(
            std::forward<ActionT>(action));
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_SCOPEGUARD_HPP
