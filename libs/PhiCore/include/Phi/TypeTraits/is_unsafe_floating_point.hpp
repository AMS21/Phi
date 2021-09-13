#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_FLOATING_POINT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_FLOATING_POINT_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_same_rcv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_unsafe_floating_point
    : public bool_constant<is_same_rcv_v<TypeT, float> || is_same_rcv_v<TypeT, double> ||
                           is_same_rcv_v<TypeT, long double>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unsafe_floating_point_v =
        is_unsafe_floating_point<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_FLOATING_POINT_HPP
