#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/declval.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_swappable_with.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

namespace detail
{
    template <typename TypeT, typename OtherT = TypeT,
              bool IsSwappable = is_swappable_with<TypeT, OtherT>::value>
    struct is_nothrow_swappable_with_impl
    {
        static PHI_CONSTEXPR_AND_CONST bool value =
                PHI_NOEXCEPT_EXPR(swap(declval<TypeT>(), declval<OtherT>())) &&
                PHI_NOEXCEPT_EXPR(swap(declval<OtherT>(), declval<TypeT>()));
    };

    template <typename TypeT, typename OtherT>
    struct is_nothrow_swappable_with_impl<TypeT, OtherT, false> : public false_type
    {};
} // namespace detail

template <typename TypeT, typename OtherT>
struct is_nothrow_swappable_with
    : public integral_constant<bool, detail::is_nothrow_swappable_with_impl<TypeT, OtherT>::value>
{};

template <typename TypeT, typename OtherT>
struct is_not_nothrow_swappable_with
    : public integral_constant<bool, !is_nothrow_swappable_with<TypeT, OtherT>::value>
{};

PHI_GCC_SUPPRESS_WARNING_POP()

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename OtherT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_nothrow_swappable_with_v =
        is_nothrow_swappable_with<TypeT, OtherT>::value;

template <typename TypeT, typename OtherT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_nothrow_swappable_with_v =
        is_not_nothrow_swappable_with<TypeT, OtherT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
