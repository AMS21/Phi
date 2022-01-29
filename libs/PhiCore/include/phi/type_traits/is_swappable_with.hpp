#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/core/declval.hpp"
#include "phi/type_traits/void_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    using phi::swap;

    template <typename TypeT, typename OtherT, typename = void>
    struct is_swappable_with_helper : public false_type
    {};

    template <typename TypeT, typename OtherT>
    struct is_swappable_with_helper<
            TypeT, OtherT, void_t<decltype(swap(phi::declval<TypeT>(), phi::declval<OtherT>()))>>
        : public true_type
    {};

    template <typename TypeT, typename OtherT>
    struct is_swappable_with_impl
        : public bool_constant<is_swappable_with_helper<TypeT, OtherT>::value &&
                               is_swappable_with_helper<OtherT, TypeT>::value>
    {};
} // namespace detail

template <typename TypeT, typename OtherT>
struct is_swappable_with
    : public bool_constant<detail::is_swappable_with_impl<TypeT, OtherT>::value>
{};

template <typename TypeT, typename OtherT>
struct is_not_swappable_with : public bool_constant<!is_swappable_with<TypeT, OtherT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename OtherT>
PHI_INLINE_VARIABLE constexpr bool is_swappable_with_v = is_swappable_with<TypeT, OtherT>::value;

template <typename TypeT, typename OtherT>
PHI_INLINE_VARIABLE constexpr bool is_not_swappable_with_v =
        is_not_swappable_with<TypeT, OtherT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP
