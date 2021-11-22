#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_AGGREGATE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_AGGREGATE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsAggregate.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_AGGREGATE()

#    include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_aggregate : public bool_constant<PHI_IS_AGGREGATE(remove_cv_t<TypeT>)>
{};

template <typename TypeT>
struct is_not_aggregate : public bool_constant<!PHI_IS_AGGREGATE(remove_cv_t<TypeT>)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_aggregate_v = PHI_IS_AGGREGATE(remove_cv_t<TypeT>);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_aggregate_v = !PHI_IS_AGGREGATE(remove_cv_t<TypeT>);

#    endif

#else

#    include "Phi/TypeTraits/false_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_aggregate : public false_type
{
    static_assert(false_t<TypeT>::value,
                  "phi::is_aggregate requires compiler support for intrinsic __is_aggregate");
};

template <typename TypeT>
struct is_not_aggregate : public false_type
{
    static_assert(false_t<TypeT>::value,
                  "phi::is_not_aggregate requires compiler support for intrinsic __is_aggregate");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_aggregate_v = is_aggregate<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_aggregate_v = is_not_aggregate<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_AGGREGATE_HPP
