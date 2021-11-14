#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNION_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsUnion.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_UNION()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_union : public bool_constant<PHI_IS_UNION(TypeT)>
{};

template <typename TypeT>
struct is_not_union : public bool_constant<!PHI_IS_UNION(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_union_v = PHI_IS_UNION(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_union_v = !PHI_IS_UNION(TypeT);

#    endif

#else

#    include "Phi/TypeTraits/always_false.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_union : public false_type
{
    static_assert(always_false<TypeT>, "phi::is_union requires compiler support to properly work.");
};

template <typename TypeT>
struct is_not_union : public bool_constant<!is_union<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_union_v = is_union<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_union_v = is_not_union<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNION_HPP
