#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_NON_BOOL_INTEGRAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_NON_BOOL_INTEGRAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_safe_type.hpp"
#include "phi/type_traits/is_unsafe_non_bool_integral.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool = is_safe_type<TypeT>::value>
    struct is_safe_non_bool_integral_impl
        : public is_unsafe_non_bool_integral<typename TypeT::value_type>
    {};

    template <typename TypeT>
    struct is_safe_non_bool_integral_impl<TypeT, false> : public false_type
    {};
} // namespace detail

template <typename TypeT>
struct is_safe_non_bool_integral
    : public detail::is_safe_non_bool_integral_impl<TypeT, is_safe_type<TypeT>::value>
{};

template <typename TypeT>
struct is_not_safe_non_bool_integral
    : public integral_constant<bool, !is_safe_non_bool_integral<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_safe_non_bool_integral_v =
        is_safe_non_bool_integral<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_safe_non_bool_integral_v =
        is_not_safe_non_bool_integral<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_NON_BOOL_INTEGRAL_HPP
