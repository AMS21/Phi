#ifndef INCG_PHI_CORE_SCOPED_VALUE_GUARD_HPP
#define INCG_PHI_CORE_SCOPED_VALUE_GUARD_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/cpp_standard.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ValueT>
class scoped_value_guard
{
public:
    using this_type  = scoped_value_guard<ValueT>;
    using value_type = ValueT;

    constexpr explicit scoped_value_guard(ValueT& variable) noexcept
        : m_Variable(variable)
        , m_SavedValue(variable)
    {}

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    scoped_value_guard(const scoped_value_guard&) = delete;
    scoped_value_guard(scoped_value_guard&&)      = delete;

    scoped_value_guard& operator=(const scoped_value_guard&) = delete;
    scoped_value_guard& operator=(scoped_value_guard&&)      = delete;
#else
    scoped_value_guard(const scoped_value_guard&) = default;
    scoped_value_guard(scoped_value_guard&&)      = default;

    scoped_value_guard& operator=(const scoped_value_guard&)  = default;
    scoped_value_guard& operator=(scoped_value_guard&&)       = default;
#endif

    PHI_CONSTEXPR_DESTRUCTOR ~scoped_value_guard() noexcept
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
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
    ValueT& m_Variable;
    ValueT  m_SavedValue;
};

#if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
template <typename TypeT>
scoped_value_guard(TypeT) -> scoped_value_guard<TypeT>;
#endif

template <typename ValueT>
class armed_scoped_value_guard
{
public:
    using this_type  = armed_scoped_value_guard<ValueT>;
    using value_type = ValueT;

    constexpr explicit armed_scoped_value_guard(ValueT& variable) noexcept
        : m_Variable(variable)
        , m_SavedValue(variable)
        , m_Armed(true)
    {}

#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    armed_scoped_value_guard(const armed_scoped_value_guard&) = delete;
    armed_scoped_value_guard(armed_scoped_value_guard&&)      = delete;

    armed_scoped_value_guard& operator=(const armed_scoped_value_guard&) = delete;
    armed_scoped_value_guard& operator=(armed_scoped_value_guard&&)      = delete;
#else
    armed_scoped_value_guard(const armed_scoped_value_guard&) = default;
    armed_scoped_value_guard(armed_scoped_value_guard&&)      = default;

    armed_scoped_value_guard& operator=(const armed_scoped_value_guard&) = default;
    armed_scoped_value_guard& operator=(armed_scoped_value_guard&&)      = default;
#endif

    PHI_CONSTEXPR_DESTRUCTOR ~armed_scoped_value_guard() noexcept
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

    PHI_NODISCARD constexpr boolean is_armed() const noexcept
    {
        return m_Armed;
    }

private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
    ValueT& m_Variable;
    ValueT  m_SavedValue;
    boolean m_Armed;
};

#if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
template <typename TypeT>
armed_scoped_value_guard(TypeT) -> armed_scoped_value_guard<TypeT>;
#endif

template <typename ValueT>
PHI_NODISCARD constexpr scoped_value_guard<ValueT> make_scoped_value_guard(
        ValueT& variable) noexcept
{
    return scoped_value_guard<ValueT>(variable);
}

template <typename ValueT>
PHI_NODISCARD constexpr armed_scoped_value_guard<ValueT> make_armed_scoped_value_guard(
        ValueT& variable) noexcept
{
    return armed_scoped_value_guard<ValueT>(variable);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_SCOPED_VALUE_GUARD_HPP
