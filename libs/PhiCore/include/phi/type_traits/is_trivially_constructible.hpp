#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_trivially_constructible.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/type_traits/false_t.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_TRIVIALLY_CONSTRUCTIBLE()

#    define PHI_HAS_WORKING_IS_TRIVIALLY_CONSTRUCTIBLE() 1

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wignored-qualifiers")

template <typename TypeT, typename... ArgsT>
struct is_trivially_constructible
    : public integral_constant<bool, PHI_IS_TRIVIALLY_CONSTRUCTIBLE(TypeT, ArgsT...)>
{};

template <typename TypeT, typename... ArgsT>
struct is_not_trivially_constructible
    : public integral_constant<bool, !PHI_IS_TRIVIALLY_CONSTRUCTIBLE(TypeT, ArgsT...)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_trivially_constructible_v =
        PHI_IS_TRIVIALLY_CONSTRUCTIBLE(TypeT, ArgsT...);

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_trivially_constructible_v =
        !PHI_IS_TRIVIALLY_CONSTRUCTIBLE(TypeT, ArgsT...);

#    endif

PHI_GCC_SUPPRESS_WARNING_POP()

#else

#    define PHI_HAS_WORKING_IS_TRIVIALLY_CONSTRUCTIBLE() 0

template <typename TypeT, typename... ArgsT>
struct is_trivially_constructible : public false_type
{
    static_assert(false_t<TypeT>::value,
                  "phi::is_trivially_constructible requires compiler support "
                  "for intrinsic __is_trivially_constructible");
};

template <typename TypeT, typename... ArgsT>
struct is_not_trivially_constructible : public false_type
{
    static_assert(false_t<TypeT>::value,
                  "phi::is_not_trivially_constructible requires compiler support "
                  "for intrinsic __is_trivially_constructible");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_trivially_constructible_v =
        is_trivially_constructible<TypeT, ArgsT...>::value;

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_trivially_constructible_v =
        is_trivially_constructible<TypeT, ArgsT...>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
