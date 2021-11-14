#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Core/Declval.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_destructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <bool, typename TypeT>
    struct is_nothrow_destructible_impl;

    template <typename TypeT>
    struct is_nothrow_destructible_impl<false, TypeT> : public false_type
    {};

    template <typename TypeT>
    struct is_nothrow_destructible_impl<true, TypeT>
        : public bool_constant<noexcept(declval<TypeT>().~TypeT())>
    {};
} // namespace detail

template <typename TypeT>
struct is_nothrow_destructible
    : public detail::is_nothrow_destructible_impl<is_destructible<TypeT>::value, TypeT>
{};

template <typename TypeT, std::size_t Dimension>
struct is_nothrow_destructible<TypeT[Dimension]> : public is_nothrow_destructible<TypeT>
{};

template <typename TypeT>
struct is_nothrow_destructible<TypeT&> : public true_type
{};

template <typename TypeT>
struct is_nothrow_destructible<TypeT&&> : public true_type
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_destructible_v =
        is_nothrow_destructible<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
