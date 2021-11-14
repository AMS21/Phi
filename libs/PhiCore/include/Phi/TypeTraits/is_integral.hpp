#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_INTEGRAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_INTEGRAL_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_safe_integral.hpp"
#include "Phi/TypeTraits/is_unsafe_integral.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_integral
    : public bool_constant<is_safe_integral<TypeT>::value || is_unsafe_integral<TypeT>::value>
{};

template <typename TypeT>
struct is_not_integral : public bool_constant<!is_integral<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_integral_v = is_integral<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_integral_v = is_not_integral<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_INTEGRAL_HPP
