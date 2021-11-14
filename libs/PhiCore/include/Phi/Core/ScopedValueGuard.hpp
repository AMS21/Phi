#ifndef INCG_PHI_SCOPEDVALUEGUARD_HPP
#define INCG_PHI_SCOPEDVALUEGUARD_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/CPlusPlus.hpp"
#include "Phi/Core/Boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ValueT>
class ScopedValueGuard
{
public:
    using this_type  = ScopedValueGuard<ValueT>;
    using value_type = ValueT;

    constexpr explicit ScopedValueGuard(ValueT& variable) noexcept
        : m_Variable(variable)
        , m_SavedValue(variable)
    {}

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    ScopedValueGuard(const ScopedValueGuard&) = delete;
    ScopedValueGuard(ScopedValueGuard&&)      = delete;

    ScopedValueGuard& operator=(const ScopedValueGuard&) = delete;
    ScopedValueGuard& operator=(ScopedValueGuard&&) = delete;
#else
    ScopedValueGuard(const ScopedValueGuard&) = default;
    ScopedValueGuard(ScopedValueGuard&&)      = default;

    ScopedValueGuard& operator=(const ScopedValueGuard&) = default;
    ScopedValueGuard& operator=(ScopedValueGuard&&)     = default;
#endif

    PHI_CONSTEXPR_DESTRUCTOR ~ScopedValueGuard() noexcept
    {
        m_Variable = m_SavedValue;
    }

    PHI_NODISCARD constexpr ValueT& get_variable() const noexcept
    {
        return m_Variable;
    }

    PHI_NODISCARD constexpr ValueT get_saved_value() const noexcept
    {
        return m_SavedValue;
    }

    PHI_EXTENDED_CONSTEXPR void override_saved_value(const ValueT& new_value) noexcept
    {
        m_SavedValue = new_value;
    }

private:
    ValueT& m_Variable;
    ValueT  m_SavedValue;
};

#if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
template <typename TypeT>
ScopedValueGuard(TypeT) -> ScopedValueGuard<TypeT>;
#endif

template <typename ValueT>
class ArmedScopedValueGuard
{
public:
    using this_type  = ArmedScopedValueGuard<ValueT>;
    using value_type = ValueT;

    constexpr explicit ArmedScopedValueGuard(ValueT& variable) noexcept
        : m_Variable(variable)
        , m_SavedValue(variable)
        , m_Armed(true)
    {}

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    ArmedScopedValueGuard(const ArmedScopedValueGuard&) = delete;
    ArmedScopedValueGuard(ArmedScopedValueGuard&&)      = delete;

    ArmedScopedValueGuard& operator=(const ArmedScopedValueGuard&) = delete;
    ArmedScopedValueGuard& operator=(ArmedScopedValueGuard&&) = delete;
#else
    ArmedScopedValueGuard(const ArmedScopedValueGuard&) = default;
    ArmedScopedValueGuard(ArmedScopedValueGuard&&)      = default;

    ArmedScopedValueGuard& operator=(const ArmedScopedValueGuard&) = default;
    ArmedScopedValueGuard& operator=(ArmedScopedValueGuard&&) = default;
#endif

    PHI_CONSTEXPR_DESTRUCTOR ~ArmedScopedValueGuard() noexcept
    {
        if (m_Armed)
        {
            m_Variable = m_SavedValue;
        }
    }

    PHI_NODISCARD constexpr ValueT& get_variable() const noexcept
    {
        return m_Variable;
    }

    PHI_NODISCARD constexpr ValueT get_saved_value() const noexcept
    {
        return m_SavedValue;
    }

    PHI_EXTENDED_CONSTEXPR void override_saved_value(const ValueT& new_value) noexcept
    {
        m_SavedValue = new_value;
    }

    PHI_EXTENDED_CONSTEXPR void disarm() noexcept
    {
        m_Armed = false;
    }

    PHI_EXTENDED_CONSTEXPR void rearm() noexcept
    {
        m_Armed = true;
    }

    PHI_NODISCARD constexpr Boolean is_armed() const noexcept
    {
        return m_Armed;
    }

private:
    ValueT& m_Variable;
    ValueT  m_SavedValue;
    Boolean m_Armed;
};

#if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
template <typename TypeT>
ArmedScopedValueGuard(TypeT) -> ArmedScopedValueGuard<TypeT>;
#endif

template <typename ValueT>
PHI_NODISCARD constexpr ScopedValueGuard<ValueT> make_scoped_value_guard(ValueT& variable) noexcept
{
    return ScopedValueGuard<ValueT>(variable);
}

template <typename ValueT>
PHI_NODISCARD constexpr ArmedScopedValueGuard<ValueT> make_armed_scoped_value_guard(
        ValueT& variable) noexcept
{
    return ArmedScopedValueGuard<ValueT>(variable);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_SCOPEDVALUEGUARD_HPP
