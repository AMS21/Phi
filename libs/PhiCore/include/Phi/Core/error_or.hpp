#ifndef INCG_PHI_CORE_ERROR_OR_HPP
#define INCG_PHI_CORE_ERROR_OR_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/Config/Inline.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Boolean.hpp"
#include "Phi/Core/Forward.hpp"
#include "Phi/Core/Move.hpp"
#include "Phi/Core/Optional.hpp"
#include "Phi/TypeTraits/is_same.hpp"
#include "Phi/TypeTraits/is_void.hpp"

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
    PHI_ALWAYS_INLINE constexpr error_or(OtherT&& value) noexcept
        : m_Value(forward<OtherT>(value))
    {}

    constexpr error_or(ErrorT&& error) noexcept
        : m_Error(move(error))
    {}

    error_or(error_or&& other) = default;

    error_or(error_or const& other) = default;

    ~error_or() = default;

    error_or& operator=(error_or&& other) = default;

    error_or& operator=(error_or const& other) = default;

    PHI_NODISCARD constexpr ValueT& value() const noexcept
    {
        PHI_DBG_ASSERT(!is_error(), "Calling value() with error set");
        PHI_DBG_ASSERT(has_value(), "Calling value() with no value set");

        return m_Value.value();
    }

    PHI_NODISCARD constexpr ErrorT& error() const noexcept
    {
        PHI_DBG_ASSERT(is_error(), "Calling error() with no error set");
        PHI_DBG_ASSERT(!has_value(), "Calling error() with value set");

        return m_Error.value();
    }

    PHI_NODISCARD constexpr Boolean is_error() const noexcept
    {
        return m_Error.has_value();
    }

    PHI_NODISCARD constexpr Boolean has_value() const noexcept
    {
        return m_Value.has_value();
    }

private:
    Optional<ValueT> m_Value;
    Optional<ErrorT> m_Error;
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

    error_or(error_or&& other) = default;

    ~error_or() = default;

    error_or& operator=(error_or const& other) = default;

    error_or& operator=(error_or&& other) = default;

    template <typename ReturnT>
    ReturnT value() = delete;

    PHI_NODISCARD constexpr ErrorT& error() const noexcept
    {
        PHI_DBG_ASSERT(is_error(), "Calling error() with no error set");

        return m_Error.value();
    }

    PHI_NODISCARD constexpr Boolean is_error() const noexcept
    {
        return m_Error.has_value();
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr Boolean has_value() const noexcept
    {
        return false;
    }

private:
    Optional<ErrorT> m_Error;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ERROR_OR_HPP
