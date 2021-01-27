#ifndef INCG_PHI_SCOPEDVALUEGUARD_HPP
#define INCG_PHI_SCOPEDVALUEGUARD_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/Core/Boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ValueT>
class ScopedValueGuard
{
public:
    using this_type  = ScopedValueGuard<ValueT>;
    using value_type = ValueT;

    constexpr ScopedValueGuard(ValueT& variable) noexcept
        : m_Variable(variable)
        , m_SavedValue(variable)
    {}

    ScopedValueGuard(ScopedValueGuard&&)      = delete;
    ScopedValueGuard(const ScopedValueGuard&) = delete;

    ScopedValueGuard& operator=(const ScopedValueGuard&) = delete;
    ScopedValueGuard& operator=(ScopedValueGuard&&) = delete;

    ~ScopedValueGuard()
    {
        m_Variable = m_SavedValue;
    }

    [[nodiscard]] constexpr const ValueT& get_variable() const noexcept
    {
        return m_Variable;
    }

    [[nodiscard]] constexpr ValueT& get_variable() noexcept
    {
        return m_Variable;
    }

    [[nodiscard]] constexpr ValueT get_saved_value() const noexcept
    {
        return m_SavedValue;
    }

    constexpr void override_saved_value(const ValueT& new_value) noexcept
    {
        m_SavedValue = new_value;
    }

private:
    ValueT& m_Variable;
    ValueT  m_SavedValue;
};

template <typename ValueT>
class ArmedScopedValueGuard
{
public:
    using this_type  = ArmedScopedValueGuard<ValueT>;
    using value_type = ValueT;

    constexpr ArmedScopedValueGuard(ValueT& variable) noexcept
        : m_Variable(variable)
        , m_SavedValue(variable)
        , m_Armed(true)
    {}

    ArmedScopedValueGuard(ArmedScopedValueGuard&&)      = delete;
    ArmedScopedValueGuard(const ArmedScopedValueGuard&) = delete;

    ArmedScopedValueGuard& operator=(const ArmedScopedValueGuard&) = delete;
    ArmedScopedValueGuard& operator=(ArmedScopedValueGuard&&) = delete;

    ~ArmedScopedValueGuard()
    {
        if (m_Armed)
        {
            m_Variable = m_SavedValue;
        }
    }

    [[nodiscard]] constexpr const ValueT& get_variable() const noexcept
    {
        return m_Variable;
    }

    [[nodiscard]] constexpr ValueT& get_variable() noexcept
    {
        return m_Variable;
    }

    [[nodiscard]] constexpr const ValueT get_saved_value() const noexcept
    {
        return m_SavedValue;
    }

    constexpr void override_saved_value(const ValueT& new_value) noexcept
    {
        m_SavedValue = new_value;
    }

    constexpr void disarm() noexcept
    {
        m_Armed = false;
    }

    constexpr void rearm() noexcept
    {
        m_Armed = true;
    }

    [[nodiscard]] constexpr Boolean is_armed() const noexcept
    {
        return m_Armed;
    }

private:
    ValueT& m_Variable;
    ValueT  m_SavedValue;
    Boolean m_Armed;
};

template <typename ValueT>
[[nodiscard]] constexpr ScopedValueGuard<ValueT> make_scoped_value_guard(ValueT& variable) noexcept
{
    return ScopedValueGuard<ValueT>(variable);
}

template <typename ValueT>
[[nodiscard]] constexpr ArmedScopedValueGuard<ValueT> make_armed_scoped_value_guard(
        ValueT& variable) noexcept
{
    return ArmedScopedValueGuard<ValueT>(variable);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_SCOPEDVALUEGUARD_HPP
