#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_INTEGER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_INTEGER_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_same_rcv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_unsafe_integer
    : public bool_constant<is_same_rcv_v<TypeT, signed char> ||
                           is_same_rcv_v<TypeT, unsigned char> || is_same_rcv_v<TypeT, short> ||
                           is_same_rcv_v<TypeT, unsigned short> || is_same_rcv_v<TypeT, int> ||
                           is_same_rcv_v<TypeT, unsigned> || is_same_rcv_v<TypeT, long> ||
                           is_same_rcv_v<TypeT, unsigned long> || is_same_rcv_v<TypeT, long long> ||
                           is_same_rcv_v<TypeT, unsigned long long>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unsafe_integer_v = is_unsafe_integer<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_INTEGER_HPP
