#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_AGGREGATE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_AGGREGATE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsAggregate.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_AGGREGATE()

template <typename TypeT>
struct is_aggregate : public bool_constant<__is_aggregate(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_aggregate_v = __is_aggregate(TypeT);
#    endif

#else

template <typename TypeT>
struct is_aggregate : public false_type
{
    static_assert(always_false<TypeT>::value,
                  "phi::is_aggregate requires compiler support for intrinsic __is_aggregate");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_aggregate_v = is_aggregate<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_AGGREGATE_HPP
