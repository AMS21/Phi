#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_FUNDAMENTAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_FUNDAMENTAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/is_null_pointer.hpp"
#include "phi/type_traits/is_unsafe_arithmetic.hpp"
#include "phi/type_traits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_unsafe_fundamental
    : public bool_constant<is_void<TypeT>::value || is_null_pointer<TypeT>::value ||
                           is_unsafe_arithmetic<TypeT>::value>
{};

template <typename TypeT>
struct is_not_unsafe_fundamental : public bool_constant<!is_unsafe_fundamental<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unsafe_fundamental_v = is_unsafe_fundamental<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_unsafe_fundamental_v =
        is_not_unsafe_fundamental<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_FUNDAMENTAL_HPP
