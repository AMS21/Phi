#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_MOVE_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_MOVE_ASSIGNABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/add_lvalue_reference.hpp"
#include "phi/type_traits/add_rvalue_reference.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_assignable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_move_assignable : public is_assignable<typename add_lvalue_reference<TypeT>::type,
                                                 typename add_rvalue_reference<TypeT>::type>
{};

template <typename TypeT>
struct is_not_move_assignable : public bool_constant<!is_move_assignable<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_move_assignable_v = is_move_assignable<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_move_assignable_v = is_not_move_assignable<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_MOVE_ASSIGNABLE_HPP
