#ifndef INCG_PHI_CORE_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/nodiscard.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, TypeT Value>
struct integral_constant
{
    using this_type  = integral_constant<TypeT, Value>;
    using value_type = TypeT;
    using type       = integral_constant<TypeT, Value>;

    static constexpr TypeT value = Value;

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr operator TypeT() const noexcept
    {
        return value;
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr TypeT operator()() const noexcept
    {
        return value;
    }
};

template <typename TypeT, TypeT Value>
constexpr TypeT integral_constant<TypeT, Value>::value;

template <bool Value>
using bool_constant = integral_constant<bool, Value>;

using true_type  = bool_constant<true>;
using false_type = bool_constant<false>;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
