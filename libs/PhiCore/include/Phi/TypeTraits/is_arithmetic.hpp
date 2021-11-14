#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ARITHMETIC_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ARITHMETIC_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/is_safe_arithmetic.hpp"
#include "Phi/TypeTraits/is_unsafe_arithmetic.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_arithmetic
    : public bool_constant<is_unsafe_arithmetic<TypeT>::value || is_safe_arithmetic<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_arithmetic_v = is_arithmetic<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ARITHMETIC_HPP
