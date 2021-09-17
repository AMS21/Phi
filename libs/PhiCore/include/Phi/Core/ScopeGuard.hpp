#ifndef INCG_PHI_CORE_SCOPEGUARD_HPP
#define INCG_PHI_CORE_SCOPEGUARD_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/CPlusPlus.hpp"
#include "Phi/Core/Boolean.hpp"
#include "Phi/Core/Forward.hpp"
#include "Phi/Core/Move.hpp"
#include "Phi/TypeTraits/is_const.hpp"
#include "Phi/TypeTraits/is_reference.hpp"
#include "Phi/TypeTraits/is_volatile.hpp"
#include "Phi/TypeTraits/remove_cvref.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ActionT>
class ScopeGuard
{
private:
    static_assert(!is_reference<ActionT>::value && !is_const<ActionT>::value &&
                          !is_volatile<ActionT>::value,
                  "phi::ScopeGuard should store its callable by value");

public:
    using this_type   = ScopeGuard<ActionT>;
    using action_type = ActionT;

    constexpr explicit ScopeGuard(ActionT action) noexcept
        : m_Action(phi::move(action))
    {}

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    ScopeGuard(ScopeGuard&&)      = delete;
    ScopeGuard(const ScopeGuard&) = delete;

    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ScopeGuard& operator=(ScopeGuard&&) = delete;
#endif

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
    static_assert(!is_reference<ActionT>::value && !is_const<ActionT>::value &&
                          !is_volatile<ActionT>::value,
                  "phi::ArmedScopeGuard should store its callable by value");

public:
    using this_type   = ArmedScopeGuard<ActionT>;
    using action_type = ActionT;

    constexpr explicit ArmedScopeGuard(ActionT action) noexcept
        : m_Action(phi::move(action))
        , m_Armed{true}
    {}

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    ArmedScopeGuard(ArmedScopeGuard&&)      = delete;
    ArmedScopeGuard(const ArmedScopeGuard&) = delete;

    ArmedScopeGuard& operator=(const ArmedScopeGuard&) = delete;
    ArmedScopeGuard& operator=(ArmedScopeGuard&&) = delete;
#endif

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

    PHI_NODISCARD constexpr Boolean is_armed() const noexcept
    {
        return m_Armed;
    }

private:
    ActionT m_Action;
    Boolean m_Armed;
};

template <typename ActionT>
PHI_NODISCARD constexpr ScopeGuard<remove_cvref_t<ActionT>> make_scope_guard(
        ActionT&& action) noexcept
{
    return ScopeGuard<remove_cvref_t<ActionT>>(phi::forward<ActionT>(action));
}

template <typename ActionT>
PHI_NODISCARD constexpr ArmedScopeGuard<remove_cvref_t<ActionT>> make_armed_scope_guard(
        ActionT&& action) noexcept
{
    return ArmedScopeGuard<remove_cvref_t<ActionT>>(phi::forward<ActionT>(action));
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_SCOPEGUARD_HPP
