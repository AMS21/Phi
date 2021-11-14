#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_INTEGRAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_INTEGRAL_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsIntegral.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

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

#    include "Phi/CompilerSupport/Char8_t.hpp"
#    include "Phi/TypeTraits/is_same_rcv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_unsafe_integral
    : public bool_constant<is_same_rcv_v<TypeT, bool> || is_same_rcv_v<TypeT, char> ||
                           is_same_rcv_v<TypeT, signed char> ||
                           is_same_rcv_v<TypeT, unsigned char> || is_same_rcv_v<TypeT, char8_t> ||
                           is_same_rcv_v<TypeT, char16_t> || is_same_rcv_v<TypeT, char32_t> ||
                           is_same_rcv_v<TypeT, wchar_t> || is_same_rcv_v<TypeT, short> ||
                           is_same_rcv_v<TypeT, unsigned short> || is_same_rcv_v<TypeT, int> ||
                           is_same_rcv_v<TypeT, unsigned> || is_same_rcv_v<TypeT, long> ||
                           is_same_rcv_v<TypeT, unsigned long> || is_same_rcv_v<TypeT, long long> ||
                           is_same_rcv_v<TypeT, unsigned long long>>
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
