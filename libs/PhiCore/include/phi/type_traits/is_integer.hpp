#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_INTEGER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_INTEGER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/is_safe_integer.hpp"
#include "phi/type_traits/is_unsafe_integer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_integer
    : public bool_constant<is_safe_integer<TypeT>::value || is_unsafe_integer<TypeT>::value>
{};

template <typename TypeT>
struct is_not_integer : public bool_constant<!is_integer<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_integer_v = is_integer<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_integer_v = is_not_integer<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_INTEGER_HPP
