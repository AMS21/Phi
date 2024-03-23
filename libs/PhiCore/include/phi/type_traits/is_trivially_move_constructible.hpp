#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/add_rvalue_reference.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_trivially_constructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#define PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE()                                          \
    PHI_HAS_WORKING_IS_TRIVIALLY_CONSTRUCTIBLE()

template <typename TypeT>
struct is_trivially_move_constructible
    : public is_trivially_constructible<TypeT, typename add_rvalue_reference<TypeT>::type>
{};

template <typename TypeT>
struct is_not_trivially_move_constructible
    : public integral_constant<bool, !is_trivially_move_constructible<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_trivially_move_constructible_v =
        is_trivially_move_constructible<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_trivially_move_constructible_v =
        is_not_trivially_move_constructible<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_HPP
