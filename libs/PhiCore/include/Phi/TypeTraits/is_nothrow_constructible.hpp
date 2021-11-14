#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsNothrowConstructible.hpp"
#include "Phi/Core/Declval.hpp"
#include "Phi/Core/SizeT.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_constructible.hpp"
#include "Phi/TypeTraits/is_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_NOTHROW_CONSTRUCTIBLE()

template <typename TypeT, typename... ArgsT>
struct is_nothrow_constructible
    : public bool_constant<PHI_IS_NOTHROW_CONSTRUCTIBLE(TypeT, ArgsT...)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_constructible_v =
        PHI_IS_NOTHROW_CONSTRUCTIBLE(TypeT, ArgsT...);

#    endif

#else

namespace detail
{
    template <bool, bool, typename TypeT, typename... ArgsT>
    struct is_nothrow_constructible_impl;

    template <typename TypeT, typename... ArgsT>
    struct is_nothrow_constructible_impl</*is constructible*/ true, /*is reference*/ false, TypeT,
                                         ArgsT...>
        : public bool_constant<noexcept(TypeT(declval<ArgsT>()...))>
    {};

    template <typename TypeT>
    void implicit_conversion_to(TypeT) noexcept
    {}

    template <typename TypeT, typename ArgT>
    struct is_nothrow_constructible_impl</*is constructible*/ true, /*is reference*/ true, TypeT,
                                         ArgT>
        : public bool_constant<noexcept(implicit_conversion_to<TypeT>(declval<ArgT>()))>
    {};

    template <typename TypeT, bool IsReference, typename... ArgsT>
    struct is_nothrow_constructible_impl</*is constructible*/ false, IsReference, TypeT, ArgsT...>
        : public false_type
    {};
} // namespace detail

template <typename TypeT, typename... ArgsT>
struct is_nothrow_constructible
    : detail::is_nothrow_constructible_impl<is_constructible_v<TypeT, ArgsT...>,
                                            is_reference_v<TypeT>, TypeT, ArgsT...>
{};

template <typename TypeT, size_t Dimension>
struct is_nothrow_constructible<TypeT[Dimension]>
    : detail::is_nothrow_constructible_impl<is_constructible_v<TypeT>, is_reference_v<TypeT>, TypeT>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_constructible_v =
        is_nothrow_constructible<TypeT, ArgsT...>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP
