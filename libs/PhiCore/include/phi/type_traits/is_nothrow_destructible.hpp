#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_nothrow_destructible.hpp"
#include "phi/core/declval.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/is_destructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_NOTHROW_DESTRUCTIBLE()

template <typename TypeT>
struct is_nothrow_destructible : public bool_constant<PHI_IS_NOTHROW_DESTRUCTIBLE(TypeT)>
{};

template <typename TypeT>
struct is_not_nothrow_destructible : public bool_constant<!PHI_IS_NOTHROW_DESTRUCTIBLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_destructible_v = PHI_IS_NOTHROW_DESTRUCTIBLE(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_nothrow_destructible_v =
        !PHI_IS_NOTHROW_DESTRUCTIBLE(TypeT);

#    endif

#else

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

template <typename TypeT, size_t Dimension>
struct is_nothrow_destructible<TypeT[Dimension]> : public is_nothrow_destructible<TypeT>
{};

template <typename TypeT>
struct is_nothrow_destructible<TypeT&> : public true_type
{};

template <typename TypeT>
struct is_nothrow_destructible<TypeT&&> : public true_type
{};

template <typename TypeT>
struct is_not_nothrow_destructible : public bool_constant<!is_nothrow_destructible<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_destructible_v =
        is_nothrow_destructible<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_nothrow_destructible_v =
        is_not_nothrow_destructible<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
