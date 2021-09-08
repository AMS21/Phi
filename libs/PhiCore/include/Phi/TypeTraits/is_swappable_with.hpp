#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/is_not_same.hpp"
#include "Phi/TypeTraits/is_void.hpp"
#include "Phi/TypeTraits/nat.hpp"
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, typename OtherT = TypeT,
              bool is_not_void = !is_void<TypeT>::value && !is_void<OtherT>::value>
    struct is_swappable_with_impl
    {
        template <typename LhsT, typename RhsT>
        static decltype(std::swap(std::declval<LhsT>(), std::declval<RhsT>())) test_swap(int);

        template <typename, typename>
        static nat test_swap(long);

        // Extra parens are needed for the C++03 definition of decltype.
        using swap1 = decltype((test_swap<TypeT, OtherT>(0)));
        using swap2 = decltype((test_swap<OtherT, TypeT>(0)));

        static const bool value = is_not_same<swap1, nat>::value && is_not_same<swap2, nat>::value;
    };

    template <typename TypeT, typename OtherT>
    struct is_swappable_with_impl<TypeT, OtherT, false> : false_type
    {};
} // namespace detail

template <typename TypeT, typename OtherT>
struct is_swappable_with
    : public bool_constant<detail::is_swappable_with_impl<TypeT, OtherT>::value>
{};

template <typename TypeT, typename OtherT>
constexpr PHI_INLINE_VARIABLE bool is_swappable_with_v = is_swappable_with<TypeT, OtherT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP
