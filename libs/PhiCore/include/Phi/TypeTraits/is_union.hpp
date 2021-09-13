#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNION_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_UNION()

template <typename TypeT>
struct is_union : public bool_constant<__is_union(TypeT)>
{};

#else

template <typename TypeT>
struct is_union : public false_type
{
    static_assert(always_false<TypeT>, "phi::is_union requires compiler support to properly work.");
};

#endif

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_union_v = is_union<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNION_HPP
