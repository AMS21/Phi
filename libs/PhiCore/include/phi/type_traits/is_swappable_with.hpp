#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/core/declval.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/is_void.hpp"
#include "phi/type_traits/nat.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, typename OtherT = TypeT,
              bool IsNotVoid = !is_void<TypeT>::value && !is_void<OtherT>::value>
    struct is_swappable_with_impl
    {
        template <typename LhsT, typename RhsT>
        static decltype(swap(declval<LhsT>(), declval<RhsT>())) test_swap(int);

        template <typename, typename>
        static nat test_swap(long);

        // Extra parens are needed for the C++03 definition of decltype.
        using swap1 = decltype((test_swap<TypeT, OtherT>(0)));
        using swap2 = decltype((test_swap<OtherT, TypeT>(0)));

        static const bool value = is_not_same<swap1, nat>::value && is_not_same<swap2, nat>::value;
    };

    template <typename TypeT, typename OtherT>
    struct is_swappable_with_impl<TypeT, OtherT, false> : public false_type
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
