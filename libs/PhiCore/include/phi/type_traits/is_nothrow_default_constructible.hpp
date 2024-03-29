#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_nothrow_constructible.hpp"

#define PHI_HAS_WORKING_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE()                                         \
    PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_nothrow_default_constructible : public is_nothrow_constructible<TypeT>
{};

template <typename TypeT>
struct is_not_nothrow_default_constructible
    : public integral_constant<bool, !is_nothrow_default_constructible<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_nothrow_default_constructible_v =
        is_nothrow_default_constructible<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_nothrow_default_constructible_v =
        is_not_nothrow_default_constructible<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP
