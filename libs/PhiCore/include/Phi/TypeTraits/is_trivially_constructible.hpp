#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE()

template <typename TypeT, typename... ArgsT>
struct is_trivially_constructible
    : public bool_constant<__is_trivially_constructible(TypeT, ArgsT...)>
{};

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_constructible_v =
        __is_trivially_constructible(TypeT, ArgsT...);

#else

template <typename TypeT, typename... ArgsT>
struct is_trivially_constructible : public false_type
{
    static_assert(always_false<TypeT>, "phi::is_trivially_constructible requires compiler support "
                                       "for intrinsic __is_trivially_constructible");
};

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_constructible_v =
        is_trivially_constructible<TypeT, ArgsT...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
