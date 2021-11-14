#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/Algorithm/Swap.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Core/Declval.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_swappable_with.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, typename OtherT = TypeT,
              bool IsSwappable = is_swappable_with<TypeT, OtherT>::value>
    struct is_nothrow_swappable_with_impl
    {
        static const bool value = noexcept(swap(declval<TypeT>(), declval<OtherT>()))&& noexcept(
                swap(declval<OtherT>(), declval<TypeT>()));
    };

    template <typename TypeT, typename OtherT>
    struct is_nothrow_swappable_with_impl<TypeT, OtherT, false> : public false_type
    {};
} // namespace detail

template <typename TypeT, typename OtherT>
struct is_nothrow_swappable_with
    : public bool_constant<detail::is_nothrow_swappable_with_impl<TypeT, OtherT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename OtherT>
constexpr PHI_INLINE_VARIABLE bool is_nothrow_swappable_with_v =
        is_nothrow_swappable_with<TypeT, OtherT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
