#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Core/Declval.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_constructible.hpp"
#include "Phi/TypeTraits/is_reference.hpp"
#include <cstdint>

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_NOTHROW_CONSTRUCTIBLE()

template <typename TypeT, typename... ArgsT>
struct is_nothrow_constructible : public bool_constant<__is_nothrow_constructible(TypeT, ArgsT...)>
{};

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_constructible_v =
        __is_nothrow_constructible(TypeT, ArgsT...);

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

template <typename TypeT, std::size_t Dimension>
struct is_nothrow_constructible<TypeT[Dimension]>
    : detail::is_nothrow_constructible_impl<is_constructible_v<TypeT>, is_reference_v<TypeT>, TypeT>
{};

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_constructible_v =
        is_nothrow_constructible<TypeT, ArgsT...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP
