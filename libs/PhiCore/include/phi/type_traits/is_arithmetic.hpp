#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ARITHMETIC_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ARITHMETIC_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/is_safe_arithmetic.hpp"
#include "phi/type_traits/is_unsafe_arithmetic.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_arithmetic
    : public bool_constant<is_unsafe_arithmetic<TypeT>::value || is_safe_arithmetic<TypeT>::value>
{};

template <typename TypeT>
struct is_not_arithmetic : public bool_constant<!is_arithmetic<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_arithmetic_v = is_arithmetic<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_arithmetic_v = is_not_arithmetic<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ARITHMETIC_HPP
