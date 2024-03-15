#ifndef INCG_PHI_CORE_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/nodiscard.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// 21.3.4 Helper classes, https://eel.is/c++draft/type.traits#meta.help
template <typename TypeT, TypeT Value>
struct integral_constant
{
    using this_type  = integral_constant<TypeT, Value>;
    using value_type = TypeT;
    using type       = integral_constant<TypeT, Value>;

    static PHI_CONSTEXPR_AND_CONST TypeT value = Value;

    PHI_NODISCARD PHI_ALWAYS_INLINE PHI_CONSTEXPR operator TypeT() const noexcept
    {
        return value;
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE PHI_CONSTEXPR TypeT operator()() const noexcept
    {
        return value;
    }
};

#if PHI_CPP_STANDARD_IS_BELOW(17)

template <typename TypeT, TypeT Value>
PHI_CONSTEXPR TypeT
        integral_constant<TypeT, Value>::value; // NOLINT(readability-redundant-declaration)

#endif

using true_type  = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
