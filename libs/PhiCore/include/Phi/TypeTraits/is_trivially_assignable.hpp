#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE()

template <typename TypeT, typename ArgT>
struct is_trivially_assignable : public bool_constant<__is_trivially_assignable(TypeT, ArgT)>
{};

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_assignable_v = __is_trivially_assignable(TypeT,
                                                                                         ArgT);

#else

template <typename TypeT, typename ArgT>
struct is_trivially_assignable : public false_type
{
    static_assert(always_false<TypeT>, "phi::is_trivially_assignable requires compiler support for "
                                       "intrinsic __is_trivially_assignable");
};

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_assignable_v =
        is_trivially_assignable<TypeT, ArgT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP
