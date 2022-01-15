#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/add_lvalue_reference.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_nothrow_swappable_with.hpp"
#include "phi/type_traits/is_referenceable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_nothrow_swappable
    : public conditional<is_referenceable<TypeT>::value,
                         is_nothrow_swappable_with<typename add_lvalue_reference<TypeT>::type,
                                                   typename add_lvalue_reference<TypeT>::type>,
                         false_type>::type
{};

template <typename TypeT>
struct is_not_nothrow_swappable : public bool_constant<!is_nothrow_swappable<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_nothrow_swappable_v =
        is_not_nothrow_swappable<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_HPP
