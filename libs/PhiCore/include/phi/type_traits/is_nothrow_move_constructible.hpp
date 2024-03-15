#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/type_traits/add_rvalue_reference.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/is_nothrow_constructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE()
#    define PHI_HAS_WORKING_IS_NOTHROW_MOVE_CONSTRUCTIBLE() 1
#else
#    define PHI_HAS_WORKING_IS_NOTHROW_MOVE_CONSTRUCTIBLE() 0
#endif

template <typename TypeT>
struct is_nothrow_move_constructible
    : public is_nothrow_constructible<TypeT, add_rvalue_reference_t<TypeT>>
{};

template <typename TypeT>
struct is_not_nothrow_move_constructible
    : public bool_constant<!is_nothrow_move_constructible<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_nothrow_move_constructible_v =
        is_nothrow_move_constructible<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_nothrow_move_constructible_v =
        is_not_nothrow_move_constructible<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP
