#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_INTEGRAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_INTEGRAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_safe_integral.hpp"
#include "phi/type_traits/is_unsafe_integral.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_integral : public integral_constant<bool, is_safe_integral<TypeT>::value ||
                                                            is_unsafe_integral<TypeT>::value>
{};

template <typename TypeT>
struct is_not_integral : public integral_constant<bool, !is_integral<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_integral_v = is_integral<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_integral_v = is_not_integral<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_INTEGRAL_HPP
