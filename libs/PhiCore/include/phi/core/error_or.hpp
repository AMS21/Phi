#ifndef INCG_PHI_CORE_ERROR_OR_HPP
#define INCG_PHI_CORE_ERROR_OR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/move.hpp"
#include "phi/core/optional.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ValueT, typename ErrorT>
class PHI_NODISCARD_CLASS error_or
{
    static_assert(is_not_same<ValueT, ErrorT>::value, "ValueT and ErrorT must be distinct types");
    static_assert(is_not_void<ErrorT>::value, "ErrorT may not be void");

public:
    using this_type  = error_or<ValueT, ErrorT>;
    using value_type = ValueT;
    using error_type = ErrorT;

    constexpr error_or(const ValueT& value) noexcept
        : m_Value(value)
    {}

    constexpr error_or(ValueT&& value) noexcept
        : m_Value(move(value))
    {}

    template <typename OtherT>
    // NOLINTNEXTLINE(bugprone-forwarding-reference-overload)
    PHI_ALWAYS_INLINE constexpr error_or(OtherT&& value) noexcept
        : m_Value(forward<OtherT>(value))
    {}

    constexpr error_or(ErrorT&& error) noexcept
        : m_Error(move(error))
    {}

    // NOLINTNEXTLINE(performance-noexcept-move-constructor)
    error_or(error_or&& other) = default;

    error_or(error_or const& other) = default;

    ~error_or() = default;

    // NOLINTNEXTLINE(performance-noexcept-move-constructor)
    error_or& operator=(error_or&& other) = default;

    error_or& operator=(error_or const& other) = default;

    PHI_NODISCARD constexpr ValueT& value() const noexcept
    {
        PHI_ASSERT(!is_error(), "Calling value() with error set");
        PHI_ASSERT(has_value(), "Calling value() with no value set");

        return m_Value.value();
    }

    PHI_NODISCARD constexpr ErrorT& error() const noexcept
    {
        PHI_ASSERT(is_error(), "Calling error() with no error set");
        PHI_ASSERT(!has_value(), "Calling error() with value set");

        return m_Error.value();
    }

    PHI_NODISCARD constexpr boolean is_error() const noexcept
    {
        return m_Error.has_value();
    }

    PHI_NODISCARD constexpr boolean has_value() const noexcept
    {
        return m_Value.has_value();
    }

private:
    optional<ValueT> m_Value;
    optional<ErrorT> m_Error;
};

// Partial specialization for void value type
template <typename ErrorT>
class PHI_NODISCARD_CLASS error_or<void, ErrorT>
{
    static_assert(is_not_void<ErrorT>::value, "ErroT may not be void");

public:
    using this_type  = error_or<void, ErrorT>;
    using value_type = void;
    using error_type = ErrorT;

    error_or() = default;

    constexpr error_or(ErrorT error) noexcept
        : m_Error(move(error))
    {}

    error_or(error_or const& other) = default;

    // NOLINTNEXTLINE(performance-noexcept-move-constructor)
    error_or(error_or&& other) = default;

    ~error_or() = default;

    error_or& operator=(error_or const& other) = default;

    // NOLINTNEXTLINE(performance-noexcept-move-constructor)
    error_or& operator=(error_or&& other) = default;

    template <typename ReturnT>
    ReturnT value() = delete;

    PHI_NODISCARD constexpr ErrorT& error() const noexcept
    {
        PHI_ASSERT(is_error(), "Calling error() with no error set");

        return m_Error.value();
    }

    PHI_NODISCARD constexpr boolean is_error() const noexcept
    {
        return m_Error.has_value();
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr boolean has_value() const noexcept
    {
        return false;
    }

private:
    optional<ErrorT> m_Error;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ERROR_OR_HPP
