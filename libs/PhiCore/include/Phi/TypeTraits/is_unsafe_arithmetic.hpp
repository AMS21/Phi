#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_ARITHMETIC_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_ARITHMETIC_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/is_unsafe_floating_point.hpp"
#include "Phi/TypeTraits/is_unsafe_integral.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_unsafe_arithmetic : public bool_constant<is_unsafe_integral<TypeT>::value ||
                                                   is_unsafe_floating_point<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unsafe_arithmetic_v = is_unsafe_arithmetic<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_ARITHMETIC_HPP