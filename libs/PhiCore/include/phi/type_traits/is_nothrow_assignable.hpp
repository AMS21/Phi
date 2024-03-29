#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_nothrow_assignable.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_NOTHROW_ASSIGNABLE()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename ArgT>
struct is_nothrow_assignable
    : public integral_constant<bool, PHI_IS_NOTHROW_ASSIGNABLE(TypeT, ArgT)>
{};

template <typename TypeT, typename ArgT>
struct is_not_nothrow_assignable
    : public integral_constant<bool, !PHI_IS_NOTHROW_ASSIGNABLE(TypeT, ArgT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_nothrow_assignable_v =
        PHI_IS_NOTHROW_ASSIGNABLE(TypeT, ArgT);

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_nothrow_assignable_v =
        !PHI_IS_NOTHROW_ASSIGNABLE(TypeT, ArgT);

#    endif

#elif PHI_HAS_FEATURE_NOEXCEPT()

#    include "phi/compiler_support/warning.hpp"
#    include "phi/core/declval.hpp"
#    include "phi/type_traits/is_assignable.hpp"

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(
        4244) // 'conversion' conversion from 'type1' to 'type2', possible loss of data

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <bool, typename TypeT, typename ArgT>
    struct is_nothrow_assignable_impl;

    template <typename TypeT, typename ArgT>
    struct is_nothrow_assignable_impl<false, TypeT, ArgT> : public false_type
    {};

    template <typename TypeT, typename ArgT>
    struct is_nothrow_assignable_impl<true, TypeT, ArgT>
        : public integral_constant<bool, noexcept(declval<TypeT>() = declval<ArgT>())>
    {};
} // namespace detail

PHI_MSVC_SUPPRESS_WARNING_POP()

template <typename TypeT, typename ArgT>
struct is_nothrow_assignable
    : public detail::is_nothrow_assignable_impl<is_assignable<TypeT, ArgT>::value, TypeT, ArgT>
{};

template <typename TypeT, typename ArgT>
struct is_not_nothrow_assignable
    : public integral_constant<bool, !is_nothrow_assignable<TypeT, ArgT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_nothrow_assignable_v =
        is_nothrow_assignable<TypeT, ArgT>::value;

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_nothrow_assignable_v =
        is_not_nothrow_assignable<TypeT, ArgT>::value;

#    endif

#else

#    include "phi/type_traits/integral_constant.hpp"

// No noexcept so always return true

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename ArgT>
struct is_nothrow_assignable : public true_type
{};

template <typename TypeT, typename ArgT>
struct is_not_nothrow_assignable : public false_type
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_nothrow_assignable_v = true;

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_nothrow_assignable_v = false;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
