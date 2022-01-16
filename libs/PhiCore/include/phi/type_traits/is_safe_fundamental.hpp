#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_FUNDAMENTAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_FUNDAMENTAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_null_pointer.hpp"
#include "phi/type_traits/is_safe_arithmetic.hpp"
#include "phi/type_traits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_safe_fundamental
    : public bool_constant<is_void<TypeT>::value || is_null_pointer<TypeT>::value ||
                           is_safe_arithmetic<TypeT>::value>
{};

template <typename TypeT>
struct is_not_safe_fundamental : public bool_constant<!is_safe_fundamental<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_safe_fundamental_v = is_safe_fundamental<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_safe_fundamental_v =
        is_not_safe_fundamental<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_FUNDAMENTAL_HPP
