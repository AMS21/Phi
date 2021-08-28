#ifndef INCG_PHI_CORE_SCOPEGUARD_HPP
#define INCG_PHI_CORE_SCOPEGUARD_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Core/Boolean.hpp"
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
    using this_type   = ScopeGuard<ActionT>;
    using action_type = ActionT;

    constexpr explicit ScopeGuard(ActionT action) noexcept
        : m_Action(std::move(action))
    {}

    ScopeGuard(ScopeGuard&&)      = delete;
    ScopeGuard(const ScopeGuard&) = delete;

    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ScopeGuard& operator=(ScopeGuard&&) = delete;

    ~ScopeGuard()
    {
        m_Action();
    }

private:
    ActionT m_Action;
};

template <typename ActionT>
class ArmedScopeGuard
{
private:
    static_assert(!std::is_reference_v<ActionT> && !std::is_const_v<ActionT> &&
                          !std::is_volatile_v<ActionT>,
                  "phi::ArmedScopeGuard should store its callable by value");

public:
    using this_type   = ArmedScopeGuard<ActionT>;
    using action_type = ActionT;

    constexpr explicit ArmedScopeGuard(ActionT action) noexcept
        : m_Action(std::move(action))
        , m_Armed{true}
    {}

    ArmedScopeGuard(ArmedScopeGuard&&)      = delete;
    ArmedScopeGuard(const ArmedScopeGuard&) = delete;

    ArmedScopeGuard& operator=(const ArmedScopeGuard&) = delete;
    ArmedScopeGuard& operator=(ArmedScopeGuard&&) = delete;

    ~ArmedScopeGuard()
    {
        if (m_Armed)
        {
            m_Action();
        }
    }

    constexpr void disarm() noexcept
    {
        m_Armed = false;
    }

    constexpr void rearm() noexcept
    {
        m_Armed = true;
    }

    PHI_NODISCARD Boolean is_armed() const noexcept
    {
        return m_Armed;
    }

private:
    ActionT m_Action;
    Boolean m_Armed;
};

template <typename ActionT>
PHI_NODISCARD constexpr ScopeGuard<
        typename std::remove_cv_t<typename std::remove_reference_t<ActionT>>>
make_scope_guard(ActionT&& action) noexcept
{
    return ScopeGuard<typename std::remove_cv_t<typename std::remove_reference_t<ActionT>>>(
            std::forward<ActionT>(action));
}

template <typename ActionT>
PHI_NODISCARD constexpr ArmedScopeGuard<
        typename std::remove_cv_t<typename std::remove_reference_t<ActionT>>>
make_armed_scope_guard(ActionT&& action) noexcept
{
    return ArmedScopeGuard<typename std::remove_cv_t<typename std::remove_reference_t<ActionT>>>(
            std::forward<ActionT>(action));
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_SCOPEGUARD_HPP
