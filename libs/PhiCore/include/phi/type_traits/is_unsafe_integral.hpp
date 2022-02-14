#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_INTEGRAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_INTEGRAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_integral.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_INTEGRAL()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_unsafe_integral : public bool_constant<PHI_IS_INTEGRAL(TypeT)>
{};

template <typename TypeT>
struct is_not_unsafe_integral : public bool_constant<!PHI_IS_INTEGRAL(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unsafe_integral_v = PHI_IS_INTEGRAL(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_unsafe_integral_v = !PHI_IS_INTEGRAL(TypeT);

#    endif

#else

#    include "phi/compiler_support/char8_t.hpp"
#    include "phi/type_traits/is_same_rcv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_unsafe_integral
    : public bool_constant<
              is_same_rcv<TypeT, bool>::value || is_same_rcv<TypeT, char>::value ||
              is_same_rcv<TypeT, signed char>::value || is_same_rcv<TypeT, unsigned char>::value ||
              is_same_rcv<TypeT, char8_t>::value || is_same_rcv<TypeT, char16_t>::value ||
              is_same_rcv<TypeT, char32_t>::value || is_same_rcv<TypeT, wchar_t>::value ||
              is_same_rcv<TypeT, short>::value || is_same_rcv<TypeT, unsigned short>::value ||
              is_same_rcv<TypeT, int>::value || is_same_rcv<TypeT, unsigned>::value ||
              is_same_rcv<TypeT, long>::value || is_same_rcv<TypeT, unsigned long>::value ||
              is_same_rcv<TypeT, long long>::value || is_same_rcv<TypeT, unsigned long long>::value>
{};

template <typename TypeT>
struct is_not_unsafe_integral : public bool_constant<!is_unsafe_integral<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unsafe_integral_v = is_unsafe_integral<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_unsafe_integral_v = is_not_unsafe_integral<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_INTEGRAL_HPP
