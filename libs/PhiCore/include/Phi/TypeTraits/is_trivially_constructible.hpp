#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsTriviallyConstructible.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_TRIVIALLY_CONSTRUCTIBLE()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wignored-qualifiers")

template <typename TypeT, typename... ArgsT>
struct is_trivially_constructible
    : public bool_constant<PHI_IS_TRIVIALLY_CONSTRUCTIBLE(TypeT, ArgsT...)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_constructible_v =
        PHI_IS_TRIVIALLY_CONSTRUCTIBLE(TypeT, ArgsT...);

#    endif

PHI_GCC_SUPPRESS_WARNING_POP()

#else

template <typename TypeT, typename... ArgsT>
struct is_trivially_constructible : public false_type
{
    static_assert(always_false<TypeT>, "phi::is_trivially_constructible requires compiler support "
                                       "for intrinsic __is_trivially_constructible");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_constructible_v =
        is_trivially_constructible<TypeT, ArgsT...>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
