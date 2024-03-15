#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ASSIGNABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_assignable.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_ASSIGNABLE()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename ArgT>
struct is_assignable : public bool_constant<PHI_IS_ASSIGNABLE(TypeT, ArgT)>
{};

template <typename TypeT, typename ArgT>
struct is_not_assignable : public bool_constant<!PHI_IS_ASSIGNABLE(TypeT, ArgT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_assignable_v = PHI_IS_ASSIGNABLE(TypeT, ArgT);

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_assignable_v = !PHI_IS_ASSIGNABLE(TypeT, ArgT);

#    endif

#else

#    include "phi/core/declval.hpp"
#    include "phi/type_traits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

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

template <typename TypeT, typename ArgT>
struct is_not_assignable : public bool_constant<!is_assignable<TypeT, ArgT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_assignable_v = is_assignable<TypeT, ArgT>::value;

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_assignable_v = is_not_assignable<TypeT, ArgT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ASSIGNABLE_HPP
