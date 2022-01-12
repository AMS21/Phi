#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_MOVE_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_MOVE_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/add_rvalue_reference.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_constructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_move_constructible
    : public is_constructible<TypeT, typename add_rvalue_reference<TypeT>::type>
{};

template <typename TypeT>
struct is_not_move_constructible : public bool_constant<!is_move_constructible<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_move_constructible_v = is_move_constructible<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_move_constructible_v =
        is_not_move_constructible<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_MOVE_CONSTRUCTIBLE_HPP
