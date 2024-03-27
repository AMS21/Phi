#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_INTEGER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_INTEGER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_same_rcv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// clang-format off
template <typename TypeT>
struct is_unsafe_integer
    : public integral_constant<bool,
              is_same_rcv<TypeT, signed char>::value    ||
              is_same_rcv<TypeT, unsigned char>::value  ||
              is_same_rcv<TypeT, short>::value          ||
              is_same_rcv<TypeT, unsigned short>::value ||
              is_same_rcv<TypeT, int>::value            ||
              is_same_rcv<TypeT, unsigned>::value       ||
              is_same_rcv<TypeT, long>::value           ||
              is_same_rcv<TypeT, unsigned long>::value  ||
              is_same_rcv<TypeT, long long>::value      ||
              is_same_rcv<TypeT, unsigned long long>::value>
{};
// clang-format on

template <typename TypeT>
struct is_not_unsafe_integer : public integral_constant<bool, !is_unsafe_integer<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_unsafe_integer_v = is_unsafe_integer<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_unsafe_integer_v =
        is_not_unsafe_integer<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_INTEGER_HPP
