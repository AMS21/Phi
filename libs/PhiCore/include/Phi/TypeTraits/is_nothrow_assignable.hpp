#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Core/Declval.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_assignable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_NOTHROW_ASSIGNABLE()

template <typename TypeT, typename ArgT>
struct is_nothrow_assignable : public bool_constant<__is_nothrow_assignable(TypeT, ArgT)>
{};

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_assignable_v = __is_nothrow_assignable(TypeT, ArgT);

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
    : public detail::is_nothrow_assignable_impl<is_assignable_v<TypeT, ArgT>, TypeT, ArgT>
{};

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_assignable_v =
        is_nothrow_assignable<TypeT, ArgT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
