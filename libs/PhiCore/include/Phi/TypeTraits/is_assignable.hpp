#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ASSIGNABLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsAssignable.hpp"
#include "Phi/Core/Declval.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_ASSIGNABLE()

template <typename TypeT, typename ArgT>
struct is_assignable : public bool_constant<PHI_IS_ASSIGNABLE(TypeT, ArgT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE constexpr bool is_assignable_v = PHI_IS_ASSIGNABLE(TypeT, ArgT);

#    endif

#else

namespace detail
{
    template <typename, typename TypeT>
    struct select_2nd
    {
        using type = TypeT;
    };

    template <typename TypeT, typename ArgT>
    typename select_2nd<decltype((declval<TypeT>() = declval<ArgT>())), true_type>::type
    is_assignable_test(int);

    template <typename, typename>
    false_type is_assignable_test(...);

    template <typename TypeT, typename ArgT, bool = is_void<TypeT>::value || is_void<ArgT>::value>
    struct is_assignable_imp : public decltype((is_assignable_test<TypeT, ArgT>(0)))
    {};

    template <typename TypeT, typename ArgT>
    struct is_assignable_imp<TypeT, ArgT, true> : public false_type
    {};
} // namespace detail

template <typename TypeT, typename ArgT>
struct is_assignable : public detail::is_assignable_imp<TypeT, ArgT>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE constexpr bool is_assignable_v = is_assignable<TypeT, ArgT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ASSIGNABLE_HPP