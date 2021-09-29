#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_SAME()

template <typename LhsT, typename RhsT>
struct is_same : public bool_constant<__is_same(LhsT, RhsT)>
{};

template <typename LhsT, typename RhsT>
struct is_not_same : public bool_constant<!__is_same(LhsT, RhsT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename LhsT, typename RhsT>
PHI_INLINE_VARIABLE constexpr bool is_same_v = __is_same(LhsT, RhsT);

template <typename LhsT, typename RhsT>
PHI_INLINE_VARIABLE constexpr bool is_not_same_v = !__is_same(LhsT, RhsT);

#    endif

#else

template <typename LhsT, typename RhsT>
struct is_same : public false_type
{};

template <typename TypeT>
struct is_same<TypeT, TypeT> : public true_type
{};

template <typename TypeT, typename OtherT>
struct is_not_same : public true_type
{};

template <typename TypeT>
struct is_not_same<TypeT, TypeT> : public false_type
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename LhsT, typename RhsT>
PHI_INLINE_VARIABLE constexpr bool is_same_v = is_same<LhsT, RhsT>::value;

template <typename TypeT, typename OtherT>
PHI_INLINE_VARIABLE constexpr bool is_not_same_v = is_not_same<TypeT, OtherT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_HPP
