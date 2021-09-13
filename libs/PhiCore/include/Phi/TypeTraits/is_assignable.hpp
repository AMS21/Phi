#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ASSIGNABLE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_void.hpp"
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_ASSIGNABLE()

template <typename TypeT, typename ArgT>
struct is_assignable : public bool_constant<__is_assignable(TypeT, ArgT)>
{};

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE constexpr bool is_assignable_v = __is_assignable(TypeT, ArgT);

#else

namespace detail
{
    template <typename, typename TypeT>
    struct select_2nd
    {
        using type = TypeT;
    };

    template <typename TypeT, typename ArgT>
    typename select_2nd<decltype((std::declval<TypeT>() = std::declval<ArgT>())), true_type>::type
    is_assignable_test(int);

    template <typename, typename>
    false_type is_assignable_test(...);

    template <typename TypeT, typename ArgT, bool = is_void<TypeT>::value || is_void<ArgT>::value>
    struct is_assignable_imp : public decltype((is_assignable_test<TypeT, ArgT>(0)))
    {};

    template <typename TypeT, typename ArgT>
    struct is_assignable_imp<TypeT, ArgT, true> : public false_type
    {};
} // namespace detail

template <typename TypeT, typename ArgT>
struct is_assignable : public detail::is_assignable_imp<TypeT, ArgT>
{};

template <typename TypeT, typename ArgT>
PHI_INLINE_VARIABLE constexpr bool is_assignable_v = is_assignable<TypeT, ArgT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ASSIGNABLE_HPP
