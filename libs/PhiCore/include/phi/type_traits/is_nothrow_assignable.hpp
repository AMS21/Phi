#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_nothrow_assignable.hpp"
#include "phi/core/declval.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_assignable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_NOTHROW_ASSIGNABLE()

template <typename TypeT, typename ArgT>
struct is_nothrow_assignable : public bool_constant<PHI_IS_NOTHROW_ASSIGNABLE(TypeT, ArgT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_assignable_v = PHI_IS_NOTHROW_ASSIGNABLE(TypeT, ArgT);

#    endif

#else

namespace detail
{
    template <bool, typename TypeT, typename ArgT>
    struct is_nothrow_assignable_impl;

    template <typename TypeT, typename ArgT>
    struct is_nothrow_assignable_impl<false, TypeT, ArgT> : public false_type
    {};

    template <typename TypeT, typename ArgT>
    struct is_nothrow_assignable_impl<true, TypeT, ArgT>
        : public bool_constant<noexcept(declval<TypeT>() = declval<ArgT>())>
    {};
} // namespace detail

template <typename TypeT, typename ArgT>
struct is_nothrow_assignable
    : public detail::is_nothrow_assignable_impl<is_assignable<TypeT, ArgT>::value, TypeT, ArgT>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_assignable_v =
        is_nothrow_assignable<TypeT, ArgT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
