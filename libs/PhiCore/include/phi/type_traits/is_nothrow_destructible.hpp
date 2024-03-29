#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_nothrow_destructible.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_NOTHROW_DESTRUCTIBLE()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_nothrow_destructible : public integral_constant<bool, PHI_IS_NOTHROW_DESTRUCTIBLE(TypeT)>
{};

template <typename TypeT>
struct is_not_nothrow_destructible
    : public integral_constant<bool, !PHI_IS_NOTHROW_DESTRUCTIBLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_nothrow_destructible_v =
        PHI_IS_NOTHROW_DESTRUCTIBLE(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_nothrow_destructible_v =
        !PHI_IS_NOTHROW_DESTRUCTIBLE(TypeT);

#    endif

#elif PHI_HAS_FEATURE_NOEXCEPT()

#    include "phi/core/declval.hpp"
#    include "phi/core/size_t.hpp"
#    include "phi/type_traits/is_destructible.hpp"

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
        : public integral_constant<bool, noexcept(declval<TypeT>().~TypeT())>
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
struct is_not_nothrow_destructible
    : public integral_constant<bool, !is_nothrow_destructible<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_nothrow_destructible_v =
        is_nothrow_destructible<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_nothrow_destructible_v =
        is_not_nothrow_destructible<TypeT>::value;

#    endif

#else

// No noexcept so always return true

#    include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_nothrow_destructible : public true_type
{};

template <typename TypeT>
struct is_not_nothrow_destructible : false_type
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_nothrow_destructible_v = true;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_nothrow_destructible_v = false;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
